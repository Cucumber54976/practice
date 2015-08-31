#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <memory>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <functional>
#include <unordered_map>
#include <stack>
using namespace std;

//class AVLTree {
//private:
//	struct AVLTreeNode {
//		AVLTreeNode() : left(NIL), right(NIL), height(0), key(0), value(0) { }
//		AVLTreeNode(int h, int k, int v) : left(NIL), right(NIL), height(h), key(k), value(v) { }
//		AVLTreeNode(AVLTreeNode *l, AVLTreeNode *r, int h, int k, int v) : left(l), right(r), height(h), key(k), value(v) { }
//		int height;
//		int key, value;
//		AVLTreeNode *left, *right;
//		static AVLTreeNode *NIL;
//	};
//public:
//	AVLTree() {
//		root = AVLTreeNode::NIL;
//	}
//	AVLTree(AVLTree &toCopy) {
//		// TODO
//	}
//	virtual ~AVLTree () {
//		// TODO
//		// NOTICE: there is no loop in tree, try using unique_ptr !!!
//	}
//	string preOrder() {
//		string result;
//		preOrderVisit(root, result);
//		return result;
//	}
//	string inOrder() {
//		string result;
//		inOrderVisit(root, result);
//		return result;
//	}
//	string postOrder() {
//		string result;
//		postOrderVisit(root, result);
//		return result;
//	}
//	bool hasKey(int key) {
//		// TODO: similar code of insert, consider use an separate func for traverse !!!
//	}
//	template <typename Func>
//	void traverse(int key, Func foo) {
//		for (auto tra = root; tra != AVLTreeNode::NIL; ) {
//			foo(tra);
//			if (tra->key < key) {
//				tra = tra->right;
//			} else if (tra->key > key) {
//				tra = tra->left;
//			} else {
//				tra = AVLTreeNode::NIL;
//			}
//		}
//	}
//	bool containsKey(int key) {
//		AVLTreeNode *node = AVLTreeNode::NIL;
//		traverse(key, [&node](AVLTreeNode *tra) {node = tra;});
//		if (node == AVLTreeNode::NIL || node->key != key) {
//			return false;
//		}
//		return true;
//	}
//	bool insert(int key, int value) {
//		if (root == AVLTreeNode::NIL) {
//			root = new AVLTreeNode(1, key, value);
//			return true;
//		} 
//		AVLTreeNode *tra = root, *parent = root;
//		stack<AVLTreeNode*> stk;
//		traverse(key, [&stk](AVLTreeNode *tra) {stk.push(tra);});
//		if (stk.empty()) {}		// NOT suppose to happen
//		if (stk.top()->key == key) {
//			return false;
//		}
//		if (stk.top()->key < key) {
//			stk.top()->right = new AVLTreeNode(1, key, value);
//			stk.push(stk.top()->right);
//		} else {
//			stk.top()->left = new AVLTreeNode(1, key, value);
//			stk.push(stk.top()->left);
//		}
//		adjust(stk);
//	}
//	bool deleteKey(int key) {
//		stack<AVLTreeNode*> stk;
//		traverse(key, [&stk](AVLTreeNode *tra) {stk.push(tra);});
//		if (stk.empty() || stk.top()->key != key) {
//			return false;
//		}
//		if (stk.top()->left == AVLTreeNode::NIL && stk.top()->right == AVLTreeNode::NIL) {
//			if (stk.size() == 1) {
//				root = AVLTreeNode::NIL;
//			} else {
//				AVLTreeNode *toDelete = stk.top();	stk.pop();
//				if (stk.top()->left == toDelete) {
//					stk.top()->left = AVLTreeNode::NIL;
//				} else {
//					stk.top()->right = AVLTreeNode::NIL;
//				}
//				delete toDelete;
//				adjust(stk);
//			}
//		} else if (stk.top()->left == AVLTreeNode::NIL) {
//			AVLTreeNode *toDelete = stk.top();
//			for (AVLTreeNode *tra = stk.top()->right; tra != AVLTreeNode::NIL; tra = tra->left) {
//				stk.push(tra);
//			}
//			swap(toDelete->value, stk.top()->value);		swap(toDelete->key, stk.top()->key);	
//			toDelete = stk.top();	stk.pop();
//			if (stk.top()->left == toDelete) {
//				stk.top()->left = toDelete->right;
//			} else {
//				stk.top()->right = toDelete->right;
//			}
//			delete toDelete;
//			adjust(stk);
//		} else {
//			AVLTreeNode *toDelete = stk.top();
//			for (AVLTreeNode *tra = stk.top()->left; tra != AVLTreeNode::NIL; tra = tra->right) {
//				stk.push(tra);
//			}
//			swap(toDelete->value, stk.top()->value);		swap(toDelete->key, stk.top()->key);	
//			toDelete = stk.top();	stk.pop();
//			if (stk.top()->right == toDelete) {
//				stk.top()->right = toDelete->left;
//			} else {
//				stk.top()->left = toDelete->left;
//			}
//			delete toDelete;
//			adjust(stk);
//		}
//	}
//	void adjust(stack<AVLTreeNode*> &path) {
//		if (path.size() == 0) {
//			return;
//		}
//		AVLTreeNode *sonL, *sonR, *parrent, *temp;
//		while (!path.empty()) {
//			parrent = path.top();	path.pop();
//			sonL = parrent->left, sonR = parrent->right;
//			parrent->height = max(parrent->left->height, parrent->right->height) + 1;
//			if (abs(sonL->height - sonR->height) != 2) {		// only update the height
//				continue;
//			}
//			if (sonL->height - sonR->height == 2) {
//				if (sonL->left->height - sonR->height == 1) {
//					temp = rotateRight(parrent);
//				} else {
//					parrent->left = rotateLeft(sonL);
//					temp = rotateRight(parrent);
//				}
//			} else if (sonL->height - sonR->height == -2) {
//				if (sonR->right->height - sonL->height == 1) {
//					temp = rotateLeft(parrent);
//				} else {
//					parrent->right = rotateRight(sonR);
//					temp = rotateLeft(parrent);
//				}
//			}
//			if (path.empty()) {
//				root = temp;
//			} else if (path.top()->left == parrent) {
//				path.top()->left = temp;
//			} else {
//				path.top()->right = temp;
//			}
//		}
//	}
//
//	AVLTreeNode *rotateLeft(AVLTreeNode *r) {
//		AVLTreeNode *left = r->left, *right = r->right;
//		r->right = right->left;	
//		r->height = max(r->left->height, r->right->height) + 1;
//		right->left = r;	
//		right->height = (right->left->height, right->right->height) + 1;
//		return right;
//	}
//	AVLTreeNode *rotateRight(AVLTreeNode *r) {
//		AVLTreeNode *left = r->left, *right = r->right;
//		r->left = left->right;
//		r->height = max(r->left->height, r->right->height) + 1;
//		left->right = r;
//		left->height = max(left->left->height, left->right->height) + 1;
//		return left;
//	}
//private:
//	AVLTreeNode *root;
//	void preOrderVisit(AVLTreeNode* r, string &result) {
//		if (r == AVLTreeNode::NIL) {
//			return;
//		}
//		string number = to_string(r->key);
//		result.insert(result.end(), number.begin(), number.end());
//		result.push_back(' ');
//		preOrderVisit(r->left, result);
//		preOrderVisit(r->right, result);
//	}
//	void inOrderVisit(AVLTreeNode* r, string &result) {
//		if (r == AVLTreeNode::NIL) {
//			return;
//		}
//		inOrderVisit(r->left, result);
//		string number = to_string(r->key);
//		result.insert(result.end(), number.begin(), number.end());
//		result.push_back(' ');
//		inOrderVisit(r->right, result);
//	}
//	void postOrderVisit(AVLTreeNode* r, string &result) {
//		if (r == AVLTreeNode::NIL) {
//			return;
//		}
//		postOrderVisit(r->left, result);
//		postOrderVisit(r->right, result);
//		string number = to_string(r->key);
//		result.insert(result.end(), number.begin(), number.end());
//		result.push_back(' ');
//	}
//};
//AVLTree::AVLTreeNode* AVLTree::AVLTreeNode::NIL = new AVLTree::AVLTreeNode(NULL, NULL, 0, 0, 0);

