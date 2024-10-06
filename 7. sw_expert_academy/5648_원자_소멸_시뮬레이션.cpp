// 최대한 깔끔하고 수학적으로 생각해야함.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Atom
{
    ll x, y;
    ll vx, vy;
    ll energy;
};

struct Collision
{
    ll t;
    ll p, q;
    bool operator<(Collision r)
    {
        return t < r.t;
    }
};

bool collision(vector<Atom> &atoms, ll p, ll q, vector<Collision> &cols)
{
    Atom a = atoms[p];
    Atom b = atoms[q];
    if (b.vx - a.vx == 0)
    {
        if (a.x - b.x == 0)
        {
               
            if (b.vy - a.vy == 0 && a.y - b.y != 0)
                return false;
            else
            {
                ll t = 2 * (a.y - b.y) / (b.vy - a.vy);
              //  printf("y: %lld %lld %lld %lld\n",a.y,b.y,a.vy,b.vy);
                if(t<=0){
                    return false;
                }
                cols.push_back({t, p, q});
                return true;
            }
        }
        else
            return false;
    }
    else
    {
        ll t = 2 * (a.x - b.x) / (b.vx - a.vx);
        if (2 * (a.y - b.y) != (b.vy - a.vy) * t || t<=0)
            return false;
        else
        {
            
            cols.push_back({t, p, q});
            return true;
        }
    }
}

ll solve()
{
    ll n;
    cin >> n;
    vector<Atom> atoms(n + 1);
    for (ll i = 1; i <= n; i++)
    {
        ll dir;
        cin >> atoms[i].x >> atoms[i].y >> dir >> atoms[i].energy;
        if (dir == 0)
            atoms[i].vx = 0, atoms[i].vy = 1;
        else if (dir == 1)
            atoms[i].vx = 0, atoms[i].vy = -1;
        else if (dir == 2)
            atoms[i].vx = -1, atoms[i].vy = 0;
        else if (dir == 3)
            atoms[i].vx = 1, atoms[i].vy = 0;
    }

    ll ans = 0;
    vector<Collision> collisions;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = i + 1; j <= n; j++)
        {
            bool res = collision(atoms, i, j, collisions);
        }
    }
    sort(collisions.begin(),collisions.end());

    vector<ll> die(n+1);
    for(ll i=0;i<collisions.size();i++){
        ll p=collisions[i].p;
        ll q=collisions[i].q;
        ll t=collisions[i].t;
        if((die[p]==0 || die[p]==t) && (die[q]==0 || die[q]==t)){
            if(die[p]==0) ans+=atoms[p].energy;
            if(die[q]==0) ans+=atoms[q].energy;
            die[p]=t;
            die[q]=t;
        }
    }
    return ans;
}

int main()
{
    ll T;
    cin >> T;
    for (ll i = 1; i <= T; i++)
    {
        cout << "#" << i << " " << solve() << endl;
    }
    return 0;
}