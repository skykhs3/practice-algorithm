//서로 교환하는 케이스의 경우 꼼꼼히 따져봐야한다.
#include <iostream>
#include <vector>
using namespace std;
int q,n,m;
struct Present{
  int before,after;
};
vector<Present> presents;
vector<int> beltSize;
void preProcess(){
  presents.resize(m+n+n+1);
  beltSize.resize(n+1);
  for(int i=1;i<=n;i++){
    presents[m+i].after=m+n+i;
    presents[m+n+i].before=m+i;
  }
}
void insert(int next,int target,int beltPos){
  int prev=presents[next].before;
  presents[prev].after=target;
  presents[target].before=prev;
  presents[next].before=target;
  presents[target].after=next;
  beltSize[beltPos]++;
}
void move200(int mSrc,int mDst){ //n:벨트, m:선물
  if(beltSize[mSrc]>0){
    int x1=m+mSrc;
    int x2=presents[x1].after;
    int x4=m+n+mSrc;
    int x3=presents[x4].before;
    presents[x1].after=x4;
    presents[x4].before=x1;

    int y1=m+mDst;
    int y2=presents[y1].after;
    presents[y1].after=x2;
    presents[x2].before=y1;
    presents[x3].after=y2;
    presents[y2].before=x3;

    beltSize[mDst]+=beltSize[mSrc];
    beltSize[mSrc]=0;
  }
}
void move300(int mSrc,int mDst){
  int x1=m+mSrc;
  int x2=presents[x1].after;
  int x3=presents[x2].after;
  int y1=m+mDst;
  int y2=presents[y1].after;
  int y3=presents[y2].after;

  bool move1=false,move2=false;
  if(beltSize[mSrc]==0) x3=x2;
  if(beltSize[mDst]==0) y3=y2;
  
  if(beltSize[mSrc]>0) move1=true;
  if(beltSize[mDst]>0) move2=true;
  
  if(move1){
    presents[x1].after=x3;
    presents[x3].before=x1;
    
    presents[y1].after=x2;
    presents[x2].before=y1;
    presents[x2].after=y3;
    presents[y3].before=x2;
    beltSize[mSrc]--;
    beltSize[mDst]++;
  }
  if(move2){
    if(move1==false){
      presents[y1].after=y3;
      presents[y3].before=y1;
    }

    presents[x1].after=y2;
    presents[y2].before=x1;
    presents[y2].after=x3;
    presents[x3].before=y2;
    beltSize[mSrc]++;
    beltSize[mDst]--;
  }
}
void move400(int mSrc,int mDst){
  if(beltSize[mSrc]<=1) return;
  int x1=m+mSrc;
  int x2=presents[m+mSrc].after;
  int x3=m+mSrc;
  for(int i=1;i<=beltSize[mSrc]/2;i++){
    x3=presents[x3].after;
  }
  int x4=presents[x3].after;
  int y1=m+mDst;
  int y2=presents[y1].after;
  presents[x1].after=x4;
  presents[x4].before=x1;

  presents[y1].after=x2;
  presents[x2].before=y1;
  presents[x3].after=y2;
  presents[y2].before=x3;

  beltSize[mDst]+=beltSize[mSrc]/2;
  beltSize[mSrc]-=beltSize[mSrc]/2;
}
void print(){
  for(int i=1;i<=n;i++){
    int st=m+i;
    while(st<=m+n){
      printf("%d ",st);
      st=presents[st].after;
    }
    printf("\n");
  }
  printf("\n");
}
int main(){
  cin>>q;
  for(int i=1;i<=q;i++){
    int ord,b,mSrc,mDst,num;
    cin>>ord;
    if(ord==100){
      cin>>n>>m;
      preProcess();
      for(int j=1;j<=m;j++){
        cin>>b;
        insert(m+n+b,j,b);
      }
    } else if(ord==200){
      cin>>mSrc>>mDst;
      move200(mSrc,mDst);
      cout<<beltSize[mDst]<<endl;

    } else if(ord==300){
      cin>>mSrc>>mDst;
      move300(mSrc,mDst);
      cout<<beltSize[mDst]<<endl;
    } else if(ord==400){
      cin>>mSrc>>mDst;
      move400(mSrc,mDst);
      cout<<beltSize[mDst]<<endl;
    } else if(ord==500){
      cin>>num;
      int ans=2*(presents[num].after>=m+1?-1:presents[num].after)+(presents[num].before>=m+1?-1:presents[num].before);
      cout<<ans<<endl;
    } else if(ord==600){
      cin>>num;
      int x1=m+num;
      int x2=m+num+n;
      int a=presents[x1].after;
      int b=presents[x2].before;
      if(a>=m+1) a=-1;
      if(b>=m+1) b=-1;
      cout<<a+2*b+beltSize[num]*3<<endl;
    }
    //print();
  }
  return 0;
}