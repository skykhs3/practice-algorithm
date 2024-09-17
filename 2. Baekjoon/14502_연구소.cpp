#include <bits/stdc++.h>
using namespace std;
int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};

struct Point{
    int y,x;
    Point(int _y,int _x):y(_y),x(_x){};
    bool operator != (Point rig){
        return !(rig.x==x && rig.y==y);
    }
};

int bfs(int N,int M,vector<vector<int>> &a){
    queue<int> Q;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
           // cout<<a[i][j]<<" ";
            if(a[i][j]==2)Q.push(i),Q.push(j);
        }
      //  cout<<endl;
    }
  //  cout<<endl;
    
    while(!Q.empty()){
        int y=Q.front();Q.pop();
        int x=Q.front();Q.pop();
        for(int k=0;k<4;k++){
            int ty=y+dy[k];
            int tx=x+dx[k];
            if(1<=ty && ty<=N && 1<=tx && tx<=M && a[ty][tx]==0){
                a[ty][tx]=2;
                Q.push(ty);
                Q.push(tx);
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(a[i][j]==0) cnt++;

    return cnt;
}
int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int> > oriMap(N+1,vector<int>(M+1));
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            cin>> oriMap[i][j];

    int ans=0;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            for(int k=1;k<=N;k++){
                for(int l=1;l<=M;l++)
                    for(int m=1;m<=M;m++){
                        for(int n=1;n<=M;n++){
                            vector<vector<int>> b=oriMap;
                            if(Point(i,l)!=Point(j,m) && Point(j,m)!=Point(k,n) && Point(k,n)!=Point(i,l) && b[i][l]==0 && b[j][m]==0 && b[k][n]==0){
                                b[i][l]=1;
                                b[j][m]=1;
                                b[k][n]=1;
                                int res=bfs(N,M,b);
                                ans=max(ans,res);
                               // cout<<res<<endl;
                                //return 0;
                            }
                        }
                    }
            }
        }
    }
    cout<<ans;
    return 0;
}