#include <bits/stdc++.h>
using namespace std;

int getSum(int s, int e, vector<int>& sumA) {
    if (s == 0) return sumA[e];
    else return sumA[e] - sumA[s - 1];
}

int get(int e, vector<int>& sumA, int limit, vector<int>& memo) {
    if (memo[e] != -1) return memo[e];
    int left = 0, right = e;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (getSum(mid, e, sumA) <= limit) right = mid - 1;
        else left = mid + 1;
    }
    return memo[e] = right + 1;
}

int getAB(int y1, int x1, int y2, int x2, vector<vector<int>>& sumAB) {
    int sum = 0;
    if (y1 > y2 || x1 > x2) return 0;
    if (y1 > 0 && x1 > 0) sum += sumAB[y1 - 1][x1 - 1];
    if (y1 > 0) sum -= sumAB[y1 - 1][x2];
    if (x1 > 0) sum -= sumAB[y2][x1 - 1];
    return sum + sumAB[y2][x2];
}

void update(int y, int x, vector<vector<int>>& sumAB, int aij) {
    sumAB[y][x] = aij;
    if (y > 0) sumAB[y][x] += sumAB[y - 1][x];
    if (x > 0) sumAB[y][x] += sumAB[y][x - 1];
    if (y > 0 && x > 0) sumAB[y][x] -= sumAB[y - 1][x - 1];
}

void solution() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    vector<int> sumA(n + 1), sumB(n + 1);
    vector<vector<int>> sumAB(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<int> memo1(n + 1, -1), memo2(n + 1, -1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) sumA[i] = sumA[i - 1] + a[i], sumB[i] = sumB[i - 1] + b[i];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            } else {
                int la = max(0, get(i, sumA, k, memo1) - 1);
                int lb = max(0, get(j, sumB, k, memo2) - 1);
                if (getAB(la, j, i - 1, j, sumAB) != (i - la) || getAB(i, lb, i, j - 1, sumAB) != (j - lb)) {
                    dp[i][j] = 1;
                }
            }
            update(i, j, sumAB, dp[i][j]);
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i][j]) ans++;
        }
    }
    cout << ans << " " << (n + 1) * (n + 1) - ans << endl;
}

int main() {
    setbuf(stdout, NULL);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ":" << endl;
        solution();
    }
    return 0;
}
