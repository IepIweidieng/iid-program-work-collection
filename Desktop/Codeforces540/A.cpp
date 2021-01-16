#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie((ostream*)NULL);

    int q;
    cin >> q;
    while (q--) {
        unsigned long long int n, a, b;
        cin >> n >> a >> b;

        if (b < 2*a) {
            cout << (n%2) * a + (n/2) * b << '\n';
        }
        else {
            cout << n*a << '\n';
        }
    }

    return 0;
}