class AVLTree {
private:
	struct Node {
		int key, value, height;
		Node *left, *right;
		Node() : key(0), value(0), height(0), left(NIL), right(NIL) { }
		Node(int key, int value, int height, Node *left, Node *right) : key(key), value(value), height(height), left(left), right(right) { }
		Node (int key, int value, int height = 1) : key(key), value(value), height(height), left(NIL), right(NIL) { }
		static Node *NIL;
	};
	Node *root;
public:
	AVLTree() {
		root = Node::NIL;
	}
	string preOrder() {
		string result;
		preOrderVisit(root, result);
		return result;
	}
	string inOrder() {
		string result;
		inOrderVisit(root, result);
		return result;
	}
	string postOrder() {
		string result;
		postOrderVisit(root, result);
		return result;
	}
	template<typename Foo>
	void find(Node *r, int key, Foo f) {
		Node *tra = root;
		for (; tra != Node::NIL; ) {
			f(tra);
			if (tra->key < key) {
				tra = tra->right;
			} else if (tra->key > key) {
				tra = tra->left;
			} else {
				break;
			}
		}
	}
	bool insert(int key, int value) {
		if (root == Node::NIL) {
			root = new Node(key, value);
		} else {
			stack<Node*> path;
			find(root, key, [&path](Node *tra) {path.push(tra);});
			if (path.top()->key == key) {
				return false;
			} else if (path.top()->key < key) {
				path.top()->right = new Node(key, value);
			} else {
				path.top()->left = new Node(key, value);
			}
			adjust(path);
		}
		return true;
	}
	bool exist(int key) {
		if (root == Node::NIL) {
			return false;
		}
		Node *result = Node::NIL;
		find(root, key, [&result](Node *tra) {result = tra;});
		if (result != Node::NIL && result->key == key) {
			return true;
		}
		return false;
	}
	bool deleteKey(int key) {
		if (root == Node::NIL) {
			return false;
		}
		stack<Node*> path;
		find(root, key, [&path](Node *tra) {path.push(tra);});
		if (path.top()->key != key) {
			return false;
		}
		Node *toDelete = path.top();
		if (toDelete->left == Node::NIL && toDelete->right == Node::NIL) {
			path.pop();
			if (path.empty()) {
				root = Node::NIL;
			} else if (path.top()->left == toDelete) {
				path.top()->left = Node::NIL;
			} else {
				path.top()->right = Node::NIL;
			}
		} else if (toDelete->left == Node::NIL) {
			if (toDelete->right->left == Node::NIL) {
				path.pop();
				if (path.empty()) {
					root = toDelete->right;
				} else if (path.top()->left == toDelete) {
					path.top()->left = toDelete->right;
				} else {
					path.top()->right = toDelete->right;
				}
			} else {
				Node * tra = toDelete->right;
				for (; tra->left != Node::NIL; tra = tra->left) {
					path.push(tra);
				}
				toDelete->key = tra->key;	
				toDelete->key = tra->key;
				toDelete = path.top();	path.pop();
				path.top()->left = toDelete->right;
			}
		} else {
			if (toDelete->left->right == Node::NIL) {
				path.pop();
				if (path.empty()) {
					root = toDelete->left;
				} else if (path.top()->left == toDelete) {
					path.top()->left = toDelete->left;
				} else {
					path.top()->right = toDelete->left;
				}
			} else {
				Node *tra = toDelete->left;
				for (; tra->right != Node::NIL; tra = tra->right) {
					path.push(tra);
				}
				toDelete->key = tra->key;
				toDelete->value = tra->value;
				toDelete = path.top();	path.pop();
				path.top()->right = toDelete->left;
			}
		}
		delete toDelete;
		adjust(path);
		return true;
	}
	void adjust(stack<Node*> &path) {
		while (!path.empty()) {
			Node *cur = path.top();	path.pop();
			cur->height = max(cur->left->height, cur->right->height) + 1;
			if (cur->left->height - cur->right->height == 2) {
				if (cur->left->left->height >= cur->left->right->height) {
					cur = rotateRight(cur);
				} else {
					cur->left = rotateLeft(cur->left);
					cur = rotateRight(cur);
				}
			} else if (cur->left->height - cur->right->height == -2) {
				if (cur->right->right->height >= cur->right->left->height) {
					cur = rotateLeft(cur);
				} else {
					cur->right = rotateRight(cur->right);
					cur = rotateLeft(cur);
				}
			}
			if (path.empty()) {
				root = cur;
			} else if (path.top()->key < cur->key) {
				path.top()->right = cur;
			} else {
				path.top()->left = cur;
			}
		}
	}
private:
	void preOrderVisit(Node* r, string &result) {
		if (r == Node::NIL) {
			return;
		}
		string number = to_string(r->key);
		result.insert(result.end(), number.begin(), number.end());
		result.push_back(' ');
		preOrderVisit(r->left, result);
		preOrderVisit(r->right, result);
	}
	void inOrderVisit(Node* r, string &result) {
		if (r == Node::NIL) {
			return;
		}
		inOrderVisit(r->left, result);
		string number = to_string(r->key);
		result.insert(result.end(), number.begin(), number.end());
		result.push_back(' ');
		inOrderVisit(r->right, result);
	}
	void postOrderVisit(Node* r, string &result) {
		if (r == Node::NIL) {
			return;
		}
		postOrderVisit(r->left, result);
		postOrderVisit(r->right, result);
		string number = to_string(r->key);
		result.insert(result.end(), number.begin(), number.end());
		result.push_back(' ');
	}
	Node *rotateLeft(Node *r) {
		Node *left = r->left, *right = r->right;
		r->right = right->left;
		right->left = r;
		r->height = max(r->left->height, r->right->height) + 1;
		right->height = max(right->left->height, right->right->height) + 1;
		return right;
	}
	Node *rotateRight(Node *r) {
		Node *left = r->left, *right = r->right;
		r->left = left->right;
		left->right = r;
		r->height = max(r->left->height, r->right->height) + 1;
		left->height = max(left->left->height, left->right->height) + 1;
		return left;
	}
};
AVLTree::Node *AVLTree::Node::NIL = new AVLTree::Node(0, 0, 0, NULL, NULL);

