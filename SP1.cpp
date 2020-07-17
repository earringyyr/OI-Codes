#include<iostream>
int main()
{
	int a;
	while(std::cin>>a)
	{
		if(a==42)
			return 0;
		std::cout<<a<<std::endl;
	}
} 
