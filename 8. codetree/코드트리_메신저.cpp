//부모 같은거 교환하는게 코너 케이스
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Node {
  bool on = true;
  ll parent = 0, depth = 0, power = 0;
  vector<ll> children;
  vector<ll> alarm=vector<ll>(22);  // Correct initialization
};

void dfs(ll v,ll depth,vector<Node>&nodes){
  nodes[v].depth=depth;
  for(auto child:nodes[v].children){
    dfs(child,depth+1,nodes);
    for(ll i=0;i<=21;i++){
      nodes[v].alarm[i]+=nodes[child].alarm[i];
    }
  }
  nodes[v].alarm[max(0LL,depth-nodes[v].power)]++;
}
void update(ll v,vector<Node> & nodes){
  fill(nodes[v].alarm.begin(),nodes[v].alarm.end(),0);
  for(auto child:nodes[v].children)
    if(nodes[child].on==true)
      for(ll i=0;i<=21;i++)
        nodes[v].alarm[i]+=nodes[child].alarm[i];
  
  nodes[v].alarm[max(0LL,nodes[v].depth-nodes[v].power)]++;
  if(v==0) return;
  update(nodes[v].parent,nodes);
}
int main(){
  ll n,q;
  cin>>n>>q;
  vector<Node> nodes(n+1);

  for(ll i=1;i<=q;i++){
    ll ord,c1,c2,power;
    cin>>ord;
    if(ord==100){
      for(ll j=1;j<=n;j++) cin>>nodes[j].parent;
      for(ll j=1;j<=n;j++) cin>>nodes[j].power;
        
      for(ll j=1;j<=n;j++) nodes[nodes[j].parent].children.push_back(j);

      dfs(0,0,nodes);

    }else if(ord==200){
      cin>>c1;
      nodes[c1].on=!nodes[c1].on;
      update(c1,nodes);
    }else if(ord==300){
      cin>>c1>>power;
      nodes[c1].power=power;
      update(c1,nodes);
    }else if(ord==400){
      cin>>c1>>c2;
      if(nodes[c1].parent==nodes[c2].parent) continue;
      for(auto &child:nodes[nodes[c1].parent].children)
        if(child==c1) child=c2;
      
      for(auto &child:nodes[nodes[c2].parent].children)
        if(child==c2) child=c1;
      
      swap(nodes[c1].parent,nodes[c2].parent);

      update(c1,nodes);
      update(c2,nodes);
    }else if(ord==500){
      cin>>c1;
      ll ans=0;
      for(ll j=0;j<=nodes[c1].depth;j++)
        ans+=nodes[c1].alarm[j];
      cout<<ans-1<<endl;
    }
  }
  return 0;
}