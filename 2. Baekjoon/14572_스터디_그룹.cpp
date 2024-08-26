#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Student{
  ll M,d;
  vector<ll> A;
};
bool cmp(Student &lef,Student &rig){
  return lef.d < rig.d;
}
void add(Student &stu,vector<ll> &algo){
  for(auto al:stu.A){
    algo[al]++;
  }
}
void del(Student &stu,vector<ll> &algo){
  for(auto al:stu.A){
    algo[al]--;
  }
}
ll get(vector<ll> &algo, ll K, ll totalStudents){
  ll cnt=0;
  ll cnt2=0;
  for(ll i=1;i<=K;i++){
    if(algo[i]>0) cnt++;
    if(algo[i]==totalStudents) cnt2++;
  }
  return cnt-cnt2;
}
int main(){
  ll N,K,D;
  scanf("%lld%lld%lld",&N,&K,&D);
  vector<Student> a(N+1);
  vector<ll> algo(K+1);
 // cerr<<"TEST";
  for(ll i=1;i<=N;i++){
    scanf("%lld%lld",&a[i].M,&a[i].d);
   // cerr<<"TEST "<<a[i].M;
    a[i].A.resize(a[i].M+1);
    for(ll j=1;j<=a[i].M;j++){
      scanf("%lld",&a[i].A[j]);
    }
  }
  ll mx=0;
  sort(a.begin()+1,a.end(),cmp);
  ll lef=1;
  for(ll i=1;i<=N;i++){
    add(a[i], algo);

    while(a[lef].d<a[i].d-D){
      del(a[lef],algo);
      lef++;
    }
    ll sub=get(algo,K, i-lef+1);
    mx=max(sub*(i-lef+1),mx);
  }
  printf("%lld",mx);
}