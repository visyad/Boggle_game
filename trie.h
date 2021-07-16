#include<bits/stdc++.h>
using namespace std;

const int charSize=26;
class Trie {
    public:
        char data;
        Trie* child[charSize];
        bool isLeaf;
        Trie() {
            this->isLeaf=false;
            for(int i=0;i<charSize;i++) {
                this->child[i]=nullptr;
            }
        }
        void insert(string key) {
            Trie* temp=this;
            for(int i=0;i<key.length();i++) {
                int idx=(int)key[i]-'a';
                if(temp->child[idx]==NULL) {
                    temp->child[idx]=new Trie();
                }
                    temp=temp->child[idx];
            }
            temp->isLeaf=true;
        }
        bool search(string word) {
            Trie* temp = this;
            for(int i=0;i<word.length();i++) {
                int idx=(int)word[i]-'a';
                if(temp->child[idx]==NULL)
                    return false;
                temp=temp->child[idx];
            }
            if(temp!=NULL && temp->isLeaf)
                return true;
            return false;
        }
        bool haveChildren(Trie const* curr) {
            for(int i=0;i<charSize;i++)
            {
                if(curr->child[i])
                    return true;
            }
            return false;
        }
        bool deleteTrie(Trie*& curr,string key) {
            if(curr==NULL) {
                return false;
            }
            if(key.length()) {
                if(curr!=NULL && curr->child[key[0]]!=NULL && deleteTrie(curr->child[key[0]],key.substr(1)) && curr->isLeaf==false) {
                    if(!haveChildren(curr)) {
                        delete curr;
                        curr=NULL;
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            }
            if(key.length()==0 && curr->isLeaf) {
                if(!haveChildren(curr)) {
                    delete curr;
                    curr=NULL;
                    return true;
                }
                else {
                    curr->isLeaf=false;
                    return false;
                }
            }
            return false;
        }
        Trie(string filename) {
            fstream file;
            file.open(filename,ios::in);
            if(file.is_open()) {
                string line;
                int cnt=0;
                while(getline(file,line)) {
                    if(line.size()==0)
                        continue;
                    this->insert(line);
                    cnt++;
                }
                file.close();
                if(cnt==0)
                    cout<<"No words found in "<<filename<<endl;
                else if(cnt==1)
                    cout<<"1 word is initialized in the Trie"<<endl;
                else cout<<cnt<<" words are initialized in the Trie"<<endl;
            }
            else{
                cout<<"Error occurred while Opening "<<filename<<endl;
            }
        }
};
