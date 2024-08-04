// 96점 풀이임. 추후 만점 풀이로 교체 필요.
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Data{
  char own=0;
  ll size=0, numTre=0;
  char ans;
  bool two;
  Data(char _own,ll _size,ll _numTre,bool _two){
    own=_own;
    size=_size;
    numTre = _numTre;
    ans='B';
    two=_two;
  }
};

void dfs(ll v, vector<bool> &visit,vector<vector<ll>> &G,string &own,string &tre, ll &gCnt, ll &gTreCnt,ll &groupNum,vector<ll> &group,bool& two){
  visit[v]=true;
  group[v]=groupNum;
  ++gCnt;
  if(tre[v]=='T') gTreCnt++;
  for(auto to:G[v]){
    if(own[to] == own[v] && tre[to]=='.' && tre[v]=='.') two=true;
    if(!visit[to] && own[v]==own[to]){
      dfs(to,visit,G,own,tre,gCnt,gTreCnt,groupNum,group,two);
    }
  }
}
void case1(ll n,vector<vector<ll>> &G,vector<Data> &nodeData){
  for(ll i=1;i<=n;i++){
    nodeData[i].ans='B';
    if(nodeData[i].own=='B'){
      nodeData[i].ans='A';
    } else{
      for(auto to:G[i]){
        if(nodeData[to].own=='B')
          nodeData[i].ans='A';
      }
      if(nodeData[i].size>=2 && nodeData[i].numTre>0) nodeData[i].ans='A';
    }
  }
}

void case2(ll n,vector<vector<ll>> &G,vector<Data> &nodeData){
  for(ll i=1;i<=n;i++){
    if(nodeData[i].own=='B'){
      if(nodeData[i].two) nodeData[i].ans='B';
      else nodeData[i].ans='A';
    } 
  }
  for(ll i=1;i<=n;i++){
    if(nodeData[i].own=='A'){
      nodeData[i].ans='B';
      if(nodeData[i].size>=2) nodeData[i].ans='A';
      for(auto to:G[i]){
        if(nodeData[to].own=='B' && nodeData[to].ans=='A'){
          nodeData[i].ans='A';
          break;
        }
      }
    }
  }
}

void case3(ll n,vector<vector<ll>> &G,vector<Data> &nodeData){
  vector<bool> check(n+1);
  for(ll i=1;i<=n;i++){
    if(nodeData[i].own=='B'){
      if(nodeData[i].size>=2){
        nodeData[i].ans='B';
        continue;
      }
      check[i]=true;
      for(auto to:G[i]){
        if(nodeData[to].own=='A' && !((nodeData[to].size==1 && nodeData[to].numTre==1) || (nodeData[to].size>=2 && nodeData[to].numTre>0))){
          check[i]=false;
        }
      }
      if(check[i]==true)
        nodeData[i].ans='A';
      else nodeData[i].ans='B';
    }
  }
  for(ll i=1;i<=n;i++){
    if(nodeData[i].own=='A'){
      if(nodeData[i].size>=2 && nodeData[i].numTre>0){
        nodeData[i].ans='A';
      }
      else{
        nodeData[i].ans='B';
        for(auto to:G[i]){
          if(nodeData[to].own=='B' && nodeData[to].ans=='A'){
            nodeData[i].ans='A';
            break;
          }
        }
      }
    }
  }
}

void solve(){
  ll N,M;
  cin>>N>>M;

  vector<vector<ll>> G(N+1);
  string own;
  string tre;
  cin>>own;
  cin>>tre;
  own=" "+own;
  tre=" "+tre;

  for(ll i=1;i<=M;i++){
    ll x,y;
    cin>>x>>y;
    G[x].push_back(y);
    G[y].push_back(x);
  }

  ll aCnt=0,bCnt=0,aTreCnt=0,bTreCnt=0;
  for(ll i=1;i<=N;i++){
    if(own[i]=='A'){
      aCnt++;
      if(tre[i]=='T') aTreCnt++;
    }
    else{
      bCnt++;
      if(tre[i]=='T') bTreCnt++;
    }
  }


  ll groupNum=0;
  vector<bool> visit(N+1);
  vector<ll> group(N+1);
  vector<Data> nodeData;
  nodeData.push_back({'A',1,1,false});
  for(ll i=1;i<=N;i++){
    ll gTreCnt=0,gCnt=0;
    if(!visit[i]){
      bool t=false;
      dfs(i,visit,G,own,tre,gCnt,gTreCnt,++groupNum,group,t);
      nodeData.push_back({own[i],gCnt,gTreCnt,t});
    }
  }

  vector<vector<ll>> newG(groupNum+1);
  for(ll i=1;i<=N;i++){
    for(auto to:G[i]){
      newG[group[i]].push_back(group[to]);
    }
  }

  if(bCnt==bTreCnt){
    case1(groupNum,newG,nodeData);
    for(ll i=1;i<=N;i++){
      cout<<nodeData[group[i]].ans;
    }
  } else if(aCnt==aTreCnt){
    case2(groupNum,newG,nodeData);
    for(ll i=1;i<=N;i++){
      cout<<nodeData[group[i]].ans;
    }
  } else if(bTreCnt==0){
    case3(groupNum,newG,nodeData);
    for(ll i=1;i<=N;i++){
      cout<<nodeData[group[i]].ans;
    }
  } 
  else{
    for(ll i=1;i<=N;i++)
    cout<<"B";
  }
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