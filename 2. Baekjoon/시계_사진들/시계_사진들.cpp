#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
vector<ll> getPartialMatch(vector<ll> &d, ll N){
    ll matched=0;
    vector<ll> pi(N,0);
    for(ll i=1;i<N;i++){
        while(matched>0 && d[matched]!=d[i]) matched=pi[matched-1];
        if(d[matched]==d[i]) pi[i]=++matched;
    }
    return pi;
}
bool kmp(vector<ll> &c,vector<ll> &d,ll N){
    ll matched=0;
    vector<ll> pi=getPartialMatch(d,N);

    for(ll i=0;i<c.size();i++){
        while(matched!=0 && d[matched]!=c[i]) matched=pi[matched-1];

    //    printf("%lld %lld %lld %lld\n",i,matched,d[matched],c[i]);
        if(d[matched]==c[i]) {
            ++matched;
            if(matched==N){
                return true;
                matched=pi[matched-1];
            }

        }
    }
    return false;
}
int main(){
  //  freopen("input.txt","r",stdin);
    ll n;
    scanf("%lld",&n);
    vector<ll> a(n),b(n);
    for(ll i=0;i<n;i++){
        scanf("%lld",&a[i]);
    }
    for(ll i=0;i<n;i++){
        scanf("%lld",&b[i]);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    vector<ll> c(n),d(n);
    for(ll i=0;i<n-1;i++){
        c[i]=a[i+1]-a[i];
        d[i]=b[i+1]-b[i];
    }
    c[n-1]=a[0]+360000-a[n-1];
    d[n-1]=b[0]+360000-b[n-1];
//    for(ll i=0;i<n;i++) printf("%lld ",c[i]);
//    printf("\n");
//    for(ll i=0;i<n;i++) printf("%lld ",d[i]);
    for(ll i=0;i<n;i++){
        c.push_back(c[i]);
    }
    bool res = kmp(c,d,n);
    if(res) printf("possible");
    else printf("impossible");
}
