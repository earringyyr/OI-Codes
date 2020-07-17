#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define mod 1000000007
long long n,k,a[3][3],b[3][3],c[3][3];
void ksm()
{
        memset(b,0,sizeof(b));
        for(int i=0;i<=2;++i)
                b[i][i]=1;
        while(k>0)
        {
                if(k%2==1)
                {
                        memset(c,0,sizeof(c));
                        for(int i=0;i<=2;++i)
                                for(int j=0;j<=2;++j)
                                       for(int kk=0;kk<=2;++kk)
                                       {
                                                c[i][j]+=(a[i][kk]*b[kk][j])%mod;
                                                c[i][j]%=mod;
                            			}
                        for(int i=0;i<=2;++i)
                                for(int j=0;j<=2;++j)
                                        b[i][j]=c[i][j];
                }
                k/=2;
                memset(c,0,sizeof(c));
                for(int i=0;i<=2;++i)
                        for(int j=0;j<=2;++j)
                                for(int kk=0;kk<=2;++kk)
                                {
                                        c[i][j]+=(a[i][kk]*a[kk][j])%mod;
                                        c[i][j]%=mod;
                                }
                for(int i=0;i<=2;++i)
                     for(int j=0;j<=2;++j)
                        a[i][j]=c[i][j];
        }
        return;
}
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;++i)
    {
        cin>>n; 
        k=n-3;
        a[0][0]=0;
        a[0][1]=1;
        a[0][2]=0;
        a[1][0]=0;
        a[1][1]=0;
        a[1][2]=1;
        a[2][0]=1;
        a[2][1]=0;
        a[2][2]=1;
        ksm();
        cout<<(b[2][0]+b[2][1]+b[2][2])%mod<<endl;
    }
        return 0;
}
