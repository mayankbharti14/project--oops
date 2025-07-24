#include <bits/stdc++.h>
using namespace std;

class SortingAlgos{
    public:
    auto re(auto& v){
        sort(v.begin(),v.end(),[](auto &a, auto &b){
            if(a.first!=b.first)return (a.first>b.first);
            else return(a.second<b.second);
        })
    };
};