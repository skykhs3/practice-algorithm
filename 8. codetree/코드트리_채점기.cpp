#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Problem{
  ll priority;
  ll time;
  string url;
  string domain;
  bool operator < (const Problem &r) const{
    return priority>r.priority || (priority==r.priority &&  time>r.time);
  }
};
ll n;
ll oo=987654321987LL;

set<string> url;
map<string,priority_queue<Problem>> Q;

map<string,ll> startTime;
map<string,ll> endTime;

priority_queue<ll,vector<ll>,greater<ll>> solver;
vector<string> solverState(50001);

string makeP(string u0){
  ll i;
  for(i=0;i<u0.size();i++){
    if(u0[i]=='/') break;
  }
  return u0.substr(0,i);
}
void ord100(){
  string u0;
  cin>>n>>u0;
  string domain=makeP(u0);
  if(url.find(u0)==url.end()){
    url.insert(u0);
    Q[domain].push({1,0,u0,domain});
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
    Q[domain].push({p,t,u,domain});
  }
}
void ord300(){
  ll t;
  cin>>t;
  string v="-";
  Problem mx;
  for(auto &it:Q){
    string domain=it.first;
    auto &que=it.second;
    ll start=startTime[domain];
    ll end=endTime[domain];
    ll gap=end-start;
   // cout<<domain<<endl;
    if((end==0 || (t>=start+3*gap)) && !que.empty()){
      Problem top=que.top();
      if(v=="-" || mx<top){
        mx=top;
        v=domain;
      }
    }
  }
  //cout<<"---"<<endl;

  if(v!="-" && !solver.empty()){
    ll index=solver.top();solver.pop();
    startTime[v]=t;
    endTime[v]=oo;
    solverState[index]=v;

    url.erase(Q[v].top().url);
    Q[v].pop();
    
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