#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, len, cnt, sum, top;
int bo[20005], l[20005], nxt[20005];
int head[20005], num[20005], ans[20005];
int tr[20005][26];
char S[155][75], s[1000005];
struct node
{
	int v;
	int nxt;
} a[20005];
void ins(int u, int v)
{
	++sum;
	a[sum].v = v;
	a[sum].nxt = head[u];
	head[u] = sum;
	return;
}
void dfs(int k)
{
	int d = head[k];
	while (d)
	{
		dfs(a[d].v);
		num[k] += num[a[d].v];
		d = a[d].nxt;
	}
	return;
}
int main()
{
	while (scanf("%d", &n))
	{
		if (!n)
			break;
		cnt = 0;
		sum = 0;
		top = 0;
		memset(bo, 0, sizeof(bo));
		memset(tr, 0, sizeof(tr));
		memset(head, 0, sizeof(head));
		memset(num, 0, sizeof(num));
		memset(nxt, 0, sizeof(nxt));
		for (int i = 1; i <= n; ++i)
		{
			scanf("%s", S[i] + 1);
			int len = strlen(S[i] + 1), rt = 0;
			for (int j = 1; j <= len; ++j)
			{
				int k = S[i][j] - 'a';
				if (!tr[rt][k])
					tr[rt][k] = ++cnt;
				rt = tr[rt][k];
			}
			bo[rt] = i;
		}
		int hh = 0, tt = 0;
		for (int i = 0; i < 26; ++i)
			if (tr[0][i])
				l[++tt] = tr[0][i];
		while (hh < tt)
		{
			int k = l[++hh];
			for (int i = 0; i < 26; ++i)
				if (tr[k][i])
				{
					nxt[tr[k][i]] = tr[nxt[k]][i];
					l[++tt] = tr[k][i];
				}
				else
					tr[k][i] = tr[nxt[k]][i];
		}
		scanf("%s", s + 1);
		int rt = 0, len = strlen(s + 1);
		for (int i = 1; i <= len; ++i)
		{
			int k = s[i] - 'a';
			rt = tr[rt][k];
			++num[rt];
		}
		for (int i = 1; i <= cnt; ++i)
			ins(nxt[i], i);
		dfs(0);
		int maxn = 0;
		for (int i = 1; i <= cnt; ++i)
			if (bo[i])
			{
				if (num[i] > maxn)
				{
					maxn = num[i];
					top = 0;
				}
				if (num[i] == maxn)
					ans[++top] = bo[i];
			}
		sort(ans + 1, ans + top + 1);
		printf("%d\n", maxn);
		for (int i = 1; i <= top; ++i)
		{
			int len = strlen(S[ans[i]] + 1);
			for (int j = 1; j <= len; ++j)
				putchar(S[ans[i]][j]);
			putchar('\n');
		}
	}
	return 0;
}