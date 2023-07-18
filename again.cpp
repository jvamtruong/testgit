#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n + 3];
        int f[n + 3];
        f[n] = -1;
        for (int i = 0 ; i < n; i++) cin >> a[i];
        for (int i = n - 1 ; i >= 0; i--) f[i] = max(a[i], f[i + 1]); // f[i]: max(a[i : n - 1])
        int ans = 0;
        for (int i = 0 ; i < n; i++) {
            int l = i + 1;
            int r = n - 1;
            while (l <= r) {
                int m = l + r >> 1;
                if (f[m] >= a[i]) {
                    ans = max(ans, m - i);
                    l = m + 1;
                }
                else r = m - 1;
            }
        }
        cout << ans << endl;
    }
}