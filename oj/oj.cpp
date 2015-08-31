#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
#include <functional>
using namespace std;

static const int MAX_VAR_CNT = 15 * 2;
static const int MAX_PROG_CNT = 2;
static const int MAX_REG_CNT = 2;
const int MAX_INSTRUCTION_CNT = 30;

struct Node {
	Node() { 
        init();
	}
    Node(const Node &n) {
        memcpy(reg, n.reg, MAX_PROG_CNT * MAX_REG_CNT * sizeof(double));
        memcpy(var, n.var, MAX_VAR_CNT * sizeof(double));
    }
    void init() {
		memset(reg, 0, sizeof(reg));
		memset(var, 0, sizeof(reg) * sizeof(double));
    }
	double reg[MAX_PROG_CNT][MAX_REG_CNT];
	double var[MAX_VAR_CNT];
};

struct Instruction {
	Instruction() : operation(0), leftVar(""), rightVar0(""), rightVar1(""), rightVal0(0), rightVal1(0) { }
	char operation;
	string leftVar, rightVar0, rightVar1;
	int rightVal0, rightVal1;
};

Node state[MAX_INSTRUCTION_CNT * 4][MAX_INSTRUCTION_CNT * 4];

Instruction ins[MAX_PROG_CNT][MAX_INSTRUCTION_CNT];
double prob[MAX_INSTRUCTION_CNT * 4][MAX_INSTRUCTION_CNT * 4];
double mean[MAX_INSTRUCTION_CNT * 4][MAX_INSTRUCTION_CNT * 4];

int l[2],n;  
string v1[30][2],v2[30][2],v3[30][2];//存储变量  
char op[30][2];//存储操作符  
int n1[30][2],n2[30][2],n3[30][2];//存储常量  
map<string,int>mp;//hash  
bool check(string s,int &a)//读取常量  
{  
    if(s[0]-'0'>=0&&s[0]-'0'<=9)  
    {  
        istringstream sin(s);  
            sin>>a;  
        return 0;  
    }  
    return 1;  
}  

Instruction readInstruction(string s) {
	Instruction ins;
	for (int i = 0, state = 0; i < s.size(); ++i) {
		bool hasSpace = false;
		while (i < s.size() && isspace(s[i])) {
			++i;
			hasSpace = true;
		}
		if (state == 0) {
			if (isalpha(s[i])) {
				ins.leftVar.push_back(s[i]);
				state = 1;
			}
		} else if (state == 1) {
			if ((isalpha(s[i]) || isdigit(s[i])) && !hasSpace) {
				ins.leftVar.push_back(s[i]);
			} else if (s[i] == ':') {
				state = 2;
			}
		} else if (state == 2) {
			if (s[i] == '=') {
				state = 3;
			}
		} else if (state == 3) {
			if (isalpha(s[i])) {
				ins.rightVar0.push_back(s[i]);
				state = 4;
			} else if (isdigit(s[i])) {
				ins.rightVal0 = /*ins.rightVal0 * 10 +*/ s[i] - '0';
				state = 4;
			}
		} else if (state == 4) {
			if ((isalpha(s[i]) || isdigit(s[i])) && ins.rightVar0.size() != 0 && !hasSpace) {
				ins.rightVar0.push_back(s[i]);
			} else if (isdigit(s[i]) && ins.rightVar0.size() == 0 && !hasSpace) {
				ins.rightVal0 = ins.rightVal0 * 10 + s[i] - '0';
			} else if (s[i] == '+' || s[i] == '-') {
				state = 5;
				ins.operation = s[i];
			}
		} else if (state == 5) {
			if (isalpha(s[i])) {
				ins.rightVar1.push_back(s[i]);
				state = 6;
			} else if (isdigit(s[i])) {
				ins.rightVal1 = s[i] - '0';
				state = 6;
			}
		} else if (state == 6) {
			if ((isalpha(s[i]) || isdigit(s[i]))&& ins.rightVar1.size() != 0 && !hasSpace) {
				ins.rightVar1.push_back(s[i]);
			} else if (isdigit(s[i]) && ins.rightVar1.size() == 0 && !hasSpace) {
				ins.rightVal1 = ins.rightVal1 * 10 + s[i] - '0';
			}
		}
	}
	return ins;
}

