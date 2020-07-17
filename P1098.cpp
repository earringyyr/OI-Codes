#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int p1,p2,p3,sum=0;
	char a[101];//b[100001];
	cin>>p1>>p2>>p3;
	gets(a);
	gets(a);
	int l=strlen(a);
	for(int i=0;i<l;i++)
	{
		if(a[i]!='-'||i==0||i==l-1)
			cout<<a[i];//	b[++sum]=a[i];
		else
		{
			if(a[i+1]<=a[i-1]||(a[i+1]>='a'&&a[i+1]<='z'&&a[i-1]<'a')||(a[i+1]>='A'&&a[i+1]<='Z'&&a[i-1]<'A')||a[i-1]=='-'||a[i+1]=='-')
				cout<<a[i];//	b[++sum]=a[i];
			else
			{
		//		if(a[i+1]-a[i]==1)
		//			continue;
				if(p3==1)
				{
					if(p1==1)
					{
						if(a[i-1]>='0'&&a[i-1]<='9')
						{
							for(int j=a[i-1]+1;j<a[i+1];j++)
								for(int x=1;x<=p2;x++)
									cout<<char(j);//	b[++sum]=char(j);
						}
						else
						{
							if(a[i-1]>='a'&&a[i-1]<='z')
							{
								for(int j=a[i-1]+1;j<a[i+1];j++)
									for(int x=1;x<=p2;x++)
										cout<<char(j);//	b[++sum]=char(j);
							}
							else
							{
								for(int j=a[i-1]+1;j<a[i+1];j++)
									for(int x=1;x<=p2;x++)
										cout<<char(j+32);//	b[++sum]=char(j+32);
							}
						}
					}
					if(p1==2)
					{
						if(a[i-1]>='0'&&a[i-1]<='9')
						{
							for(int j=a[i-1]+1;j<a[i+1];j++)
								for(int x=1;x<=p2;x++)
									cout<<char(j);//	b[++sum]=char(j);
						}
						else
						{
							if(a[i-1]>='a'&&a[i-1]<='z')
							{
								for(int j=a[i-1]+1;j<a[i+1];j++)
									for(int x=1;x<=p2;x++)
										cout<<char(j-32);	//b[++sum]=char(j-32);
							}
							else
							{
								for(int j=a[i-1]+1;j<a[i+1];j++)
									for(int x=1;x<=p2;x++)
										cout<<char(j);//	b[++sum]=char(j);
							}
						}
					}
					if(p1==3)
					{
						for(int j=a[i-1]+1;j<a[i+1];j++)
							for(int x=1;x<=p2;x++)
								cout<<'*';//	b[++sum]='*';
					}
				}
				else
				{
					if(p1==1)
					{
						if(a[i-1]>='0'&&a[i-1]<='9')
						{
							for(int j=a[i+1]-1;j>a[i-1];j--)
								for(int x=1;x<=p2;x++)
									cout<<char(j);//	b[++sum]=char(j);
						}
						else
						{
							if(a[i-1]>='a'&&a[i-1]<='z')
							{
								for(int j=a[i+1]-1;j>a[i-1];j--)
									for(int x=1;x<=p2;x++)
										cout<<char(j);//	b[++sum]=char(j);
							}
							else
							{
								for(int j=a[i+1]-1;j>a[i-1];j--)
									for(int x=1;x<=p2;x++)
										cout<<char(j+32);//	b[++sum]=char(j+32);
							}
						}
					}
					if(p1==2)
					{
						if(a[i-1]>='0'&&a[i-1]<='9')
						{
							for(int j=a[i+1]-1;j>a[i-1];j--)
								for(int x=1;x<=p2;x++)
										cout<<char(j);//	b[++sum]=char(j);
						}
						else
						{
							if(a[i-1]>='a'&&a[i-1]<='z')
							{
								for(int j=a[i+1]-1;j>a[i-1];j--)
									for(int x=1;x<=p2;x++)
										cout<<char(j-32);//	b[++sum]=char(j-32);
							}
							else
							{
								for(int j=a[i+1]-1;j>a[i-1];j--)
									for(int x=1;x<=p2;x++)
										cout<<char(j);//	b[++sum]=char(j);
							}
						}
					}
					if(p1==3)
					{
						for(int j=a[i+1]-1;j>a[i-1];j--)
							for(int x=1;x<=p2;x++)
								cout<<'*';//	b[++sum]='*';
					}
				}	
			}
		}
	}
//	for(int i=1;i<=sum;i++)
//		cout<<b[i];
	return 0;
} 
