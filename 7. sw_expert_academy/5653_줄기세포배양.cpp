#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>
#include <utility>
typedef long long ll;
using namespace std;

struct Cell
{
  ll time;
  ll life;
};

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

map<pair<ll, ll>, Cell> cell;
map<pair<ll, ll>, ll> create;
ll solve()
{
  ll n, m, endOfTime;
  scanf("%lld%lld%lld", &n, &m, &endOfTime);
  vector<vector<ll>> a(n + 1, vector<ll>(m + 1));
  cell.clear();
  create.clear();

  queue<ll> A;
  priority_queue<pair<long long, pair<long long, long long>>> B;

  for (ll i = 1; i <= n; i++)
    for (ll j = 1; j <= m; j++)
    {
      scanf("%lld", &a[i][j]);
      if (a[i][j] != 0)
      {
        cell[make_pair(i, j)] = {a[i][j], a[i][j]};
        create[{i, j}] = 0;
        A.push(i);
        A.push(j);
      }
    }

  for (ll currentTime = 1; currentTime <= endOfTime; currentTime++)
  {

    for (ll q = A.size() / 2; q >= 1; q--)
    {
      ll y = A.front();
      A.pop();
      ll x = A.front();
      A.pop();
      auto &ce = cell[{y, x}];
      if (ce.time-- == 0)
      {
        B.push({ce.life, {y, x}});
      }
      else
      {
        A.push(y);
        A.push(x);
      }
    }

    //printf("%lld\n", currentTime);
    while (!B.empty())
    {
      ll y = B.top().second.first;
      ll x = B.top().second.second;
      B.pop();
     // printf("->%lld %lld\n", y, x);
      auto ce = cell[{y, x}];
      for (ll k = 0; k < 4; k++)
      {
        ll ty = y + dy[k];
        ll tx = x + dx[k];
        if (cell.find({ty, tx}) == cell.end())
        {
          cell[{ty, tx}] = {ce.life, ce.life};
          create[{ty, tx}] = currentTime;
         // printf("%lld %lld\n", ty, tx);
          A.push(ty);
          A.push(tx);
        }
      }
    }

    if (currentTime == endOfTime)
    {
      ll ans = 0;
      for (auto it : cell)
      {
        ll life = it.second.life;
        ll time = it.second.time;
        ll record = create[{it.first.first, it.first.second}];
        // printf("%lld %lld %lld\n",it.first.first,it.first.second, record);
        if (currentTime >= record && record + 2 * life - 1 >= currentTime)
          ans++;
      }
      return ans;
    }
  }

  return 0;
}

int main()
{
  ll test;
  scanf("%lld", &test);
  for (ll i = 1; i <= test; i++)
  {
    printf("#%lld %lld\n", i, solve());
  }
  return 0;
}