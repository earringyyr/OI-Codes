#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
	int b[105], n, a[105], m = 0, pan = 1;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
	{
		pan = 1;
		for (int j = 1; j <= m; j++)
			if (b[j] == a[i])
				pan = 0;
		if (pan == 1)
			b[++m] = a[i];
	}
	sort(b + 1, b + m + 1);
	cout << m;
	for (int i = 1; i <= m; i++)
		cout << b[i];
	return 0;
}
