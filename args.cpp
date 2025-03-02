#include <string>
#include <iostream>
#include "args.h"

Arguments args;

int parse_int(int argc, char **argv, int i)
{
    if (i >= argc) {
        std::cerr << "ERROR: Expected integer argument." << std::endl;
        exit(1);
    }

    int result;

    try {
        result = std::stoi(argv[i]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "ERROR: Cannot convert argument to integer." << std::endl;
        exit(1);
    } catch (const std::out_of_range& e) {
        std::cerr << "ERROR: Integer argument out of range." << std::endl;
        exit(1);
    }

    return result;
}

bool is_prime(int x)
{
    for (int d = 2; d * d <= x; d++)
        if (x % d == 0)
            return false;
    return x >= 2;
}

void parse_args(int argc, char **argv)
{
    // defaults
    args.field = 5;
    args.length = 10;
    args.only_start_at_one = false;
    args.print_sequence = false;
    args.print_counts = false;
    args.print_m_values = false;
    args.stop_after_first = false;
    args.time = false;
    for (int i = 1; i < argc; ) {
        std::string arg = argv[i++];
        if (arg == "-f" || arg == "--field") {
            args.field = parse_int(argc, argv, i++);
            if (!is_prime(args.field)) {
                std::cerr << "ERROR: Field order must be prime." << std::endl;
                exit(1);
            }
        } else if (arg == "-l" || arg == "--length") {
            args.length = parse_int(argc, argv, i++);
            if (args.length >= 200) {
                std::cerr << "ERROR: Length too long." << std::endl;
                exit(1);
            }
        } else if (arg == "-1" || arg == "--one") {
            args.only_start_at_one = true;
        } else if (arg == "-p" || arg == "--print") {
            args.print_sequence = true;
        } else if (arg == "-c" || arg == "--counts") {
            args.print_counts = true;
        } else if (arg == "-m" || arg == "--mvals") {
            args.print_m_values = true;
        } else if (arg == "-s" || arg == "--stop") {
            args.stop_after_first = true;
        } else if (arg == "-t" || arg == "--time") {
            args.time = true;
        } else {
            std::cerr << "ERROR: Invalid argument." << std::endl;
            std::cerr << "Valid command line args:" << std::endl;
            std::cerr << "  -f / --field [p]" << std::endl;
            std::cerr << "  -l / --length [n]" << std::endl;
            std::cerr << "  -1 / --one" << std::endl;
            std::cerr << "  -p / --print" << std::endl;
            std::cerr << "  -c / --counts" << std::endl;
            std::cerr << "  -m / --mvals" << std::endl;
            std::cerr << "  -s / --stop" << std::endl;
            std::cerr << "  -t / --time" << std::endl;
            exit(1);
        }
    }
}
