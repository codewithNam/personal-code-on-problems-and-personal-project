#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
const ll MAXN = 1e5 + 5;
ll n , k , x;
ll a[MAXN];

void inp() {
    cin >> n >> k >> x;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void solve() {
    ll ans = 0;
    for (ll mask = 0; mask < (1 << 9); mask++) {
        if (__builtin_popcount(mask) != k)continue;

        ll left = 1;
        ll cost = 0;

        for (ll right = 1; right <= n; right++) {
            if ((mask & (1 << (a[right] - 1))) == 0)cost++;

            while (cost > x) {
                if ((mask & (1 << (a[left] - 1))) == 0)cost--;
                left++;
            }
            ans = max(ans, right - left + 1);
        }
    }
    cout << ans << '\n';
}

int main() {
    FASTIO;
    inp();
    solve();
    return 0;
}
