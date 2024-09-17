#include <bits/stdc++.h>
using namespace std;
struct Point{
  int y,x;
};
int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};
void print(int n, vector<vector<bool>> snake){
  int i,j;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++)
      printf("%d ",snake[i][j]?1:0);
    printf("\n");
  }
  printf("\n");
}
int main(){
  int n,m;
  scanf("%d %d ",&n,&m);
  vector<vector<bool>> apple(n+1,vector<bool>(n+1));
  vector<vector<bool>> snake(n+1,vector<bool>(n+1));
  for(int i=1;i<=m;i++){
    int x,y;
    scanf("%d %d ",&y,&x);
    apple[y][x]=true;
  }
  int l;
  scanf("%d",&l);
  int ordX[l+1];
  int currentL=1;
  char ordY[l+1];
  for(int i=1;i<=l;i++){
    int x;
    char y;
    scanf("%d %c ",&ordX[i],&ordY[i]);
  }

  deque<Point> deq;
  int dir=0,yy=1,xx=1;
  snake[1][1]=true;
  deq.push_back({1,1});

  for(int i=1;i<1000000;i++){
    int ty=yy+dy[dir];
    int tx=xx+dx[dir];
    if(!(1<=ty && ty<=n && 1<=tx && tx<=n)){
      printf("%d",i);
      break;
    }
    else if(snake[ty][tx]){
      printf("%d",i);
      break;
    }
    else if(apple[ty][tx]){
      snake[ty][tx]=true;
      apple[ty][tx]=false;
      deq.push_back({ty,tx});
    }
    else{
      snake[ty][tx]=true;
      deq.push_back({ty,tx});
      Point tail=deq.front();deq.pop_front();
      snake[tail.y][tail.x]=false;
    }
    yy=ty;xx=tx;
    if(currentL<=l && ordX[currentL]==i){
      if(ordY[currentL]=='L') dir=(dir+3)%4;
      else dir=(dir+1)%4;
      currentL++;
    }
  }
}