//입력 실수 했음
// 플레 1까지는 풀 수 있도록 노력하자.
#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> s(1010);  // 크기가 1010인 int형 vector s 선언
vector<int> h(1010);  // 크기가 1010인 int형 vector h 선언
vector<vector<int> > dp(1010,vector<int>(1010));
int oo=999999999;
void input() {
    cin >> n;  // 변수 n에 입력을 받음
    cin >> k;  // 변수 k에 입력을 받음

    // 벡터 s의 원소들을 입력 받음
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];  // s의 i번째 원소에 값을 입력
    }

    // 벡터 h의 원소들을 입력 받음
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];  // h의 i번째 원소에 값을 입력
    }
}

int main() {
    input();  // input 함수 호출

    dp = vector<vector<int> >(1010, vector<int>(1010, -oo));


    dp[0][100]=0;
    for(int i=0;i<n;i++){
      for(int j=0;j<=100;j++){
        if(dp[i+1][min(100,j+k)]<dp[i][j])
          dp[i+1][min(100,j+k)]=dp[i][j];
        if(min(j+k,100)-h[i+1]>=0 && dp[i+1][min(100,j+k)-h[i+1]]<dp[i][j]+s[i+1])
          dp[i+1][min(100,j+k)-h[i+1]]=dp[i][j]+s[i+1];
      }
    }
    int mx=0;
    for(int i=0;i<=100;i++) mx=max(mx,dp[n][i]);
    printf("%d",mx);
    return 0;
}
