#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int kid[1000001],size[250001],zu[250002][3],invite[1000001],use[250001],pa[250001];
int main()
{
	int n,g,sum=0,ans,daan=100000000;
    cin>>n>>g; 
    for(int i=1;i<=g;i++)
    {
        cin>>size[i];
        for(int j=1;j<=size[i];j++)
        {
            cin>>kid[++sum];
        } 
        zu[i][1]=zu[i-1][2]+1;
        zu[i][2]=zu[i-1][2]+size[i];
    } 
    ans=0; 
	invite[1]=1;
    int pan;
    do
    {
        pan=0;
        for(int k=1;k<=g;k++)
        {
            if(use[k]==0)
            {
                int len=0;
                for(int j=zu[k][1];j<=zu[k][2];j++)
                    if(invite[kid[j]]==1)
                        len++;
                if(len==size[k]-1)
                {
                    use[k]=1;
                    pan=1;
                    for(int j=zu[k][1];j<=zu[k][2];j++)
                        invite[kid[j]]=1;
                }
                if(len==size[k])
                    use[k]=1;
            }
        }
    }while(pan==1);
    for(int i=1;i<=n;i++)
    if(invite[i]==1)
  	  ans++;
    cout<<ans;
    return 0;
} 
