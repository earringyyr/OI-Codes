#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, cnt, tr[300005][26], l[300005], dep[300005], vis[300005][26], nxt[300005];
long long ans, f[65][300005];
char s[10005][35];
void ins(int k)
{
	int rt = 0, len = strlen(s[k]);
	for (int i = 0; i < len; ++i)
	{
		int id = s[k][i] - 'a';
		if (!tr[rt][id])
		{
			tr[rt][id] = ++cnt;
			dep[cnt] = i;
			vis[rt][id] = 1;
		}
		rt = tr[rt][id];
	}
	return;
}
void doit()
{
	int head = 0, tail = 0;
	for (int i = 0; i < 26; ++i)
		if (tr[0][i])
			l[++tail] = tr[0][i];
	while (head < tail)
	{
		++head;
		int rt = l[head];
		for (int i = 0; i < 26; ++i)
			if (!tr[rt][i])
				tr[rt][i] = tr[nxt[rt]][i];
			else
			{
				nxt[tr[rt][i]] = tr[nxt[rt]][i];
				l[++tail] = tr[rt][i];
			}
	}
	return;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", s[i]);
		ins(i);
	}
	doit();
	for (int i = 1; i <= cnt; ++i)
		if (nxt[i])
			++ans;
	for (int i = 0; i <= cnt; ++i)
		for (int j = 0; j < 26; ++j)
			if (!vis[i][j] && tr[i][j])
				++f[1][tr[i][j]];
	for (int i = 1; i <= 30; ++i)
		for (int j = 0; j <= cnt; ++j)
		{
			ans += f[i][j];
			for (int k = 0; k < 26; ++k)
				if (dep[tr[j][k]] >= i)
					f[i + 1][tr[j][k]] += f[i][j];
		}
	printf("%lld", ans);
	return 0;
}