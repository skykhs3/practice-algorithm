#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
ll q,n,m;
map<ll,ll> mapping;
vector<ll> beltParent;
struct Box{
  ll bef,aft,id,w,beltId;
};
vector<ll> id(100001),w(100001);
vector<Box> boxes;
void o100(){
  // n 상자
  // m 벨트
  //설립
  beltParent.resize(m+1);
  for(ll i=1;i<=m;i++) beltParent[i]=i;

  boxes.resize(n+2*m+1);

  for(ll i=1;i<=n;i++){
    boxes[i]={0,0,id[i],w[i],(i-1)/(n/m)+1};
    mapping[id[i]]=i;
  }
  for(ll i=1;i<=m;i++){
    boxes[n+i].aft=(i-1)*(n/m)+1;
    boxes[(i-1)*(n/m)+1].bef=n+i;
    for(ll j=2;j<=n/m;j++){
      boxes[(i-1)*(n/m)+j].bef=(i-1)*(n/m)+j-1;
      boxes[(i-1)*(n/m)+j-1].aft=(i-1)*(n/m)+j;
    }
    boxes[n+m+i].bef=(i-1)*(n/m)+n/m;
    boxes[(i-1)*(n/m)+n/m].aft=n+m+i;
  }
}
void o200(ll w_max){
  ll ans=0;
  for(ll i=1;i<=m;i++){
    ll x1=n+i;
    ll x2=boxes[x1].aft;
    if(x2!=n+m+i){
      if(boxes[x2].w<=w_max){
        ans+=boxes[x2].w;
        ll x3=boxes[x2].aft;
        boxes[x1].aft=x3;
        boxes[x3].bef=x1;

        boxes[x2].beltId=-1;
      } else{
        ll x3=boxes[x2].aft;
        if(x3<n+m+1){
          ll x5=n+m+i,x4;
          x4=boxes[x5].bef;

          boxes[x1].aft=x3;
          boxes[x3].bef=x1;

          boxes[x4].aft=x2;
          boxes[x2].bef=x4;

          boxes[x2].aft=x5;
          boxes[x5].bef=x2;
        }
      }
    }
  }
  cout<<ans<<endl;
}
ll getBeltId(ll v){
  if(v==beltParent[v]) return v;
  return getBeltId(beltParent[v]);
}
void o300(ll r_id){
  ll idx=mapping[r_id]; // 항상 존재?
  if(idx==0){
    cout<<-1<<endl;
    return;
  }

  if(boxes[idx].beltId==-1){
    cout<<-1<<endl;
  }else{
    ll x1,x2,x3;
    x2=idx;
    x1=boxes[x2].bef;
    x3=boxes[x2].aft;

    boxes[x1].aft=x3;
    boxes[x3].bef=x1;

    cout<<r_id<<endl;
    boxes[x2].beltId=-1;
  }
}
void o400(ll f_id){
  ll idx=mapping[f_id];
  if(idx==0){
    cout<<-1<<endl;
    return;
  }
  if(boxes[idx].beltId==-1){
    cout<<-1<<endl;
  } else{
    ll x4=idx;
    ll x3=boxes[idx].bef;
    ll x1,x2,x5,x6;
    if(x3<=n){
      x1=n+getBeltId(boxes[idx].beltId);
      x6=n+m+getBeltId(boxes[idx].beltId);
      x2=boxes[x1].aft;
      x5=boxes[x6].bef;
      
      boxes[x1].aft=x4;
      boxes[x4].bef=x1;
      boxes[x5].aft=x2;
      boxes[x2].bef=x5;
      boxes[x3].aft=x6;
      boxes[x6].bef=x3;
    }
    cout<<getBeltId(boxes[idx].beltId)<<endl;
  }
}
void o500(ll b_num){
  if(beltParent[b_num]==b_num){
    for(ll i=1;i<=m;i++){
      ll next_bm=(b_num+i-1)%m+1;
      if(beltParent[next_bm]==next_bm){
        ll x1,x2,x3,x4,y1,y2;
        x1=b_num+n;
        x4=b_num+n+m;
        x2=boxes[x1].aft;
        x3=boxes[x4].bef;
        y2=next_bm+n+m;
        y1=boxes[y2].bef;
        if(x2!=x4){
          boxes[x1].aft=x4;
          boxes[x4].bef=x1;
          boxes[y1].aft=x2;
          boxes[x2].bef=y1;
          boxes[x3].aft=y2;
          boxes[y2].bef=x3;
        }
        beltParent[b_num]=next_bm;
        break;
      }
    }
    cout<<b_num<<endl;
  } else{
    cout<<-1<<endl;
  }
}
void print(){
  printf("=>\n");
  for(int i=1;i<=m;i++){
    int v=n+i;
    while(v){
      printf("%d ",boxes[v].id);
      if(v>=n+m+1) break;
      v=boxes[v].aft;
    }
    printf("\n");
  }
  printf("\n");
}
void input(){
  cin>>q;
  for(ll i=1;i<=q;i++){
    ll ord,w_max;
    cin>>ord;
    if(ord==100){
      cin>>n>>m;
      for(ll j=1;j<=n;j++) cin>>id[j];
      for(ll j=1;j<=n;j++) cin>>w[j];
      o100();

    } else if(ord==200){
      cin>>w_max;
      o200(w_max);
    } else if(ord==300){
      ll r_id;
      cin>>r_id;
      o300(r_id);
    } else if(ord==400){
      ll f_id;
      cin>>f_id;
      o400(f_id);
    } else if(ord==500){
      ll b_num;
      cin>>b_num;
      o500(b_num);
    }
   // print();
  }
}
int main(){
  input();

  return 0;
}