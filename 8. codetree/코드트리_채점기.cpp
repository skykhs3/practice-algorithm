// unordered_map 사용법 알기.
#include <bits/stdc++.h>
using namespace std;
typedef int ll;
struct Problem{
  ll priority;
  ll time;
  string url;
  bool operator < (const Problem &r) const{
    return priority>r.priority || (priority==r.priority &&  time>r.time);
  }
};
ll n;
ll oo=987654321;

unordered_set<string> url;
unordered_map<string,priority_queue<Problem>> Q;

unordered_map<string,ll> startTime;
unordered_map<string,ll> endTime;

priority_queue<ll,vector<ll>,greater<ll>> solver;
vector<string> solverState(50001);


string makeP(string u0){
  int i=u0.find('/');
  return u0.substr(0,i);
}
void ord100(){
  string u0;
  cin>>n>>u0;
  string domain=makeP(u0);
  if(url.find(u0)==url.end()){
    url.insert(u0);
    Q[domain].push({1,0,u0});
  }
  for(ll i=1;i<=n;i++) solver.push(i);
}
void ord200(){
  ll t,p;
  string u;
  cin>>t>>p>>u;
  string domain=makeP(u);

  if(url.find(u)==url.end()){
    url.insert(u);
    Q[domain].push({p,t,u});
  }
}
void ord300(){
  ll t;
  cin>>t;
  string v="-";
  Problem mx;
  if(solver.empty()) return;

  for(auto &it:Q){
    string domain=it.first;
    ll start=startTime[domain];
    ll end=endTime[domain];
    ll gap=end-start;
    if(end==oo || !(end==0 || (t>=start+3*gap))) continue;
    auto &que=it.second;
    if(!que.empty()){
      Problem top=que.top();
      if(v=="-" || mx<top){
        mx=top;
        v=domain;
      }
    }
  }

  if(v!="-"){
    ll index=solver.top();solver.pop();
    startTime[v]=t;
    endTime[v]=oo;
    solverState[index]=v;

    auto &que=Q[v];
    url.erase(que.top().url);
    que.pop();
  }
}
void ord400(){
  ll t, jid;
  cin>> t>>jid;
  if(solverState[jid]=="") return;
  string domain=solverState[jid];
  endTime[domain]=t;
  solverState[jid]="";
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