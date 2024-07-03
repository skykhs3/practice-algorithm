//kmp problem
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string A,B;
vector<int> whereBIsIncluded; //틀린 이우 string ans라 함
void input(){
  getline(cin,A);
  getline(cin,B);
}

vector<int> getPartialMatch(string B){
  int M=(int)B.size(), matched=0;
  vector<int> pi(M, 0);

  for(int i=1;i<M;i++){
    while(matched>0 && B[matched]!=B[i]) matched=pi[matched-1];

    if(B[matched]==B[i]) pi[i]=++matched;
  }
  return pi;
}

void kmp(string A, string B){
  vector<int> pi=getPartialMatch(B);

  int match=0;
  int N = (int)A.size(), M = (int)B.size();
  for(int i=0;i<N;i++){
    while(match>0 && A[i]!=B[match])
      match=pi[match-1];

    if(A[i]==B[match])
      if(++match==M){
        whereBIsIncluded.push_back(i-match+1);
        match=pi[match-1];
      }
  }
}

void output(){
  printf("%d\n",whereBIsIncluded.size());
  for(auto a:whereBIsIncluded) printf("%d ",a+1);
}

int main(){
  input();
  kmp(A,B);
  output();
  return 0;
}