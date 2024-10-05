// 모든 맵의 격자를 보면 안되고 각 세포를 봐야 시간 초과가 안난다.
#include <stdio.h>
#include <vector>
#define S 151
#include <queue>
using namespace std;

typedef long long ll;

struct Cell
{
  ll life = 0, time = 0, y, x;
};

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

ll solve()
{
  ll n, m, k;
  scanf("%lld%lld%lld", &n, &m, &k);
  vector<Cell> cells;
  ll map[350][350] = {};

  for (ll i = 1; i <= n; i++)
  {
    for (ll j = 1; j <= m; j++)
    {
      ll x;
      scanf("%lld", &x);
      cells.push_back({x, x, i + 150, j + 150});
      map[i + 150][j + 150] = x;
    }
  }

  priority_queue<pair<ll, ll>> activate;

  for (ll t = 1; t <= k; t++)
  {

    for (ll i = cells.size() - 1; i >= 0; i--)
    {
      cells[i].time--;

      if (cells[i].time == 0)
      {
        activate.push({cells[i].life, i});
      }
    }

    while (!activate.empty())
    {
      auto it = activate.top();
      activate.pop();
      auto v = it.second;

      for (ll dir = 0; dir < 4; dir++)
      {
        ll ty = cells[v].y + dy[dir];
        ll tx = cells[v].x + dx[dir];
        if (!(0 <= ty && ty < 350 && 0 <= tx && tx < 350 && map[ty][tx] == 0))
          continue;
        map[ty][tx] = cells[v].life;
        cells.push_back({cells[v].life, cells[v].life + 1, ty, tx});
      }
    }
  }
  ll ans=0;
  for(auto cell:cells){
    if(cell.time>-cell.life && cell.time<=cell.life)
      ans++;
  }
  return ans;
}
int main()
{
  ll t;
  scanf("%lld", &t);
  for (ll i = 1; i <= t; i++)
  {
    printf("#%lld %lld\n", i, solve());
  }
}