//class MyHashTable {
//public:
//	MyHashTable(int size) {
//		table.resize(size);
//	}
//	bool set(int key, int value) {
//		int hashVal = myHash(key) % table.size();
//		for (auto ite = table[hashVal].begin(); ite != table[hashVal].end(); ++ite) {
//			if (ite->first == key) {
//				ite->second = value;
//				return true;
//			}
//		}
//		return false;
//	}
//	bool insert(int key, int value) {
//		int hashVal = myHash(key) % table.size();
//		for (auto ite = table[hashVal].begin(); ite != table[hashVal].end(); ++ite) {
//			if (ite->first == key) {
//				return false;
//			}
//		}
//		table[hashVal].push_front(make_pair(key, value));
//		return true;
//	}
//	int getValue(int key) {
//		int hashVal = myHash(key) % table.size();
//		for (auto ite = table[hashVal].begin(); ite != table[hashVal].end(); ++ite) {
//			if (ite->first == key) {
//				return ite->second;
//			}
//		}
//		return 0;
//	}
//	int maxConflitCnt() {
//		int cnt = 0;
//		for (int i = 0; i < table.size(); ++i) {
//			cnt = max(cnt, static_cast<int>(table[i].size()));
//		}
//		return cnt;
//	}
//private:
//	vector< list<pair<int, int>> > table;
//	int myHash(int key) {
//		return ((key * key) ^ key) * HASH_FACTOR;
//	}
//	static const int HASH_FACTOR = 2654435761;
//};

class HashTable {
public:
	HashTable(int size) {
		table.resize(size, Element());
		nElementes = size;
		capacityFactor = 0.7;
	}
	bool insert(int key, int value) {
		int insertIndex = findIndex(key);
		if (insertIndex == -1
			|| table[insertIndex].state == State::OCCUPIED 
				&& table[insertIndex].key == key) {
			return false;
		}
		table[insertIndex].key = key;	table[insertIndex].value = value;	table[insertIndex].state = OCCUPIED;
		return true;
	}
	int getValue(int key) {
		int index = findIndex(key);
		if (index != -1 && table[index].state == State::OCCUPIED && table[index].key == key) {
			return table[index].value;
		}
		return 0;
	}
	bool removeByKey(int key) {
		int insertIndex = findIndex(key);
		if (insertIndex != -1 && table[insertIndex].state == State::OCCUPIED && table[insertIndex].key == key) {
			table[insertIndex].state = State::DELETED;
			return true;
		}
		return false;
	}
	// return:
	// index if key found
	// index for deleted slot or empty slot if key not found
	int findIndex(int key) {
		int h = myHash(key) % table.size(), index = -1, deletedIndex = -1, o;
		for (o = 0; o < table.size(); ++o) {
			index = (h + o) % table.size();		// TODO: other type of searching
			if (table[index].state == State::EMPTY || table[index].state == State::OCCUPIED && table[index].key == key) {
				break;
			}
			if (table[index].state == State::DELETED) {
				deletedIndex = index;
			}
		}
		if (/*LOG_LEVEL >= 1*/ true && o > 10) {
			cout << "search offset: " << o << endl;
		}
		if (o == table.size() || table[index].state == State::EMPTY && deletedIndex != -1) {		// key not found
			return deletedIndex;
		}
		return index;
	}
private:
	int myHash(int key) {
		return (key >> 19) ^ (key << 13) ^ 2654435761;
	}
	enum State {EMPTY, OCCUPIED, DELETED};
	struct Element {
		int key, value;
		enum State state;	// state = 0, empty; 1, delete; 2, occupied
		Element() : key(0), value(0), state(State::EMPTY) { }
		Element(int key, int value) : key(key), value(value), state(State::OCCUPIED) { }
	};
	vector<Element> table;
	int nElementes;
	double capacityFactor;
};

//class Trie {
//public:
//	Trie() : idEnd(1) {
//		root = new TrieNode(0, 0);
//	}
//	void insert(const string &str) {
//		root->insert(str, 0, nextTrieNode, idEnd);
//	}
//	int wordCnt(string &word) {
//		return root->count(word, 0, nextTrieNode);
//	}
//private:
//	struct TrieNode;
//	struct MyPairHash {
//		int operator() (const pair<int, char> &p) {
//			return hash<int>()(p.first) ^ hash<char>()(p.second);
//		}
//	};
//
//	unordered_map<pair<int, char>, TrieNode*, MyPairHash> nextTrieNode;
//	TrieNode *root;
//	int idEnd;
//	struct TrieNode {
//		int id;
//		char character;
//		int wordCnt;
//		void insert(const string &str, int index, unordered_map<pair<int, char>, TrieNode*, MyPairHash> &nextTrieNode, int &idEnd) {
//			if (index == str.size()) {
//				wordCnt += 1;
//				return;
//			}
//			pair<int, char> p = make_pair(id, str[index]);
//			if (nextTrieNode[p] == NULL) {
//				nextTrieNode[p] = new TrieNode(idEnd++, str[index]);
//			}
//			nextTrieNode[p]->insert(str, index + 1, nextTrieNode, idEnd);
//		}
//		int count(string &str, int index, unordered_map<pair<int, char>, TrieNode*, MyPairHash> &nextTrieNode) {
//			if (str.size() == index) {
//				return wordCnt;
//			}
//			pair<int, char> p = make_pair(id, str[index]);
//			if (nextTrieNode[p] == NULL) {
//				return 0;
//			}
//			return nextTrieNode[p]->count(str, index + 1, nextTrieNode);
//		}
//		TrieNode (int id, char character) : id(id), character(character), wordCnt(0) { }
//		TrieNode operator= (const TrieNode &x) {
//			this->id = x.id;
//			this->character = x.character;
//			this->wordCnt = x.wordCnt;
//			return *this;
//		}
//		bool operator==(const TrieNode &x) {
//			return this->id == x.id && this->character == x.character;
//		}
//		// TODO: copy constructor ...
//	};
//};

