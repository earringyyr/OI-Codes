#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,a[505],k=0,b[505];
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    	if(a[i]%2==1)
    		b[++k]=a[i];
    }
    sort(b+1,b+k+1);
    for(int i=1;i<=k;i++)
    {
    	if(i!=1)
    		cout<<",";
    	cout<<b[i];
	}
	return 0;
}
