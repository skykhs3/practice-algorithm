#include <bits/stdc++.h>
using namespace std;

const int ALPHABET =26;
int toNumber(char chr){
  return chr-'a';
}

struct TrieNode{
  vector<TrieNode*> children;
  int terminal;
  TrieNode* fail;
  vector<int> output; // 해당 위치에서 접미사가 되는 바늘 문자열의 인덱스들.
  TrieNode() : children(ALPHABET,nullptr), terminal(-1), fail(nullptr){};
  ~TrieNode() {
    for(int i=0;i<children.size();i++)
      delete children[i];
  }

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
        child->output.push_back(child->terminal);
      q.push(child);
    }
  }
}

void ahoCorasick(string &s, TrieNode *root){
  vector<pair<int,int>> ret;
  TrieNode *state=root;
  for(int i=0;i<s.size();i++){
    int chr= toNumber(s[i]);
    while(state!=root && state->children[chr]==nullptr)
      state=state->fail;
    if(state->children[chr]) state=state->children[chr];
    for(int j=0;j<state->output.size();j++){
      cout<<"YES";
      return;
    }
  }
  cout<<"NO";
}

int main(){
  int N;
  cin>>N;
  vector<string> input(N);
  TrieNode *root = new TrieNode();
  for(int i=0;i<N;i++){
    cin>>input[i];
    root->insert(0,input[i],i);
  }
  computeFailFunc(root);

  int Q;
  string s;
  cin>>Q;
  for(int i=0;i<Q;i++){
    cin>>s;
    ahoCorasick(s,root);
    cout<<endl;
  }
  return 0;
}