class Trie {
public:
	Trie() {
		root = new Node(0, 0);
		nodeID = 0;
		nextNode[make_pair(0, 0)] = root;
	}
	virtual ~Trie() {
		// remove all node
	}
	void insert(const string &str) {
		Node *cur = root;
		pair<int, char> index = make_pair(0, 0);
		for (int i = 0; i < str.size(); ++i) {
			index = make_pair(cur->id, str[i]);
			if (nextNode.find(index) == nextNode.end()) {
				nextNode[index] = new Node(++nodeID, str[i]);
			}
			cur = nextNode[index];
		}
		nextNode[index]->wordCnt += 1;	// counts empty string too
	}
	int countWord(const string &word) {
		Node *cur = root;
		pair<int, char> index = make_pair(0, 0);
		for (int i = 0; i < word.size(); ++i) {
			index = make_pair(cur->id, word[i]);
			if (nextNode.find(index) == nextNode.end()) {
				return 0;
			}
			cur = nextNode[index];
		}
		return nextNode[index]->wordCnt;
	}
private:
	struct Node {
		int id;
		char character;
		int wordCnt;
		Node() : id(0), character(0), wordCnt(0) { }
		Node(int id, char character) : id(id), character(character), wordCnt(0) { }
	};
	class PairHash {
	public:
		int operator() (const pair<int, char> &p) const {
			return hashInt(p.first) ^ hashChar(p.second);
		}
	private:
		hash<int> hashInt;
		hash<char> hashChar;
	};
	Node* root;
	unordered_map<pair<int, char>, Node*, PairHash> nextNode;
	int nodeID;
};

//class UnionSet {
//public:
//	UnionSet(int size) {
//		unionSet.resize(size, -1);
//	}
//	void unite(int x, int y) {
//		int px = x, py = y;
//		int heightX = 0, heightY = 0;
//		for (; unionSet[px] >= 0; px = unionSet[px], heightX++) { }
//		for (; unionSet[py] >= 0; py = unionSet[py], heightY++) { }
//		if (px == py) {		
//			return;
//		}
//		for (int tra = x, t; unionSet[tra] >= 0; ) {
//			t = unionSet[tra];
//			unionSet[tra] = px;
//			tra = t;
//		}
//		for (int tra = y, t; unionSet[tra] >= 0;) {
//			t = unionSet[tra];
//			unionSet[tra] = py;
//			tra = t;
//		}
//		unionSet[px] += unionSet[py];
//		unionSet[py] = px;
//	}
//	bool isInSameSet(int x, int y) {
//		int px = x, py = y;
//		int heightX = 0, heightY = 0;
//		for (; unionSet[px] >= 0; px = unionSet[px], heightX++) { }
//		for (; unionSet[py] >= 0; py = unionSet[py], heightY++) { }
//		if (px == py) {		
//			return true;;
//		}
//		return false;
//	}
//	int find(int s) {
//		// return top
//		return -1;
//	}
//private:
//	vector<int> unionSet;
//};

class UnionSet {
public:
	UnionSet(int size) {
		reset(size);
	}
	void reset(int size) {
		us.resize(size, -1);
	}
	void unite(int x, int y) {
		int px = findParrent(x), py = findParrent(y);
		if (px == py) {
			return;
		}
		if (-us[px] < -us[py]) {
			swap(x, y);
			swap(px, py);
		}
		us[px] += us[py];
		us[py] = px;
	}
	bool isInSameSet(int x, int y) {
		return findParrent(x) == findParrent(y);
	}
	int findParrent(int x) {
		int p = x, t;
		for (; us[p] >= 0; p = us[p]) { }
		for (; us[x] >= 0; ) {
			t = us[x];
			us[x] = p;
			x = t;
		}
		return p;
	}
private:
	vector<int> us;
};

//class SparseTable {
//public:
//	SparseTable(vector<int> &vec) {
//		reset(vec);
//	}
//	void reset(vector<int> &vec) {
//		int size = vec.size();
//		int log2size = log2(size);
//		st.resize(log2size + 1, vector<int>(size, 0));
//		copy(vec.begin(), vec.end(), st[0].begin());
//		for (int e = 1; e < st.size(); ++e) {
//			for (int i = 0; i < st[e].size(); ++i) {
//				st[e][i] = max(st[e-1][i], st[e-1][min(static_cast<int>(st[e].size())-1, i+(1<<(e-1)))]);
//			}
//		}
//	}
//	int rangeMaximumQuery(int from, int toExclusive) {
//		int log2range = log2(toExclusive - from);
//		return max(st[log2range][from], st[log2range][toExclusive - (1<<log2range)]);
//	}
//private:
//	vector< vector<int> > st;
//	int log2(int n) {
//		if (n <= 0) {
//			return -1;
//		} else if (n == 1) {
//			return 0;
//		}
//		int result = 0;
//		for (; n != 1; result += 1, n /= 2) {}
//		return result;
//	}
//};

class SparseTable {
public:
	SparseTable(vector<int> &vec) {
		int size = vec.size(), log2size = log2(size) + 1;
		table.resize(log2size, vector<int>(size, 0));
		for (int i = 0; i < size; ++i) {
			table[0][i] = vec[i];
		}
		for (int logi = 1, len = 1; logi < log2size; logi += 1, len <<= 1) {
			for (int i = 0; i < size; ++i)  {
				table[logi][i] = max(table[logi-1][i], table[logi-1][min(i+len, size-1)]);
			}
		}
	}
	int rangeMaximumQuery(int from, int to) {
		int size = to - from, log2size = log2(to - from);
		return max(table[log2size][from], table[log2size][to - (1<<log2size)]);
	}
private:
	int log2(int n) {
		if (n <= 1) {
			return 0;
		}
		int result = 0;
		for (int i = n; n > 1; n /= 2, result += 1) { }
		return result;
	}
	vector< vector<int> > table;
};

//class TreeArray {
//public:
//	TreeArray(vector<int> &vec) {
//		reset(vec);
//	}
//	void reset(vector<int> &vec) {
//		tree.resize(vec.size(), 0);
//		for (int i = 0; i < vec.size(); ++i) {
//			tree[i] = vec[i];
//			for (int endJ = lowbit(i+1), j = 1; j < endJ; j <<= 1) {
//				tree[i] += tree[i - j];
//			}
//		}
//	}
//	int sumBefore(int i) {
//		if (i == 0) {
//			return 0;
//		}
//		int sum = 0;
//		for (; i != 0; i -= lowbit(i)) {
//			sum += tree[i - 1];
//		}
//		return sum;
//	}
//	void add(int index, int val) {	
//		for (int i = index + 1; i <= tree.size(); i += lowbit(i)) {
//			tree[i-1] += val;
//		}
//	}
//private:
//	int lowbit(int n) {
//		return n & (-n);
//	}
//	vector<int> tree;
//};

class TreeArray {
public:
	TreeArray(vector<int> &vec) {
		tree.resize(vec.size(), 0);
		for (int i = 0; i < vec.size(); ++i) {
			tree[i] = vec[i];
			int lb = lowbit(i + 1);
			for (int b = 1; b < lb; b <<= 1) {
				tree[i] += tree[i - b];
			}
		}
	}
	int sumBefore(int n) {
		int result = 0;
		for (int i = n; i != 0; i -= lowbit(i)) {
			result += tree[i - 1];
		}
		return result;
	}
	void addValue(int n, int value) {
		for (int i = n + 1; i <= tree.size(); i += lowbit(i)) {
			tree[i - 1] += value;
		}
	}
private:
	vector<int> tree;
	int lowbit(int n) {
		return n & (-n);
	}
};

