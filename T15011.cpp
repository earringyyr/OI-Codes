#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long f[101][101][101]={0};
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    int a[101],b[101],c[101],l,j,k,t;
    cin>>l>>j>>k;
    for(int i=l;i>=1;i--)
        cin>>a[i];
    for(int i=j;i>=1;i--)
        cin>>b[i];
    for(int i=k;i>=1;i--)
        cin>>c[i];
    for(int x=0;x<=l;x++)
        for(int y=0;y<=j;y++)
            for(int z=0;z<=k;z++)
            {
                t=x+y+z;	
                if(x>=1)
                    f[x][y][z]=max(f[x][y][z],f[x-1][y][z]+a[x]*t);
                if(y>=1)
  					f[x][y][z]=max(f[x][y][z],f[x][y-1][z]+b[y]*t);
  				if(z>=1)
    				f[x][y][z]=max(f[x][y][z],f[x][y][z-1]+c[z]*t);
            }
    cout<<f[l][j][k];
    return 0;
}
