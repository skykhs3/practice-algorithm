// 코드트리_빵.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, m;
int dy[4] = { -1,0,0,1 };
int dx[4] = { 0,-1, 1, 0 };
int oo = 987654321;
vector<vector<int>> a(20, vector<int>(20));
vector<vector<bool>> block(20, vector<bool>(20));
struct Point {
	int y, x;
	bool disabled = false;
};
vector<Point> p, c, base;
void input() {
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= n;j++) {
			cin >> a[i][j];
			if (a[i][j])
				base.push_back({ i,j,false });
		}
	p.resize(m + 1);
	c.resize(m + 1);
	for (int i = 1;i <= m;i++) {
		cin >> c[i].y >> c[i].x;
	}
}
void move(int person) {
	if (p[person].disabled) return;
	queue<int> Q;
	vector<vector<int>> b(20, vector<int>(20,oo));
	vector<vector<int>> path(20, vector<int>(20, 0));
	b[p[person].y][p[person].x] = 0;
	Q.push(p[person].y);
	Q.push(p[person].x);

	while (!Q.empty()) {
		int y = Q.front();Q.pop();
		int x = Q.front();Q.pop();
		for (int i = 0;i < 4;i++) {
			int ty = y + dy[i];
			int tx = x + dx[i];
			if (1 <= ty && ty <= n && 1 <= tx && tx <= n && b[ty][tx] > b[y][x] + 1 && !block[ty][tx]) {
				b[ty][tx] = b[y][x] + 1;
				Q.push(ty);
				Q.push(tx);
				path[ty][tx] = i;
			}
		}
	}
	int y = c[person].y;
	int x = c[person].x;
	while (1) {
		int ty, tx;
		ty = y - dy[path[y][x] % 4];
		tx = x - dx[path[y][x] % 4];
		if (ty == p[person].y && tx == p[person].x) break;
		y = ty;
		x = tx;
	}

	p[person].y = y;
	p[person].x = x;
	
}
void base2(int idx) {
	queue<int> Q;
	vector<vector<int>> b(20, vector<int>(20, oo));
	Q.push(c[idx].y);
	Q.push(c[idx].x);
	b[c[idx].y][c[idx].x] = 0;
	while (!Q.empty()) {
		int y = Q.front();Q.pop();
		int x = Q.front();Q.pop();
	//	cerr << y << " " << x << endl;
		for (int i = 0;i < 4;i++) {
			int ty = y + dy[i];
			int tx = x + dx[i];
			if (1 <= ty && ty <= n && 1 <= tx && tx <= n && b[ty][tx] > b[y][x] + 1 && !block[ty][tx]) {
				b[ty][tx] = b[y][x] + 1;
				Q.push(ty);
				Q.push(tx);
			}
		}
	}
	int mn = oo, v;
	for (int i = 0;i < base.size();i++) {
		
		if (base[i].disabled) continue;
		if (mn > b[base[i].y][base[i].x] ||
			(mn == b[base[i].y][base[i].x] && base[v].y > base[i].y) ||
			(mn == b[base[i].y][base[i].x] && base[v].y == base[i].y && base[v].x > base[i].x)
			) {
			mn = b[base[i].y][base[i].x], v = i;
		}
	}

	base[v].disabled = true;
	p[idx].y = base[v].y;p[idx].x = base[v].x;
	block[p[idx].y][p[idx].x] = true;
}
bool deter() {
	for (int i = 1;i <= m;i++)
		if (!p[i].disabled) return false;
	return true;
}
void print() {
	for (int i = 1;i <= m;i++) printf("%d %d %d\n", i, p[i].y, p[i].x);
	printf("\n");
}
void conv() {
	for(int i=1;i<=m;i++)
		if (p[i].y == c[i].y && p[i].x == c[i].x) {
			p[i].disabled = true;
			c[i].disabled = true;
			block[p[i].y][p[i].x] = true;
		}
}
void process() {
	for (int turn = 1;;turn++) {

		for (int j = 1;j <= m;j++) {
			if (j >= turn) continue;
			move(j);
		}

		conv();
		if (turn <= m) {
			base2(turn);
		}

		if (deter()) {
			cout << turn;
			break;
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	input();
	process();
	return 0;
}

	// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
	// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

	// 시작을 위한 팁: 
	//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
	//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
	//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
	//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
	//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
	//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
