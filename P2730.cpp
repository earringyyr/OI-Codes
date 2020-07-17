#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
int a[9],l[500000][9],huan,naive,ans,qian[500001][3],sum=0;
bool k[17000000];
void print(int d,int num)
{
    if(qian[d][1]==0)
    {
        cout<<num<<endl;
        return;
    }
    num++;
    print(qian[d][1],num);
    cout<<char(qian[d][2]+'A'-1);
    sum++;
    if(sum==60)
    {
    	sum=0;
    	cout<<endl;
    }
    return;
}
void bfs()
{
    int head=0,tail=1;
    while(head<tail)
    {
        head++;
        for(int i=1;i<=8;++i)
            a[i]=l[head][i];
        huan=a[1];
        a[1]=a[8];
        a[8]=huan;
        huan=a[2];	
        a[2]=a[7];
        a[7]=huan;
        huan=a[3];
        a[3]=a[6];
        a[6]=huan;
        huan=a[4];
        a[4]=a[5];
        a[5]=huan;
        naive=0;
        for(int i=1;i<=8;++i)
            naive=naive*8+a[i];
        if(k[naive]==0)
        {
            tail++;
            k[naive]=1;
            qian[tail][1]=head;
            qian[tail][2]=1;
            for(int i=1;i<=8;++i)
                l[tail][i]=a[i];
        }
        if(naive==ans)
        {
            print(tail,0);
            return;
        }
        for(int i=1;i<=8;++i)
            a[i]=l[head][i];
        huan=a[3];
        a[3]=a[4];
        a[4]=huan;
        huan=a[2];
        a[2]=a[3];
        a[3]=huan;
        huan=a[1];
        a[1]=a[2];
        a[2]=huan;
        huan=a[5];
        a[5]=a[6];
        a[6]=huan;
        huan=a[6];
        a[6]=a[7];
        a[7]=huan;
        huan=a[7];
        a[7]=a[8];
        a[8]=huan;
        naive=0;
        for(int i=1;i<=8;++i)
            naive=naive*8+a[i];
        if(k[naive]==0)
        {
            tail++;
            k[naive]=1;
            qian[tail][1]=head;
            qian[tail][2]=2;
            for(int i=1;i<=8;++i)
                l[tail][i]=a[i];
        }
        if(naive==ans)
        {
            print(tail,0);
            return;
        }
        for(int i=1;i<=8;++i)
            a[i]=l[head][i];
        huan=a[3];
        a[3]=a[6];
        a[6]=huan;
        huan=a[3];
        a[3]=a[7];
        a[7]=huan;
        huan=a[2];
        a[2]=a[3];
        a[3]=huan;
        naive=0;
        for(int i=1;i<=8;++i)
            naive=naive*8+a[i];
        if(k[naive]==0)
        {
            tail++;
            k[naive]=1;
            qian[tail][1]=head;
            qian[tail][2]=3;
            for(int i=1;i<=8;++i)
                l[tail][i]=a[i];
        }
        if(naive==ans)
        {
            print(tail,0);
            return;
        }
    }
}
int main()
{
    for(int i=1;i<=8;++i)
    {
    	cin>>a[i];
    	a[i]--;
    }
    naive=0;
    for(int i=1;i<=8;++i)
        naive=naive*8+a[i];
    ans=naive;
    l[1][1]=0;
    l[1][2]=1;
    l[1][3]=2;
    l[1][4]=3;
    l[1][5]=4;
    l[1][6]=5;
    l[1][7]=6;
    l[1][8]=7;
    for(int i=0;i<8;++i)
    	a[i+1]=i;
    naive=0;
    for(int i=1;i<=8;++i)
    	naive=naive*8+a[i];
    k[naive]=1;
    if(naive==ans)
    {
           print(0,0);
           return 0;
    }
    bfs();
    return 0;
}
