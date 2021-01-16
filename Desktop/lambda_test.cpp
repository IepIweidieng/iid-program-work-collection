#include <iostream>
#include <string>

int main()
{
    using namespace std;
    using namespace std::literals::string_literals;
    cout << boolalpha << ("Pepsi"s > "Cola"s) << '\n';
}
