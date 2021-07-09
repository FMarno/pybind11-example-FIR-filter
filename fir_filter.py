"""Python implementation of an FIR filter.
When run as main, unit tests will be run for the python and C++ filter."""

try:
    # MSVC version
    import _build.Release.cpp_fir as cpp_fir
    # other
    # import _build.cpp_fir as cpp_fir
except:
    import sys
    sys.stderr.write(
        "failed to import C++ filter, using python implementation.\n")
    sys.stderr.write(
        "See readme for instruction for building the C++ filter.\n")

from typing import List
from timeit import timeit
import numpy as np

def filter_list(filter, data_points):
    """Run all the data points through the filter"""
    filtered_data = np.zeros(len(data_points))
    for idx, data_point in enumerate(data_points):
        filtered_data[idx] = filter.do_filter(data_point)
    return filtered_data

def performance_comparison():
    """Performance comparison between the Python and C++ implementations"""
    num_of_taps = 500
    num_of_runs = 1000
    try:
        cpp_moving_avg = cpp_fir.float_fir([1/num_of_taps]*num_of_taps)
    except:
        print("C++ filter not imported, can't compare performance")
        return
    print("performance comparison with", num_of_taps,
          "taps, run", num_of_runs, "times.")
    print("pass to cpp one at a time:", timeit(
        lambda: filter_list(cpp_moving_avg, list(range(100))), number=num_of_runs))
    cpp_moving_avg = cpp_fir.float_fir([1/num_of_taps]*num_of_taps)
    print("pass full array to cpp:", timeit(
        lambda: cpp_fir.feed_fir(cpp_moving_avg, list(range(100))), number=num_of_runs))


if __name__ == "__main__":
    performance_comparison()
    print("demo")
    print("average of the last 5 values")
    num_of_taps = 5
    cpp_moving_avg = cpp_fir.float_fir([1/num_of_taps]*num_of_taps)
    for i in range(10):
        print(cpp_moving_avg.do_filter(i))

