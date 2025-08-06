#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
stack<char> S;
void solve(){
  char tmp[1000005];
  int n;
  ll ans=0;
  scanf("%d",&n);
  scanf("%s",tmp);
  vector<int> memo(n+1);

  while(!S.empty()) S.pop();

  for(int i=0;i<n;i++){
    char chr=tmp[i];
    if(chr=='(' || chr=='{') S.push(chr);
    else{
      int flg=0;
      if(!S.empty()){
        if(chr==')' && S.top()=='('){
          S.pop();
          memo[S.size()+1]=0;

          memo[S.size()]++;

          ans+=memo[S.size()];
          flg=1;
        }
        else if(chr=='}' && S.top()=='{'){
          S.pop();
          memo[S.size()+1]=0;
          
          memo[S.size()]++;

          ans+=memo[S.size()];
          flg=1;
        }
      }
      if(flg==0){
        for(int j=0;j<=S.size();j++) memo[j]=0;
        while(!S.empty())S.pop();
      }
    }
  }
  printf("%lld\n",ans);
}
int main(){
  int T;
  scanf("%d",&T);
  for(int i=1;i<=T;i++){
    printf("Case #%d\n",i);
    solve();
  }
}