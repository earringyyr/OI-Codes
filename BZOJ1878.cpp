#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, nxt, a[50005], c[50005], vis[1000005], ans[200005];
struct node
{
	int id;
	int l;
	int r;
} w[200005];
bool cmp(node aa, node bb)
{
	return aa.r < bb.r;
}
int lowbit(int x)
{
	return x & -x;
}
void add(int x, int val)
{
	while (x <= n)
	{
		c[x] += val;
		x += lowbit(x);
	}
	return;
}
int query(int x)
{
	int ans = 0;
	while (x >= 1)
	{
		ans += c[x];
		x -= lowbit(x);
	}
	return ans;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i)
	{
		w[i].id = i;
		scanf("%d%d", &w[i].l, &w[i].r);
	}
	sort(w + 1, w + m + 1, cmp);
	nxt = 1;
	for (int i = 1; i <= m; ++i)
	{
		for (int j = nxt; j <= w[i].r; ++j)
		{
			if (vis[a[j]])
				add(vis[a[j]], -1);
			add(j, 1);
			vis[a[j]] = j;
		}
		nxt = w[i].r + 1;
		ans[w[i].id] = query(w[i].r) - query(w[i].l - 1);
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}