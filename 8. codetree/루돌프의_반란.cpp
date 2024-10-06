#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m,p,c,d;
struct Deer{
  ll y,x;
};

struct Santa{
  ll y,x,score,stun=-1;
  bool isOut(){
    if(1<=y && y<=n && 1<=x && x<=n) return false;
    return true;
  }
  ll distance(ll y1,ll x1){
    return (x1-x)*(x1-x)+(y1-y)*(y1-y);
  }
};

ll mp[51][51];
ll oo=987654321;
vector<Santa> santas(31);
Deer rudolf;

ll dy8[8]={0,1,1,1,0,-1,-1,-1};
ll dx8[8]={1,1,0,-1,-1,-1,0,1};

ll dy4[4]={-1,0,1,0};
ll dx4[4]={0,1,0,-1};


void move2(ll id, ll nextY,ll nextX, ll dy,ll dx, ll turn, ll ss){
  santas[id].score+=ss;
  santas[id].stun=turn+1;
  ll ty=nextY+dy*ss;
  ll tx=nextX+dx*ss;
  while(true){
    if(!(1<=ty && ty<=n && 1<=tx && tx<=n)){
      santas[id].y=ty;
      santas[id].x=tx;
      break;
    }else{
      if(mp[ty][tx]>0){
        ll newId=mp[ty][tx];
            
        santas[id].y=ty;
        santas[id].x=tx;
        mp[ty][tx]=id;

        id=newId;
        ty+=dy;
        tx+=dx;
      }
      else{
        santas[id].y=ty;
        santas[id].x=tx;
        mp[ty][tx]=id;
        break;
      }
    }
  }
}
int main(){
  cin>>n>>m>>p>>c>>d;

  cin>>rudolf.y>>rudolf.x;
  mp[rudolf.y][rudolf.x]=-1;

  for(ll i=1;i<=p;i++){
    ll num;
    cin>>num;
    cin>>santas[num].y>>santas[num].x;
    mp[santas[num].y][santas[num].x]=num;
  }

  for(ll turn=1;turn<=m;turn++){
    // printf("turn:%lld\n\n",turn);
    ll mn=oo,mxi,mxj,v,sum=0;
    for(ll i=1;i<=p;i++){
      if(santas[i].isOut()){
        sum++;
        continue;
      }
      if(santas[i].distance(rudolf.y,rudolf.x)<mn ||
      (santas[i].distance(rudolf.y,rudolf.x)==mn && mxi<santas[i].y) ||
      (santas[i].distance(rudolf.y,rudolf.x)==mn && mxi==santas[i].y && mxj<santas[i].x)){
        mn=santas[i].distance(rudolf.y,rudolf.x);
        v=i;
        mxi=santas[i].y;
        mxj=santas[i].x;
      }
    }
    
    
    if(sum==p) break;
    
    
    mn=oo;
    ll bestDir=-1;
    
    Santa santa=santas[v];
    for(ll i=0;i<8;i++){
      ll ty=rudolf.y+dy8[i],tx=rudolf.x+dx8[i];
      if(santa.distance(ty,tx)<mn){
       mn=santa.distance(ty,tx);
       bestDir=i;
      }
    }

    ll nextY=rudolf.y+dy8[bestDir];
    ll nextX=rudolf.x+dx8[bestDir];
    

    if(mp[nextY][nextX]>0){
      move2(mp[nextY][nextX],nextY,nextX,dy8[bestDir],dx8[bestDir],turn,c);
    }

    mp[rudolf.y][rudolf.x]=0;
    rudolf.y=nextY;
    rudolf.x=nextX;
    mp[nextY][nextX]=-1;

    // for(ll i=1;i<=n;i++,printf("\n"))
    //     for(ll j=1;j<=n;j++)
    //       printf("%2lld ",mp[i][j]);
    //   printf("\n");


    for(ll i=1;i<=p;i++){
      if(santas[i].isOut()) continue;
      if(santas[i].stun>=turn) continue;

      ll mn=santas[i].distance(rudolf.y,rudolf.x),v=-1;
      for(ll k=0;k<4;k++){
        ll ty=santas[i].y+dy4[k];
        ll tx=santas[i].x+dx4[k];
        if(1<=ty && ty<=n && 1<=tx && tx<=n && mp[ty][tx]<=0){
          ll dis=(ty-rudolf.y)*(ty-rudolf.y) + (tx-rudolf.x)*(tx-rudolf.x);
          if(mn>dis || (mn==dis && v>k)){
            mn=dis;
            v=k;
          }
        }
      }
      if(v==-1) continue;
      ll nextY=santas[i].y+dy4[v];
      ll nextX=santas[i].x+dx4[v];
     // printf("%lld %lld\n",i,v);
      
      mp[santas[i].y][santas[i].x]=0;
      if(mp[nextY][nextX]==-1){
       // printf("=>%lld %lld\n",nextY,nextX);
        move2(i,nextY,nextX,-dy4[v],-dx4[v],turn,d);
      }
      else{
        mp[nextY][nextX]=i;
        santas[i].y=nextY;
        santas[i].x=nextX;
      }

      // for(ll i=1;i<=n;i++,printf("\n"))
      //   for(ll j=1;j<=n;j++)
      //     printf("%2lld ",mp[i][j]);
      // printf("\n");
    }
    sum=0;
    for(ll i=1;i<=p;i++){
      if(santas[i].isOut()) sum++;
    }
    if(sum==p) break;
    for(ll i=1;i<=p;i++)
      if(!santas[i].isOut())
        santas[i].score++;
  }

  for(ll i=1;i<=p;i++) cout<<santas[i].score<<" ";
  return 0;
}