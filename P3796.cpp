#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,nxt[1000005],ma=0,l[1000005],tr[1000005][30],bo[1000005],num[100005],sum;
char b[1000005];
string a[200];
void build(int score)
{
    int root=1,l=a[score].length();
    for(int i=0;i<l;++i)
    {
        if(!tr[root][a[score][i]-'a'+1])
            tr[root][a[score][i]-'a'+1]=++sum;
        root=tr[root][a[score][i]-'a'+1];
    }
    bo[root]=score;
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
		while(d>1)
		{
			if(bo[d]!=0)
			{
				num[bo[d]]++;
				ma=max(ma,num[bo[d]]);
			}
			d=nxt[d];
		}
		u=tr[u][c];
	}
	return;
}
int main()
{
    while(cin>>n)
    {
    	if(n==0)
    		break;
    	sum=1;
    	ma=0;
    	memset(tr,0,sizeof(tr));
    	memset(bo,0,sizeof(bo));
    	memset(num,0,sizeof(num));
	    for(int i=1;i<=n;++i)
	    {
	        cin>>a[i];
	        build(i);
	    }
	    doit(); 
	    scanf("%s",b);
	    find();
	    cout<<ma<<endl;
	    for(int i=1;i<=n;++i)
	    	if(num[i]==ma)
	    		cout<<a[i]<<endl;
	}
    return 0;
}
