#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	vector<int> a;
	int n,m,top=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		a.push_back(i);
	while(!a.empty())
	{
		top+=m;
		top%=a.size();
		if(top==0)
			top=a.size();
		cout<<a[top-1]<<" ";
		a.erase(a.begin()+top-1);
		top--;
	}
	return 0;
} 
