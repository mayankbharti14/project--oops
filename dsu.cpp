#include <bits/stdc++.h>
using namespace std;


class UnionFind{
  //tmeplate for applying DSU
  private:vector<int> p,rank;//p-->root of each node     rank-->height of each node
  public:
    UnionFind(int n){
      //constructor off DSU to start working with n nodes
      rank.assign(n,0);
      p.assign(n,0);
      iota(p.begin(),p.end(),0);
      //iota-->sets p[i]=i

    }
    int findSet(int i){
      //function to find the root(the ultimate daddy(after path compression)
      // of the component'i' is the part of)
      if(p[i]==i)return i;
      return (p[i]=findSet(p[i]));
    }
    bool isSameSet(int i, int j){
      //checks if i and j have common ultimate daddy(after path compression)
      //meaning i and j are part of same component or not
      return(findSet(i)==findSet(j));
    }
    void UnionSet(int i, int j){
      //connect i and j by doing proper path compression as per requirement
      //the logic followed here is, if rank of the ultimate daddy of i(x)
      //is greater than the rank of the ultimate daddy of j(y)
      //then, x is made the daddy of y making y the ultimate daddy of both x's components 
      //and y's components
      //and if the ranks are equal, you can make either of them the daddy and the rank
      //of the new daddy will increase by one
      if(!isSameSet(i,j)){
        int x= findSet(i);
        int y= findSet(j);
        if(rank[x]>rank[y])p[y]=x;
        else{
          p[x]=y;
          if(rank[x]==rank[y])rank[y]++;
        }
      }
    }
};