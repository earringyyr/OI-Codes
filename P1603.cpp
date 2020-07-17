#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	string a;
	int c[7],sum=0; 
	for(int i=1;i<=6;i++)
	{
		int b=0;
		cin>>a;
			if(a=="one")b=1;
			if(a== "two")b=2;
			if(a== "three")b=3;
			if(a== "four")b=4;
			if(a== "five")b=5;
			if(a== "six")b=6;
			if(a== "seven")b=7;
			if(a== "eight")b=8;
			if(a== "nine")b=9;
			if(a== "ten")b=10;
			if(a== "eleven")b=11;
			if(a== "twelve")b=12;
			if(a== "thirteen")b=13;
			if(a== "fourteen")b=14;
			if(a== "fifteen")b=15;
			if(a== "sixteen")b=16;
			if(a== "seventeen")b=17; 
			if(a== "eighteen")b=18;
			if(a== "nineteen")b=19;
			if(a== "twenty")b=20;
			if(a== "a")b=1;
			if(a== "both")b=2;
			if(a== "another")b=2;
			if(a== "first")b=1;
			if(a== "second")b=2;
			if(a== "third")b=3;
		if(b!=0)
			c[++sum]=b*b%100;
	}
	sort(c+1,c+sum+1);
	cout<<c[1];
	for(int i=2;i<=sum;i++)
	{
		if(c[i]<10)
			cout<<0<<c[i];
		else
			cout<<c[i];
	}
	return 0;
} 
