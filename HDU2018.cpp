#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	 int n,la=1,f[56]={0};
	 f[1]=1;
	 while(1)
	 {
	 	cin>>n;
	 	if(n==0)
	 		break;
	 	for(int i=la;i<=n;i++)
	 	{
	 		f[i]+=f[i-1];
	 		if(i>=4)
	 		{
	 			f[i]+=f[i-3];
	 		}
	 		else
	 		{
	 			if(i!=1)
	 				f[i]+=f[1];
	 		}
	 	}
	 	la=n+1;
	 	cout<<f[n]<<endl;
	 }
	return 0;
} 
