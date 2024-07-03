
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

ll Answer;

ll getCount(ll l,ll r, vector<ll> &a){
  if(l>r) swap(l,r);
  return lower_bound(a.begin(),a.end(),r+1)-lower_bound(a.begin(),a.end(),l);
}

int main()
{
	ll T, test_case;
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = 0;
		
		ll n,d;
		scanf("%lld %lld",&n,&d);
    vector<ll> x(n);

		for(ll i=0;i<n;i++) scanf("%lld",&x[i]);
    sort(x.begin(),x.end());
   // for(auto y:x) printf("%d ",y);

    for(ll i=0;i<n;i++){
      ll temp=0;
      if(abs(x[i])>d) continue;
      if(x[i]>0){
      //  printf("%lld\n",d-2*x[i]);
        temp=getCount(min(0LL,-d+2*x[i]),x[i],x);}
      else{
        // printf("%lld %lld\n",x[i],d+2*x[i]);
        temp=getCount(x[i],max(0LL,d+2*x[i]),x);}
      // printf("temp:%lld\n\n",temp);
      Answer=max(Answer,temp);
    }
		
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