//class RangeTree {
//public:
//	void build(vector<int> &vec) {
//		range = vec.size();
//		rangeTree.resize(range * 4, Range());
//		subBuild(vec, 0, 0, range);
//	}
//	int queryMaximum(int from, int to) {
//		return subQueryMaximum(from, to, 0, 0, range);
//	}
//	void add(int from, int to, int value) {
//		subAdd(from, to, value, 0, 0, range);
//	}
//private:
//	int subBuild(vector<int> &vec, int treeIndex, int start, int end) {
//		if (start + 1 == end) {
//			rangeTree[treeIndex].value = vec[start];
//			return rangeTree[treeIndex].value;
//		}
//		int mid = (start + end) / 2;
//		rangeTree[treeIndex].value = subBuild(vec, treeIndex * 2 + 1, start, mid);
//		rangeTree[treeIndex].value = max(rangeTree[treeIndex].value, subBuild(vec, treeIndex * 2 + 2, mid, end));
//		return rangeTree[treeIndex].value;
//	}
//	int subQueryMaximum(int from, int to, int treeIndex, int rangeStart, int rangeEnd) {
//		updateLasy(treeIndex);
//		if (rangeStart == from && rangeEnd == to) {
//			return rangeTree[treeIndex].value;
//		}
//		int rangeMid = (rangeStart + rangeEnd) / 2;
//		if (rangeMid <= from) {
//			return subQueryMaximum(from, to, treeIndex * 2 + 2, rangeMid, rangeEnd);
//		} else if (rangeMid > from && rangeMid < to) {
//			return max(
//				subQueryMaximum(from, rangeMid, treeIndex * 2 + 1, rangeStart, rangeMid), 
//				subQueryMaximum(rangeMid, to, treeIndex * 2 + 2, rangeMid, rangeEnd));
//		} else {
//			return subQueryMaximum(from, to, treeIndex * 2 + 1, rangeStart, rangeMid);
//		}
//	}
//	int subAdd(int from, int to, int value, int treeIndex, int rangeStart, int rangeEnd) {
//		updateLasy(treeIndex);
//		if (from == rangeStart && to == rangeEnd) {
//			rangeTree[treeIndex].lasyAdd = true;
//			rangeTree[treeIndex].addValue = value;
//			rangeTree[treeIndex].value += rangeTree[treeIndex].addValue;
//			return rangeTree[treeIndex].value;
//		}
//		int rangeMid = (rangeStart + rangeEnd) / 2;
//		if (rangeMid <= from) {
//			rangeTree[treeIndex].value = max(rangeTree[treeIndex].value, subAdd(from, to, value, treeIndex * 2 + 2, rangeMid, rangeEnd));
//		} else if (rangeMid > from && rangeMid < to) {
//			rangeTree[treeIndex].value = max(rangeTree[treeIndex].value, subAdd(from, rangeMid, value, treeIndex * 2 + 1, rangeStart, rangeMid));
//			rangeTree[treeIndex].value = max(rangeTree[treeIndex].value, subAdd(rangeMid, to, value, treeIndex * 2 + 2, rangeMid, rangeEnd));
//		} else {
//			rangeTree[treeIndex].value = max(rangeTree[treeIndex].value, subAdd(from, to, value, treeIndex * 2 + 1, rangeStart, rangeMid));
//		}
//		return rangeTree[treeIndex].value;
//	}
//	void updateLasy(int treeIndex) {
//		if (!rangeTree[treeIndex].lasyAdd) {
//			return;
//		}
//		if (2 * treeIndex + 1 < rangeTree.size()) {
//			rangeTree[treeIndex * 2 + 1].lasyAdd = true;
//			rangeTree[treeIndex * 2 + 1].addValue += rangeTree[treeIndex].addValue;
//			rangeTree[treeIndex * 2 + 1].value += rangeTree[treeIndex * 2 + 1].addValue;
//		}
//		if (2 * treeIndex + 2 < rangeTree.size()) {
//			rangeTree[treeIndex * 2 + 2].lasyAdd = true;
//			rangeTree[treeIndex * 2 + 2].addValue += rangeTree[treeIndex].addValue;
//			rangeTree[treeIndex * 2 + 2].value += rangeTree[treeIndex * 2 + 2].addValue;
//		}
//		rangeTree[treeIndex].lasyAdd = false;
//		rangeTree[treeIndex].addValue = 0;
//	}
//	struct Range {
//		int value, addValue;
//		bool lasyAdd;
//		Range() : lasyAdd (false), addValue(0), value(0) { }
//	};
//
//	int range;
//	vector<Range> rangeTree;
//};

class RangeTree {
public:
	RangeTree(vector<int> &vec) {
		build(vec);
	}
	void build(vector<int> &vec) {
		range = vec.size();
		tree.resize(range * 4);
		subBuild(vec, 0, 0, vec.size());
	}
	int queryMaximum(int from, int to) {
		return subQueryMaximum(from, to, 0, 0, range);
	}
	void addValue(int from, int to, int value) {
		subAddValue(from, to, value, 0, 0, range);
	}
private:
	struct Range {
		int value, addValue/*, setValue*/;
		bool lasyAdd/*, lasySet*/;
		Range() : value(0), addValue(0)/*, setValue(0)*/, lasyAdd(false)/*, lasySet(false)*/ { }
	};
	int range;
	vector<Range> tree;
	int subBuild(vector<int> &vec, int treeIndex, int startIndex, int endIndex) {
		if (startIndex + 1 == endIndex) {
			tree[treeIndex].value = vec[startIndex];
			return tree[treeIndex].value;
		}
		int midIndex = (startIndex + endIndex) / 2;
		tree[treeIndex].value = max(subBuild(vec, treeIndex * 2 + 1, startIndex, midIndex), subBuild(vec, treeIndex * 2 + 2, midIndex, endIndex));
		return tree[treeIndex].value;
	}
	int subQueryMaximum(int from, int to, int treeIndex, int startIndex, int endIndex) {
		updateLasy(treeIndex);
		int leftChild = 2 * treeIndex + 1, rightChild = 2 * treeIndex + 2;
		if (from == startIndex && to == endIndex) {
			return tree[treeIndex].value;
		}
		int midIndex = (startIndex + endIndex) / 2;
		if (midIndex <= from) {
			return subQueryMaximum(from, to, rightChild, midIndex, endIndex); 
		} else if (midIndex > from && midIndex < to) {
			return max(subQueryMaximum(from, midIndex, leftChild, startIndex, midIndex), subQueryMaximum(midIndex, to, rightChild, midIndex, endIndex));
		} else {
			return subQueryMaximum(from, to, leftChild, startIndex, midIndex);
		}
	}
	int subAddValue(int from, int to, int value, int treeIndex, int startIndex, int endIndex) {
		updateLasy(treeIndex);
		if (from == startIndex && to == endIndex) {
			tree[treeIndex].lasyAdd = true;
			tree[treeIndex].addValue += value;
			tree[treeIndex].value += value;
			return tree[treeIndex].value;
		}
		int leftChild = 2 * treeIndex + 1, rightChild = 2 * treeIndex + 2;
		int midIndex = (startIndex + endIndex) / 2;
		if (midIndex <= from) {
			tree[treeIndex].value = max(tree[treeIndex].value, subAddValue(from, to, value, rightChild, midIndex, endIndex));
		} else if (midIndex > from && midIndex < to) {
			tree[treeIndex].value = max(tree[treeIndex].value, subAddValue(from, midIndex, value, leftChild, startIndex, midIndex));
			tree[treeIndex].value = max(tree[treeIndex].value, subAddValue(midIndex, to, value, rightChild, midIndex, endIndex));
		} else {
			tree[treeIndex].value = max(tree[treeIndex].value, subAddValue(from, to, value, leftChild, startIndex, midIndex));
		}
		return tree[treeIndex].value;
	} 
	void updateLasy(int treeIndex) {
		int leftChild = treeIndex * 2 + 1, rightChild = treeIndex * 2 + 2;
		if (tree[treeIndex].lasyAdd) {
			if (leftChild < tree.size()) {
				tree[leftChild].lasyAdd = true;
				tree[leftChild].addValue += tree[treeIndex].addValue;
				tree[leftChild].value += tree[treeIndex].addValue;
			}
			if (rightChild < tree.size()) {
				tree[rightChild].lasyAdd = true;
				tree[rightChild].addValue += tree[treeIndex].addValue;
				tree[rightChild].value += tree[treeIndex].addValue;
			}
			tree[treeIndex].lasyAdd = false;
			tree[treeIndex].addValue = 0;
		}
	}
};

