#include <cstdio>
#include <cstdlib>
int n, seed;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++, printf("\n"))
		for(int j = 0; j < n; j ++)
			printf("%d", rand() % 5 ? 0 : 1);
}
