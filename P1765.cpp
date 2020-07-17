#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[26]={1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4};
int main()
{
	string b;
	int ans=0;
	getline(cin,b);
	int l=b.length();
	for(int i=0;i<l;++i)
	{
		if(b[i]!=' '&&(b[i]<'a'||b[i]>'z'))
			break;
		if(b[i]==' ')
			ans++;
		else
			ans+=a[b[i]-'a'];
	}
	cout<<ans;
	return 0;
}
