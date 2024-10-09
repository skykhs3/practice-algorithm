#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct Node{
  vector<bool> color=vector<bool>(6);
  int colorT=-1,colorNum;
  int limDep,dep;
  vector<int> child;
  int p_id;
};
vector<int> root;
int cnt;
int ans;
int oo=987654321;
vector<Node> a(100001);
void ord100(){

  int m_id,p_id,color,max_depth;
  cin>>m_id>>p_id>>color>>max_depth;
  if(p_id==-1) root.push_back(m_id);
  if(p_id==-1){
    
    a[m_id]={vector<bool>(6),cnt,color,max_depth,1,vector<int>(0),-1};
  } else{
    if(a[p_id].limDep>=a[p_id].dep+1)
    {
      a[p_id].child.push_back(m_id);
      a[m_id]={vector<bool>(6),cnt,color,min(a[p_id].limDep,a[p_id].dep+max_depth),a[p_id].dep+1,vector<int>(0),p_id};
    }
  }
}
void dfs(int v, int colorT,int colorNum){
  if(colorT<a[v].colorT){
    colorT=a[v].colorT;
    colorNum=a[v].colorNum;
  }
  //cout<<"->"<<v<<" "<<colorNum<<endl;
  for(auto child:a[v].child){
    dfs(child,colorT,colorNum);
  }
  for(int i=0;i<6;i++) a[v].color[i]=false;
  a[v].color[colorNum]=true;
  for(auto child:a[v].child){
    for(int i=0;i<6;i++)
      a[v].color[i]=a[v].color[i] || a[child].color[i];
  }
  int c=0;
  for(int i=0;i<6;i++)
    if(a[v].color[i]) c++;
  ans+=c*c;
}
void ord200(){
  int m_id,color;
  cin>>m_id>>color;
  a[m_id].colorT=cnt;
  a[m_id].colorNum=color;
}
void dfs2(int v){
  int colorT=0,colorNum;
  while(1){
    if(colorT<a[v].colorT){
      colorT=a[v].colorT;
      colorNum=a[v].colorNum;
    }
    v=a[v].p_id;
    if(v==-1) break;
  }
  cout<<colorNum<<endl;
}
void ord300(){
  int m_id;
  cin>>m_id;
  dfs2(m_id);
}
void ord400(){
  ans=0;
  for(auto rt:root)
    dfs(rt,0,-1);
  cout<<ans<<endl;
}
int main(){
  int q;
  cin>>q;
  for(int i=1;i<=q;i++){
    cnt=i;
    int ord;
    cin>>ord;
    if(ord==100){
      ord100();
    }else if(ord==200){
      ord200();
    }else if(ord==300){
      ord300();
    }else if(ord==400){
      ord400();
    }
  }
}