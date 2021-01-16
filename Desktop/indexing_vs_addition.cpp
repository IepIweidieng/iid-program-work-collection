#include <chrono>
#include <iostream>
#include <random>

static short succ_array[1024];
static inline short succ_func(short k)  { return 1024 - k; }

static short ans_array[1024];

int main()
{
    for (int k = 0; k < 1024; ++k) {
        succ_array[k] = 1024 - k;
    }

    std::random_device rdev;
    std::default_random_engine reng (rdev());
    std::uniform_int_distribution<int> uni_dist(0, 1023);

    using Sys_clk = std::chrono::system_clock;

    double total_sec_expr = 0.0;
    double total_sec_index = 0.0;
    double total_sec_func = 0.0;

    for (int k = 0; k < 65536; ++k) {
        std::fill(ans_array, (&ans_array)[1], '\0');

        auto start_expr = Sys_clk::now();
        for (int k = 0; k < 1024; ++k) {
            short ind = uni_dist(reng);
            short ans = 1024 - ind;

            ans_array[k] = ans;
        }
        auto end_expr = Sys_clk::now();

        std::fill(ans_array, (&ans_array)[1], '\0');

        auto start_index = Sys_clk::now();
        for (int k = 0; k < 1024; ++k) {
            short ind = uni_dist(reng);
            short ans = succ_array[ind];

            ans_array[k] = ans;
        }
        auto end_index = Sys_clk::now();

        std::fill(ans_array, (&ans_array)[1], '\0');

        auto start_func = Sys_clk::now();
        for (int k = 0; k < 1024; ++k) {
            short ind = uni_dist(reng);
            short ans = succ_func(ind);

            ans_array[k] = ans;
        }
        auto end_func = Sys_clk::now();

        using Dur = std::chrono::duration<double>;

        Dur sec_expr = end_expr - start_expr;
        Dur sec_index = end_index - start_index;
        Dur sec_func = end_func - start_func;

        total_sec_expr += sec_expr.count();
        total_sec_index += sec_index.count();
        total_sec_func += sec_func.count();
    }

    std::cout << "Expr: " << total_sec_expr << "s\n"
      "Index: " << total_sec_index << "s\n"
      "Func: " << total_sec_func << "s\n";

    return 0;
}
