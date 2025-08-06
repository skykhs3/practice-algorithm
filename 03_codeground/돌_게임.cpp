#include <bits/stdc++.h>
using namespace std;
void solve(){
  int n;
  scanf("%d",&n);
  vector<int> a(n+1);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  int cnt=0;
  for(int i=1;i<=n;i++){
    if(a[i]%2==0) cnt++;
  }
  if(cnt%2==1){
    printf("2nd\n");
  }else{
    printf("1st\n");
  }
}
int main(){
  setbuf(stdout, NULL);
  int T;
  scanf("%d",&T);
  for(int i=1;i<=T;i++){
    printf("Case #%d\n",i);
    solve();
  }
}