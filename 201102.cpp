#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("testdata.in","r",stdin);
	//freopen("testdata.out","w",stdout);
	bool ge=true,deng,have=false;
	char ci[11],wen[1000001];
	int wei,num=0,l;
	cin>>ci;
	gets(wen);
	gets(wen);
	l=strlen(wen); 
	for(int i=0;i<l;i++)
	{
		if((i==0||wen[i-1]==' ')&&(wen[i]==ci[0]||wen[i]==char(int(ci[0])+32)||wen[i]==char(int(ci[0])-32)))
		{	
			deng=true;
			if(i+strlen(ci)<=l)
			{
				for(int j=1;j<strlen(ci);j++)
				{
					if(wen[i+j]!=ci[j]&&wen[i+j]!=char(int(ci[j])+32)&&wen[i+j]!=char(int(ci[j])-32))
						deng=false;
				}
				if(deng==true&&(i+strlen(ci)==l||wen[i+strlen(ci)]==' '))
				{
					have=true;
					num++;
					if(ge)
					{
						wei=i;
						ge=false;
					}
					i+=strlen(ci);
					i=i-1;
				}
			}
		}
	}
	if(have)
		cout<<num<<" "<<wei;
	else
		cout<<-1;
	return 0;
}
