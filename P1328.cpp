#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,na,nb;
	int a[300],b[300];
	int ans1=0,ans2=0;
	cin>>n>>na>>nb;
	for(int i=1;i<=na;++i)
		cin>>a[i];
	for(int i=1;i<=nb;++i)
		cin>>b[i];
	for(int i=1;i<=n;++i){
		int aa=i%na,bb=i%nb;
		if(aa==0)
			aa=na;
		if(bb==0)
			bb=nb;
		if(a[aa]==b[bb])
			continue;
		if(a[aa]==0&&b[bb]==2){
			ans1++;
			continue;
		}
		if(a[aa]==0&&b[bb]==3){
			ans1++;
			continue;
		}
		if(a[aa]==1&&b[bb]==3){
			ans1++;
			continue;
		}
		if(a[aa]==2&&b[bb]==4){
			ans1++;
			continue;
		}
		if(a[aa]==3&&b[bb]==4){
			ans1++;
			continue;
		}
		if(a[aa]==1&&b[bb]==0){
			ans1++;
			continue;
		}
		if(a[aa]==2&&b[bb]==1){
			ans1++;
			continue;
		}
		if(a[aa]==3&&b[bb]==2){
			ans1++;
			continue;
		}
		if(a[aa]==4&&b[bb]==0){
			ans1++;
			continue;
		}
		if(a[aa]==4&&b[bb]==1){
			ans1++;
			continue;
		}
		ans2++;
	}
	cout<<ans1<<" "<<ans2;
	return 0;
}
