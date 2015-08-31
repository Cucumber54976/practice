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


struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
 
struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};


class Solution {
public:
    /**
     * @param intervals: An interval array
     * @return: Count of airplanes are in the sky.
     */
    int countOfAirplanes(vector<Interval> &airplanes) {
        // write your code here
        sort(airplanes.begin(), airplanes.end(), [](const Interval &a, const Interval &b) -> bool { return a.start < b.start;});
        priority_queue<int, vector<int>, less<int> > Q;
		return 0;
    }
    
};




int main(int argc, char* argv[]) {
	priority_queue<int, vector<int>, greater<int> > Q;
	Q.push(1); Q.push(2);
	cout << Q.top() << endl;

	return 0;
	Solution s;
	
	string str;
	vector<Interval> intervalvec;
	vector<Point> pointarr;
	vector< vector<char> > mat;
	vector< int > vec;
	vector< int > vec2;
	vector< string > strvec;
	unordered_set<string> strset;
	ListNode r(0);
	int intervalarr[][2] = {{0,9},{5,4},{0,12},{6,9},{6,5},{0,4},{4,11},{0,0},{3,5},{6,7},{3,12},{0,5},{6,13},{7,5},{3,6},{4,4},{0,8},{3,1},{4,6},{6,1},{5,12},{3,8},{7,0},{2,9},{1,4},{3,0},{1,13},{2,13},{6,0},{6,4},{0,13},{0,3},{7,4},{1,8},{5,5},{5,7},{5,10},{5,3},{6,10},{6,2},{3,10},{2,7},{1,12},{5,0},{4,5},{7,13},{3,2}};
	int arr[] = {-1,4,-2,3,-2,3};
	int arr2[] = {1,3,2,5,6,4};
	char *strarr[] = {"fooo","barr","wing","ding","wing"};
	char arr2d[][2] = {{'O', 'O'}, {'O', 'O'}};
	//char *strarr[] = {"hot","dot","dog","lot","log"};
	int v = 1;
	int matRows = 2;
	int matCols = 2;
	for (int i = 0; i < matRows; i++) {
		mat.push_back( vector<char>() );
		for (int j = 0; j < matCols; j++) {
			mat[i].push_back(arr2d[i][j]);
		}
	}
	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
		vec.push_back(arr[i]);
	}
	for (int i = 0; i < sizeof(intervalarr) / sizeof(int) / 2; ++i) {
		intervalvec.push_back(Interval(intervalarr[i][0], intervalarr[i][1]));
		pointarr.push_back(Point(intervalarr[i][0], intervalarr[i][1]));
	}
	for (int i = 0; i < sizeof(arr2) / sizeof(int); ++i) {
		vec2.push_back(arr2[i]);
	}
	for (int i = 0; i < sizeof(strarr) / sizeof(char*); ++i) {
		strvec.push_back(strarr[i]);
		strset.insert(strarr[i]);
	}
	
	ListNode* ite = &r;
	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i, ite = ite->next) {
		ite->next = new ListNode(arr[i]);
	}
	r.next = new ListNode(1);	r.next->next = r.next;
	
	char board[][10] = {".........","......3..","...18....","...7.....","....1.97.",".........","...36.1..",".........",".......2."};
	vector< vector<char> > sudo;
	for (int i = 0; i < 9; ++i) {
		sudo.push_back(vector<char>());
		for (int j = 0; j < 9; ++j) {
			sudo.back().push_back(board[i][j]);
		}
	}
	vector< vector<char> > charmat(1, vector<char>(2, '1'));
	charmat[0][0] = '0';

	
	cout << 0 << endl;
	
	//for (int i = 0; i < ret.size(); i++) {
	//	cout << '#' << ret[i] << '#' << endl;
	//}
	//for (ListNode* ite = ret; ite != NULL; ite = ite->next) {
	//	cout << ite->val << " ";
	//}
	//for (int i = 0; i < ret.size(); ++i) {
	//	for (int j = 0; j < ret[0].size(); ++j) {
	//		cout << ret[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	return 0;
}
