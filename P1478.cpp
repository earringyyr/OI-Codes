#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int x,y;
}app[5001];//������¼ÿһ��ƻ���ĸ߶Ⱥ��������� 
bool camp(node a,node b)
{
	return a.y<b.y;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,s,a,b,hi,x,y,sum=0,ans=0;//sum��ʾ�����д����ƻ���ĸ��� 
	cin>>n>>s>>a>>b;
	hi=a+b;//��¼���õ���ƻ������߸߶�
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		if(x<=hi)//��������õ�ƻ��������뵽���鵱�� 
		{
			app[++sum].x=x;
			app[sum].y=y;
		} 
	} 
	sort(app+1,app+sum+1,camp);//���ķѵ�������С��������
	int i=0;//��ʾ��ǰö�ٵ��˵ڼ���ƻ�� 
	while(s>0)
	{
		s-=app[++i].y;//��ʣ��������ȥժ���ƻ����Ҫ������ 
		if(s>=0)//�������ժ�����ƻ������ô��ans++ 
			ans++;
	} 
	cout<<ans;
	return 0;
} 
