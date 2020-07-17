#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    char a[101],b[101],c[101],ans[101],yuan[101]={0};
    int pan[101]={0},sum=0;
    scanf("%s%s",a,b);
    for(int i=0;i<strlen(a);i++)
    {
        if(yuan[a[i]]==0)
        {
            yuan[a[i]]=b[i];
        }
        else
        {
            if(yuan[a[i]]!=b[i])
            {
                cout<<"Failed";
                return 0;
            }
        }
    }
    for(int i='A';i<='Z';i++)
    {
        if(pan[yuan[i]]==1)
        {
            cout<<"Failed";
            return 0;
        }
        pan[yuan[i]]=1;
    }
    scanf("%s",c);
    for(int i=0;i<strlen(c);i++)
    {
        if(yuan[c[i]]==0)
        {
            cout<<"Failed";
            return 0;
        }
        else
        {
            ans[++sum]=yuan[c[i]];
        }
    }
    for(int i=1;i<=sum;i++)
        cout<<ans[i];
    return 0;
}
