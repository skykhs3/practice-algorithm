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

vector<int> kmp(string &A, string &B){
  int match=0;
  int N = (int)A.size(), M = (int)B.size();
  vector<int> pi=getPartialMatch(B);
  vector<int> prev(N);

  for(int i=0;i<N;i++){
    while(match>0 && A[i]!=B[match])
      match=pi[match-1];
    if(A[i]==B[match]){
        match++;
        prev[i]=match;
      if(match==M){
        match=pi[match-1];
      }
      
    }
  }
  return prev;
}

void solution()
{
  string R, P;
  cin>>R;
  cin>>P;
  auto prev=kmp(R,P);

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
  freopen("output.txt","w",stdout);
  printf("A");
  return 0;
  int T;
  cin>>T;
  for (int i = 0; i < T; i++)
  {
    cout<< "Case #" << i + 1<<"\n";
    solution();
  }
}