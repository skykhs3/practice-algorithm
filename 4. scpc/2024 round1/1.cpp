#include <bits/stdc++.h>
using namespace std;
void solve(){
  int n;
  string a;
  scanf("%d",&n);
  cin>>a;
  int last=-1;
  int ans=0;
  for(int i=0;i<a.size();i++){
    if(a[i]=='A'){
      if(last==-1){
        last=i;
      }
      else{
        ans+=max(2-(i-last-1),0);
        last=i;
      }
    }
  }
  printf("%d\n",ans);
}
int main(){
  int t;
  scanf("%d",&t);
  for(int i=1;i<=t;i++){
    printf("Case #%d\n",i);
    solve();
  }
}