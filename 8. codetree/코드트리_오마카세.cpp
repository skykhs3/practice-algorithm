#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll l,q;
struct OriginQuery{
  ll ord;
  ll t;
  ll x;
  string name;
  ll n;
};

struct Query{
  ll type; //1:food+, 2:food-, 3:person+,4:person-;
  ll t;
  bool operator <(Query r){
    return t<r.t || (t==r.t && type<r.type);
  }
};

map<string,ll> customer;
map<string,ll> lastFood;

int main(){
  cin>>l>>q;
  vector<OriginQuery> query(q+1);
  for(ll i=1;i<=q;i++){
    cin>>query[i].ord;
    if(query[i].ord==100){
      cin>>query[i].t>>query[i].x>>query[i].name;
    }
    else if(query[i].ord==200){
      cin>>query[i].t>>query[i].x>>query[i].name>>query[i].n;
      customer[query[i].name]=i;
    }
    else if(query[i].ord==300){
      cin>>query[i].t;
    }
  }

  vector<Query> process;

  for(ll i=1;i<=q;i++){
    if(query[i].ord==100){
      ll qID=customer[query[i].name];
      ll t;
      if(query[i].t<query[qID].t){
        ll real1=query[i].x-query[i].t;
        real1=(real1%l+l)%l;
        ll real2=query[qID].x-query[qID].t;
        real2=(real2%l+l)%l;
        t=query[qID].t+((real2-real1)%l+l)%l;
      }
      else{
        ll real1=query[i].x-query[i].t;
        real1=(real1%l+l)%l;
        ll real2=query[qID].x-query[qID].t;
        real2=(real2%l+l)%l;
        ll real3=real2-(query[i].t-query[qID].t);
        real3=(real3%l+l)%l;
        t=query[i].t+((real3-real1)%l+l)%l;
      }
      process.push_back({1,query[i].t});
      process.push_back({2,t});
      if(lastFood[query[i].name]<t) lastFood[query[i].name]=t;
    }
    else if(query[i].ord==300){
      process.push_back({5,query[i].t});
    }
  }
  for(ll i=1;i<=q;i++){
    if(query[i].ord==200){
      process.push_back({3,query[i].t});
      process.push_back({4,lastFood[query[i].name]});
    }
  }
  sort(process.begin(),process.end());
  ll person=0,food=0;
  for(auto pro:process){
    if(pro.type==1) food++;
    else if(pro.type==2) food--;
    else if(pro.type==3) person++;
    else if(pro.type==4) person--;
    else if(pro.type==5) cout<<person<<" "<<food<<endl;
  }
  return 0;
}