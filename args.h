#ifndef ARGS_H
#define ARGS_H

struct Arguments {
    int field;
    int length;
    bool only_start_at_one;
    bool print_sequence;
    bool print_counts;
    bool print_m_values;
    bool print_b_values;
    bool stop_after_first;
    bool time;
};

extern Arguments args;

void parse_args(int argc, char **argv);

#endif
