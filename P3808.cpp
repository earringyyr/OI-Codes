#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,nxt[1000005],ans=0,l[1000005],tr[1000005][30],bo[1000005],sum=1;
char b[1000005];
string a;
void build()
{
    int root=1,l=a.length();
    for(int i=0;i<l;++i)
    {
        if(!tr[root][a[i]-'a'+1])
            tr[root][a[i]-'a'+1]=++sum;
        root=tr[root][a[i]-'a'+1];
    }
    bo[root]++;
    return;
}
void doit()
{
    for(int i=1;i<=26;++i)
        tr[0][i]=1;
    int head=0,tail=1;
    l[1]=1;
    nxt[1]=0;
    while(head<tail)
    {
        head++;
		int k=l[head];
		for(int i=1;i<=26;++i)
			if(!tr[k][i])
				tr[k][i]=tr[nxt[k]][i];
			else
			{
				nxt[tr[k][i]]=tr[nxt[k]][i];
				l[++tail]=tr[k][i];
			}
    }
    return;
}
void find()
{
	int ll=strlen(b),u=1;
	for(int i=0;i<ll;++i)
	{
		int c=b[i]-'a'+1;
		int d=tr[u][c];
		while(d>1&&bo[d]!=-1)
		{
			ans+=bo[d];
			bo[d]=-1;
			d=nxt[d];
		}
		u=tr[u][c];
	}
	return;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a;
        build();
    }
    doit(); 
    scanf("%s",b);
    find();
    cout<<ans;
    return 0;
}
