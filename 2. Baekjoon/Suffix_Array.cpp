#include <bits/stdc++.h>
using namespace std;
struct Comparator {
  const vector<int> &group;
  int t;
  Comparator(const vector<int> &_group, int _t): group(_group),t(_t) {};
  bool operator () (int indexA, int indexB){ // 해당 객체를 함수처럼 쓸 수 있게 해준다.
    if(group[indexA]!=group[indexB]) return group[indexA] < group[indexB];
    return group[indexA+t]<group[indexB+t]; // group[indexA]==group[indexB]이므로 적어도 t개가 앞에서부터 겹침-> s[indexA..]와 s[indexB..]의 길이는 적어도 t이상. 따라서 indexA+t<=n && indexB+t<=n. n번째 인덱스까지 접근할 수 있으므로 group[n]=-1로 세팅.
  }
};

void  countingSort(vector<int> &suffixArray, vector<int> &group, int t){
  int n=suffixArray.size();
  int sum,maxi=max(300,n+1);
  vector<int> c(maxi);
  for(int i=0;i<n;i++) c[i+t<n?group[i+t]:0]++;
  for(int i=1;i<maxi;i++) c[i]+=c[i-1];
  
  vector<int> temp(n);
  for(int i=n-1;i>=0;i--) temp[--c[suffixArray[i]+t<n?group[suffixArray[i]+t]:0]]=suffixArray[i];
  suffixArray=temp;
}

vector<int> getSuffixArray(const string &s){
  int n = s.size(), t=1; 
  vector<int> group(n+1); // group[i]=접미사들이 첫 t글자를 기준으로 정렬했을 때, s[i...]가 들어가는 그룹 번호.
  vector<int> suffixArray(n); // suffixArray[0] = i 이면 s[i..]가 사전 순으로 가장 빠르다.
  for(int i=0;i<n;i++) group[i]=s[i], suffixArray[i]=i;
  group[n]=0;
  while(t<n){
    Comparator compareUsing2T(group,t);
    // O(NlogN) std sort와 O(N) counting sort 중 선택.
    // sort(suffixArray.begin(),suffixArray.end(),compareUsing2T);
    countingSort(suffixArray,group,t); 
    countingSort(suffixArray,group,0);

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

vector<int> getLCPArray(string s, vector<int> &suffixArray){
  int n=s.size();
  vector<int> iSA(n);
  vector<int> LCP(n);

  for(int i=0;i<n;i++) iSA[suffixArray[i]]=i;
  for(int i=0,L=0;i<n;i++){
    if(iSA[i]==0) continue;
    while(i+L<n && suffixArray[iSA[i]-1]+L<n && s[i+L]==s[suffixArray[iSA[i]-1]+L]) L++;
    LCP[iSA[i]]=L;
    L=max(L-1,0);
  }

  return LCP;
}

int main(){
  string s;
  cin>>s;
  auto suffixArray=getSuffixArray(s);
  for(auto index:suffixArray)cout<<index+1<< " ";
  cout <<endl;
  
  auto LCPArray=getLCPArray(s, suffixArray);
  for(int i=0;i<LCPArray.size();i++)
    if(i==0) cout<<"x ";
    else cout<<LCPArray[i]<<" ";
}