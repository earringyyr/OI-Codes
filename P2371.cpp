#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define inf 1000000000000000
#define int long long
using namespace std;
int n, mi, sum, b_mi, b_ma, ans, aa[20], head[500005], s[500005], vis[500005];
struct node
{
	int v;
	int w;
	int next;
} a[6000005];
struct point
{
	int id;
	int d;
	bool operator<(point bb) const
	{
		return d > bb.d;
	}
	point(int aaa, int bbb)
	{
		id = aaa;
		d = bbb;
	}
};
priority_queue<point> q;
void ins(int u, int v, int w)
{
	++sum;
	a[sum].v = v;
	a[sum].w = w;
	a[sum].next = head[u];
	head[u] = sum;
	return;
}
void dijkstra()
{
	fill(s, s + 500005, inf);
	s[0] = 0;
	q.push(point(0, 0));
	while (!q.empty())
	{
		point k = q.top();
		q.pop();
		if (vis[k.id])
			continue;
		vis[k.id] = 1;
		int d = head[k.id];
		while (d)
		{
			if (!vis[a[d].v] && s[a[d].v] > s[k.id] + a[d].w)
			{
				s[a[d].v] = s[k.id] + a[d].w;
				q.push(point(a[d].v, s[a[d].v]));
			}
			d = a[d].next;
		}
	}
	return;
}
signed main()
{
	scanf("%lld%lld%lld", &n, &b_mi, &b_ma);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", &aa[i]);
		mi = (i == 1 ? aa[i] : min(mi, aa[i]));
	}
	for (int i = 0; i < mi; ++i)
		for (int j = 1; j <= n; ++j)
			ins(i, (i + aa[j]) % mi, aa[j]);
	dijkstra();
	for (int i = 0; i < mi; ++i)
		if (s[i] != inf)
		{
			int ans1, ans2;
			if (b_mi - s[i] - 1 < 0)
				ans1 = 0;
			else
				ans1 = (b_mi - s[i] - 1) / mi + 1;
			if (b_ma - s[i] < 0)
				ans2 = 0;
			else
				ans2 = (b_ma - s[i]) / mi + 1;
			ans = ans + ans2 - ans1;
		}
	printf("%lld", ans);
	return 0;
}
