
#include <bits/stdc++.h>
#define Limit 50000
typedef long long ll;
using namespace std;
ll k; // bucket size

struct Query{
  ll s,e,index,ans;
};

bool compareByBucket(Query& lef,Query& rig){
  return (lef.s-1)/k<(rig.s-1)/k || ( (lef.s-1)/k==(rig.s-1)/k&& lef.e<rig.e );
}

bool compareByIndex(Query& lef,Query& rig){
  return lef.index<rig.index;
}

void updateWhenErase(ll num, ll &currentSqCnt,vector<ll> &count){
  if(num==1) return;
  ll cur=num;
  vector<ll> history;
  while(1){
    if(cur>Limit || count[cur]>0){
      if(cur<=Limit) count[cur]--;
      for(auto temp:history)count[temp]=temp-1;
      currentSqCnt-=history.size();
      break;
    }
    history.push_back(cur);
    cur=cur*cur;
  }
}

void updateWhenInsert(ll num, ll &currentSqCnt,vector<ll> &count){
  if(num==1) return;
  ll cur=num;
  vector<ll> history;
  while(1){
    if(cur>Limit || count[cur]+1<cur){
      if(cur<=Limit) count[cur]++;
      for(auto temp:history) count[temp]=0;
      currentSqCnt+=history.size();
      break;
    }
    history.push_back(cur);
    cur=cur*cur;
  }
}

void solution(){
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

  for(k=1;k*k<n;k++); //find bucket size

  sort(queries.begin(),queries.end(),compareByBucket); // sort

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
    while(s<query.s) updateWhenErase(a[s],currentSqCnt,count),s++;
    while(s>query.s) updateWhenInsert(a[s-1],currentSqCnt,count),s--;
    while(e>query.e) updateWhenErase(a[e],currentSqCnt,count),e--;
    while(e<query.e) updateWhenInsert(a[e+1],currentSqCnt,count),e++;
    queries[i].ans=currentSqCnt;
  }

  sort(queries.begin(),queries.end(),compareByIndex);
  for(auto query:queries) printf("%lld\n",query.ans);
  
}

int main(){
  ll T;
  scanf("%lld",&T);
  for(ll i=1;i<=T;i++){
    printf("Case #%lld\n",i);
    solution();
  }
  return 0;
}