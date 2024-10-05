//시간을 줄이기 위한 아이디어
//1. queue는 느리다.
//2. 가로로 인접한 셀은 똑같은 작업을 가로에 대해 다시 탐색할 필요가 없다.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};
ll oo = 987654321;

// Maximum grid size
const int MAX_N = 102;

// Global variables
ll a[MAX_N][MAX_N]; // `a` as a 2D array
pair<ll, ll> wom[11][2]; // Assuming that each value between 6 and 10 has exactly 2 positions
deque<ll> Q;
ll d[4][MAX_N][MAX_N]; // `d` as a 3D array

struct Point{
  ll dir,y,x,val;
};

Point determine(ll n, ll dir, ll y, ll x, ll val) {
    if (1 <= y && y <= n && 1 <= x && x <= n) {
        ll ty, tx, tdir;
        bool col = false;
        if (a[y][x] == 0) {
            ty = y + dy[dir];
            tx = x + dx[dir];
            tdir = dir;
        } else if (a[y][x] == 1) {
            if (dir == 0 || dir == 3)
                tdir = (dir + 2) % 4;
            else if (dir == 2)
                tdir = 3;
            else if (dir == 1)
                tdir = 0;

            ty = y + dy[tdir];
            tx = x + dx[tdir];
            col = true;
        } else if (a[y][x] == 2) {
            if (dir == 0 || dir == 1)
                tdir = (dir + 2) % 4;
            else if (dir == 2)
                tdir = 1;
            else if (dir == 3)
                tdir = 0;

            ty = y + dy[tdir];
            tx = x + dx[tdir];
            col = true;
        } else if (a[y][x] == 3) {
            if (dir == 1 || dir == 2)
                tdir = (dir + 2) % 4;
            else if (dir == 0)
                tdir = 1;
            else if (dir == 3)
                tdir = 2;

            ty = y + dy[tdir];
            tx = x + dx[tdir];
            col = true;
        } else if (a[y][x] == 4) {
            if (dir == 2 || dir == 3)
                tdir = (dir + 2) % 4;
            else if (dir == 1)
                tdir = 2;
            else if (dir == 0)
                tdir = 3;

            ty = y + dy[tdir];
            tx = x + dx[tdir];
            col = true;
        } else if (a[y][x] == 5) {
            tdir = (dir + 2) % 4;

            ty = y + dy[tdir];
            tx = x + dx[tdir];
            col = true;
        } else if (a[y][x] >= 6 && a[y][x] <= 10) {
            ll yy, xx;
            if (wom[a[y][x]][0].first == y && wom[a[y][x]][0].second == x) {
                yy = wom[a[y][x]][1].first;
                xx = wom[a[y][x]][1].second;
            } else {
                yy = wom[a[y][x]][0].first;
                xx = wom[a[y][x]][0].second;
            }
            ty = yy + dy[dir];
            tx = xx + dx[dir];
            tdir = dir;

        } else {
          // blackhole
            return {-1,ty,tx,val};
        }

        return {tdir,ty,tx,val + (col ? 1 : 0)};

    } else {
        ll ty = y + dy[(dir + 2) % 4];
        ll tx = x + dx[(dir + 2) % 4];
        ll tdir = (dir + 2) % 4;
        ll tval = val + 1;
        return {tdir,ty,tx,tval};
    }
}

ll solve() {
    ll n;
    cin >> n;

    // Clear global structures before each test case
    memset(a, 0, sizeof(a));
    memset(d, oo, sizeof(d));
    for (int i = 6; i <= 10; ++i)
        wom[i][0] = wom[i][1] = {0, 0};
    Q.clear();

    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (a[i][j] >= 6 && a[i][j] <= 10) {
                if (wom[a[i][j]][0].first == 0)
                    wom[a[i][j]][0] = {i, j};
                else
                    wom[a[i][j]][1] = {i, j};
            }
        }

    ll ans = 0;
    ll prevc=-10;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (a[i][j] != 0) continue;
            

            for (ll k = 0; k < 4; k++) {
                if(prevc+1==j && (k==0 || k==2)) continue;
                ll ty = i + dy[k];
                ll tx = j + dx[k];
                ll tdir=k;
                ll val=0;

                while(true){
                  Point point=determine(n,tdir,ty,tx,val);
                  if(point.dir==-1){
                    ans=max(ans,point.val);
                    break;
                  }
                  if(point.y==i && point.x==j){
                    ans=max(ans,point.val);
                    break;
                  }
                  ty=point.y;
                  tx=point.x;
                  tdir=point.dir;
                  val=point.val;
                }
            }
            prevc=j;
        }
    }

    return ans;
}

int main() {
    //freopen("input.txt","r",stdin);
    ll T;
    cin >> T;
    for (ll i = 1; i <= T; i++)
        cout << "#" << i << " " << solve() << endl;
    return 0;
}
