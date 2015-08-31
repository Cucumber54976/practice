// Google Template
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <deque>
#include <queue>
#include <list>
#include <map>
#include <tuple>
#include <string.h>
#include <cstring>
using namespace std;

#if 1

FILE *f;
char* of = "C:/Users/hjp/Desktop/codejam.txt";

void init() {
	f = fopen(of, "w");
}
void done() {
	fclose(f);
}


int kthCharOfGoogleString(long long k, vector<long long>& stringSize) {
    if (k == 0) {
        return 0;
    }
    int i = 1;
    for (; i < stringSize.size(); ++i) {
        if (k <= stringSize[i]) {
            break;
        }     
    }

    if (k == stringSize[i]) {
        return 0;
    }
    int c = kthCharOfGoogleString((stringSize[i] - stringSize[i-1] - 1 - 1) - (k - stringSize[i-1] - 1), stringSize);
    return c ^ 1;
}

int main(int argc, char *argv[])
{
	init();

    vector<long long> stringSize(1, 0);
    for (int i = 1; stringSize.back() < 1000000000000000000LL; ++i) {
        stringSize.push_back(2 * stringSize.back() + 1);
    }

    long long cases, k;
	scanf("%I64d", &cases);
    //cin >> cases;
	for (int c = 1; c <= cases; ++c) {
        scanf("%I64d", &k);
        //cin >> k;
        int result = kthCharOfGoogleString(k - 1, stringSize);
        fprintf(f, "Case #%d: %d\n", c, result);
        printf("Case #%d: %d\n", c, result);
	}

	done();
	system("pause");
	return 0;
}

// some one else's code
#else

FILE *f;
char* of = "C:/Users/hjp/Desktop/codejam-o.txt";

void init() {
	f = fopen(of, "w");
}
void done() {
	fclose(f);
}

////////////////////////////////////////////////

#include <iostream>
using namespace std;

int board[100][100];

int block[7][4][4][4] = {
	{
		{
			0, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 0, 0,
				0, 1, 0, 0
		},
		{
			0, 0, 0, 0,
				0, 0, 0, 0,
				0, 1, 1, 0,
				1, 1, 0, 0
			},
			{
				0, 0, 0, 0,
					1, 0, 0, 0,
					1, 1, 0, 0,
					0, 1, 0, 0
			},
			{
				0, 0, 0, 0,
					0, 0, 0, 0,
					0, 1, 1, 0,
					1, 1, 0, 0
				},
	},
	{
		{
			0, 0, 0, 0,
				0, 1, 0, 0,
				1, 1, 0, 0,
				1, 0, 0, 0
		},
		{
			0, 0, 0, 0,
				0, 0, 0, 0,
				1, 1, 0, 0,
				0, 1, 1, 0
			},
			{
				0, 0, 0, 0,
					0, 1, 0, 0,
					1, 1, 0, 0,
					1, 0, 0, 0
			},
			{
				0, 0, 0, 0,
					0, 0, 0, 0,
					1, 1, 0, 0,
					0, 1, 1, 0
				},
				},
				{
					{
						0, 0, 0, 0,
							1, 0, 0, 0,
							1, 0, 0, 0,
							1, 1, 0, 0
					},
					{
						0, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 1, 0,
							1, 1, 1, 0
						},
						{
							0, 0, 0, 0,
								1, 1, 0, 0,
								0, 1, 0, 0,
								0, 1, 0, 0
						},
						{
							0, 0, 0, 0,
								0, 0, 0, 0,
								1, 1, 1, 0,
								1, 0, 0, 0
							},
				},
				{
					{
						0, 0, 0, 0,
							0, 1, 0, 0,
							0, 1, 0, 0,
							1, 1, 0, 0
					},
					{
						0, 0, 0, 0,
							0, 0, 0, 0,
							1, 1, 1, 0,
							0, 0, 1, 0
						},
						{
							0, 0, 0, 0,
								1, 1, 0, 0,
								1, 0, 0, 0,
								1, 0, 0, 0
						},
						{
							0, 0, 0, 0,
								0, 0, 0, 0,
								1, 0, 0, 0,
								1, 1, 1, 0
							},
							},
							{
								{
									0, 0, 0, 0,
										0, 0, 0, 0,
										1, 1, 0, 0,
										1, 1, 0, 0
								},
								{
									0, 0, 0, 0,
										0, 0, 0, 0,
										1, 1, 0, 0,
										1, 1, 0, 0
									},
									{
										0, 0, 0, 0,
											0, 0, 0, 0,
											1, 1, 0, 0,
											1, 1, 0, 0
									},
									{
										0, 0, 0, 0,
											0, 0, 0, 0,
											1, 1, 0, 0,
											1, 1, 0, 0
										},
							},
							{
								{
									1, 0, 0, 0,
										1, 0, 0, 0,
										1, 0, 0, 0,
										1, 0, 0, 0
								},
								{
									0, 0, 0, 0,
										0, 0, 0, 0,
										0, 0, 0, 0,
										1, 1, 1, 1
									},
									{
										1, 0, 0, 0,
											1, 0, 0, 0,
											1, 0, 0, 0,
											1, 0, 0, 0
									},
									{
										0, 0, 0, 0,
											0, 0, 0, 0,
											0, 0, 0, 0,
											1, 1, 1, 1
										},
										},
										{
											{
												0, 0, 0, 0,
													0, 0, 0, 0,
													0, 1, 0, 0,
													1, 1, 1, 0
											},
											{
												0, 0, 0, 0,
													0, 1, 0, 0,
													1, 1, 0, 0,
													0, 1, 0, 0
												},
												{
													0, 0, 0, 0,
														0, 0, 0, 0,
														1, 1, 1, 0,
														0, 1, 0, 0
												},
												{
													0, 0, 0, 0,
														1, 0, 0, 0,
														1, 1, 0, 0,
														1, 0, 0, 0
													},
										},
};

