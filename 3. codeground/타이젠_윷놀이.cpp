#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
  ll nexP = 0;
  ll cnt = 0;
};

Point simul[50][6]; // i 위치에서 숫자 j가 나왔을 때.
void preProcess()
{
  for (ll i = 1; i <= 20; i++)
  {
    for (ll j = 1; j <= 5; j++)
    {
      if (i + j == 21)
        simul[i][j] = {30, 0};
      else if (i + j > 21)
        simul[i][j] = {1, 1};
      else
        simul[i][j] = {i + j, 0};
    }
  }
  simul[6][1]={21,0};
  simul[6][2]={22,0};
  simul[6][3]={23,0};
  simul[6][4]={24,0};
  simul[6][5]={25,0};

  simul[11][1]={26,0};
  simul[11][2]={27,0};
  simul[11][3]={23,0};
  simul[11][4]={28,0};
  simul[11][5]={29,0};

  simul[30][1] = {1, 1};
  simul[30][2] = {1, 1};
  simul[30][3] = {1, 1};
  simul[30][4] = {1, 1};
  simul[30][5] = {1, 1};

  simul[21][1]= {22,0};
  simul[21][2]= {23,0};
  simul[21][3]= {24,0};
  simul[21][4]= {25,0};
  simul[21][5]= {16,0};

  simul[22][1]= {23,0};
  simul[22][2]= {24,0};
  simul[22][3]= {25,0};
  simul[22][4]= {16,0};
  simul[22][5]= {17,0};

  simul[24][1]= {25,0};
  simul[24][2]= {16,0};
  simul[24][3]= {17,0};
  simul[24][4]= {18,0};
  simul[24][5]= {19,0};

  simul[25][1]= {16,0};
  simul[25][2]= {17,0};
  simul[25][3]= {18,0};
  simul[25][4]= {19,0};
  simul[25][5]= {20,0};

  simul[26][1]= {27,0};
  simul[26][2]= {23,0};
  simul[26][3]= {28,0};
  simul[26][4]= {29,0};
  simul[26][5]= {30,0};

  simul[27][1]= {23,0};
  simul[27][2]= {28,0};
  simul[27][3]= {29,0};
  simul[27][4]= {30,0};
  simul[27][5]= {1,1};

  simul[23][1]= {28,0};
  simul[23][2]= {29,0};
  simul[23][3]= {30,0};
  simul[23][4]= {1,1};
  simul[23][5]= {1,1};

  simul[28][1]= {29,0};
  simul[28][2]= {30,0};
  simul[28][3]= {1,1};
  simul[28][4]= {1,1};
  simul[28][5]= {1,1};

  simul[29][1]= {30,0};
  simul[29][2]= {1,1};
  simul[29][3]= {1,1};
  simul[29][4]= {1,1};
  simul[29][5]= {1,1};
}
void solve()
{
  ll N, K;
  
  scanf("%lld%lld", &N, &K);
  vector<int> a(N+1);
  for(ll i=1;i<=N;i++){
    scanf("%d",&a[i]);
  }

  vector<Point> dp(50);
  
  for(ll j=1;j<=30;j++){
    ll current=j,cnt=0;
    for(ll i=1;i<=N;i++){
      ll x,y;
      x=simul[current][a[i]].nexP;
      y=simul[current][a[i]].cnt;
      current=x;
      cnt+=y;
    }
    dp[j]={current,cnt};
  }

  ll current=1,cnt=0;
  for(ll i=1;i<=K;i++){
    ll x=dp[current].nexP;
    ll y=dp[current].cnt;
    current=x;
    cnt+=y;
  }
  printf("%lld\n",cnt);
}
int main()
{
  setbuf(stdout, NULL);
  ll T;
  preProcess();
  scanf("%lld", &T);
  for (ll i = 1; i <= T; i++)
  {
    printf("Case #%lld\n",i);
    solve();
  }
}