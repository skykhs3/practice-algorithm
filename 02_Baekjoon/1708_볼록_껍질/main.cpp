#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
  ll x, y;
};

Point standard;  // ������

ll distance(Point a, Point b){
  return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

// ��ǥ�� �������� ���� (y�� �켱, ������ y�������� x�� �켱)
bool compareByCoordinate(Point a, Point b) {
  return (a.y == b.y) ? a.x < b.x : a.y < b.y;
}

// ���������� ������ ���� ����
bool compareByAngle(Point a, Point b) {
  ll cross_product = (a.x - standard.x) * (b.y - standard.y) - (b.x - standard.x) * (a.y - standard.y);
  if (cross_product != 0) return cross_product > 0;

  // �Ÿ��� �� ª�� ���� �켱
  return distance(a,standard) < distance(b,standard);
}

// CCW ���� Ȯ�� (���� ȸ������ Ȯ��)
bool isCounterClockwise(Point p0, Point p1, Point p2) {
  ll cross_product = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
  if (cross_product != 0) return cross_product > 0;

  // ���� ���� �� ���� �� �� �� ���� �켱
  return distance(p1,p0) > distance(p2,p0);
}

int main() {
  ll n;
  scanf("%lld", &n);

  vector<Point> points(n);
  for (ll i = 0; i < n; i++)
    scanf("%lld%lld", &points[i].x, &points[i].y);

  // ���� �Ʒ���(�׸��� ����)�� ���� ���������� ����
  sort(points.begin(), points.end(), compareByCoordinate);

  // ������ ������ ���������� ������ ����
  standard = points[0];
  sort(points.begin() + 1, points.end(), compareByAngle);

  vector<Point> hull;  // Convex Hull�� ������ ����
  hull.push_back(points[0]);
  hull.push_back(points[1]);

  for (ll i = 2; i < n; i++) {
    while (hull.size() >= 2 && !isCounterClockwise(hull[hull.size() - 2], hull[hull.size() - 1], points[i]))
      hull.pop_back();  // �ð� �������� ȸ���ϴ� ������ ����
    hull.push_back(points[i]);  // ���ο� ���� �߰�
  }

  // Convex Hull�� �� ���� ���
  printf("%lld", hull.size());
  return 0;
}
