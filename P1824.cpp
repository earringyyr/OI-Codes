#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    //freopen("niu.in","r",stdin);
    //freopen("niu.out","w",stdout);
    int n,c,x[100001]={0};
    int left=0,right=0;
    cin>>n>>c;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        if(x[i]>right)
            right=x[i];
    }
    sort(x+1,x+n+1);
    while(left<right)
    {
        int mid=(left+right+1)/2;
        int pan=1,sum=-1*mid,j=0;
        for(int i=1;i<=c;i++)
        {
            sum+=mid;
            j++;
            while(x[j]<sum)
            {
                j++;
                if(j>n)
                {
                    pan=0;
                    break;
                }
            }
            sum=x[j];
            if(pan==0)
                break;
        }
        if(pan==1)
            left=mid;
        else
            right=mid-1;
    }
    cout<<left;
    return 0;
}
