#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int f[21][21][21];
long long w(int a,int b,int c)
{ 
	if(a<=0||b<=0||c<=0)
		return 1;
	if(a>20||b>20||c>20)
	{
		if(f[20][20][20]!=0)
			return f[20][20][20];
		else
			return w(20,20,20);
	}
	if(f[a][b][c]!=0)
		return f[a][b][c];
	if(a<b&&b<c)
	{
		long long x,y,z;
		if(f[a][b][c-1]!=0)
			x=f[a][b][c-1];
		else
		{
			x=w(a,b,c-1);
			f[a][b][c-1]=x;
		}
		if(f[a][b-1][c-1]!=0)
			y=f[a][b-1][c-1];
		else
		{
			y=w(a,b-1,c-1);
			f[a][b-1][c-1]=y;
		}
		if(f[a][b-1][c]!=0)
			z=f[a][b-1][c];
		else
		{
			z=w(a,b-1,c);
			f[a][b-1][c]=z;
		}
		return x+y-z;
	}
	long long x,y,z,q;
	if(f[a-1][b][c]!=0)
		x=f[a-1][b][c];
	else
	{
		x=w(a-1,b,c);
		f[a-1][b][c]=x;
	}
	if(f[a-1][b-1][c]!=0)
		y=f[a-1][b-1][c];
	else
	{
		y=w(a-1,b-1,c);
		f[a-1][b-1][c]=y;
	}
	if(f[a-1][b][c-1]!=0)
		z=f[a-1][b][c-1];
	else
	{
		z=w(a-1,b,c-1);
		f[a-1][b][c-1]=z;
	}
	if(f[a-1][b-1][c-1]!=0)
		q=f[a-1][b-1][c-1];
	else
	{
		q=w(a-1,b-1,c-1);
		f[a-1][b-1][c-1]=q;
	}
	return x+y+z-q;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int a,b,c;
	while(cin>>a>>b>>c)
	{
		if(a!=-1&&b!=-1&&c!=-1)
		{
			long long d=w(a,b,c);
			cout<<"w("<<a<<","<<b<<","<<c<<")"<<"="<<d<<endl;
		}
		else
			break;
	} 
	return 0;
}
