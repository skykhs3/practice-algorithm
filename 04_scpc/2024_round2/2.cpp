#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Data{
  ll val,index,ans;
};
bool cmp(Data &l,Data &r){
  return l.val<r.val || ( l.val==r.val && l.index<r.index);
}

ll sum2(ll i,vector<ll> &bit){
  ll s=0;
  while(i>0){
    s+=bit[i];
    i-=i&-i;
  }
  return s;
}
void add(ll i,ll n,vector<ll> &bit){
  while(i<=n){
    bit[i]+=1;
    i+=i&-i;
  }
}

bool cmp2(Data &l, Data &r){
  return l.index<r.index;
}
void solve(){
  ll N,Q;
  cin>>N>>Q;
  vector<Data> a(N+1),b(N+1);
  vector<Data> queries(Q+1);
  for(ll i=1;i<=N;i++){
    cin>>a[i].val;
    a[i].index=i;
    b[i]=a[i];
  }
  for(ll i=1;i<=Q;i++){
    cin>>queries[i].val;
    queries[i].index=i;
  }
  sort(queries.begin()+1,queries.end(),cmp);
  sort(b.begin()+1,b.end(),cmp);

  ll MAX_N=1;
  while(MAX_N<N) MAX_N*=2;
  vector<ll> bit(MAX_N+10);



  vector<ll> sum(N+1);
  for(ll i=1;i<=N;i++){
    sum[i]=(b[i].val-b[i-1].val)*(N-i+1)+sum[i-1];
  }
  ll pointer=0;
  ll ans=0;
  for(ll i=1;i<=Q;i++){
    auto query=queries[i];

    while(pointer<N && sum[pointer+1]<query.val){
      pointer++;
      add(b[pointer].index,N,bit);
    }
    
    ll namu=query.val-sum[pointer];
    ll toFind=namu % (N-pointer);
    if(toFind==0) toFind=(N-pointer);
   // printf("%lld %lld %lld\n",query.val,sum[pointer],toFind);
    ll l=1,r=N;
    while(l<=r){
      ll mid=(l+r)/2;
      if(mid-sum2(mid,bit)>=toFind) r=mid-1;
      else l=mid+1;
    }
    ans+=r+1;
    queries[i].ans=r+1;
  }
  cout<<ans;

  // sort(queries.begin()+1,queries.end(),cmp2);
  // cout<<endl;
  // for(ll i=1;i<=Q;i++)
  //   cout<<queries[i].val <<" "<<  queries[i].ans<<endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  ll T;
  cin>>T;
  for(ll i=1;i<=T;i++){
    cout<<"Case #"<<i<<endl;
    solve();
    cout<<endl;
  }
}