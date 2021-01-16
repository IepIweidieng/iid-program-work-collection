#include <iostream>
#include <list>
#include <regex>
#include <set>
#include <string>
#include <vector>
#include <utility>

#ifdef __GNUG__
  #include <cxxabi.h>
#endif

std::string getSimpleTypeName(const std::string& name)
{
    using namespace std;
    return regex_replace(regex_replace(regex_replace(
              name, regex{R"(<.*>)"}, ""),
            regex{R"((?:\w+::)+)"}, ""),
          regex{R"(\b +\B)"}, "");
}

std::string demangle(const char* id)
#ifdef __GNUG__
{
    int status;
    char* name = abi::__cxa_demangle(id, 0, 0, &status);
    std::string res = name;
    free(name);
    return getSimpleTypeName(res);
}
#else
  { return getSimpleTypeName(id); }
#endif

template <class T, typename std::enable_if<std::is_scalar<T>::value, int>::type = 0>
 std::ostream& nested_print(const T& obj)
  { return std::cout << obj; }

template <class T, typename std::enable_if<!std::is_scalar<T>::value, int>::type = 0>
  std::ostream& nested_print(const T& obj)
{
    bool printed = false;
    std::cout << demangle(typeid(obj).name()) << '{';
    for (const auto& k: obj) {
        if (printed) { std::cout << ", "; }
        nested_print(k);
        printed = true;
    }
    return std::cout << '}';
}

int main(...)
{
    using namespace std;
    set<vector<list<int>>> vec[2] = {{
        {{3}, {1, 4}, {1, 5, 9},},
        {{2, 6}, {5, 3}, {5, 8, 9},},
    }, {
        {{2, 7}, {1, 8}, {2, 8},},
    }};
    nested_print(vec) << '\n';
}
