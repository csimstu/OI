// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define FOR(I, A, B)	for(int I = (A); I < (B); I ++)
#define REP(I, N)	FOR(I, 0, N)
#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
#define ALL(I) (I).begin(), (I).end()
#define PB(X) push_back(X)

using namespace std;

typedef long long ll;

// }}}

const int V_MAX = 10010;

struct Edge
{
	int to;
	bool able;
	Edge *next, *inv;
} edge[V_MAX * 2], *begin[V_MAX];
int color[V_MAX], capital[V_MAX];
int size[V_MAX];
vector<Edge*> son[V_MAX][3];
vector<int> ans[V_MAX];
int B, nv, colorIdx;

Edge *makeEdge(int u, int v)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u];
	e->able = true;
	return begin[u] = e;
}

void addEdge(int u, int v)
{
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inv = e2, e2->inv = e1;
}

int getSize(int u, int pre)
{
	size[u] = 1;
	for(Edge *e = begin[u]; e; e = e->next)
		if(e->able && e->to != pre)
			size[u] += getSize(e->to, u);
	return size[u];
}

void paint(int cur, int pre, int c)
{
	assert(color[cur] == -1);
	color[cur] = c;
	for(Edge *e = begin[cur]; e; e = e->next)
		if(e->able && e->to != pre)
			paint(e->to, cur, c);
}

void solve()
{
	int cur = 0;
	while(1)
	{
		if(size[cur] <= 3 * B)
		{
			capital[colorIdx] = cur;
			paint(cur, -1, colorIdx ++);
			break;
		}
		for(Edge *e = begin[cur]; e; e = e->next)
			if(e->able)
			{
				int v = e->to;
				if(size[v] < B)
					son[cur][0].PB(e);
				else if(size[v] <= 2 * B)
					son[cur][1].PB(e);
				else
					son[cur][2].PB(e);
			}
		int acc = 0;
		FOREACH(it, son[cur][0])
			acc += size[(*it)->to];
		if(acc < B && (int)son[cur][1].size() == 0)
		{
			assert(son[cur][2].size());
			Edge *w = son[cur][2][0];
			int tmp = size[cur];
			size[cur] = tmp - size[w->to];
			size[w->to] = tmp;
			cur = w->to;
			continue;
		}
		acc = 0;
		int pre = 0, secondColor = -1;
		FOR(i, 0, (int)son[cur][0].size())
		{
			Edge *t = son[cur][0][i];
			acc += size[t->to];
			if(acc >= B)
			{
				FOR(j, pre, i + 1)
				{
					Edge *e = son[cur][0][j];
					size[cur] -= size[e->to];
					capital[colorIdx] = cur;
					e->able = e->inv->able = false;
					paint(e->to, -1, colorIdx);
				}
				secondColor = colorIdx ++;
				acc = 0;
				pre = i + 1;
			}
		}
		FOREACH(it, son[cur][1])
		{
			capital[colorIdx] = cur;
			(*it)->able = (*it)->inv->able = false;
			paint((*it)->to, -1, secondColor = colorIdx ++);
			size[cur] -= size[(*it)->to];
		}
		assert(secondColor != -1);
		FOR(i, pre, (int)son[cur][0].size())
		{
			Edge *e = son[cur][0][i];
			e->able = e->inv->able = false;
			paint(e->to, -1, secondColor);
			size[cur] -= size[e->to];
		}
		if(son[cur][2].size() != 0)
		{
			Edge *e = son[cur][2][0];
			int tmp = size[cur];
			size[cur] = tmp - size[e->to];
			size[e->to] = tmp;
			cur = e->to;
			continue;
		}
		else
		{
			color[cur] = secondColor;
			break;
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nv, &B);
	if(nv < B)
	{
		printf("0\n");
		return 0;
	}
	REP(i, nv - 1)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u --, v --;
		addEdge(u, v);
	}
	memset(color, -1, sizeof(color));
	memset(capital, -1, sizeof(capital));
	getSize(0, -1);
	solve();
	printf("%d\n", colorIdx);
	REP(i, nv)
		printf("%d ", color[i] + 1);
	printf("\n");
	REP(i, colorIdx)
		printf("%d ", capital[i] + 1);
}
