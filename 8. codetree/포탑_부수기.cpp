#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
ll n, m, k;
ll oo = 98765432198LL;
vector<vector<ll>> a(12, vector<ll>(12));
vector<vector<ll>> t(12, vector<ll>(12));
ll r1, c1;// 공격자
ll r2, c2;// 받는 사람
vector<vector<ll>> path(12, vector<ll>(12));
vector<vector<bool>> visited(12, vector<bool>(12));
vector<vector<bool>> history(12, vector<bool>(12));
ll dy[4] = {0,1,0,-1};
ll dx[4] = {1,0,-1,0};
void input() {
	cin >> n >> m >> k;
	
	for (ll i = 0;i < n;i++)
		for (ll j = 0;j < m;j++)
			cin >> a[i][j];
}
bool A() {
	int cnt = 0;
	for (int i = 0;i < n;i++)
		for (int j = 0;j < m;j++)
			if (a[i][j] != 0) cnt++;
	return cnt == 1;
}
void B(ll turn) {
// 공격자 선정
	ll mnA=oo, mnT,mnRC,mnC;
	for(int i=0;i<n;i++)
		for (int j = 0;j < m;j++)
		{
			if (a[i][j] == 0) continue;
			if (mnA > a[i][j] ||
				(mnA == a[i][j] && mnT < t[i][j]) ||
				(mnA == a[i][j] && mnT == t[i][j] && mnRC < i + j) ||
				(mnA == a[i][j] && mnT == t[i][j] && mnRC == i + j && mnC < j)
				)
			{
				mnA = a[i][j]; mnT = t[i][j];mnRC = i + j; mnC = j;
				r1 = i, c1 = j;
			}
		}
	a[r1][c1] += n + m;
	t[r1][c1] = turn;
}
void C() {
	// 공격자 대상자 선정
	ll mnA = -oo, mnT, mnRC, mnC;
	for (int i = 0;i < n;i++)
		for (int j = 0;j < m;j++)
		{
			if (a[i][j] == 0 || (i==r1 && j==c1)) continue;
			if (mnA < a[i][j] ||
				(mnA == a[i][j] && mnT > t[i][j]) ||
				(mnA == a[i][j] && mnT == t[i][j] && mnRC > i + j) ||
				(mnA == a[i][j] && mnT == t[i][j] && mnRC == i + j && mnC > j)
				)
			{
				mnA = a[i][j]; mnT = t[i][j];mnRC = i + j; mnC = j;
				r2 = i, c2 = j;
			}
		}
}
bool D() {
	queue<ll> Q;
	for (ll i = 0;i < visited.size();i++) {
		for (ll j = 0;j < visited.size();j++) {
			visited[i][j] = false;
			path[i][j] = 0;
			
		}
	
	}
	visited[r1][c1] = true;
	Q.push(r1);Q.push(c1);
	while (!Q.empty()) {
		ll y = Q.front();Q.pop();
		ll x = Q.front();Q.pop();
		for (ll i = 0;i < 4;i++) {
			ll ty = y + dy[i], tx = x + dx[i];
			ty = (ty + n) % n;
			tx = (tx + m) % m;
			if (a[ty][tx] == 0) continue;
			if (!visited[ty][tx]) {
				visited[ty][tx] = true;
				path[ty][tx] = i;
				Q.push(ty);Q.push(tx);
			}
		}
	}
	return visited[r2][c2];
}
void E() {
	vector<pair<ll, ll>> p;
	int y = r2, x = c2;
	a[r2][c2] = max((a[r2][c2] - a[r1][c1]), 0LL);
	history[r2][c2] = true;
	//cout << r1 << " " << c1 << endl;
	while (!(y==r1 && x==c1)) {
		int ty, tx;
		
		ty = y + dy[(path[y][x] + 2) % 4];
		tx = x + dx[(path[y][x] + 2) % 4];
		ty = (ty + n) % n;
		tx = (tx + m) % m;
		y = ty;
		x = tx;
		
		history[y][x] = true;
		if (!(y == r1 && x == c1)) {
			
			a[y][x] = max(0LL, (a[y][x] - a[r1][c1] / 2));
		}
	}
}
void print() {
	for (int i = 0;i < n;i++,printf("\n"))
		for (int j = 0;j < m;j++)
			printf("%lld ", a[i][j]);
	printf("\n");
}
void F() {
	int ddy[8] = { 0,1,1,1,0,-1,-1,-1 };
	int ddx[8] = { 1,1,0,-1,-1,-1,0,1 };
	for (int i = 0;i < 8;i++) {
		int ty = r2 + ddy[i];
		int tx = c2 + ddx[i];
		ty = (ty + n) % n;
		tx = (tx + m) % m;
		if (ty == r1 && tx == c1) continue;
		a[ty][tx] = max(0LL, a[ty][tx] - a[r1][c1] / 2);
		history[ty][tx] = true;
	}
	history[r2][c2] = true;
	history[r1][c1] = true;
	a[r2][c2] = max(0LL, a[r2][c2] - a[r1][c1]);
}
void G() {
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if (!history[i][j] && a[i][j] > 0) {
				a[i][j]++;
			}
}
void process() {
	for (int i = 1;i <= k;i++) {
		if (A()) break;
	
		B(i);
		C();
		

		for (int j = 0;j < n;j++)
			for (int l = 0;l < m;l++)
				history[j][l] = false;
		
		if (D()) {
			//printf("A");
			E();
			//print();
		}
		else {
			
			F();
		}

		
		if (A()) break;
		G();
	
	}
}
void output() {
	ll ans = -oo;
	for (ll i = 0;i < n;i++)
		for (ll j = 0;j < m;j++)
			ans = max(ans, a[i][j]);
	cout << ans;
}
int main() {
	freopen("input.txt", "r", stdin);
	input();
	process();
	output();
	return 0;
}