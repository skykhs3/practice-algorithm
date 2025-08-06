#include <bits/stdc++.h>
using namespace std;

struct Point
{
  int y, x;
  bool operator==(const Point &other) const
  {
    return y == other.y && x == other.x;
  }
  bool operator!=(const Point &other) const
  {
    return !(*this == other);
  }
};

struct Edge
{
  int len;
  Point p, q;
  bool operator<(const Edge &other) const
  {
    return len < other.len;
  }
};

const int dy[4] = {0, 1, 0, -1};
const int dx[4] = {1, 0, -1, 0};

// Find the root ancestor of a point with path compression
Point findAncestor(Point p, vector<vector<Point>> &parent)
{
  if (p != parent[p.y][p.x])
    parent[p.y][p.x] = findAncestor(parent[p.y][p.x], parent);
  
  return parent[p.y][p.x];
}

// Merge two sets by connecting their roots
void unionSets(Point p, Point q, vector<vector<Point>> &parent)
{
  Point rootP = findAncestor(p, parent);
  Point rootQ = findAncestor(q, parent);
  if (rootP != rootQ) parent[rootQ.y][rootQ.x] = rootP;
}

// Read the heights matrix from input
void readHeights(int n, int m, vector<vector<int>> &heights)
{
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &heights[i][j]);

}

// Generate all possible edges with their lengths
void generateEdges(int n, int m, const vector<vector<int>> &heights, vector<Edge> &edges)
{
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int k = 0; k < 4; ++k){
        int ny = i + dy[k];
        int nx = j + dx[k];
        if (1 <= ny && ny <= n && 1 <= nx && nx <= m)
          edges.push_back({max(heights[i][j], heights[ny][nx]), {i, j}, {ny, nx}});
      }
}

// Read the queries from input
void readQueries(int q, vector<pair<Point, Point>> &queries)
{
  for (int i = 0; i < q; ++i)
    scanf("%d%d%d%d", &queries[i].first.y, &queries[i].first.x, &queries[i].second.y, &queries[i].second.x);
}

// Perform parallel binary search on the queries
void parallelBinarySearch(int n, int m, int q, const vector<Edge> &edges, const vector<pair<Point, Point>> &queries, vector<int> &results, const vector<vector<int>> &heights)
{
  vector<int> left(q, 1);
  vector<int> right(q, 1000000);
  vector<vector<int>> midQueryIndices(1000001);

  while (true){
    bool allQueriesResolved = true;
    vector<vector<Point>> parent(n + 1, vector<Point>(m + 1));

    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        parent[i][j] = {i, j};

    for (int i = 0; i < q; ++i)
      if (left[i] <= right[i]){
        int mid = (left[i] + right[i]) / 2;
        midQueryIndices[mid].push_back(i);
        allQueriesResolved = false;
      }

    if (allQueriesResolved)
      break;

    int currentEdgeIndex = -1;

    for (int currentHeight = 1; currentHeight <= 1000000; ++currentHeight){
      while (currentEdgeIndex + 1 < edges.size() && edges[currentEdgeIndex + 1].len <= currentHeight){
        unionSets(edges[currentEdgeIndex + 1].p, edges[currentEdgeIndex + 1].q, parent);
        ++currentEdgeIndex;
      }

      for (int queryIndex : midQueryIndices[currentHeight]){
        Point rootP = findAncestor(queries[queryIndex].first, parent);
        Point rootQ = findAncestor(queries[queryIndex].second, parent);
        if (rootP == rootQ)
          right[queryIndex] = currentHeight - 1;
        else
          left[queryIndex] = currentHeight + 1;
      
      }

      midQueryIndices[currentHeight].clear(); // Clear for the next iteration
    }
  }

  for (int i = 0; i < q; ++i){
    if (queries[i].first == queries[i].second)
      results[i] = heights[queries[i].first.y][queries[i].first.x];
    else
      results[i] = right[i] + 1;
  }
}

int main()
{
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);

  vector<vector<int>> heights(n + 1, vector<int>(m + 1));
  vector<Edge> edges;
  vector<pair<Point, Point>> queries(q);
  vector<int> results(q);

  readHeights(n, m, heights);
  generateEdges(n, m, heights, edges);
  readQueries(q, queries);
  sort(edges.begin(), edges.end());

  parallelBinarySearch(n, m, q, edges, queries, results, heights);

  for (int result : results)
    printf("%d\n", result);

  return 0;
}
