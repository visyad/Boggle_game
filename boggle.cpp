#include<bits/stdc++.h>
#include<chrono>
#include<thread>
#include"Trie.h"
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

const string dictionary="dictionary.txt";
unsigned int microsecond = 1000000;

class Boggle;
static void searchWord(int i,int j,string,Boggle*,Trie*);
class Boggle {
    public:
        int row;
        int col;
        vector<string>mat;
        vector<vector<bool>>visited;
        vector<vector<int>>dir={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
        set<string>solutions;
        Boggle(int n,int m) {
            this->row=n;
            this->col=n;
            this->mat.resize(n);
            this->visited=vector<vector<bool>>(n,vector<bool>(m));
            cout<<"Enter board values of "<<n<<" by "<<m<<endl;
            vector<string>a{"hello","onder","telad","hoatr"};
            for(int i=0;i<n;i++)
                cin>>this->mat[i];
        }
        void findSolution(Trie *root) {
            for(int i=0;i<this->row;i++)
            {
                for(int j=0;j<this->col;j++)
                    searchWord(i,j,"",this,root);
            }
        }
        void printSolution(Trie* root){
            auto sstart=chrono::high_resolution_clock::now();
            cout<<endl;
            if(solutions.size()==0)
                findSolution(root);
            if(solutions.size()!=0) {
                if(solutions.size()==1)
                    cout<<"Possible word is:"<<endl;
                else cout<<"Possible words are:"<<endl;
            }
            for(auto i:solutions)
                cout<<i<<endl;
            if(solutions.size()==0)
                cout<<"No words are found in Boggle"<<endl;
            else cout<<"Total "<<solutions.size()<<((solutions.size()==1)?(" word"):(" words"))<<" found"<<endl;
            auto eend=chrono::high_resolution_clock::now();
            long double time_taken=((chrono::duration_cast<chrono::nanoseconds>(eend - sstart).count())*(1e-9))*1000;
            cout<<"Time taken: "<<fixed<<time_taken<<setprecision(9)<<" milisecs"<<endl;
        }
        bool isValidMove(int i,int j) {
                if(i>=0 && j>=0 && i<row && j<col)
                        return true;
                return false;
        }
};
void searchWord(int i,int j,string s,Boggle* boggle,Trie* root) {
    char x=boggle->mat[i][j];
    if(root->child[x-'a']==NULL)
        return;
    s+=x;
    boggle->visited[i][j]=true;
    if(root->child[x-'a']->isLeaf)
        boggle->solutions.insert(s);
    for(int k=0;k<8;k++)
    {
            int r=i+boggle->dir[k][0];
            int c=j+boggle->dir[k][1];
            if(boggle->isValidMove(r,c) && !(boggle->visited[r][c]))
                    searchWord(r,c,s,boggle,root->child[x-'a']);
    }
    s.pop_back();
    boggle->visited[i][j]=false;
}
int main() {
    Trie* root=new Trie(dictionary);
    cout<<"Enter number of rows and cols"<<endl;
    int n,m;
    cin>>n>>m;
    Boggle board(n,m);
    board.printSolution(root);
}
