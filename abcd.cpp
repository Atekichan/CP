               //  ॐ
#include <bits/stdc++.h>
 
using namespace std;

#define ll long long
#define ld long double
#define endl "\n"
typedef vector<ll> vll;
using vi = vector<int>;
#define pb              push_back 
#define Sort(a)         sort(a.begin(),a.end())
const ll N = 1e5+10;
const ll f =  998244353;
const int maxn = 60;

vi g[N];
vi ch(N,0);
vector<vi> adj(N), adj_rev(N);
vector<bool> used(N,false);
vi order, component, leaf;
vi vis(N,0);
vector<pair<int,vi>> seg;

void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);

    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}

void dfs(int v){
    vis[v]=1;

    for(auto x: g[v])
        if(!vis[x])
            dfs(x);
    if(adj[v].size()==0)
        leaf.pb(v);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin>>n;
    for (int i = 1; i <= n; ++i) {
        cin>>ch[i];
        adj[ch[i]].pb(i);
        adj_rev[i].pb(ch[i]);
        g[i].pb(ch[i]);g[ch[i]].pb(i);
    }

    used.assign(n+1, false);

    for (int i = 1; i <= n; i++)
        if (!used[i])
            dfs1(i);

    used.assign(N, false);
    reverse(order.begin(), order.end());

    ll ct=0,flag=0;
    for (auto v : order)
        if (!used[v]) {
            dfs2 (v);
            if(component.size()>1){
                dfs(v);
                if(leaf.size()==0){
                    leaf.pb(v);
                    flag=1;
                }
                seg.pb({v,leaf});
                ct+=(leaf.size());
            }
            component.clear();
            leaf.clear();
        }
    int sz=seg.size();
    if(sz==1&&flag){
        cout<<"0";
    }else{
        cout<<ct<<"\n";
        for(auto x: seg[sz-1].second)
            cout<<seg[0].first<<" "<<x<<"\n";
        for(int i = 0; i < sz-1; i++){
           for(auto x: seg[i].second)
               cout<<seg[i+1].first<<" "<<x<<"\n";
        }
    }
    
    return 0;
}


