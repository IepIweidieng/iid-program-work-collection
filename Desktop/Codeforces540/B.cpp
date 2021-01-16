#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    short *a = new short[n];

    int sum[2] = {};
    for (int k = 0; k < n; ++k) {
        cin >> a[k];
        sum[k%2] += a[k];
    }

    int ans = 0;
    for (int k = 0; k < n; ++k) {
        sum[k%2] -= a[k];
        if (k) { sum[k%2] += a[k-1]; }
        if (sum[0] == sum[1]) { ++ans; }
    }
    delete[] a;

    cout << ans << '\n';

    return 0;
}
