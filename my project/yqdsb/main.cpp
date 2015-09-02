#include <iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#define maxn 10005
#define INF 100000
using namespace std;
int bre;
int dis[maxn][maxn];
int lca[maxn][maxn];
int user[maxn], doc[maxn];
bool vis[maxn];
int first[maxn];
int tot = 0;
int v[maxn], next1[maxn];
void add(int x, int y)
{
	v[tot] = y;
	next1[tot] = first[x];
	first[x] = tot++;
}
void dfs(int cur, int dep, int *d)
{
	d[cur] = min(d[cur], dep);
	for (int e = first[cur]; e != -1; e = next1[e])
		dfs(v[e], dep + 1,d);
}
int n, m, u, d, a;
int main()
{
	int arr[10005];
	int arr_n = 0;
	cin >> n >> m >> u >> d >> a;
	for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j)dis[i][j] = 0;
            else dis[i][j] = INF;
	memset(first, -1, sizeof(first));
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		add(y, x);
	}
	for (int i = 1; i <= u; i++)
		cin >> user[i];
	for (int i = 1; i <= d; i++)
	{
		cin >> doc[i];
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i<a; i++)
	{
		int x, y;
		char s[10];
		cin >> x >> s >> y;
		if (s[0] == 'r')
		{
			if (!vis[user[x]]){
				dfs(user[x], 0, dis[user[x]]);
				vis[user[x]] = 1;
			}
			if (!vis[doc[y]]){
				dfs(doc[y], 0, dis[doc[y]]);
				vis[doc[y]] = 1;
			}
			int pp = user[x], qq = doc[y];
			int cur = INF;
			for (int i = 1; i <= n; i++)
			{

				if (cur>dis[pp][i] + dis[qq][i])
				{
					cur = dis[pp][i] + dis[qq][i];
					user[x] = i;
				}
			}
			arr[arr_n++] = user[x];
		}
		else
		{
			if (!vis[user[x]]){
				dfs(user[x], 0, dis[user[x]]);
				vis[user[x]] = 1;
			}
			if (!vis[doc[y]]){
				dfs(doc[y], 0, dis[doc[y]]);
				vis[doc[y]] = 1;
			}
			int pp = user[x], qq = doc[y];
			int cur = INF;
			for (int i = 1; i <= n; i++)
			{

				if (cur>dis[pp][i] + dis[qq][i])
				{
					cur = dis[pp][i] + dis[qq][i];
					doc[y] = i;
				}
			}
			arr[arr_n++] = doc[y];
		}
	}
	for (int i = 0; i<arr_n; i++) cout << arr[i] << endl;
	return 0;
}
