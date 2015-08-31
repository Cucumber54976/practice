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
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <stack>
#include <string.h>
#include <vector>
using namespace std;

const int N = 200;
const int M = 200;
int matrix[N + 2][M + 2];
int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void fill_matrix(int row, int col, int maxr, int maxc, int fold) {	
	deque< pair<int, int> > q;	q.push_back(make_pair(row, col));
	for (int i = 0; i < fold; ++i) {
		for (int j = 0, nj = q.size(); j < nj; ++j) {
			pair<int, int> cur = q.front();	q.pop_front();
			for (int k = 0; k < 4; ++k) {
				pair<int, int> tra = make_pair(cur.first + dir[k][0], cur.second + dir[k][1]);
				while (tra.first >= 0 && tra.first < maxr && tra.second >= 0 && tra.second < maxc
					&& matrix[tra.first][tra.second] <= 0) {
					if (matrix[tra.first][tra.second] == 0) {
						matrix[tra.first][tra.second] = -(i + 1);
						q.push_back(make_pair(tra.first, tra.second));
					}
					tra.first += dir[k][0];
					tra.second += dir[k][1];
				}
			}
		}
	}
}


int main(int argc, const char *argv[]) {
	const int a = 10;
	int *p = (int *) (&a);
	*p = 20;
	cout << "a=" << a << "; *p=" << *p;

	system("PAUSE");
	return 0;
}