#include <bits/stdc++.h>
#include <limits>
using namespace std;
typedef std::numeric_limits<double> dbl;

void solve(){
  int n;
  cin>>n;
  vector<double> a(n+1);
  for(int i=1;i<=n;i++) cin>>a[i];

  sort(a.begin()+1,a.end());
  vector<double> candidate;
  int cnt0=0,cnt1=0;
  for(int i=1;i<=n;i++){
    if(a[i]==0) cnt0++;
    if(a[i]<1) cnt1++;
  }
  candidate.push_back((double)cnt0/n);
  candidate.push_back((double)cnt1/n-1);
  candidate.push_back(0);

  for(int i=1;i<=n;i++){
    candidate.push_back((double)(i-1)/n-a[i]);
    while(i+1<=n && a[i]==a[i+1]) i++;
    candidate.push_back((double)i/n-a[i]);
  }
  double mx=-1,mn=1;
  for(auto c:candidate){
    mx=max(mx,c);
    mn=min(mn,c);
  }
  cout<<mx-mn;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  cout.precision(dbl::max_digits10);
  int T;
  cin>>T;
  for(int i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
    cout<<endl;
  }
}