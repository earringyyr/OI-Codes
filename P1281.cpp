#include<iostream>
#include<cstdio>
using namespace std;
int num,ma,f[501][501],a[501],qian[501][501],b[501],sheng;
int m,k;
void print(int kk,int d)
{
    if(kk==0)
    	return;
    int head,tail;
    tail=d-1;
    int sum=0,num=0;
    while(sum<=ma&&d>=1&&num-1<=sheng)
    {
    	num++;
    	sum+=b[--d];
    }
    sheng-=num-2;
    d++;
    head=d;
    print(kk-1,d);
    cout<<head<<" "<<tail<<endl;
}
int main()
{
    cin>>m>>k;
    for(int i=1;i<=m;++i)
    {
        cin>>a[i];
        b[i]=a[i];
        a[i]+=a[i-1];
    }
    for(int i=1;i<=m;++i)
    	f[1][i]=a[i];
    for(int i=2;i<=k;++i)
        for(int j=1;j<=m;++j)
        {
            f[i][j]=0x3f3f3f;
             for(int kk=0;kk<=j;++kk)
             	if(f[i][j]>max(f[i-1][kk],a[j]-a[kk]))
	                f[i][j]=max(f[i-1][kk],a[j]-a[kk]);
        }
	ma=f[k][m];
	sheng=m-k;
    print(k,m+1);
    return 0;
} 
