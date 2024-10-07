// string은 인덱스에 넣지 말자.
// string은 서로 비교를 하지 말자
// string은 복사를 하지 말자.
#include <bits/stdc++.h>
using namespace std;
typedef int ll;
struct Problem{
  ll priority;
  ll time;
  ll urlID;
  bool operator < (const Problem &r) const{
    return priority>r.priority || (priority==r.priority &&  time>r.time);
  }
};
ll n;
ll oo=987654321;

unordered_set<ll> url;
vector<priority_queue<Problem>> Q(50001);

vector<ll> startTime(50001);
vector<ll> endTime(50001);

priority_queue<ll,vector<ll>,greater<ll>> solver;
vector<ll> solverState(50001);

map<string,ll> wholeUrl;
map<string,ll> wholeDomain;
ll cnt=0;
ll cnt2=0;

string makeP(string u0){
  int i=u0.find('/');
  return u0.substr(0,i);
}
void ord100(){
  string u0;
  cin>>n>>u0;
  string domain=makeP(u0);
  if(wholeUrl.find(u0)==wholeUrl.end()) wholeUrl[u0]=++cnt;
  if(wholeDomain.find(domain)==wholeDomain.end()) wholeDomain[domain]=++cnt2;

  if(url.find(wholeUrl[u0])==url.end()){
    url.insert(wholeUrl[u0]);
    Q[wholeDomain[domain]].push({1,0,wholeUrl[u0]});
  }
  for(ll i=1;i<=n;i++) solver.push(i);
}
void ord200(){
  ll t,p;
  string u;
  cin>>t>>p>>u;
  string domain=makeP(u);
  if(wholeDomain.find(domain)==wholeDomain.end()) wholeDomain[domain]=++cnt2;
  if(wholeUrl.find(u)==wholeUrl.end()) wholeUrl[u]=++cnt;

  if(url.find(wholeUrl[u])==url.end()){
    url.insert(wholeUrl[u]);
    Q[wholeDomain[domain]].push({p,t,wholeUrl[u]});
  }
}
void ord300(){
  ll t;
  cin>>t;
  ll v=0;
  Problem mx;
  if(solver.empty()) return;

  for(ll i=1; i<=cnt2; i++){
   
    ll start=startTime[i];
    ll end=endTime[i];
    ll gap=end-start;
    if(end==oo || !(end==0 || (t>=start+3*gap))) continue;

    auto &que=Q[i];
    if(!que.empty()){
  
      Problem top=que.top();
      if(v==0 || mx<top){
        mx=top;
        v=i;
      }
    }
  }


  if(v!=0){
    ll index=solver.top();solver.pop();
    startTime[v]=t;
    endTime[v]=oo;
    solverState[index]=v;
    auto &que=Q[v];
    url.erase(que.top().urlID);
    que.pop();
  }
}
void ord400(){
  ll t, jid;
  cin>> t>>jid;
  if(solverState[jid]==0) return;
  ll domainID=solverState[jid];

  endTime[domainID]=t;
  solverState[jid]=0;
  solver.push(jid);
}
void ord500(){
  ll t;
  cin>> t;
  cout<<url.size()<<endl;
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  ll q;
  cin>>q;
  for(ll qq=1;qq<=q;qq++){
    ll ord;
    cin>>ord;
    if(ord==100) ord100();
    else if(ord==200) ord200();
    else if(ord==300) ord300();
    else if(ord==400) ord400();
    else ord500();
  }
  return 0;
}