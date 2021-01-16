#include <ruby.h>

int run_ruby(const char *code)
{
    static int inited = 0;
    if (!inited) {
        ruby_init();
        ruby_init_loadpath();
        const char* options[] = {"", "-enil", 0};
        ruby_exec_node(ruby_options(2, (char **)options));
        inited = 1;
    }
    ruby_exec_node(rb_load_file("empty.rb"));

    int result;
    rb_eval_string_protect(code, &result);
    if (result) {
        VALUE e = rb_errinfo();
        rb_set_errinfo(Qnil);

        if (RTEST(e)) {
            rb_warn("%"PRIsVALUE, e);
        }
        return 1;
    }
    return 0;
}

int main(void)
{
    run_ruby("puts 'Hello, world!'; X = 4\n");
    run_ruby("puts X");
    run_ruby("puts 'Hello, world, too!'\n");
}