int main(int argc, char *argv[]) {
	int nCase, nIns[2];
	string s;
	char buffer[1024];
    map<string, int> var2id;
	scanf("%d\n", &nCase);
	while (nCase--) {
        // parse instruction
		Instruction t_ins;
        nIns[0] = 0;    nIns[1] = 0;
		for (int i = 0; i < 2; i += (t_ins.operation == 0)) {
            for (bool done = false; !done; ) {
                fgets(buffer, sizeof(buffer) / sizeof(char) - 1, stdin);
                for (int i = 0; buffer[i] != 0; ++i) {
                    if (!isspace(buffer[i])) {
                        done = true;
                        break;
                    }
                }
            }
            string cmd = buffer;
            transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
            t_ins = readInstruction(cmd);
            if (t_ins.operation != 0) { // END command
                ins[i][nIns[i]++] = t_ins;
            }
		}

        // map var to id
        var2id.clear();
        int varID = 0;
        for (int pi = 0; pi < 2; ++pi) {
            for (int ii = 0; ii < nIns[pi]; ++ii) {
                if (var2id.find(ins[pi][ii].leftVar) == var2id.end()) {
                    var2id[ins[pi][ii].leftVar] = varID++;
                }
                if (ins[pi][ii].rightVar0.size() != 0 && var2id.find(ins[pi][ii].rightVar0) == var2id.end()) {
                    var2id[ins[pi][ii].rightVar0] = varID++;
                }
                if (ins[pi][ii].rightVar1.size() != 0 && var2id.find(ins[pi][ii].rightVar1) == var2id.end()) {
                    var2id[ins[pi][ii].rightVar1] = varID++;
                }
            }
        }

        // dp
        prob[0][0] = 1;
        state[0][0].init();
        for (int i0 = 0, ni0 = nIns[0] * 4; i0 <= ni0; ++i0) {
            for (int i1 = 0, ni1 = nIns[1] * 4; i1 <= ni1; ++i1) {
                if (i0 == 0 && i1 == 0) {
                    continue;
                }
                double p0, p1;
                p0 = i0 != 0 ? prob[i0 - 1][i1] * (i1 != ni1 ? 0.5 : 1) : 0;
                p1 = i1 != 0 ? prob[i0][i1 - 1] * (i0 != ni0? 0.5 : 1) : 0;
                prob[i0][i1] = p0 + p1;

                // execute
                int ind[2] = { i0, i1 };
                int preInd[2][2] = { {i0 - 1, i1}, {i0, i1 - 1} };
                Node stt[2] = {ind[0] != 0 ? state[preInd[0][0]][preInd[0][1]] : Node(), ind[1] != 0 ? state[preInd[1][0]][preInd[1][1]] : Node()};
                for (int progi = 0; progi < 2; ++progi) {
                    if (ind[progi] != 0) {
                        switch (ind[progi] % 4) {
                        case 1:     // move to register 1
                            stt[progi].reg[progi][0] = 
                                ins[progi][(ind[progi]-1)/4].rightVar0.size() != 0 ? 
                                    stt[progi].var[ var2id[ins[progi][(ind[progi]-1)/4].rightVar0] ] : 
                                    ins[progi][(ind[progi]-1)/4].rightVal0;
                            break;
                        case 2:     // move to register 1
                            stt[progi].reg[progi][1] = 
                                ins[progi][(ind[progi]-1)/4].rightVar1.size() != 0 ? 
                                    stt[progi].var[ var2id[ins[progi][(ind[progi]-1)/4].rightVar1] ] : 
                                    ins[progi][(ind[progi]-1)/4].rightVal1;
                            break;
                        case 3:     // operate
                            if (ins[progi][(ind[progi] - 1)/4].operation == '+') {
                                stt[progi].reg[progi][0] += stt[progi].reg[progi][1];
                            } else {
                                stt[progi].reg[progi][0] -= stt[progi].reg[progi][1];
                            }
                            break;
                        case 0:     // move register to var
                            stt[progi].var[var2id[ins[progi][(ind[progi] - 1)/4].leftVar]] =
                                stt[progi].reg[progi][0];
                            break;
                        }
                    }
                }

                // evaluate expection
                for (int vi = 0; vi < varID; ++vi) {
                    state[i0][i1].var[vi] = (stt[0].var[vi] * p0 + stt[1].var[vi] * p1) / (p0 + p1);
                }
                for (int progi = 0; progi < 2; progi++) {
                    for (int regi = 0; regi < 2; regi++) {
                        state[i0][i1].reg[progi][regi] = (stt[0].reg[progi][regi] * p0 + stt[1].reg[progi][regi] * p1) / (p0 + p1);
                    }
                }
            }
        }

        for (map<string, int>::iterator ite = var2id.begin(); ite != var2id.end(); ++ite) {
            printf("%.4lf\n", /*ite->first.c_str(),*/ state[nIns[0] * 4][nIns[1] * 4].var[ite->second]);
        }
        printf("\n");
	}

	return 0;
}
 