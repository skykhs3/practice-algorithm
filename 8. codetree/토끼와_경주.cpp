// long long 범위 조심.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Rabbit{
  ll pid,r=1,c=1;
  ll jump=0;
  bool operator <(const Rabbit right)const{
    if(jump!=right.jump) return jump>right.jump;
    if(r+c!=right.r+right.c) return r+c>right.r+right.c;
    if(r!=right.r) return r>right.r;
    if(c!=right.c) return c>right.c;
    return pid>right.pid;
  }
};
int dy[4]={0,1,0,-1};
int dx[4]={1,0,-1,0};
ll oo=98765432198LL;
ll n,m,p;
vector<ll> preN(200002),preM(200002);
vector<Rabbit> rabbits(2001);

priority_queue<Rabbit> Q;
ll totalScore=0;
map<ll,ll> score;
map<ll,ll> d;

pair<ll,ll> moveRabbit(ll y,ll x,ll dir,ll k){
  ll ty=y+dy[dir]*k;
  ll tx=x+dx[dir]*k;
  if(tx>m){
    tx=preM[((tx-m)%(2*(m-1))+(2*m-3))%(2*(m-1))];
    return {ty,tx};
  }else if(ty>n){
    ty=preN[((ty-n)%(2*(n-1))+(2*n-3))%(2*(n-1))];
    return {ty,tx};
  } else if(ty<=0 || tx<=0){
    pair<ll,ll> temp=moveRabbit(n+1-y,m+1-x,(dir+2)%4,k);
    return {n+1-temp.first,m+1-temp.second};
  } else{
    return {ty,tx};
  }
}
void cal(){
  ll cnt=n-1;
  ll pl=-1;
  for(ll i=0;i<preN.size();i++){
    preN[i]=cnt;
    cnt+=pl;
    if(cnt==0){
      cnt=2;
      pl=1;
    }
    else if(cnt==n+1){
      cnt=n-1;
      pl=-1;
    }
  }
  cnt=m-1;
  pl=-1;
  for(ll i=0;i<preM.size();i++){
    preM[i]=cnt;
    cnt+=pl;
    if(cnt==0){
      cnt=2;
      pl=1;
    }
    else if(cnt==m+1){
      cnt=m-1;
      pl=-1;
    }
  }
}
bool cmp(const pair<ll,ll> &left,const pair<ll,ll> &right){
  if(left.first+left.second!=right.first+right.second) return left.first+left.second < right.first+right.second;
  if(left.first!=right.first) return left.first<right.first;
  return left.second<right.second;
}
bool cmp2(const Rabbit &left,const Rabbit &right){

  if(left.r+left.c!=right.r+right.c) return left.r+left.c<right.r+right.c;
  if(left.r!=right.r) return left.r<right.r;
  if(left.c!=right.c) return left.c<right.c;
  return left.pid<right.pid;
}
int main(){
  ll q;
  cin>>q;
  for(ll qq=1;qq<=q;qq++){
    ll ord,k,s,di;
    cin>>ord;
    if(ord==100){
      cin>>n>>m>>p;
      for(ll i=1;i<=p;i++){
        cin>>rabbits[i].pid>>di;
        d[rabbits[i].pid]=di;
        Q.push(rabbits[i]);
      }

      cal();
    }
    else if(ord==200){
      cin>>k>>s;

      map<ll,Rabbit> pick;

      for(ll kk=1;kk<=k;kk++){
        
        auto rabbit=Q.top();Q.pop();
        vector<pair<ll,ll>> temp;
        ll di=d[rabbit.pid];
        
        for(int dir=0;dir<4;dir++){
          pair<ll,ll> pp=moveRabbit(rabbit.r,rabbit.c,dir,di);
          temp.push_back(pp);
        }
     
        sort(temp.begin(),temp.end(),cmp);
        
        rabbit.r=temp.back().first;
        rabbit.c=temp.back().second;
        rabbit.jump+=1;
        Q.push(rabbit);
        
        totalScore+=rabbit.r+rabbit.c;
        score[rabbit.pid]-=rabbit.r+rabbit.c; //pid 기준

        pick[rabbit.pid]=rabbit;
        //cout<<rabbit.pid<<" "<<rabbit.r<< " "<<rabbit.c<< " "<<totalScore<<endl;
      }
 

      vector<Rabbit> beforeSort;
      for(auto it:pick){
        beforeSort.push_back(it.second);
      }
      sort(beforeSort.begin(),beforeSort.end(),cmp2);

      score[beforeSort.back().pid]+=s;

    } else if(ord==300){
      ll pid,l;
      cin>>pid>>l;
      d[pid]*=l;
    } else if(ord==400){
      ll mx=-oo;
      while(!Q.empty()){
        auto rabbit=Q.top();Q.pop();
        mx=max(mx,totalScore+score[rabbit.pid]);
      }
      cout<<mx;
    }
  }
  return 0;
}