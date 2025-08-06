#include <bits/stdc++.h>
using namespace std;
void solution(){
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> a(n),b(n);
  for(int i=0;i<n;i++){
    scanf("%d",&a[i]);
  }
  for(int i=0;i<n;i++){
    scanf("%d",&b[i]);
  }
  sort(a.begin(),a.end());
  sort(b.begin(),b.end());
  int mx=0;
  for(int i=0;i<m;i++)
    mx=max(mx,a[i]+b[m-1-i]);
  printf("%d\n",mx);
}
int main(){
  int T;
  scanf("%d",&T);
  for(int i=1;i<=T;i++){
    printf("Case #%d\n",i);
    solution();
  }
}