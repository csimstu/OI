#include <cstdio>
#include <algorithm>
using namespace std;

int n;
struct Song {
	int l, p;
	bool operator< (const Song &T) const {
		return p*l*(100-T.p) > T.p*T.l*(100-p);
	}
} song[55555];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d%d", &song[i].l, &song[i].p);
	sort(song+1, song+1+n);
	double acc = 0, ans = 0;
	for ( int i = n; i >= 1; i -- ) {
		ans += song[i].p/100.0*acc*song[i].l+song[i].l;
		acc += 1.0-song[i].p/100.0;
	}
	printf("%.10lf\n", ans);
}
