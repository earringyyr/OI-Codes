#include<iostream>
using namespace std;
int b[20],n,a[20],pan;
void zhishu(int x,int y)
{
	int z;
	pan=1;
	z=x+y;
	for(int i=2;i<=z/2+1;i++)
	{
		if(z%i==0)
			pan=0;
	}
	return;
}
int search(int k)
{
	for(int i=2;i<=n;i++) 
	{
		if(a[i]==0)
		{
			b[k]=i;
			if(k==n)
				zhishu(b[k],1);
			else
				zhishu(b[k],b[k-1]);
			if(pan==1)
			{
				a[i]=1;
				if(k==n)
				{
					for(int j=1;j<=k;j++)
						cout<<b[j]<<" ";
					cout<<endl;
				}
				else
					search(k+1);
				a[i]=0;
			}
		}
	}
} 
int main()
{
    cin>>n;
    b[1]=1;
	search(2); 
	return 0;
}
