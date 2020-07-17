#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    b--;
    c-=2;
    cout<<min(min(a,b),c)*3+3;
    return 0;
}