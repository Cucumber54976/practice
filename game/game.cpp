#include <iostream>
#include <vector>
#include <random>
using namespace std;

class GreedySnake {
public:
	bool addCandy(int r, int c) {
		if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != -1) {
			return false;
		}
		board[r][c] = -2;
		return true;
	}
	GreedySnake(vector<int> &path, int nRow, int nCol) {
		board.resize(nRow, vector<int>(nCol, -1));
		id = 0;
		for (int i = 0; i < path.size(); i += 2) {
			board[path[i]][path[i + 1]] = id++;
		}
		tailRow = path[0];	tailCol = path[1];
		headRow = path[path.size() - 2];	headCol = path[path.size() - 1];
	}
	void printBoard() {
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[0].size(); ++j) {
				printf("%4d", board[i][j]);
			}
			printf("\n");
		}
	}
	int move(int direction) {
		int nRow = board.size(), nCol = board[0].size();
		int dir[][2] = {{-1,0}, {0, 1}, {1,0}, {0,-1}};		// up, right, down, left
		int nextTailRow, nextTailCol, nextHeadRow, nextHeadCol;
		nextHeadRow = headRow + dir[direction][0];
		nextHeadCol = headCol + dir[direction][1];
		if (nextHeadRow < 0 || nextHeadRow >= nRow || nextHeadCol < 0 || nextHeadCol >= nCol) {
			return 1;	// hit boarder
		} else if ((nextHeadRow != tailRow || nextHeadCol != tailCol) && board[nextHeadRow][nextHeadCol] >= 0) {
			return 2;	// hit snake himself
		} else if (board[nextHeadRow][nextHeadCol] == -2) {
			board[nextHeadRow][nextHeadCol] = (board[headRow][headCol] + 1) % (nRow * nCol);
			headRow = nextHeadRow;	headCol = nextHeadCol;
			return 3;	// eat candy
		} else {
			board[tailRow][tailCol] = -1;
			board[nextHeadRow][nextHeadCol] = (board[headRow][headCol] + 1) % (nRow * nCol);
			if (tailRow == headRow && tailCol == headCol) {
				tailRow = nextHeadRow;	tailCol = nextHeadCol;
			} else {
				for (int d = 0; d < 4; ++d) {
					nextTailRow = tailRow + dir[d][0];
					nextTailCol = tailCol + dir[d][1];
					if (nextTailRow < 0 || nextTailRow >= nRow || nextTailCol < 0 || nextTailCol >= nCol || board[nextTailRow][nextTailCol] != (board[tailRow][tailCol] + 1) % (nRow * nCol)) {
						continue;
					}
					tailRow = nextTailRow;	tailCol = nextTailCol;
					break;
				}
			}
			headRow = nextHeadRow;		headCol = nextHeadCol;
			return 0;	// move
		}
	}

private:
	vector<vector<int> > board;
	int headRow, headCol, tailRow, tailCol;
	int id;
};

class Maze {
public:
	void generateMaze(int nRow, int nCol) {
		depthFirstGeneration(nRow, nCol);
	}
	void depthFirstGeneration(int nRow, int nCol) {
		board.resize(nRow * 2 + 1, vector<bool>(nCol * 2 + 1, false));
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> shuffle_dist(0, 1);
		vector<int> stk;
		stk.push_back(nRow * nCol / 2);
		int dir[][2] = { {2, 0}, {-2, 0}, {0, 2}, {0, -2} };
		while (!stk.empty()) {
			int r = (stk.back() / nCol) * 2 + 1, c = (stk.back() % nCol) * 2 + 1;
			stk.pop_back();

			board[r][c] = true;
			int d[4] = { 0, 1, 2, 3 };
			for (int i = 1; i < 4; ++i) {
				int t = int(shuffle_dist(mt) * (i + 1));
				swap(d[t], d[i]);
			}
			for (int i = 0; i < 4; ++i) {
				int newr = r + dir[d[i]][0], newc = c + dir[d[i]][1];
				if (newr < 0 || newr >= nRow * 2 || newc < 0 || newc >= nCol * 2 || board[newr][newc]) {
					continue;
				}
				board[(r + newr) / 2][(c + newc) / 2] = true;	// dig through wall
				stk.push_back((r / 2) * nCol + (c / 2));
				stk.push_back((newr / 2) * nCol + (newc / 2));
				break;
			}

		}
	}
	void printMaze() {
		int nRow = board.size(), nCol = board[0].size();
		for (int r = 0; r < nRow; ++r) {
			for (int c = 0; c < nCol; ++c) {
				if (board[r][c]) {
					putchar('#');
				}
				else {
					putchar(' ');
				}
			}
			putchar('\n');
		}
	}
private:
	vector<vector<bool> > board;
};

void testGreedySnake() {
	//int p[] = { 2,2, 2,3, 2,4, 2,5, 3,5, 4,5, 4,4, 4,3, 4,2 };
	//int p[] = { 2,2, 2,3, 2,4, 2,5, 3,5, 4,5, 4,4, 4,3, 4,2, 3,2 };
	int p[] = { 2,2, 2,3, 2,4, 2,5, 3,5, 4,5, 4,4, 4,3, 4,2, 4,1, 4,0 };
	vector<int> path(p, p + sizeof(p) / sizeof(int));
	GreedySnake game(path, 10, 10);
	game.addCandy(3, 0);
	game.printBoard();
	std::cout << endl << endl;
	cout << game.move(0) << endl;
	std::cout << endl << endl;
	game.printBoard();
}

void testMaze() {
	Maze m;
	m.generateMaze(20, 50);
	m.printMaze();
}

class ClearAndHappy {
public:
	ClearAndHappy() {

	}
private:

};

int main(int argc, char *argv[]) {

	return 0;
}