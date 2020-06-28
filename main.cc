#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include "functions.hh"

void run_benchmark(int *data, int length, int chunk_size, int iterations)
{
    int chunk_amount = (int)ceil((double)length / (double)chunk_size);
    for (int i = 0; i < chunk_amount; i++) {
        int start = i * chunk_size;
        int end = std::min((i + 1) * chunk_size, length);
        int chunk_length = end - start;

        for (int i = 0; i < iterations; i++) {
            add_to_all(data + start, chunk_length, 1);
        }
    }
}

int main(int argc, char const *argv[])
{
    int amount = 1'000'000;
    std::vector<int> values(amount, 0);
    /* Warm up memory. */
    add_to_all(values.data(), amount, 1);
    add_to_all(values.data(), amount, -1);

    int add_iterations = 10;
    int benchmark_iterations = 10;

    for (int i = 0; i < benchmark_iterations; i++) {
        std::chrono::steady_clock::time_point start_time =
            std::chrono::steady_clock::now();

        run_benchmark(values.data(), values.size(), 1024, add_iterations);

        std::chrono::steady_clock::time_point end_time =
            std::chrono::steady_clock::now();
        std::chrono::nanoseconds duration = (end_time - start_time);
        std::cout << "Time: " << duration.count() << " ns\n";
    }

    // for (int &value : values) {
    //     if (value != add_iterations * benchmark_iterations) {
    //         std::cout << "Error, got value " << value << "\n";
    //     }
    // }
    std::cout << "Done.\n";

    return 0;
}
