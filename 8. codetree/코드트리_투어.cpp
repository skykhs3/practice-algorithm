// 없는 여행 상품을 삭제하는 경우에 대해 판단을 해보아야한다.
// 당황하면 꼬일 것 같다.
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Edge{
  ll to,w;
};

struct Product{
  ll id,revenue,dest,net;
  bool operator < (const Product &r)const{
    return net<r.net || (net==r.net && id>r.id);
  }
};

ll n,m;
ll oo=987654321;
vector<vector<Edge>> G(2001);
priority_queue<Product> products;
set<ll> deleted;
vector<ll> dist(2001,oo);

void changeDes(ll s){
  for(ll i=0;i<dist.size();i++)
    dist[i]=oo;
  priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> Q;
  Q.push({dist[s],s});
  dist[s]=0;

  while(!Q.empty()){
    auto temp=Q.top();Q.pop();
    ll v=temp.second;
    for(auto edge:G[v]){
      if(dist[edge.to]>dist[v]+edge.w){
        dist[edge.to]=dist[v]+edge.w;
        Q.push({dist[edge.to],edge.to});
      }
    }
  }
  
  priority_queue<Product> newProducts;
  while(!products.empty()){
    auto product=products.top();products.pop();

    if(deleted.find(product.id)==deleted.end()){
      newProducts.push({product.id,product.revenue,product.dest,product.revenue-dist[product.dest]});
    }
  }
  products=newProducts;
  deleted.clear();
}

int main(){
  ll Q;
  cin>>Q;
  for(ll q=1;q<=Q;q++){
    ll order;
    cin>>order;
    if(order==100){
      cin>>n>>m;
      for(ll i=1;i<=m;i++){
        ll v,u,w;
        cin>>v>>u>>w;
        G[v].push_back({u,w});
        G[u].push_back({v,w});
      }

      changeDes(0);
    }
    else if(order==200){
      ll id,revenue,dest;
      cin>>id>>revenue>>dest;
      if(deleted.find(id)!=deleted.end()){
        deleted.erase(id);
      }
      products.push({id,revenue,dest,revenue-dist[dest]});
    }
    else if(order==300){
      ll id;
      cin>> id;
      deleted.insert(id);
    } else if(order==400){
      bool printed=false;
      while(!products.empty()){
        auto product=products.top();
        if(deleted.find(product.id)!=deleted.end()){
          products.pop();
          continue;
        }
        if(product.net>=0){
          products.pop();
          printf("%lld\n",product.id);
          printed=true;
          break;
        }
        else{
          printf("-1\n");
          printed=true;
          break;
        }
      }
      if(printed==false) printf("-1\n");
    } else if(order==500){
      ll s;
      cin>>s;
      changeDes(s);
    }

  }
  return 0;
}