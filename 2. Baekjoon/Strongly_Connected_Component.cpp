#include <bits/stdc++.h>
using namespace std;
int dfs(int v, int n, vector<vector<int>>& E, vector<bool> &finished, vector<int> &d, int &cnt, stack<int> &st, vector<vector<int>> &ans){
  int p;
  p=d[v]= ++cnt;
  st.push(v);
  for(auto to:E[v]){
    if(d[to]==0){
      p=min(p,dfs(to, n, E, finished, d, cnt, st, ans));
    } else if(!finished[to]){
      p=min(p,d[to]);
    }
  }
  
  if(p==d[v]){
    vector<int> scc;
    while(true){
      int t=st.top();st.pop();
      finished[t]=true;
      scc.push_back(t);
      
      if(t==v) break;
    }

    ans.push_back(scc);
  }

  return p;
}

bool comp (const vector<int> lef, const vector<int> right){
  return lef[0]<right[0];
}

void tarjan(int n,vector<vector<int>> &E){
  vector<bool> finished(n+1);
  vector<int> d(n+1);
  vector<vector<int>> ans;
  stack<int> st;
  int cnt=0;

  for(int i=1;i<=n;i++){
    if(!finished[i]) dfs(i, n, E, finished, d, cnt, st, ans);
  }

  for(auto &set:ans){
    sort(set.begin(),set.end());
    for(auto v:set){
    //  printf("%d",v);
    }
    //printf("\n");
  }

  sort(ans.begin(),ans.end(),comp);

  printf("%d\n",ans.size());
  for(auto &set:ans){
    for(auto v:set){
      printf("%d ",v);
    }
    printf("-1\n");
  }

}
int main(){
  int n,m;
  vector<vector<int>> V(10005);
  scanf("%d%d",&n,&m);
  for(int i=0;i<m;i++){
    int x,y;
    scanf("%d%d",&x,&y);
    V[x].push_back(y);
  }
  tarjan(n,V);
}