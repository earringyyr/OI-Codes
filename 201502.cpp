#include<iostream>
#include<cstdio>
using namespace std;
char lei[101][101];
int zhao(int a,int b)
{
	int num=0;  
	if(lei[a+1][b]=='*') 
		num++;  
	if(lei[a+1][b-1]=='*') 
		num++; 
	if(lei[a+1][b+1]=='*') 
		num++; 
	if(lei[a][b+1]=='*') 
		num++; 
	if(lei[a][b-1]=='*') 
		num++; 
	if(lei[a-1][b]=='*') 
		num++; 
	if(lei[a-1][b-1]=='*') 
		num++; 
	if(lei[a-1][b+1]=='*') 
		num++; 
	return num;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int m,n;
	
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>lei[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(lei[i][j]=='*')
				cout<<'*';
			else
				cout<<zhao(i,j);
		}
		cout<<endl;
	}
	return 0;
}
