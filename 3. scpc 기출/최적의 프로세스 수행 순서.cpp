#include <bits/stdc++.h>
using namespace std;

int oo = 9999999;
char r[250010*2];
char p[250010*2];
vector<int> z(250010*2);
vector<int> dp(250010*2, oo);
vector<int> seg(524288*2+10, oo); 

vector<int> Z(string a, vector<int> &z)
{
  int n = a.size();
  z[0] = n;
  int l = 0, r = 0;
  for (int i = 1; i < n; i++)
  {
    if (i <= r) z[i] = min(z[i - l], r - i);
    for(;a[i + z[i]] == a[z[i]];)z[i]++;
    if(i > r) l = i;
    r = max(r, i + z[i] - 1);
  }
  return z;
}

int getMinValue(vector<int> &seg, int nn, int x)
{
  x += nn - 1;
  int mn = oo;
  while (1)
  {
    mn = min(mn, seg[x]);
    if (x == 0)
      break;
    x = (x - 1) / 2;
  }
  return mn;
}

void update(int l, int r, int x, int y, int v, int value, vector<int> &seg)
{
  if(l>r) return ;
  if(r<x || y<l) return;
  if (x <= l && r <= y)
  {
      seg[v] = min(seg[v], value);
      return;
  }
  int mid = (l + r) / 2;
  update(l, mid, x, y, 2 * v + 1, value, seg);
  update(mid + 1, r, x, y, 2 * v + 2, value, seg);
}


void solve()
{
  scanf("%s %s",&r,&p);
  string R, P;
  R=r;
  P=p;
  string A = P + "@" + R;

  for(int i=0;i<A.size()+5;i++) dp[i]=oo,z[i]=0;
  
  Z(A,z);

  int nn = 1;
  while (nn < A.size())
    nn *= 2;

  for(int i=0;i<2*nn+10;i++) seg[i]=oo;


  update(0, nn-1, P.size()+1, P.size()+z[P.size()+1], 0, 1, seg);

  for (int i = P.size()+1; i < A.size()-1; i++)
  {
    dp[i] = getMinValue(seg, nn, i);
    update(0, nn-1, i+1, i+z[i+1], 0, dp[i]+1, seg);
  }

  dp[A.size()-1]=getMinValue(seg,nn,A.size()-1);
  if(dp[A.size()-1]==oo) cout<<-1<<endl;
  else cout<<dp[A.size()-1]<<endl;
}

int main()
{
 
  int T;
  cin>>T;
  for (int i = 0; i < T; i++)
  {
    cout<< "Case #" << i + 1<<"\n";
    solve();
  }
}