class MaximumFlow {
private:
    typedef int T;
    static const T MAX_FLOW = 10000001;
	static const T EPS = 0;
	int nNode;
	vector<vector<T> > graph;
	vector<int> layer;
public:
	void init(int nNode) {
		this->nNode = nNode;
		if (graph.size() >= nNode) {
			for (int i = 0; i < nNode; ++i) {
				std::fill(graph[i].begin(), graph[i].end(), 0);
			}
			std::fill(layer.begin(), layer.end(), 0);
		} else {
			graph.resize(nNode, vector<int>(nNode, 0));
			layer.resize(nNode, 0);
		}
	}
	void addCapacity(int from, int to, T cap) {
		graph[from][to] += cap;
	}
	T getMaximumFlow(int from, int to) {
		T maximumFlow = 0;
		T extraFlow = 0;
		while (buildLayer(from, to)) {
			for (; ; ) {
				extraFlow = augmentPath(from, to, MAX_FLOW);
				if (extraFlow <= EPS) {
					break;
				}
				maximumFlow += extraFlow;
			}
		}
		return maximumFlow;
	}
private:
	bool buildLayer(int from, int to) {
		std::fill(layer.begin(), layer.end(), 0);
		vector<int> curLayer, nextLayer;
		vector<bool> visited(nNode, false);
		curLayer.push_back(from);	visited[from] = true;
		for (int lay = 1; curLayer.size() != 0; lay++) {
			for (int i = 0; i < curLayer.size(); ++i) {
				int from = curLayer[i];
				for (int j = 0; j < nNode; ++j) {
					if (graph[from][j] <= EPS || visited[j]) {
						continue;
					}
					layer[j] = lay;
					if (j != to) {
						visited[j] = true;
						nextLayer.push_back(j);
					}
				}
			}
			curLayer.swap(nextLayer);
			nextLayer.clear();
		}
		return layer[to] != 0;
	}
	T augmentPath(int from, int to, T maximumFlow) {
		if (from == to) {
			return maximumFlow;
		}
		T mf = maximumFlow;
		for (int t = 0; t < nNode; ++t) {
			if (graph[from][t] <= EPS || t != to && layer[t] != layer[from] + 1) {
				continue;
			}
			mf = augmentPath(t, to, min(maximumFlow, graph[from][t]));
			if (mf <= EPS) {
				continue;
			}
			graph[from][t] -= mf;
			graph[t][from] += mf;
			return mf;
		}
		return 0;
	}
};

// TODO
class ACAutomation {
public:
    void init() {
        words.clear();
    }
    void addWord(string word) {
        words.push_back(word);
    }
private:
    vector<string> words;
    struct TrieNode {
        TrieNode *character[256];
        TrieNode() {
            memset(character, 0, sizeof(character) * sizeof(TrieNode *));
        }
    };
};

// TODO
class Combinations {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> subset;
        vector<vector<int>> result;
        for (int i = 0; i <= nums.size(); ++i) {
            subSubsetsWithDup(nums, 0, i, subset, result);
        }
        return result;
    }
    void subSubsetsWithDup(vector<int> &nums, int startIndex, int nItems, vector<int> &subset, vector<vector<int>> &result) {
        if (nItems == 0) {
            result.push_back(subset);
            return;
        }
        for (int i = startIndex, ni = nums.size() - nItems + 1; i < ni; ++i) {
            if (i != startIndex && nums[i] == nums[i-1]) {
                continue;
            }
            subset.push_back(nums[i]);
            subSubsetsWithDup(nums, i + 1, nItems - 1, subset, result);
            subset.pop_back();
        }
    }

    void kOfNCombination(vector<int> &vec, vector<vector<int> > &result) {

    }
    void kOfNPermutation(vector<int> &vec, vector<vector<int> > &result) {

    }
};

// TODO
class MinDistance {
private:
    typedef int T;
public:
    void init(int nNode) {
        this->nNode = nNode;
        if (graph.size() < nNode) {
            graph.resize(nNode, vector<T>(nNode, std::numeric_limits<T>::max()));
        } else {
            for (int i = 0; i < nNode; ++i) {
                fill(graph[i].begin(), graph[i].end(), std::numeric_limits<T>::max());
            }
        }
    }
    void addEdge(int from, int to, T d) {
        graph[from][to] = min(graph[from][to], d);
    }
    T distance(int from, int to) {
        return dirjkstra(from, to);
    }
    void batchDistance() {
        Floyd();
    }
    T distanceStored(int from, int to) {
        return dist[from][to];
    }
private:
    vector<vector<T> > graph;
    int nNode;
    vector<vector<T> > dist;
    // Three algo
    struct DirjkstraQueueNode {
        DirjkstraQueueNode() : dis(0), id(-1) {}
        DirjkstraQueueNode(T dis, int id) : dis(dis), id(id) {}
        T dis;
        int id;
        bool operator>(const DirjkstraQueueNode &b) const {
            return dis > b.dis;
        }
    };
    T dirjkstra(int from, int to) {
        vector<T> dist(nNode, std::numeric_limits<T>::max());
        vector<int> inQTimes(nNode, 0);
        dist[to] = 0;
        priority_queue<DirjkstraQueueNode, vector<DirjkstraQueueNode>, greater<DirjkstraQueueNode> > Q;
        Q.push(DirjkstraQueueNode(0, to));
        inQTimes[to] += 1;
        while (!Q.empty()) {
            int t = Q.top().id; Q.pop();
            for (int f = 0; f < nNode; ++f) {
                if (f != t && graph[f][t] != std::numeric_limits<T>::max() && (dist[f] == std::numeric_limits<T>::max() || dist[f] > dist[t] + graph[f][t])) {
                    dist[f] = dist[t] + graph[f][t];
                    Q.push(DirjkstraQueueNode(dist[f], f));
                    inQTimes[f] += 1;
                    if (inQTimes[f] > nNode) {
                        return std::numeric_limits<T>::max();
                    }
                }
            }
        }
        return dist[from];
    }

