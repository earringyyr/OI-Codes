#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char c[501],d[501];
int a[501],b[501],ans[505],len;
void splus()
{
	for(int i=len;i>=1;i--)
	{
		ans[i]=(a[i]+b[i])%10;
		a[i-1]+=(a[i]+b[i])/10;
	}
	if(a[0]>0)
		cout<<a[0];
	for(int i=1;i<=len;i++)
		cout<<ans[i];
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	//gets(c);
	//gets(d);
	scanf("%s",c);
	scanf("%s",d); 
	len=max(strlen(c),strlen(d));
	for(int i=len-strlen(c)+1;i<=len;i++)
		a[i]=int(c[i-len+strlen(c)-1]-'0');
	for(int i=len-strlen(d)+1;i<=len;i++)
		b[i]=int(d[i-len+strlen(d)-1]-'0');
	splus();
	return 0;
}
