#include <bits/stdc++.h>
using namespace std;

const int ALPHABET =4;
int toNumber(char chr){
  if(chr=='A') return 0;
  else if(chr=='C') return 1;
  else if(chr=='G') return 2;
  else return 3;
}

struct TrieNode{
  vector<TrieNode*> children;
  int terminal;
  TrieNode* fail;
  long long output=0;
  TrieNode() : children(ALPHABET,nullptr), terminal(-1), fail(nullptr){};
  ~TrieNode() {
    for(int i=0;i<children.size();i++)
      delete children[i];
  };

  void insert(int key, string &s, int id){
    if(key>=s.size()) terminal = id;
    else{
      int next = toNumber(s[key]);
      if(children[next] == nullptr)
        children[next]= new TrieNode();
      children[next]->insert(key+1,s,id);
    }
  }
};

void computeFailFunc(TrieNode *root){
  queue<TrieNode*> q;
  root->fail=root;
  q.push(root);
  while(!q.empty()){
    TrieNode *here=q.front();
    q.pop();
    for(int edge=0;edge<ALPHABET;edge++){
      TrieNode *child=here->children[edge];
      if(!child) continue;
      if(here==root)
        child->fail=root;
      else{
        TrieNode *t = here->fail;
        while(t!=root && t->children[edge]==nullptr)
          t=t->fail;
        if(t->children[edge]) t=t->children[edge];
        child->fail=t;
      }
      child->output = child->fail->output;
      if(child->terminal !=-1)
        child->output++;
      q.push(child);
    }
  }
}

void ahoCorasick(string &s, TrieNode *root){
  vector<pair<int,int>> ret;
  TrieNode *state=root;
  long long ans=0;
  for(int i=0;i<s.size();i++){
    int chr= toNumber(s[i]);
    while(state!=root && state->children[chr]==nullptr)
      state=state->fail;
    if(state->children[chr]) state=state->children[chr];
    ans+=state->output;
  }
  cout<<ans<<endl;
}
void solve(){
  int N,M;
  string dna;
  string marker;
  TrieNode *root = new TrieNode();
  cin>>N>>M;
  cin>>marker;
  cin>>dna;
  for(int i=0;i<=M;i++){
    for(int j=i+1;j<=M;j++){
      reverse(dna.begin()+i,dna.begin()+j);
      root->insert(0,dna,i*M+j);
      reverse(dna.begin()+i,dna.begin()+j);
    }
  }
  computeFailFunc(root);
  ahoCorasick(marker,root);
  delete root;
}
int main(){
  ios::sync_with_stdio(false); // I/O 성능 최적화
  cin.tie(0); // I/O 성능 최적화

  int T;
  cin>>T;
  for(int i=1;i<=T;i++){
    solve();
  }
  return 0;
}