    void Floyd() {
        dist.resize(nNode, vector<T>(nNode, std::numeric_limits<T>::max()));
        for (int f = 0; f < nNode; ++f) {
            for (int t = 0; t < nNode; ++t) {
                dist[f][t] = graph[f][t];
            }
        }
        for (int i = 0; i < nNode; ++i) {
            dist[i][i] = 0;
        }
        for (int m = 0; m < nNode; ++m) {
            for (int f = 0; f < nNode; ++f) {
                for (int t = 0; t < nNode; ++t) {
                    dist[f][t] = min(dist[f][t], dist[f][m] == std::numeric_limits<T>::max() || dist[m][t] == std::numeric_limits<T>::max() ? std::numeric_limits<T>::max() : dist[f][m] + dist[m][t]);
                }
            }
        }
    }
};

void testAVL() {
	AVLTree t;
	for (int i = 1; i < 20; ++i) {
		int val = (i * 777 + i * i) % 97;
		t.insert(val, 0);
		cout << i << "\t" << val << "\t" << t.preOrder() << endl;
		cout << i << "\t" << val << "\t" << t.inOrder() << endl << endl;
	}
	t.deleteKey(30);
	t.deleteKey(35);
	cout << t.preOrder() << endl;
	cout << t.inOrder() << endl << endl;
}

void testTrie() {
	Trie trie;
	char *words[] = {"who", "who", "what", "what", "can", "i", "say", "who", "whamp", "", "who", "when", "where", "what", "can", "cannot", "candle", "can", "can", "", ""};
	for (int i = 0; i < sizeof(words) / sizeof(char*); ++i) {
		trie.insert(words[i]);
	}
	cout << "count of \"\": " << trie.countWord(string("")) << endl;
	cout << "count of \"who\": " << trie.countWord(string("who")) << endl;
}

void testHash() {
	HashTable myhash(1027);

	for (int i = 0; i < 600; ++i) {
		myhash.insert(i * i * i, i * i * i);
	}
	cout << myhash.getValue(3*3*3) << endl;
	cout << myhash.getValue(599*599*599) << endl;
	for (int i = 0; i < 600; i += 3) {
		myhash.removeByKey(i * i * i);
		if (myhash.getValue(i*i*i) != 0) {
			cout << myhash.getValue(i * i * i) << endl;
		}
	}
	for (int i = 600; i < 800; ++i) {
		myhash.insert(i * i * i, i * i * i);
	}
	cout << myhash.getValue(631*631*631) << endl;
	cout << myhash.getValue(713*713*713) << endl;
}

void testUnionSet() {
	UnionSet us(100);
	us.unite(1, 5);
	us.unite(1, 7);
	us.unite(5, 9);
	us.unite(9, 10);
	us.unite(7, 11);
	us.unite(10, 1);
	us.unite(2, 6);
	us.unite(6, 15);
	cout << us.isInSameSet(9, 11) << endl;
	cout << us.isInSameSet(1, 2) << endl;
}

void testST() {
	int array[] = {1, 2, 3, 4, 7, 5, 100, 4, 101, 7, 10, 15, 29, 78, 31, 155};
	vector<int> vec;
	for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
		vec.push_back(array[i]);
	}
	SparseTable st(vec);
	cout << st.rangeMaximumQuery(0, 1) << endl;
	cout << st.rangeMaximumQuery(0, 2) << endl;
	cout << st.rangeMaximumQuery(0, 4) << endl;
	cout << st.rangeMaximumQuery(0, 5) << endl;
	cout << st.rangeMaximumQuery(6, 7) << endl;
	cout << st.rangeMaximumQuery(5, 9) << endl;
	cout << st.rangeMaximumQuery(6, 10) << endl;
	cout << st.rangeMaximumQuery(14, 15) << endl;
	cout << st.rangeMaximumQuery(13, 15) << endl;
	cout << st.rangeMaximumQuery(0, 16) << endl;
	return;
}

void testTreeArray() {
	int arr[] = {1, 2, 3, 4, 5, 6, 9, 1, 7};
	vector<int> vec;
	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
		vec.push_back(arr[i]);
	}
	TreeArray ta(vec);
	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
		cout << ta.sumBefore(i + 1) << endl;
	}
	cout << endl;
	ta.addValue(5, -5);
	ta.addValue(7, 5);
	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
		cout << ta.sumBefore(i + 1) << endl;
	}
}

void testRangeTree() {
	int arr[] = {1, 2, 3, 4, 5, 6, 9, 1, 7};
	vector<int> vec;
	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
		vec.push_back(arr[i]);
	}
	RangeTree rt(vec);
	rt.build(vec);
	cout << rt.queryMaximum(0, 1) << endl;
	cout << rt.queryMaximum(8, 9) << endl;
	cout << rt.queryMaximum(2, 9) << endl;
	cout << rt.queryMaximum(2, 5) << endl;
	cout << endl;

	rt.addValue(0, 4, 15);
	rt.addValue(0, 4, 15);
	rt.addValue(2, 6, 15);
	cout << rt.queryMaximum(0, 1) << endl;
	cout << rt.queryMaximum(1, 2) << endl;
	cout << rt.queryMaximum(8, 9) << endl;
	cout << rt.queryMaximum(2, 9) << endl;
	cout << rt.queryMaximum(2, 4) << endl;
	return ;
}

void testMinDistance() {
    MinDistance md;
    md.init(100);
    md.addEdge(0, 99, 10);
    md.addEdge(99, 7, 4);
    md.addEdge(0, 10, -2);
    md.addEdge(10, 6, -2);
    md.addEdge(6, 7, -7);
    md.addEdge(7, 0, 10);
    cout << md.distance(0, 7) << endl;

    md.batchDistance();
    cout << md.distanceStored(0, 7) << endl;
    cout << md.distanceStored(0, 6) << endl;
}

