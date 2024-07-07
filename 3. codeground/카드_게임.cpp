#include <bits/stdc++.h>
using namespace std;

int getSum(int s, int e, vector<int>& sumA) {
    if (s == 0) return sumA[e];
    else return sumA[e] - sumA[s - 1];
}

int getAB(int y1, int x1, int y2, int x2, vector<vector<int>>& sumAB) {
    if (y1 > y2 || x1 > x2) return 0;
    int sum = sumAB[y2][x2];
    sum += (y1 > 0 && x1 > 0) ? sumAB[y1 - 1][x1 - 1] : 0;
    sum -= (y1 > 0) ? sumAB[y1 - 1][x2] : 0;
    sum -= (x1 > 0) ? sumAB[y2][x1 - 1] : 0;
    return sum;
}

void update(int y, int x, vector<vector<int>>& sumAB, int aij) {
    sumAB[y][x] = aij;
    sumAB[y][x] += (y > 0) ? sumAB[y - 1][x] : 0;
    sumAB[y][x] += (x > 0) ? sumAB[y][x - 1] : 0;
    sumAB[y][x] -= (y > 0 && x > 0) ? sumAB[y - 1][x - 1] : 0;
}


void solution() {
    int n, k;
    scanf("%d%d",&n,&k);
    vector<int> a(n + 1), b(n + 1);
    vector<int> sumA(n + 1), sumB(n + 1);
    vector<vector<int>> sumAB(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<int> la(n + 1), lb(n + 1);
    
    for (int i = 1; i <= n; i++) scanf("%d",&a[i]);
    for (int i = 1; i <= n; i++){
      scanf("%d",&b[i]);
      sumA[i] = sumA[i - 1] + a[i];
      sumB[i] = sumB[i - 1] + b[i];
    }

    int left = 0, right = 0, cur = 0;
    while (right <= n) {
        if (cur + a[right] <= k) {
            cur += a[right];
            la[right] = max(0, left - 1);
            right++;
        } else {
            cur -= a[left];
            left++;
        }
    }

    left = 0, right = 0, cur = 0;
    while (right <= n) {
        if (cur + b[right] <= k) {
            cur += b[right];
            lb[right] = max(0, left - 1);
            right++;
        } else {
            cur -= b[left];
            left++;
        }
    }

    int ans = 0;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            } else {
                if (getAB(la[i], j, i - 1, j, sumAB) != (i - la[i]) || getAB(i, lb[j], i, j - 1, sumAB) != (j - lb[j])) {
                    dp[i][j] = 1;
                }
            }
            update(i, j, sumAB, dp[i][j]);
            if(dp[i][j]) ans++;
        }
    }

    printf("%d %d\n",ans,(n + 1) * (n + 1) - ans );
}

int main() {
    setbuf(stdout, NULL);
    int T;
    scanf("%d",&T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d\n",i);
        solution();
    }
    return 0;
}
