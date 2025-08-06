#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
  ll x, y;
};

Point standard;  // 기준점

ll distance(Point a, Point b){
  return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

// 좌표를 기준으로 정렬 (y축 우선, 동일한 y값에서는 x축 우선)
bool compareByCoordinate(Point a, Point b) {
  return (a.y == b.y) ? a.x < b.x : a.y < b.y;
}

// 기준점과의 각도에 따라 정렬
bool compareByAngle(Point a, Point b) {
  ll cross_product = (a.x - standard.x) * (b.y - standard.y) - (b.x - standard.x) * (a.y - standard.y);
  if (cross_product != 0) return cross_product > 0;

  // 거리가 더 짧은 점이 우선
  return distance(a,standard) < distance(b,standard);
}

// CCW 방향 확인 (왼쪽 회전인지 확인)
bool isCounterClockwise(Point p0, Point p1, Point p2) {
  ll cross_product = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
  if (cross_product != 0) return cross_product > 0;

  // 같은 직선 상에 있을 때 더 먼 점이 우선
  return distance(p1,p0) > distance(p2,p0);
}

int main() {
  ll n;
  scanf("%lld", &n);

  vector<Point> points(n);
  for (ll i = 0; i < n; i++)
    scanf("%lld%lld", &points[i].x, &points[i].y);

  // 가장 아래쪽(그리고 왼쪽)의 점을 기준점으로 선택
  sort(points.begin(), points.end(), compareByCoordinate);

  // 나머지 점들을 기준점과의 각도로 정렬
  standard = points[0];
  sort(points.begin() + 1, points.end(), compareByAngle);

  vector<Point> hull;  // Convex Hull을 저장할 스택
  hull.push_back(points[0]);
  hull.push_back(points[1]);

  for (ll i = 2; i < n; i++) {
    while (hull.size() >= 2 && !isCounterClockwise(hull[hull.size() - 2], hull[hull.size() - 1], points[i]))
      hull.pop_back();  // 시계 방향으로 회전하는 점들은 제거
    hull.push_back(points[i]);  // 새로운 점을 추가
  }

  // Convex Hull의 점 개수 출력
  printf("%lld", hull.size());
  return 0;
}
