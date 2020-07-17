#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
map<string,int> fen,f;
string mingzi[1001];
int main()
{
    int n;
    string name;
    int fenshu[1001];
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>mingzi[i];
        cin>>fenshu[i];
    	fen[mingzi[i]]+=fenshu[i];
    }
    int ma=-0x3f3f3f,num=0;
    for(int i=1;i<=n;++i)
    {
    	if(fen[mingzi[i]]>ma)
    	{
    		ma=fen[mingzi[i]];
    		num=1;
    		name=mingzi[i];
    	}
    	if(fen[mingzi[i]]==ma&&mingzi[i]!=name)
    		num++;
    }
    if(num>1)
    {
	    for(int i=1;i<=n;++i)
	    {
	    	f[mingzi[i]]+=fenshu[i];
	    	if(f[mingzi[i]]>=ma&&fen[mingzi[i]]==ma)
	    	{
	    		cout<<mingzi[i];
	    		return 0;
	    	}
	    }
    }
    if(num==1)
    {
        cout<<name;
    }
    return 0;
}
