#include <bits/stdc++.h>
using namespace std;
void createReverseEdge(int n,vector<vector<int>> &rE,vector<vector<int>> &E){
  for(int i=1;i<=n;i++)
    for(auto to:E[i])
      rE[to].push_back(i);
}

void dfs(int v,int n,vector<vector<int>> &E, vector<bool> &visited, vector<int> &stk){
  visited[v]=true;
  for(auto to:E[v])
    if(!visited[to]) dfs(to, n, E, visited, stk);
  stk.push_back(v);
}

void rdfs(int v,int n,vector<vector<int>> &rE, vector<bool> &visited, vector<int> &scc){
  visited[v]=true;
  scc.push_back(v);
  for(auto to:rE[v])
    if(!visited[to]) rdfs(to, n, rE, visited, scc);
}

bool comp (const vector<int> lef, const vector<int> right){
  return lef[0]<right[0];
}

void kosaraju(int n,vector<vector<int>> E){
  vector<bool> visited(n+1);
  vector<int> stck;

  for(int i=1;i<=n;i++)
    if(!visited[i]) dfs(i,n,E,visited,stck);
  
  vector<vector<int>> rE(n+1);
  createReverseEdge(n,rE,E);

  vector<vector<int>> ans;
  fill(visited.begin(),visited.end(),false);
  for(int i=stck.size()-1;i>=0;i--){
    vector<int> scc;
    if(!visited[stck[i]]){
      rdfs(stck[i],n,rE,visited,scc);
      ans.push_back(scc);
    }
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
  scanf("%d%d",&n,&m);
  vector<vector<int>> E(n+1);
  for(int i=1;i<=m;i++){
    int x,y;
    scanf("%d%d",&x,&y);
    E[x].push_back(y);
  }
  kosaraju(n,E);
}

//Tarjan's algorithm
/*
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
*/