int main() {
	init();
	int T;
	cin >> T;
	for (int cas = 1; cas <= T; cas++) {
		int W, H, N;
		cin >> W >> H >> N;
		memset(board, 0, sizeof(board));
		bool endflag = false;
		for (int b = 0; b < N; ++b) {
			int t, r, x;
			cin >> t >> r >> x;
			if (endflag) continue;
			t--;
			int h = -4;
			bool flag = true;
			while (flag) {
				h++;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						int newi = h + i;
						int newj = x + j;
						if (newi < 0 || newj >= W) {
							continue;
						}
						if (newi >= H) {
							flag = false;
							break;
						}
						if (board[newi][newj] && block[t][r][i][j])
						{
							flag = false;
							break;
						}
					}
				}
			}
			h--;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					int newi = h + i;
					int newj = x + j;
					if (block[t][r][i][j] && newi < 0) endflag = true;
					if (newi < 0 || newj >= W) continue;
					board[newi][newj] |= block[t][r][i][j];
				}
			}
			for (int i = H - 1; i >= 0;) {
				bool full = true;
				for (int j = 0; j < W; j++) {
					if (board[i][j] == 0) {
						full = false;
						break;
					}
				}
				if (!full) {
					i--;
					continue;
				}
				else {
					for (int j = i; j > 0; j--) {
						memcpy(board[j], board[j - 1], sizeof(board[j]));
					}
					memset(board[0], 0, sizeof(board[0]));
				}
			}

			//fprintf(f, "Step %d:\n", b + 1);
			//for (int i = 0; i < H; i++) {
			//	for (int j = 0; j < W; j++) {
			//		if (board[i][j]) {
			//			fprintf(f, "%c", 'x');
			//			cout << 'x';
			//		}
			//		else {
			//			fprintf(f, "%c", '.');
			//			cout << '.';
			//		}
			//	}
			//	fprintf(f, "\n");
			//	cout << endl;
			//}
			//fprintf(f, "\n");
		}
		fprintf(f, "Case #%d:\n", cas);
		cout << "Case #" << cas << ":" << endl;
		if (endflag) {
			fprintf(f, "Game Over!\n");
			cout << "Game Over!" << endl;
		}
		else {
			for (int i = 0; i < H; i++) {
				for (int j = 0; j < W; j++) {
					if (board[i][j]) {
						fprintf(f, "%c", 'x');
						cout << 'x';
					}
					else {
						fprintf(f, "%c", '.');
						cout << '.';
					}
				}
				fprintf(f, "\n");
				cout << endl;
			}
		}
	}
	done();
}

#endif