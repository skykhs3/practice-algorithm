#include <bits/stdc++.h>
using namespace std;

int oo = 9999999;
vector<int> getPartialMatch(string &B){
  int M=(int)B.size(), matched=0;
  vector<int> pi(M, 0);

  for(int i=1;i<M;i++){
    while(matched>0 && B[matched]!=B[i]) matched=pi[matched-1];
    if(B[matched]==B[i]) pi[i]=++matched;
  }
  return pi;
}

void kmp(string &A, string &B){
  vector<int> pi=getPartialMatch(B);

  int matched=0;
  int N = (int)A.size(), M = (int)B.size();
  for(int i=0;i<N;i++){
    while(matched>0 && A[i]!=B[matched])
      matched=pi[matched-1];
    if(A[i]==B[matched]){
    ++matched;
      if(matched==M){
        whereBIsIncluded.push_back(i-matched+1);
        matched=pi[matched-1];
      }
    }
  }
}

void solve()
{
  string R, P;
  cin>>R;
  cin>>P;
  auto prev=kmp(R,P);
// for(int i=0;i<prev.size();i++) printf("%d ",prev[i]);
// printf("\n");

  vector<int> dp(R.size(),oo);
  for(int i=0;i<R.size();i++){
    if(i-prev[i]<0) dp[i]=1;
    else dp[i]=min(dp[i-prev[i]]+1,dp[i]);
  }
  if(dp[R.size()-1]==oo) printf("-1\n");
  else printf("%d\n",dp[R.size()-1]);
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