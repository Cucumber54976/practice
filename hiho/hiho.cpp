#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <deque>
#include <queue>
#include <list>
#include <map>
#include <stack>
#include <string.h>
#include <vector>
#include <memory>
using namespace std;

const int N = 1000001;
int val[N];
int inc[2][N], exc[2][N];

int main(int argc, const char *argv[]) {
	int segcnt, valcnt;
	//std::unique_ptr<long long[]> inc[2], exc[2], val;
	//inc[0].reset(new long long[N]);	inc[1].reset(new long long[N]);
	//exc[0].reset(new long long[N]);	exc[1].reset(new long long[N]);
	//val.reset(new long long[N]);
	while (scanf("%d%d", &segcnt, &valcnt) != EOF) {
		for (int i = 0; i < valcnt; ++i) {
			scanf("%d", &val[i]);
		}
		memset(exc[0], 0, sizeof(int) * (valcnt + 1));	exc[1][0] = 0;	inc[0][0] = 0;	inc[1][0] = 0;
		for (int s = 1; s <= segcnt; ++s) {
			int cur = s % 2, pre = (s + 1) % 2;
			inc[cur][s] = inc[pre][s-1] + val[s-1];
			exc[cur][s] = inc[cur][s];
			for (int v = s + 1; v <= valcnt; ++v) {
				inc[cur][v] = max(inc[cur][v-1], exc[pre][v-1]) + val[v-1];
				exc[cur][v] = max(exc[cur][v-1], inc[cur][v]);
			}
		}
		printf("%d\n", exc[segcnt % 2][valcnt]);
	}

	//system("PAUSE");
	return 0;
}