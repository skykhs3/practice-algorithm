#include <bits/stdc++.h>
using namespace std;

const int ALPHABET = 126;
int toNumber(char chr){
  return (int)chr;
}

struct TrieNode{
  vector<TrieNode*> children;
  int terminal;
  TrieNode* fail;
  vector<int> output;
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
      if(child->terminal != -1)
        child->output.push_back(child->terminal);
      q.push(child);
    }
  }
}

long long ahoCorasick(string &s, TrieNode *root, vector<string> &emo){
  vector<pair<int,int>> ret;
  TrieNode *state=root;
  long long ans=0;
  int mx=-1;
  for(int i=0;i<s.size();i++){
    int chr= toNumber(s[i]);
    while(state!=root && state->children[chr]==nullptr)
      state=state->fail;
    if(state->children[chr]) state=state->children[chr];
    bool flag=false;
    for(auto index: state->output){
      int sz=emo[index].size();
      if(mx + emo[index].size()< i+1){
        flag=true;
        break;
      }
    }
    if(flag){
      mx=i;
      ans++;
    }
  }
  return ans;
}


void solve(){
  int N,M;
  string dna;
  string marker;
  TrieNode *root = new TrieNode();
  cin>>N>>M;
  if(N==0 || M==0) exit(0);
  vector<string> emo(N);
  for(int i=0;i<N;i++){
    cin>>emo[i];
    root->insert(0,emo[i],i);
  }

  computeFailFunc(root);

  cin.ignore();
  long long ans=0;
  for(int i=0;i<M;i++){
    string marker;
    getline(cin,marker);
    ans+=ahoCorasick(marker,root,emo);
  }
  cout<<ans<<endl;
  
  delete root;
}
int main(){
  // ios::sync_with_stdio(false); // I/O 성능 최적화
  // cin.tie(NULL); // I/O 성능 최적화

  for(;;){
    solve();
  }
  return 0;
}