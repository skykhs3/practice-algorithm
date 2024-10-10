#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAX_VALUE_TO_HANDLE_ASCII = 300;

struct Comparator {
  const vector<int> &group;
  int t;
  Comparator(const vector<int> &_group, int _t): group(_group),t(_t) {};
  bool operator () (int indexA, int indexB){ // Allows this object to be used as a function
    if(group[indexA]!=group[indexB]) return group[indexA] < group[indexB];
    return group[indexA+t]<group[indexB+t];
    // Since group[indexA] == group[indexB], there is at least an overlap of t characters from the start.
    // Thus, the lengths of s[indexA..] and s[indexB..] are at least t.
    // In other words, indexA + t <= n and indexB + t <= n.
    // To handle the case where the index is n, set group[n] = -1.
  }
};

void countingSort(vector<int> &suffixArray, vector<int> &group, int t){
  int n=suffixArray.size();
  int sum,maxi=max(MAX_VALUE_TO_HANDLE_ASCII,n+1);
  // group can range from 0 to n. Consider the array bounds carefully.
  vector<int> c(maxi);
  for(int i=0;i<n;i++) c[i+t<n?group[i+t]:0]++;
  for(int i=1;i<maxi;i++) c[i]+=c[i-1];

  vector<int> temp(n);
  for(int i=n-1;i>=0;i--) temp[--c[suffixArray[i]+t<n?group[suffixArray[i]+t]:0]]=suffixArray[i];
  suffixArray=temp;
}

vector<int> getSuffixArray(const string &s){
  int n = s.size(), t=1;
  vector<int> group(n+1);
  // group[i] = the group number that s[i...] belongs to when sorted by the first t characters.
  vector<int> suffixArray(n);
  // suffixArray[0] = i means s[i..] is the lexicographically smallest.
  for(int i=0;i<n;i++) group[i]=s[i], suffixArray[i]=i;
  group[n]=0;
  while(t<n){
    Comparator compareUsing2T(group,t);
    // Choose between O(NlogN) quick sort and O(N) counting sort.
    // sort(suffixArray.begin(),suffixArray.end(),compareUsing2T);
    countingSort(suffixArray,group,t); countingSort(suffixArray,group,0);

    t*=2;
    if(t>=n) break;

    vector<int> newGroup(n+1);
    newGroup[n]=0;
    newGroup[suffixArray[0]]=1;

    for(int i=1;i<n;i++)
      if(compareUsing2T(suffixArray[i-1],suffixArray[i]))
        newGroup[suffixArray[i]]=newGroup[suffixArray[i-1]]+1;
      else
        newGroup[suffixArray[i]]=newGroup[suffixArray[i-1]];
    group=newGroup;
  }

  return suffixArray;
}

vector<int> getLcpArray(string s, vector<int> &suffixArray){
  int n=s.size();
  vector<int> iSA(n);
  vector<int> LCP(n);

  for(int i=0;i<n;i++) iSA[suffixArray[i]]=i;
  for(int i=0,L=0;i<n;i++){
    if(iSA[i]==0) continue;
    while(i+L<n && suffixArray[iSA[i]-1]+L<n
      && s[i+L]==s[suffixArray[iSA[i]-1]+L]) L++;
    LCP[iSA[i]]=L;
    L=max(L-1,0);
  }

  return LCP;
}

int main(){
  freopen("input.txt","r",stdin);
  string s;
  cin>>s;
  auto SA=getSuffixArray(s);
  auto LCP=getLcpArray(s,SA);
  ll n=s.size();
  ll ans=n*(n+1)/2;

  for(auto num:LCP){
    ans-=num;
  }
  printf("%lld",ans);
}
