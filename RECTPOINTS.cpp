#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
const ll MAXN = 2e5 + 5;
ll n , w , h;
struct Point {
    ll x, y;
};
vector<Point> a;
vector<ll> coord;

ll tree[4 * MAXN];
ll lazy[4 * MAXN];
void update(ll id, ll l, ll r, ll u, ll v, ll val) {
    if (v < l || r < u) return;
    else if (u <= l && r <= v){
        tree[id] += val;
        lazy[id] += val;
        return;
    }

    ll mid = (l + r) >> 1;

    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);

    tree[id] = lazy[id] + max(tree[id * 2], tree[id * 2 + 1]);
}
void inp(){
    cin >> n >> w >> h;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        coord.push_back(a[i].y - h);
        coord.push_back(a[i].y);
    }
    sort(a.begin(), a.end(), [](Point A, Point B) {return A.x < B.x;});

    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    return;
}
void solve() {
    ll left = 0;
    ll ans = 0;
    for (int right = 0; right < n; right++) {
        ll X = a[right].x;
        ll y = a[right].y;

        ll L = lower_bound(coord.begin(), coord.end(), y - h) - coord.begin();
        ll R = lower_bound(coord.begin(), coord.end(), y) - coord.begin();

        update(1, 0, coord.size() - 1, L, R, 1);

        while (left <= right && a[left].x < X - w) {
            y = a[left].y;

            L = lower_bound(coord.begin(), coord.end(), y - h) - coord.begin();
            R = lower_bound(coord.begin(), coord.end(), y) - coord.begin();

            update(1, 0, coord.size() - 1, L, R, -1);
            left++;
        }

        ans = max(ans, tree[1]);
    }
    cout << ans << "\n";
    return;
}

int main() {
    FASTIO;
    inp();
    solve();
    return 0;
}
