#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int y, x;
};

int mx;
bool finish;

void dfs(int n, int y, int x, int cnt, int lenLimit, vector<Point> &history)
{
    if (y > n)
    {
        mx = max(mx, cnt);
        finish = true;
    }
    else if (x > n)
        dfs(n, y + 1, 1, cnt, lenLimit, history);
    else
    {
        bool impossible = false;
        for (auto point : history)
        {
            if (abs(point.x - x) + abs(point.y - y) < lenLimit)
            {
                impossible = true;
                break;
            }
        }

        bool result;
        if (impossible == false)
        {
            history.push_back({y, x});
            dfs(n, y, x + 1, cnt + 1, lenLimit, history);
            history.pop_back();
            if (finish)
                return;
        }
        dfs(n, y, x + 1, cnt, lenLimit, history);
    }
}
void getMaximumPeople(int n,int k)
{
    if(k==1){
        printf("0");
        return;
    }
    vector<Point> history;
    for (int i = 2 * (n - 1); i >= 1; i--)
    {
        if(i==2){
            if(n%2==0) mx=n*n/2;
            else mx=n*(n/2)+n/2+1;
        }
        else if(i==1) mx=n*n;
        else{
        mx = 0;
        finish=false;
        for (int j = 1; j <= n; j++)
            dfs(n, 1, j, 0, i, history);
        }
        if(k<=mx){
            printf("%d",i);
            return;
        }
       // printf("size:%d len:%d mx:%d\n", n, i, mx);
    }
}
void solution(int n, int m, vector<vector<int>> timetable)
{
    int answer = 0;
    vector<int> time(1400);
    for (int i = 0; i < timetable.size(); i++)
        for(int j=timetable[i][0];j<=timetable[i][1];j++) time[j]++;

    int mx=0;
    for(int i=600;i<=1320;i++) mx=max(mx,time[i]);
    getMaximumPeople(n,mx);
    
}
int main()
{
    setbuf(stdout, NULL);
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> timetable(m, vector<int>(2));
    for (int i = 0; i < m; i++)
        scanf("%d %d", &timetable[i][0], &timetable[i][1]);
    solution(n, m, timetable);
    return 0;
}