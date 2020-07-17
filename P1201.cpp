#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	string ming,name[11];
	int qian[11]={0},a,b,n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>name[i];
	while(cin>>ming)
	{
		cin>>a>>b;
		for(int i=1;i<=n;i++)
			if(name[i]==ming)
				qian[i]-=a;
		if(b!=0)
		{
			for(int i=1;i<=n;i++)
				if(name[i]==ming)
					qian[i]+=(a%b);
			a/=b;
			for(int i=1;i<=b;i++)
			{
				cin>>ming;
				for(int j=1;j<=n;j++)
				{
					if(name[j]==ming)
						qian[j]+=a;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<name[i]<<" "<<qian[i]<<endl;
	}
	return 0;
}
