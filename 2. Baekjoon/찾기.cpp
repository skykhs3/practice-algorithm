//kmp problem
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string t,p;
string ans;
void input(){
  getline(cin,t);
  getline(cin,p);
}

vector<int> getPartialMatch(string a){
  int m=a.size();
  vector<int> pi(m, 0);
  int match=0;
  for(int i=1;i<m;i++){
    while(match>0 && a[match]!=a[i]) match=pi[match-1];
    if(a[match]==a[i]) pi[i]=++match;
  }
  return pi;
}

void process(){
  vector<int> pi=getPartialMatch(p);

  int match=0;
  int n = (int)t.size(), m = (int)p.size();
  for(int i=0;i<n;i++){
    while(match>0 && t[i]!=p[match]) match=pi[match-1];
    if(t[i]==p[match]){
      match++;
      if(match==m){
        ans.push_back(i-match+1);
        match=pi[match];
      }
    }
  }
}

void output(){
  printf("%d\n",ans.size());
  for(auto a:ans) printf("%d ",a+1);
}

int main(){
  input();
  process();
  output();

  return 0;
}