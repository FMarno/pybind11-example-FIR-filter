#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <stdexcept>
#include <numeric>

/// A FIR filter class that use double percision floats
class FIR_filter {
	private:
		const std::vector<double> coefficients;
		std::vector<double> taps;
		size_t next_place = 0;
	public:
		/// Create a FIR filter with the given coefficients
		/// throws std::invalid_argument if coeffs is empty
		FIR_filter(const std::vector<double> coeffs) : coefficients(std::move(coeffs)), taps(coeffs.size(), 0)
		{
			if (coefficients.size() == 0){
				throw new std::invalid_argument("there must be at least 1 coefficient");
			}
		}

		/// send a value into the FIR filter
		/// return the next output of the filter
		double do_filter(double next_value)
		{
			taps[next_place] = next_value;
			auto sum = std::transform_reduce(std::begin(coefficients), std::begin(coefficients) + next_place + 0, std::rbegin(taps) + (coefficients.size() - 1 - next_place), double{0});
			sum += std::transform_reduce(std::begin(coefficients) + next_place + 0, std::end(coefficients), std::rbegin(taps), double{0});
			next_place = (next_place + 1) % coefficients.size();
			return sum;
		}
};

/// Feed an array of input values into the filter, one at a time.
/// This is to save constantly swapping between python and C++.
/// Note that this method is separate to the FIR_filter class to respect the
/// 'real-time' nature of the assignment.
static std::vector<double> feed_fir(FIR_filter& filter, std::vector<double> input){
	std::vector<double> output;
	output.reserve(input.size());
	for (auto&& x : input){
		output.push_back(filter.do_filter(x));
	}
	return output;
}

namespace py = pybind11;

// macro needed to produce the python module.
PYBIND11_MODULE(cpp_fir, m) {
	m.doc() = R"pbdoc(
        Pybind11 FIR filter
        -----------------------
        .. currentmodule:: cpp_fir
        .. autosummary::
           :toctree: _generate
		   float_fir
		   feed_fir
    )pbdoc";

	py::class_<FIR_filter>(m, "float_fir")
	.def(py::init<const std::vector<double>>())
	.def("do_filter", &FIR_filter::do_filter);

	m.def("feed_fir", &feed_fir, R"pbdoc(
        feed a list of values to the FIR, one at a time.
        This slightly pushes the spec but is more efficient.
    )pbdoc");

#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}
