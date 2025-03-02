#include <iostream>
#include <chrono>
#include "args.h"
#include "field.h"
#include "search.h"

int main(int argc, char **argv)
{
    parse_args(argc, argv);
    MOD = args.field;

    auto start = std::chrono::high_resolution_clock::now();

    search(args.length);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (args.time) {
        std::cout << "Time: " << duration.count() << " seconds." << std::endl;
    }

    if (args.print_counts) {
        std::cout << "Number of problematic sequences of each length:" << std::endl;
        for (int i = 1; i <= args.length; i++)
            std::cout << i << ": " << cnt[args.length - i] << std::endl;
    }

    if (args.print_m_values) {
        std::cout << "Values of m for each length:" << std::endl;
        for (int i = 1; i < args.length; i++)
            std::cout << i << ": " << M[args.length - i] << std::endl;
    }

    return 0;
}
