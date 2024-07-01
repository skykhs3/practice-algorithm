#include <stdio.h>
#include <vector>
typedef long long ll;
using namespace std;

ll n;
vector<ll> a(100005);
vector<ll> b(100005);
vector<ll> pi(100005);
void input(){
  scanf("%lld",&n);
  for(int i=0;i<n;i++)
    scanf("%lld", &a[i]);
  for(int i=0;i<n;i++)
    scanf("%lld", &b[i]);
}
void getPi(){
  pi[0]=0;
  ll match=0;
  for(int i=1;i<n;i++){
    while(match>0 && b[match]!=b[i]) match=pi[match-1];
    if(b[match]==b[i]){
      match++;
      pi[i]=match;
    }
  }
}

void process(){
ll match=0;
  for(int i=0;i<n;i++){
    while(match>0 && b[match]!=a[i]) match=pi[match-1];
    if(b[match]==a[i]){
      match++;
    }
  }
  for(int i=match,j=0;i<n;i++,j++){
    if(b[i]!=a[j]){
      printf("NO");
      return;
    }
  }
  printf("YES");
}

int main(){
  input();
  getPi();
  process();
  return 0;
}