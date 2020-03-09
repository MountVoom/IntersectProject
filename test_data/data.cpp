#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
using namespace std;
const int maxn = 1e5 + 10;
mt19937 rnd(time(0));
int px[maxn];
double K[maxn];
int inf;

const int qwq = 200;
const int qwq2 = 100;
int main()
{
	#ifdef DEBUG
	freopen("data5.in", "w", stdout);
	#endif
	int n = rnd() % 50 + 100, m = rnd() % 300 + 1;
	for (int i = 1; i <= n; ++i) {
		px[i] = rnd() % 200 - 100;
	}
	sort(px + 1, px + n + 1);
	n = unique(px + 1, px + n + 1) - px - 1;
	printf("%d\n", n * 4 + m);
	for (int i = 1; i <= n; ++i) {
		inf = 0;
		for (int j = 1, x, y; j <= 4; ++j) {
			printf("L %d %d ", px[i], 0);
			x = rnd() % qwq - qwq2; y = rnd() % qwq - qwq2;
			while ((inf && x == px[i]) || !y) {
				x = rnd() % qwq - qwq2; y = rnd() % qwq - qwq2;
			}
			if (x == px[i]) inf = j;
			else {
				int fg = 0;
				while (!fg) {
					fg = 1;
					K[j] = 1. * y / (x - px[i]);
					for (int k = 1; fg && k < j; ++k)
						if (k != inf && fabs(K[k] - K[j]) < 1e-9)
							fg = 0;
					if (!fg) {
						y = rnd() % qwq - qwq2;
						while (!y) y = rnd() % qwq - qwq2;
					}
				}
				
			}
			printf("%d %d\n", x, y);
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("C %d %d %d\n", rnd() % qwq - qwq2, rnd() % qwq - qwq2, rnd() % 100000 + 1);
	return 0;
}

