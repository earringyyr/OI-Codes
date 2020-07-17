#include<iostream>
using namespace std;
int b[100000],l,s,t,m,stone[200],num=-1,mins=300,wei[100000];
int jishu(int k)
{
	if(stone[wei[k]]==2)
		num++;
	k=b[k];
	if(k>1)
		jishu(k);
}
void bfs()
{
	int head=0,tail=1;
	wei[1]=0;
	do
	{
		head++;
		int pan=0;
		if(wei[head]==l)
			head=tail;
		else
		{
		for(int i=s;i<=t;i++)
		{
			if(stone[wei[head]+i]==0)
			{
				pan=1;
				tail++;
				b[tail]=head;
				wei[tail]=wei[head]+i;
					if(stone[wei[tail]]==0)
				stone[wei[tail]]=1;
			}	
			if(wei[tail]==l)
			{
				num=0;
				jishu(tail);
			}
			if(num<mins&&num!=-1)
				mins=num;
		}
		if(pan==0)
			{
				tail++;
				wei[tail]=wei[head]+t;
				b[tail]=head;
				if(stone[wei[tail]]==0)
				stone[wei[tail]]=1;
			}
		}
	}
	while(head<tail);
}
int main()
{
	int a;
	cin>>l>>s>>t>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a;
		stone[a]=2;
	}
	bfs();
	cout<<mins;
	return 0;
} 
