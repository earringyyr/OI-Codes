#include <iostream>
#include <cstdio>
using namespace std;
int x, y;
void exgcd(int a, int b)
{
	if (b == 0)
	{
		x = 1;
		b = 0;
		return;
	}
	exgcd(b, a % b);
	int lin = x;
	x = y;
	y = lin + a / b * y;
	return;
}
int main()
{
	int a, b;
	cin >> a >> b;
	exgcd(a, -b);
	while (x < 0)
		x += b;
	x %= b;
	cout << x;
	return 0;
}