//class SuffixArray {
//public:
//	void build(string s) {
//		makeSuffixArray(s);
//		makeHeight(s);
//	}
//	void makeSuffixArray(string s, const int NCHARS = 256) {
//		str = s;
//		int n = s.size() + 1;
//		ind2rank.resize(n, 0);	rank2ind.resize(n, 0);
//		vector<int> nextInd2Rank(n, 0), nextRank2Ind(n, 0), itemsBefore(max(n, NCHARS), 0);
//		for (int i = 0; i < n; ++i) {
//			ind2rank[i] = s[i];
//			itemsBefore[s[i]]++; 
//		}
//		for (int i = 1, ni = max(NCHARS, n); i < ni; ++i) {
//			itemsBefore[i] += itemsBefore[i-1];
//		}
//		for (int i = 0; i < n; ++i) {
//			rank2ind[ --itemsBefore[ ind2rank[i] ] ] = i;
//		}
//
//		for (int len = 1; len < n; len <<= 1) {
//			for (int i = 0; i < n; ++i) {
//				int ind = rank2ind[i] - len < 0 ? rank2ind[i] - len + n : rank2ind[i] - len;
//				nextRank2Ind[ itemsBefore[ ind2rank[ind] ]++ ] = ind;
//			}
//
//			nextInd2Rank[ nextRank2Ind[ itemsBefore[0] = 0 ] ] = 0;
//			int rank = 0;
//			for (int i = 1; i < n; ++i) {
//				if (ind2rank[ nextRank2Ind[i] ] != ind2rank[ nextRank2Ind[i-1] ]
//						|| (nextRank2Ind[i]+len < n ? ind2rank[nextRank2Ind[i]+len] : 0) != (nextRank2Ind[i-1]+len < n ? ind2rank[nextRank2Ind[i-1]+len] : 0)) {
//					itemsBefore[++rank] = i;
//				}
//				nextInd2Rank[ nextRank2Ind[i] ] = rank;
//			}
//			ind2rank.swap(nextInd2Rank);
//			rank2ind.swap(nextRank2Ind);
//			if (rank >= n - 1) {
//				break;
//			}
//		}
//	}
//	void makeHeight(string s) {
//		height.resize(s.size() + 1, 0);
//		int i = 0, len = 0, r = ind2rank[0];
//		height[0] = 0;
//		for (; i < s.size(); ++i, ++len) {
//			while (len >= 0 && s[i] != s[ rank2ind[r-1] + len ]) {
//				height[r] = len;	len--;
//				r = ind2rank[ rank2ind[r] + 1 ];
//			}
//		}
//	}
//private:
//	vector<int> ind2rank;
//	vector<int> rank2ind;
//	vector<int> height;
//	string str;
//};

class SuffixArray {
public:
	void build(string s) {
		str = s;
		makeSuffixArray();
		makeHeight();
	}
	void makeSuffixArray() {
		int n = str.size() + 1;
		indexToRank.resize(n, 0);	rankToIndex.resize(n, 0);
		vector<int> nextIndexToRank(n, 0), nextRankToIndex(n, 0), itemsBefore(max(n, 256), 0);
		for (int i = 0; i < n; ++i) {
			itemsBefore[str[i]]++;
			indexToRank[i] = str[i];
		}
		for (int i = 1; i < itemsBefore.size(); ++i) {
			itemsBefore[i] += itemsBefore[i-1];
		}
		for (int i = 0; i < n; ++i) {							// * 同值元素，s中较后的rank较小！
			rankToIndex[--itemsBefore[ indexToRank[i] ]] = i;	// 也就是'\0'的rank是0, 第一轮其他同值元素的序不重要
		}
		for (int len = 1; len < n; len <<= 1) {
			for (int r = 0; r < n; ++r) {
				int index = rankToIndex[r] - len;
				if (index < 0) {	// * 以index开始的后缀长度小于len，这些后缀的序已经确定
					index += n;
				}
				nextRankToIndex[ itemsBefore[ indexToRank[index] ]++ ] = index;		// * 长度大于等于2*len且前半部分相等的元素里面，后半部分小的序要小
			}
			int rank = 0;
			itemsBefore[0] = 0;
			for (int r = 1; r < n; ++r) {
				if (indexToRank[ nextRankToIndex[r] ] != indexToRank[ nextRankToIndex[r-1] ]
						|| (nextRankToIndex[r] + len < n ? indexToRank[ nextRankToIndex[r] + len ] : 0) != (nextRankToIndex[r-1] + len < n ? indexToRank[ nextRankToIndex[r-1] + len ] : 0)) {
					itemsBefore[++rank] = r;
				}
				nextIndexToRank[ nextRankToIndex[r] ] = rank;
			}
			indexToRank.swap(nextIndexToRank);	rankToIndex.swap(nextRankToIndex);
			if (rank >= n - 1) {
				break;
			}
		}
	}
	void makeHeight() {
		height.resize(str.size() + 1, 0);
		int len = 0, rank = indexToRank[0];
		for (int i = 0; i < str.size(); ++i, ++len) {	// * 把后缀树画出来就能理解这个算法
			while (len >= 0 && str[i] != str[ rankToIndex[rank-1] + len ]) {	
				height[rank] = len--;
				rank = indexToRank[ rankToIndex[rank] + 1 ];	// 前面已经比较过len个字符，所以从后len-1个字符恢复比较
			}
		}
	}
private:
	vector<int> indexToRank;
	vector<int> rankToIndex;
	vector<int> height;
	string str;
};

const int N = 257;
char s[N]; // N > 256
// sa:   rank to index
// rank: index to rank
int n, sa[ N], height[N], rnk[N], tmp[N], top[N];
void makesa (){ // O(N * log N)
	int i, j, len, na;
	na = (n < 256 ? 256 : n);
	memset(top, 0, na * sizeof(int));
	for (i = 0; i < n ; i++) top[ rnk[i] = s[i] & 0xff ]++;
	for (i = 1; i < na; i++) top[i] += top[i - 1];
	for (i = 0; i < n ; i++) sa[ --top[ rnk[i] ] ] = i;
	for (len = 1; len < n; len <<= 1) {
		for (i = 0; i < n; i++) {           // tmp是sanext
			j = sa[i] - len; if (j < 0) j += n;
			tmp[ top[ rnk[j] ]++ ] = j;
		}
		sa[ tmp[ top[0] = 0 ] ] = j = 0;     // 现在sa是ranknext
		for (i = 1; i < n; i++) {           // 对于rank2ind/sa, 同值元素序不同, 对于ind2rank/rank, 同值元素序相同
			if (rnk[ tmp[i] ] != rnk[ tmp[i-1] ] ||
				//rnk[ tmp[i]+len ] != rnk[ tmp[i-1]+len ])
				(tmp[i] + len < n ? rnk[ tmp[i]+len ] : 0) != (tmp[i-1] + len < n ? rnk[ tmp[i-1]+len ] : 0))
				top[++j] = i;
			sa[ tmp[i] ] = j;
		}
		memcpy(rnk, sa , n * sizeof(int));
		memcpy(sa , tmp, n * sizeof(int));
		if (j >= n - 1) break;              // 也许能够提前确定每个后缀的序
	}
}
void lcp (){ // O(4 * N)
	int i, j, k;
	for (j = rnk[height[i=k=0]=0]; i < n - 1; i++, k++)
		while (k >= 0 && s[ i] != s[ sa[ j-1] + k ])
			height[j] = (k--), j = rnk[ sa[j] + 1 ];
}



int main(int argc, const char *argv[]) {
    testMinDistance();
    return 0;
	char str[] = {1, 3, 3, 3, 3, 5, 2, 2, 7, 0};
	n = strlen(str) + 1;
	memcpy(s, str, sizeof(str));
	makesa();
	lcp();

	SuffixArray suffixArray;
	suffixArray.build(str);

	return 0;
}
