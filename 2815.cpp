#include<iostream>
#include<cstdio>
using namespace std;
char a[30][30];
int n=1,m=1,ren[3],dox[5]={0,1,-1,0,0},doy[5]={0,0,0,1,-1},x,y;
void bfs()
{
	int head=0,tail=1,zou[10000][3];
	zou[1][1]=ren[1];	 
	zou[1][2]=ren[2];	//��¼�ߵĵ�һ�� 
	do
	{
		int pan=0;	//�ȱ�ʾΪ��·���� 
		head++;	 
		for(int i=1;i<=4;i++)	//ö��4��· 
		{
			x=zou[head][1]+dox[i];	 
			y=zou[head][2]+doy[i];	//��ʱ��¼�ߺ��λ�� 
			if(x>=1&&x<=m&&y>=1&&y<=n&&(a[x][y]=='.'||a[x][y]=='*'))	//�ж��Ƿ����� 
			{
				pan=1;	 //���Ϊ��·���� 
				if(a[x][y]=='*')	//���������ҩ 
				{
					cout<<head+1<<endl;	//������� 
					head=tail;
					break;	//�˳����� 
				}
				tail++;	 
				zou[tail][1]=x;
				zou[tail][2]=y;	//��¼�ߵ�λ�� 
				a[x][y]='#';	//���Ϊ�߹��� 
			}
		}
		if(pan==0)	//�����·���߾����-1 
		{
			cout<<-1<<endl;
			break;
		}
	}
	while(head<tail);
}
int main()
{	
	while(m!=0||n!=0)
	{
		cin>>m>>n;
		if(m!=0||n!=0)	//�ж��Ƿ���� 
		{
			for(int i=1;i<=m;i++)
				for(int j=1;j<=n;j++)
				{
					cin>>a[i][j];	//�������� 
					if(a[i][j]=='@')	//Ѱ����ʼλ�� 
					{
						ren[1]=i;	
						ren[2]=j;	//������ʼλ�� 
					}
				}
			bfs();	//���� 
		}
	}
	return 0;
}
