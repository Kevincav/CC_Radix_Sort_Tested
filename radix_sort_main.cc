#include <algorithm>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

#include <glog/logging.h>
#include <google/gflags.h>

#include "radix_sort.h"

DEFINE_int32(number_of_elements, 1000000, "Run the radix_sort with how many elements in the array?");
// TODO: Add functionality for this.
// DEFINE_bool(parallel_comparisons, false, "Run std::sort and radix_sort in parallel. time_std_sort should be true as well.");
DEFINE_bool(time_std_sort, false, "Time std::sort along side.");

typedef double kDataType;

std::vector<kDataType> GenerateRandomVector() {
	std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<kDataType> uniform_dist(std::numeric_limits<kDataType>::min(), std::numeric_limits<kDataType>::max());
	std::vector<kDataType> output(FLAGS_number_of_elements);
	for (int i = 0; i < output.size(); ++i) {
		output[i] = uniform_dist(engine);
	}
	return output;
}

int main (int argc, char* argv[]) {
	::google::InitGoogleLogging(argv[0]);
    ::google::ParseCommandLineFlags(&argc, &argv, true);

    using namespace std::chrono;

    // Set up test parameters.
    RadixSort radix_sort;
    std::vector<kDataType> test_vector = GenerateRandomVector();
    std::vector<kDataType> compare_vector;
    if (FLAGS_time_std_sort) {
    	compare_vector.insert(compare_vector.begin(), test_vector.begin(), test_vector.end());
    }

	// Time and run tests.
  	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	radix_sort.Sort(test_vector);
  	high_resolution_clock::time_point t2 = high_resolution_clock::now();
  	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	LOG(INFO) << "It took the radix_sort " << time_span.count() << " seconds to sort " << FLAGS_number_of_elements << " elements.\n";

	// Only runs if comparing timings to std::sort.
	if (FLAGS_time_std_sort) {
  		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		std::sort(compare_vector.begin(), compare_vector.end());
  		high_resolution_clock::time_point t2 = high_resolution_clock::now();
  		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		LOG(INFO) << "It took the std::sort " << time_span.count() << " seconds to sort " << FLAGS_number_of_elements << " elements.\n";
	}

	return 0;
}