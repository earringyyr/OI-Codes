#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a[400],b,num[5],f[41][41][41][41];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1;i<=m;++i)
    {
        cin>>b;
        num[b]++;
	}	
	f[0][0][0][0]=a[1];
	for(int i=0;i<=num[1];++i)
		for(int ii=0;ii<=num[2];++ii)
			for(int iii=0;iii<=num[3];++iii)
				for(int iiii=0;iiii<=num[4];++iiii)
				{
					int k=i+ii*2+iii*3+iiii*4+1;
					if(i!=0)
					f[i][ii][iii][iiii]=max(f[i][ii][iii][iiii],f[i-1][ii][iii][iiii]+a[k]);
					if(ii!=0)
					f[i][ii][iii][iiii]=max(f[i][ii][iii][iiii],f[i][ii-1][iii][iiii]+a[k]);
					if(iii!=0)
					f[i][ii][iii][iiii]=max(f[i][ii][iii][iiii],f[i][ii][iii-1][iiii]+a[k]);
					if(iiii!=0)
					f[i][ii][iii][iiii]=max(f[i][ii][iii][iiii],f[i][ii][iii][iiii-1]+a[k]);
				}
	cout<<f[num[1]][num[2]][num[3]][num[4]];
    return 0;
}
