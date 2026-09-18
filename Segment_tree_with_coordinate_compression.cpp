#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
const ll MAXN = 2e5 + 5, INF=1e9;
ll n , m , a[100005];
vector <ll> vals;
struct query{
    ll type , u , v;
};
query q[100005];
void inp(){
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        vals.push_back(a[i]);
    }
    cin >> m;
    for(int i = 1 ; i <= m ; i++){
        cin >> q[i].type;
        if(q[i].type == 1){
            cin >> q[i].u >> q[i].v;
            vals.push_back(q[i].v);
        }
        else{
            cin >> q[i].v;
            vals.push_back(q[i].v);
        }
    }
}
ll get_idx(ll val){
    return lower_bound(vals.begin() , vals.end() , val) - vals.begin() + 1;
}
ll st[4*MAXN];
void update(ll id , ll l , ll r , ll idx , ll delta){
    if(l > idx || r < idx)return;
    else if(l == r){
        st[id] += delta;
        return;
    }

    ll mid = (l + r) >> 1;
    update(2*id , l , mid , idx , delta);
    update(2*id + 1 , mid + 1 , r , idx , delta);

    st[id] = st[2*id] + st[2*id + 1];
    return;
}
ll get(ll id , ll l , ll r , ll u_idx , ll v_idx){
    if(l > v_idx || r < u_idx)return 0;
    else if(l >= u_idx && r <= v_idx)return st[id];

    ll mid = (l + r) >> 1;

    return get(2*id , l , mid , u_idx , v_idx) + get(2*id + 1 , mid + 1 , r , u_idx , v_idx);
}
void solve(){
    sort(vals.begin() , vals.end());
    vals.erase(unique(vals.begin() , vals.end()) , vals.end());
    ll k = vals.size();
    for(int i = 1 ; i <= n ; i++){
        ll idx = get_idx(a[i]);
        update(1 , 1 , k , idx , 1);
    }
    for(int i = 1 ; i <= m ; i++){
        if(q[i].type == 1){
            ll u = q[i].u , val = q[i].v;
            update(1 , 1 , k , get_idx(a[u]) , -1);
            a[u] = val;
            update(1 , 1 , k , get_idx(val) , 1);
        }
        else{
            ll val = q[i].v;
            ll idx = get_idx(val);
            if(idx != 1)cout << get(1 , 1 , k , 1 , idx - 1) << "\n";
            else cout << 0 << "\n";
        }
    }
}
int32_t main() {
    FASTIO;
    inp();
    solve();
    return 0;
}
