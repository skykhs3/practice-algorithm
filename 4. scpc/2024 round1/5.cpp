
#include <bits/stdc++.h>
#define Limit 50000
typedef long long ll;
using namespace std;
ll k;

struct Query{
  ll s,e,index,ans;
};

bool comp(Query& lef,Query& rig){
  return (lef.s-1)/k<(rig.s-1)/k || ( (lef.s-1)/k==(rig.s-1)/k&& lef.e<rig.e );
}

bool cmp(Query& lef,Query& rig){
  return lef.index<rig.index;
}

void mi(ll num, ll &currentSqCnt,vector<ll> &count){
  if(num==1) return;
  ll cur=num;
  vector<ll> temps;
  while(1){
    if(cur>Limit || count[cur]>0){
      if(cur<=Limit) count[cur]--;
      for(auto temp:temps){
        count[temp]=temp-1;
      }
      currentSqCnt-=temps.size();
      break;
    }
    temps.push_back(cur);
    cur=cur*cur;
  }
}

void pl(ll num, ll &currentSqCnt,vector<ll> &count){
  if(num==1) return;
  ll cur=num;
  vector<ll> temps;
  while(1){
    if(cur>Limit || count[cur]+1<cur){
      if(cur<=Limit) count[cur]++;
      for(auto temp:temps){
        count[temp]=0;
      }
      currentSqCnt+=temps.size();
      break;
    }
    temps.push_back(cur);
    cur=cur*cur;
  }
}

void solve(){
  int n;
  scanf("%lld",&n);
  vector<ll> a(n+1);
  for(ll i=1;i<=n;i++){
    scanf("%lld",&a[i]);
  }

  ll Q;
  scanf("%lld",&Q);
  vector<Query> queries(Q);
  
  for(ll i=0;i<Q;i++){
    scanf("%lld%lld",&queries[i].s,&queries[i].e);
    queries[i].index=i;
  }
  for(k=1;k*k<n;k++);

  sort(queries.begin(),queries.end(),comp);

  vector<ll> count(Limit+10);
  for(ll i=queries[0].s;i<=queries[0].e;i++){
    if(a[i]<=Limit) count[a[i]]++;
  }

  ll currentSqCnt=0,s,e;
  for(ll i=2;i<=Limit;i++){
    ll upCnt=count[i]/i;
    count[i]%=i;
    currentSqCnt+=upCnt;
    if(i*i<=Limit)
      count[i*i]+=upCnt;
  }
  s=queries[0].s,e=queries[0].e;
  queries[0].ans=currentSqCnt;

  for(int i=1;i<queries.size();i++){
    auto query=queries[i];
    while(s<query.s) mi(a[s],currentSqCnt,count),s++;
    while(s>query.s) pl(a[s-1],currentSqCnt,count),s--;
    while(e>query.e) mi(a[e],currentSqCnt,count),e--;
    while(e<query.e) pl(a[e+1],currentSqCnt,count),e++;
    queries[i].ans=currentSqCnt;
  }

  sort(queries.begin(),queries.end(),cmp);
  for(auto query:queries) printf("%lld\n",query.ans);
  
}

int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solve();
  }
  return 0;
}