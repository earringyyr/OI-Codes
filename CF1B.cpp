#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int t=1;t<=n;++t)
	{
		char a[100];
		scanf("%s",a);
		int l=strlen(a),p=0;
		if(a[0]=='R'&&a[1]>='0'&&a[1]<='9')
			for(int i=2;i<l;++i)
				if(a[i]=='C')
				{
					p=1;
					break;
				}
		if(p==1)
		{
			int c=0,d=0,len;
			for(int i=1;i<l;++i)
			{
				if(a[i]=='C')
				{
					len=i+1;
					break;
				}
				c=c*10+int(a[i]-'0');
			}
			for(int i=len;i<l;++i)
				d=d*10+int(a[i]-'0');
			int k[100];
			int num=0;
			while(d>26)
			{
				k[++num]=d%26;
				d/=26;
				if(k[num]==0)
				{
					k[num]=26;
					d--;
				}
			}
			k[++num]=d;
			for(int i=num;i>=1;--i)
				cout<<char(k[i]+'A'-1);
			cout<<c;       
			cout<<endl;
		}
		else//R228C494
		{
			int len;
			for(int i=0;i<l;++i)	
				if(a[i]>='0'&&a[i]<='9')
				{
					len=i;
					break;
				}
			int c=0;
			for(int i=len;i<l;++i)
				c=c*10+int(a[i]-'0');
			len--;
			cout<<'R'<<c<<'C';
			int num=1,sum=0;
			for(int i=len;i>=0;--i)
			{
				int k=int(a[i]-'A'+1);
				sum+=num*k;
				num*=26;
			}
			cout<<sum<<endl;
		}
	}
	return 0;
} 
