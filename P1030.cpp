#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int l,num=0;
char a[10],b[10],c[10];
void tree(int s,int e,int ss,int ee)
{
	if(s>e)
		return;
	c[++num]=b[ee];
	if(s==e)
		return;
	for(int i=s;i<=e;i++)
	{
		if(a[i]==c[num])
		{
			tree(s,i-1,ss,ss+i-s-1);
			tree(i+1,e,ss+i-s,ee-1);
			break;
		}
	}
	return;
}
int main()
{
	scanf("%s%s",a,b);
	l=strlen(a);
	tree(0,l-1,0,l-1);
	for(int i=1;i<=l;i++)
		cout<<c[i];
	return 0;
}
