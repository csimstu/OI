#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int oo = 0x3f3f3f3f;
int n, m;
int c[10010], f[10010][110], s[10010][110];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &c[i]);
	memset(f, 0x3f, sizeof(f));
	memset(s, 0x3f, sizeof(s));
	f[0][0] = 0;
	memset(s[0], 0, sizeof(s[0]));
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= min(i, m - 1); j ++)
		{
			f[i][j] = min(f[i][j], s[i - j][min(m - j, i - j)] + c[i]);
			if(j == 0)
				s[i][j] = min(s[i][j], f[i][j]);
			else
				s[i][j] = min(s[i][j], min(s[i][j - 1], f[i][j]));
		}
	int ans = oo;
	for(int j = n - m + 1; j <= n; j ++)
		for(int k = j; k <= n; k ++)
			ans = min(ans, f[k][k - j]);
	printf("%d\n", ans);
}
