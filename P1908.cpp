#include<iostream>
#include<cstdio>
using namespace std;
int n,a[40001],t[40001],num;
void nixu(int p,int q)
{
	int mid=(p+q)/2;
	if(p==q)
		return;
	nixu(p,mid);
	nixu(mid+1,q);
	int sum=p-1,l=p,r=mid+1;
	while(l<=mid||r<=q)
		if(l>mid||(a[l]>=a[r]&&r<=q))
		{
			t[++sum]=a[r++];
			num+=mid-l+1;
		}
		else
			t[++sum]=a[l++];
	for(int i=p;i<=q;++i)
		a[i]=t[i];
	return;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	nixu(1,n);
	cout<<num;
	return 0;
} 
