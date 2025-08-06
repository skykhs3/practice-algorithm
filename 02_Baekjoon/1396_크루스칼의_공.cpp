#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int p, q, temp;
  bool operator < (Edge& right) {
    return temp < right.temp;
  }
};

struct Query {
  int x, y;
};

vector<Edge> e;
vector<Query> queries;

int findAncestor(int p, vector<int> &parent) {
  if (parent[p] == p) return p;
  return parent[p] = findAncestor(parent[p], parent);
}

void merge(int p, int q, vector<int> &parent, vector<int> &sz) {
  int pA = findAncestor(p, parent);
  int qA = findAncestor(q, parent);
  if (pA != qA) {
    parent[qA] = pA;
    sz[pA] += sz[qA];
  }
}

int main() {
  //setbuf(stdout, NULL); 백준은 이거 붙이면 오류남.
  int n, m, q;
  scanf("%d%d", &n, &m);
  e.resize(m);
  for (int i = 0; i < m; ++i) scanf("%d%d%d", &e[i].p, &e[i].q, &e[i].temp);
  sort(e.begin(), e.end());

  scanf("%d", &q);
  queries.resize(q);
  for (int i = 0; i < q; ++i) scanf("%d%d", &queries[i].x, &queries[i].y);

  vector<int> lef(q, 1), rig(q, m), minTemp(q, -1), possibleCnt(q);
  
  while (true) {
    bool flag = false;
    vector<vector<int>> mid(m + 1);
    for (int i = 0; i < q; ++i) {
      if (lef[i] <= rig[i]) {
        flag = true;
        mid[(lef[i] + rig[i]) / 2].push_back(i);
      }
    }
    if (!flag) break;

    vector<int> parent(n + 1), sz(n + 1, 1);
    for(int i=1;i<=n;i++) parent[i]=i;

    for (int i = 0; i < m; ++i) {
      merge(e[i].p, e[i].q, parent, sz);
      for (int index : mid[i + 1]) {
        int p = queries[index].x;
        int q = queries[index].y;
        if (findAncestor(p, parent) == findAncestor(q, parent)) {
          rig[index] = i;
          minTemp[index] = e[i].temp;
          possibleCnt[index] = sz[findAncestor(p, parent)];
        } else {
          lef[index] = i + 2;
        }
      }
    }
  }

  for (int i = 0; i < q; ++i) {
    if (minTemp[i] == -1) printf("%d\n", -1);
    else printf("%d %d\n", minTemp[i], possibleCnt[i]);
  }
  return 0;
}
