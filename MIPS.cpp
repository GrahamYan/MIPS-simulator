#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<map>
using namespace std;



int graham = 0;




const long long MAXN = pow(2 , 32); 

map<string , int> registerMap;
map<string , int> label;

int registerArray[36];

char mem[4001005]; 
int ptr = 0;

union Word
{
	int w;
	unsigned int uw;	
	short h[2];
	unsigned short uh[2];
	char c[4];
	Word(int in) {w = in;}
	Word(unsigned int uin) {uw = uin;}
	Word(short in1, short in2) {h[0] = in1; h[1] = in2;}
	Word(unsigned short uin1, unsigned short uin2) {uh[0] = uin1; uh[1] = uin2;}
	Word(char in1, char in2, char in3, char in4) {c[0] = in1; c[1] = in2; c[2] = in3; c[3] = in4;}
	Word(int pos, char x) {c[0] = mem[pos]; c[1] = mem[pos + 1]; c[2] = mem[pos + 2]; c[3] = mem[pos + 3];}
};

union HalfWord
{
	short h;
	unsigned short uh;
	char c[2];
	HalfWord(short in) {h = in;}
	HalfWord(unsigned short uin) {uh = uin;}
	HalfWord(char in1, char in2) {c[0] = in1; c[1] = in2;}
	HalfWord(int pos, char x) {c[0] = mem[pos]; c[1] = mem[pos + 1];}
};

union LongWord
{
	long long l;
	int w[2];
	LongWord(long long in) {l = in;}
	LongWord(int in1, int in2) {w[0] = in1; w[1] = in2;}	
};

vector<string> vec;

void init () {
	registerMap["zero"] = 0;
	registerMap["at"] = 1;
	registerMap["v0"] = 2;
	registerMap["v1"] = 3;
	registerMap["a0"] = 4;
	registerMap["a1"] = 5;
	registerMap["a2"] = 6;
	registerMap["a3"] = 7;
	registerMap["t0"] = 8;
	registerMap["t1"] = 9;
	registerMap["t2"] = 10;
	registerMap["t3"] = 11;
	registerMap["t4"] = 12;
	registerMap["t5"] = 13;
	registerMap["t6"] = 14;
	registerMap["t7"] = 15;
	registerMap["s0"] = 16;
	registerMap["s1"] = 17;
	registerMap["s2"] = 18;
	registerMap["s3"] = 19;
	registerMap["s4"] = 20;
	registerMap["s5"] = 21;
	registerMap["s6"] = 22;
	registerMap["s7"] = 23;
	registerMap["t8"] = 24;
	registerMap["t9"] = 25;
	registerMap["k0"] = 26;
	registerMap["k1"] = 27;
	registerMap["gp"] = 28;
	registerMap["sp"] = 29;
	registerMap["fp"] = 30;
	registerMap["ra"] = 31;
	registerMap["lo"] = 32;
	registerMap["hi"] = 33;
	registerMap["0"] = 0;
	registerMap["1"] = 1;
	registerMap["2"] = 2;
	registerMap["3"] = 3;
	registerMap["4"] = 4;
	registerMap["5"] = 5;
	registerMap["6"] = 6;
	registerMap["7"] = 7;
	registerMap["8"] = 8;
	registerMap["9"] = 9;
	registerMap["10"] = 10;
	registerMap["11"] = 11;
	registerMap["12"] = 12;
	registerMap["13"] = 13;
	registerMap["14"] = 14;
	registerMap["15"] = 15;
	registerMap["16"] = 16;
	registerMap["17"] = 17;
	registerMap["18"] = 18;
	registerMap["19"] = 19;
	registerMap["20"] = 20;
	registerMap["21"] = 21;
	registerMap["22"] = 22;
	registerMap["23"] = 23;
	registerMap["24"] = 24;
	registerMap["25"] = 25;
	registerMap["26"] = 26;
	registerMap["27"] = 27;
	registerMap["28"] = 28;
	registerMap["29"] = 29;
	registerMap["30"] = 30;
	registerMap["31"] = 31;
	registerMap["32"] = 32;
	registerMap["33"] = 33;
	for (int i = 0; i <= 36; ++i) {
		registerArray[i] = 0;
	}
	for (int i = 0; i < 4001003; ++i) {
		mem[i] = '\0';
	}
	registerArray[registerMap["sp"]] = 4000000;
}
	
/*struct Memory {
	int nval;
	string sval;
	int type;
	int size;
};

Memory mem[1000000];*/

void instruction_fetch () {
	/*string s;
//	freopen ("array_test1-mahaojun.s" , "r" , stdin);                                      //testdata.txt
	fstream out;
	out.open("prime-5100309153-yanghuan.s" , ios::in);               //   array_test1-mahaojun    array_test2-mahaojun.s
	int cnt = 0;
	bool flag = false;
/*	while (!cin.eof()) {
		getline(cin , s);
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		++cnt;
		vec.push_back(s);
//cout << s << "\n";
	}
	while (!out.eof()) {
		getline(out , s);
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		++cnt;
		vec.push_back(s);
	}*/
	return;
}

void decode_preparation() {
	int i , j;
	int state = 0;
	for (i = 0; i < vec.size(); ++i) {
//cout << "\n" << vec[i] << "\n";
//cout << "testing row " << i << ", and the state of this line is" << state << "\n"; 
		if (vec[i].find("#") < vec[i].length()) {
			for (j = vec[i].find("#"); j < vec[i].length(); ++j) {
				vec[i][j] = ' ';
			}
		}
		
		if (vec[i].find(".") == 0) {
//cout << ".found\n";
			if (vec[i].find("data") == 1) {
//cout << "testing data\n";
				state = 1;
				continue;
			}
			if (vec[i].find("text") == 1) {
				state = 2;
				continue;
			}
		}
			if (state == 1) {
//cout << "state is: " << state << "\n";
				if (vec[i].find(":") < vec[i].length()) {
					string name;
					for (int j = 0; j < vec[i].find(":"); ++j) {
						name += vec[i][j];
					}
					label[name] = ptr;
//cout << name << ' ' << ptr << "\n";
				}
				if (vec[i].find(".align") == 0) {
					int tmp = vec[i].find(' ' , vec[i].find("align"));
					++tmp;
					int val = 0;
					while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9' && tmp < vec[i].length()) {
						val = val * 10 + (vec[i][tmp] - '0');
						++tmp;
					}
//cout << "val = " << val << "\n";
					int k = ptr;
					int tar = pow(2 , val);
					while (true) {
						if (k % tar == 0) break;
						++k;
					}
					ptr = k;
//cout << "ptr = " << ptr  << "\n";			
				}
				if (vec[i].find(".ascii") == 0) {
					if (vec[i].find(".asciiz") == 0) {
//cout << "testing asciiz" << "\n";
						int tmp = vec[i].find('"') + 1;
//cout << tmp << "\n";
						bool flag = false;
						while (vec[i][tmp] != '"') {
//cout << tmp << ' ';
							if (vec[i][tmp] == '\\') {
//cout << "flag is on\n";
								flag = true;
								++tmp;
								continue;
							}
							if (!flag) {
								mem[ptr] = vec[i][tmp];
//cout << mem[ptr] << "\n";
								++tmp;
								++ptr;
							}
							else {
								if (vec[i][tmp] == 'n') {
									mem[ptr] = '\n';
								}
								if (vec[i][tmp] == 't') {
									mem[ptr] = '\t';
								}
								if (vec[i][tmp] == '0') {
									mem[ptr] = '\0';
								}
								flag = false;
								++tmp;
								++ptr;
							}
						}
						mem[ptr] = '\0';
						++ptr;
					}
					else {
						int tmp = vec[i].find('"') + 1;
						bool flag = false;
						while (vec[i][tmp] != '"') {
							if (vec[i][tmp] == '\\') {
								flag = true;
								continue;
							}
							if (flag = false) {
								mem[ptr] = vec[i][tmp];
								++tmp;
								++ptr;
							}
							else {
								if (vec[i][tmp] == 'n') {
									mem[ptr] = '\n';
								}
								if (vec[i][tmp] == 't') {
									mem[ptr] = '\t';
								}
								if (vec[i][tmp] == '0') {
									mem[ptr] = '\0';
								}
								flag = false;
								++tmp;
								++ptr;
							}
						}
					}
				}
				if (vec[i].find(".byte") == 0) {
					int tmp = vec[i].find(' ' , vec[i].find("byte")) + 1;
					while (tmp < vec[i].length()) {
						if (vec[i][tmp] == ' ') {
							++tmp;
							continue;
						}
						if (vec[i][tmp] == ',') {
							++tmp;
							continue;
						}
						mem[ptr] = vec[i][tmp];
						++ptr; ++tmp;
					}
				}
				if (vec[i].find(".half") == 0) {
					int tmp = vec[i].find(' ' , vec[i].find("half")) + 1;
					while (tmp < vec[i].length()) {
						if (vec[i][tmp] == ' ') {
							++tmp;
							continue;
						}
						if (vec[i][tmp] == ',') {
							++tmp;
							continue;
						}
						short temp = 0;
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							temp = temp * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						mem[ptr++] = HalfWord(temp).c[0];
						mem[ptr++] = HalfWord(temp).c[1];
					}
				}
				if (vec[i].find(".word") == 0) {
					int tmp = vec[i].find(' ' , vec[i].find("word")) + 1;
//cout << tmp << "\n";
					while (tmp < vec[i].length()) {
						if (vec[i][tmp] == ' ') {
							++tmp;
//cout << "jump a ' '" << "\n";
							continue;
						}
						if (vec[i][tmp] == ',') {
							++tmp;
//cout << "jump a ,\n"; 
							continue;
						}
						int temp = 0;
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9' && tmp < vec[i].length()) {
							temp = temp * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						mem[ptr++] = Word(temp).c[0];
						mem[ptr++] = Word(temp).c[1];
						mem[ptr++] = Word(temp).c[2];
						mem[ptr++] = Word(temp).c[3];
//cout << "test word ok\n";
					}
				}
				if (vec[i].find(".space") == 0) {
					int tmp = vec[i].find(' ' , vec[i].find("space"));
					++tmp;
					int val = 0;
					while (vec[i][tmp] != ' ') {
						val = val * 10 + (vec[i][tmp] - '0');
						++tmp;
					}
					int cnt = val + ptr;
					while (ptr < cnt) {
						mem[ptr] = ' ';
						++ptr;
					}
				}
			}
			if (state == 2) {
//cout << "state is: " << state << "\n";		
				if (vec[i].find(":") < vec[i].length()) {
					string name;
					for (int j = 0; j < vec[i].find(":"); ++j) {
						name += vec[i][j];
					}
					label[name] = i;
//cout << name << ' ' << i << "\n";
				}	
			}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////  execution  ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void execution () {
	int i , j;
	for (i = label["main"] + 1; i < vec.size(); ++i) {
//cout << "\n" << vec[i] << "\n";
//cout << "testing row " << i << "\n";
				if (vec[i].find("li") == 0) {
					int tmp = vec[i].find("$") + 1;
					string tar;
					int val = 0;
					bool pos = true;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						tar += vec[i][tmp];
						++tmp;
					}
					while (true) {
						if (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							break;
						}
						++tmp;
					}
					if (vec[i][tmp] == '-') {
						pos = false;
						++tmp;
					}
					while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9' && tmp < vec[i].length()) {
						val = val * 10 + (vec[i][tmp] - '0');
						++tmp;
					}
					if (!pos) val = -val; 
					registerArray[registerMap[tar]] = val;
				}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//arithmetic instruction
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//add
				if (vec[i].find("add") == 0) {
					if (vec[i].find("addiu") == 0) {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc;
						int imm = 0;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\t' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							imm = imm * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] + imm);
					}
					else if (vec[i].find("addu") == 0) {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0;
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] + imm);
						}
						else {
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] + registerArray[registerMap[src2]]);
						}
					}
					else {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0;
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
//cout << "add imm\n";*
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
//cout << tmp << "\n";*
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9' && tmp < vec[i].length()) {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
//cout << imm << "\n";*
							registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] + imm;
						}
						else {
//cerr << "add register\n";
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] + registerArray[registerMap[src2]];
						}
						
					}
				}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//subtraction
				if (vec[i].find("sub") == 0) {
					if (vec[i].find("subu") == 0) {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0;
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] - imm);
						}
						else {
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] - registerArray[registerMap[src2]]);
						}
					}
					else {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0;
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
							registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] - imm;
						}
						else {
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] - registerArray[registerMap[src2]];
						}
					}
				}				
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//multiply
				if (vec[i].find("mul") == 0) {
					int num = 0;
					for (j = 0; j < vec[i].length(); ++j) {
						if (vec[i][j] == ',') ++ num;
					}
					if (num == 2) {
						if (vec[i].find("mulu") == 0) {
							int tmp = vec[i].find("$") + 1;
							string Rdest , Rsrc , src2;
							int imm = 0;
							bool pos = true;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rdest += vec[i][tmp];
								++tmp;
							}
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rsrc += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								} 
								if (!pos) imm = -imm;
								registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] * imm);
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] * registerArray[registerMap[src2]]);
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string Rdest , Rsrc , src2;
							int imm = 0;
							bool pos = true;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rdest += vec[i][tmp];
								++tmp;
							}
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rsrc += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								} 
								if (!pos) imm = -imm;
								registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] * imm;
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] * registerArray[registerMap[src2]];
							}
						}
					}
					if (num == 1) {
						if (vec[i].find("mulu") == 0) {
							int tmp = vec[i].find("$") + 1;
							string Rdest , src2;
							int imm = 0;
							bool pos = true;
							long long ans;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rdest += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) imm = -imm;
								ans = (unsigned int)(registerArray[registerMap[Rdest]] * imm);
								registerArray[registerMap["lo"]] = ans & ((1LL << 32) - 1);
								registerArray[registerMap["hi"]] = ans >> 32;
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								ans = (unsigned int)(registerArray[registerMap[Rdest]] * registerArray[registerMap[src2]]);
								registerArray[registerMap["lo"]] = ans & ((1LL << 32) - 1);
								registerArray[registerMap["hi"]] = ans >> 32;
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string Rdest , src2;
							int imm = 0;
							bool pos = true;
							long long ans;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								Rdest += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) imm = -imm;
								ans = (registerArray[registerMap[Rdest]] * imm);
								registerArray[registerMap["lo"]] = ans & ((1LL << 32) - 1);
								registerArray[registerMap["hi"]] = ans >> 32;
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								ans = (registerArray[registerMap[Rdest]] * registerArray[registerMap[src2]]);
								registerArray[registerMap["lo"]] = ans & ((1LL << 32) - 1);
								registerArray[registerMap["hi"]] = ans >> 32;
							}
						}
					}
				}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//divide
				if (vec[i].find("div") == 0) {
					int num = 0;
					for (j = 0; j < vec[i].length(); ++j) {
						if (vec[i][j] == ',') ++ num;
					}
					if (num == 2) {
						if (vec[i].find("divu") == 0) {
							int tmp = vec[i].find("$") + 1;
							string Rdest , Rsrc , src2;
							int imm = 0;
							bool pos = true;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rdest += vec[i][tmp];
								++tmp;
							}
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rsrc += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								} 
								if (!pos) imm = -imm;
								registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] / imm);
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] / registerArray[registerMap[src2]]);
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string Rdest , Rsrc , src2;
							int imm = 0;	
							bool pos = true;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rdest += vec[i][tmp];
								++tmp;
							}
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rsrc += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								} 
								if (!pos) imm = -imm;
								registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] / imm;
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]] / registerArray[registerMap[src2]];
//cout << registerArray[registerMap[Rsrc]] << ' ' << registerArray[registerMap[src2]] << "\n"; 
							}
						}
					}
					if (num == 1) {
						if (vec[i].find("divu") == 0) {
							int tmp = vec[i].find("$") + 1;
							string Rdest , src2;
							int imm = 0;
							bool pos = true;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rdest += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) imm = -imm;
								registerArray[registerMap["lo"]] = (unsigned int)(registerArray[registerMap[Rdest]] / imm);
								registerArray[registerMap["hi"]] = (unsigned int)(registerArray[registerMap[Rdest]] % imm);
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								registerArray[registerMap["lo"]] = (unsigned int)(registerArray[registerMap[Rdest]] / registerArray[registerMap[src2]]);
								registerArray[registerMap["hi"]] = (unsigned int)(registerArray[registerMap[Rdest]] % registerArray[registerMap[src2]]);
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string Rdest , src2;
							int imm = 0;
							bool pos = true;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								Rdest += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) >= vec[i].length()) {
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								} 
								while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
									imm = imm * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) imm = -imm;
								registerArray[registerMap["lo"]] = (registerArray[registerMap[Rdest]] / imm);
								registerArray[registerMap["hi"]] = (registerArray[registerMap[Rdest]] % imm);
							}
							else {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									src2 += vec[i][tmp];
									++tmp;
								}
								registerArray[registerMap["lo"]] = (registerArray[registerMap[Rdest]] / registerArray[registerMap[src2]]);
								registerArray[registerMap["hi"]] = (registerArray[registerMap[Rdest]] % registerArray[registerMap[src2]]);
							}
						}
					}
				}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//xor
				if (vec[i].find("xor") == 0) {
					if (vec[i].find("xoru") == 0) {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0;
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] ^ imm);
						}
						else {
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] ^ registerArray[registerMap[src2]]);
						}
					}
					else {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0; 
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
							registerArray[registerMap[Rdest]] = (registerArray[registerMap[Rsrc]] ^ imm);
						}
						else {
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = (registerArray[registerMap[Rsrc]] ^ registerArray[registerMap[src2]]);
						}
					}
				}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//neg
				if (vec[i].find("neg") == 0) {
					if (vec[i].find("negu") == 0) {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						registerArray[registerMap[Rdest]] = -registerArray[registerMap[Rsrc]];
					}
					else {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (registerArray[registerMap[Rsrc]] < 0) {
							registerArray[registerMap[Rsrc]] += MAXN;
						}
						registerArray[registerMap[Rdest]] = -registerArray[registerMap[Rsrc]];
					}
				}	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//rem				
				if (vec[i].find("rem") == 0) {
					if (vec[i].find("remu") == 0) {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0;
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] % imm);
						}
						else {
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = (unsigned int)(registerArray[registerMap[Rsrc]] % registerArray[registerMap[src2]]);
						}
					}
					else {
						int tmp = vec[i].find("$") + 1;
						string Rdest , Rsrc , src2;
						int imm = 0;
						bool pos = true;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rdest += vec[i][tmp];
							++tmp;
						}
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
							Rsrc += vec[i][tmp];
							++tmp;
						}
						if (vec[i].find("$" , tmp) >= vec[i].length()) {
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
							if (vec[i][tmp] == '-') {
								pos = false;
								++tmp;
							} 
							while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
								imm = imm * 10 + (vec[i][tmp] - '0');
								++tmp;
							} 
							if (!pos) imm = -imm;
							registerArray[registerMap[Rdest]] = (registerArray[registerMap[Rsrc]] % imm);
						}
						else {
							tmp = vec[i].find("$" , tmp) + 1;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								src2 += vec[i][tmp];
								++tmp;
							}
							registerArray[registerMap[Rdest]] = (registerArray[registerMap[Rsrc]] % registerArray[registerMap[src2]]);
						}
					}
				}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//logic instruct                    there are something wrong here
///////////////////////////////////////////////////////////////////////
//seq
				if (vec[i].find("seq") == 0) {
					int tmp = vec[i].find("$") + 1;
					string R , R1 , R2;
					int imm = 0;
					bool pos = true;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R += vec[i][tmp];
						++tmp;
					}
					tmp = vec[i].find("$" , tmp) + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R1 += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("$" , tmp) >= vec[i].length()) {
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						} 
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							imm = imm * 10 + (vec[i][tmp] - '0');
							++tmp;
						} 
						if (!pos) imm = -imm;
						if (registerArray[registerMap[R1]] == imm) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
					else {
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							R2 += vec[i][tmp];
							++tmp;
						}
						if (registerArray[registerMap[R1]] == registerArray[registerMap[R2]]) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
				}
//////////////////////////////////////////////////////////////////////
//sge
				if (vec[i].find("sge") == 0) {
					int tmp = vec[i].find("$") + 1;
					string R , R1 , R2;
					int imm = 0;
					bool pos = true;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R += vec[i][tmp];
						++tmp;
					}
					tmp = vec[i].find("$" , tmp) + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R1 += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("$" , tmp) >= vec[i].length()) {
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						} 
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							imm = imm * 10 + (vec[i][tmp] - '0');
							++tmp;
						} 
						if (!pos) imm = -imm;
						if (registerArray[registerMap[R1]] >= imm) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
					else {
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							R2 += vec[i][tmp];
							++tmp;
						}
						if (registerArray[registerMap[R1]] >= registerArray[registerMap[R2]]) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
				}
////////////////////////////////////////////////////////////////////////
//sgt
				if (vec[i].find("sgt") == 0) {
					int tmp = vec[i].find("$") + 1;
					string R , R1 , R2;
					int imm = 0;
					bool pos = true;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R += vec[i][tmp];
						++tmp;
					}
					tmp = vec[i].find("$" , tmp) + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R1 += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("$" , tmp) >= vec[i].length()) {
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						} 
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							imm = imm * 10 + (vec[i][tmp] - '0');
							++tmp;
						} 
						if (!pos) imm = -imm;
						if (registerArray[registerMap[R1]] > imm) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
					else {
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							R2 += vec[i][tmp];
							++tmp;
						}
						if (registerArray[registerMap[R1]] > registerArray[registerMap[R2]]) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
				}	
/////////////////////////////////////////////////////////////////////
//sle
				if (vec[i].find("sle") == 0) {
					int tmp = vec[i].find("$") + 1;
					string R , R1 , R2;
					int imm = 0;
					bool pos = true;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R += vec[i][tmp];
						++tmp;
					}
					tmp = vec[i].find("$" , tmp) + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R1 += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("$" , tmp) >= vec[i].length()) {
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						} 
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							imm = imm * 10 + (vec[i][tmp] - '0');
							++tmp;
						} 
						if (!pos) imm = -imm;
						if (registerArray[registerMap[R1]] <= imm) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
					else {
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							R2 += vec[i][tmp];
							++tmp;
						}
						if (registerArray[registerMap[R1]] <= registerArray[registerMap[R2]]) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
				}
/////////////////////////////////////////////////////////////////////
//slt
				if (vec[i].find("slt") == 0) {
					int tmp = vec[i].find("$") + 1;
					string R , R1 , R2;
					int imm = 0;
					bool pos = true;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R += vec[i][tmp];
						++tmp;
					}
					tmp = vec[i].find("$" , tmp) + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R1 += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("$" , tmp) >= vec[i].length()) {
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						} 
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							imm = imm * 10 + (vec[i][tmp] - '0');
							++tmp;
						} 
						if (!pos) imm = -imm;
						if (registerArray[registerMap[R1]] < imm) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
					else {
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							R2 += vec[i][tmp];
							++tmp;
						}
						if (registerArray[registerMap[R1]] < registerArray[registerMap[R2]]) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
				}	
//////////////////////////////////////////////////////////////////////
//sne
				if (vec[i].find("sne") == 0) {
					int tmp = vec[i].find("$") + 1;
					string R , R1 , R2;
					int imm = 0;
					bool pos = true;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R += vec[i][tmp];
						++tmp;
					}
					tmp = vec[i].find("$" , tmp) + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						R1 += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("$" , tmp) >= vec[i].length()) {
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						} 
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							imm = imm * 10 + (vec[i][tmp] - '0');
							++tmp;
						} 
						if (!pos) imm = -imm;
						if (registerArray[registerMap[R1]] != imm) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
					else {
						tmp = vec[i].find("$" , tmp) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							R2 += vec[i][tmp];
							++tmp;
						}
						if (registerArray[registerMap[R1]] != registerArray[registerMap[R2]]) registerArray[registerMap[R]] = 1;
						else registerArray[registerMap[R]] = 0;
					}
				}	
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//branch and jump
				if (vec[i].find("b") == 0) {
					if (vec[i].find("beq") == 0) {
						if (vec[i].find("beqz") == 0) {
							int tmp = vec[i].find("$") + 1;
							string R , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								lab += vec[i][tmp];
								++tmp;
							}
							if (registerArray[registerMap[R]] == 0) {
								i = label[lab];
								continue;
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string R , R2 , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) < vec[i].length()) {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									R2 += vec[i][tmp];
									++tmp;
								}
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] == registerArray[registerMap[R2]]) {
									i = label[lab];
										continue;
								}
							}
							else {
								int ans = 0;
								bool pos = true;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								}
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									ans = ans * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) ans = -ans;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] == ans) {
									i = label[lab];
									continue;
								}
							}
						}
					}
					else if (vec[i].find("bne") == 0) {
						if (vec[i].find("bnez") == 0) {
							int tmp = vec[i].find("$") + 1;
							string R , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								lab += vec[i][tmp];
								++tmp;
							}
							if (registerArray[registerMap[R]] != 0) {
								i = label[lab];
								continue;
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string R , R2 , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) < vec[i].length()) {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									R2 += vec[i][tmp];
									++tmp;
								}
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] != registerArray[registerMap[R2]]) {
									i = label[lab];
									continue;
								}
							}
							else {
								int ans = 0;
								bool pos = true;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								}
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									ans = ans * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) ans = -ans;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] != ans) {
									i = label[lab];
									continue;
								}
							}
						}	
					}
					else if (vec[i].find("bge") == 0) {
						if (vec[i].find("bgez") == 0) {
							int tmp = vec[i].find("$") + 1;
							string R , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								lab += vec[i][tmp];
								++tmp;
							}
							if (registerArray[registerMap[R]] >= 0) {
								i = label[lab];
								continue;
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string R , R2 , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) < vec[i].length()) {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									R2 += vec[i][tmp];
									++tmp;
								}
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] >= registerArray[registerMap[R2]]) {
									i = label[lab];
										continue;
								}
							}
							else {
								int ans = 0;
								bool pos = true;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								}
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									ans = ans * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) ans = -ans;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] >= ans) {
									i = label[lab];
									continue;
								}
							}
						}
						
					} 
					else if (vec[i].find("ble") == 0) {
						if (vec[i].find("blez") == 0) {
							int tmp = vec[i].find("$") + 1;
							string R , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								lab += vec[i][tmp];
								++tmp;
							}
							if (registerArray[registerMap[R]] <= 0) {
								i = label[lab];
								continue;
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string R , R2 , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) < vec[i].length()) {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									R2 += vec[i][tmp];
									++tmp;
								}
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] <= registerArray[registerMap[R2]]) {
									i = label[lab];
										continue;
								}
							}
							else {
								int ans = 0;
								bool pos = true;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								}
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									ans = ans * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) ans = -ans;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] <= ans) {
									i = label[lab];
									continue;
								}
							}
						}		
					}
					else if (vec[i].find("bgt") == 0) {
						if (vec[i].find("bgtz") == 0) {
							int tmp = vec[i].find("$") + 1;
							string R , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								lab += vec[i][tmp];
								++tmp;
							}
							if (registerArray[registerMap[R]] > 0) {
								i = label[lab];
								continue;
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string R , R2 , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) < vec[i].length()) {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									R2 += vec[i][tmp];
									++tmp;
								}
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] > registerArray[registerMap[R2]]) {
									i = label[lab];
										continue;
								}
							}
							else {
								int ans = 0;
								bool pos = true;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								}
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									ans = ans * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) ans = -ans;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] > ans) {
									i = label[lab];
									continue;
								}
							}
						}
					}
					else if (vec[i].find("blt") == 0) {
						if (vec[i].find("bltz") == 0) {
							int tmp = vec[i].find("$") + 1;
							string R , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
								lab += vec[i][tmp];
								++tmp;
							}
							if (registerArray[registerMap[R]] < 0) {
								i = label[lab];
								continue;
							}
						}
						else {
							int tmp = vec[i].find("$") + 1;
							string R , R2 , lab;
							while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
								R += vec[i][tmp];
								++tmp;
							}
							if (vec[i].find("$" , tmp) < vec[i].length()) {
								tmp = vec[i].find("$" , tmp) + 1;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									R2 += vec[i][tmp];
									++tmp;
								}
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] < registerArray[registerMap[R2]]) {
									i = label[lab];
										continue;
								}
							}
							else {
								int ans = 0;
								bool pos = true;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								if (vec[i][tmp] == '-') {
									pos = false;
									++tmp;
								}
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
									ans = ans * 10 + (vec[i][tmp] - '0');
									++tmp;
								}
								if (!pos) ans = -ans;
								while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
								while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
									lab += vec[i][tmp];
									++tmp;
								}
								if (registerArray[registerMap[R]] < ans) {
									i = label[lab];
									continue;
								}
							}
						}
					}
					else {
						int tmp = vec[i].find("b") + 1; 
						string lab;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0' || vec[i][tmp] == '\t') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
							lab += vec[i][tmp];
							++tmp;
						}
						i = label[lab];
						continue;
					}
				}
				if (vec[i].find("j") == 0) {
					if (vec[i].find("jr") == 0) {
						string R;
						int tmp = vec[i].find("$" , vec[i].find("jr")) + 1;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && tmp < vec[i].length()) {
							R += vec[i][tmp];
							++tmp;
						} 
//cerr << R << "\n";*
//cerr << registerArray[registerMap[R]] << "\n";*
						i = registerArray[registerMap[R]] - 1;
						continue;
					}
					else if (vec[i].find("jal") == 0) {
						string R; 
						int tmp = vec[i].find(' ' , vec[i].find("jal"));
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && tmp < vec[i].length()) {
							R += vec[i][tmp];
							++tmp;
						} 
						registerArray[registerMap["ra"]] = i + 1;
//cerr << R << "\n";*
						i = label[R];
						continue;
					}
					else if (vec[i].find("jalr") == 0) {
						string R;
						int tmp = vec[i].find("$" , vec[i].find("jalr"));
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && tmp < vec[i].length()) {
							R += vec[i][tmp];
							++tmp;
						} 
						registerArray[registerMap["ra"]] = i + 1;
						i = registerArray[registerMap[R]] - 1;
						continue;
					}
					else {
						string R;
						int tmp = vec[i].find(' ' , vec[i].find("j"));
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && tmp < vec[i].length()) {
							R += vec[i][tmp];
							++tmp;
						} 
						i = label[R];
						continue;
					}
				}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//load
				if (vec[i].find("la") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] !=  ' ' && vec[i][tmp] != ',') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("(") < vec[i].length()) {
						int offset = 0;
						string Reg;
						bool pos = true;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						}
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							offset = offset * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						if (!pos) offset = -offset;
						tmp = vec[i].find("$" , vec[i].find("(")) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							Reg += vec[i][tmp];
							++tmp;
						}
						registerArray[registerMap[Rdest]] = registerArray[registerMap[Reg]] + offset;
					}
					else {
						string adrs;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							adrs += vec[i][tmp];
							++tmp;
						}
						registerArray[registerMap[Rdest]] = label[adrs];
					}
				}
				if (vec[i].find("lb") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] !=  ' ' && vec[i][tmp] != ',') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("(") < vec[i].length()) {
						int offset = 0;
						string Reg;
						bool pos = true;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						}
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							offset = offset * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						if (!pos) offset = -offset;
						tmp = vec[i].find("$" , vec[i].find("(")) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							Reg += vec[i][tmp];
							++tmp;
						}
						registerArray[registerMap[Rdest]] = int(mem[registerArray[registerMap[Reg]] + offset]);
					}
					else {
						string adrs;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							adrs += vec[i][tmp];
							++tmp;
						}
						registerArray[registerMap[Rdest]] = int(mem[label[adrs]]);
					}
				}
				if (vec[i].find("lh") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] !=  ' ' && vec[i][tmp] != ',') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("(") < vec[i].length()) {
						int offset = 0;
						string Reg;
						bool pos = true;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						}
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							offset = offset * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						if (!pos) offset = -offset;
						tmp = vec[i].find("$" , vec[i].find("(")) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							Reg += vec[i][tmp];
							++tmp;
						}
						short ans = HalfWord(registerArray[registerMap[Reg]] + offset , 'a').h;
						registerArray[registerMap[Rdest]] = ans;
					}
					else {
						string adrs;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							adrs += vec[i][tmp];
							++tmp;
						}
						short ans = HalfWord(label[adrs] , 'a').h;
						registerArray[registerMap[Rdest]] = ans;
					}
				}
				if (vec[i].find("lw") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] !=  ' ' && vec[i][tmp] != ',') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("(") < vec[i].length()) {
						int offset = 0;
						string Reg;
						bool pos = true;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						}
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							offset = offset * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						if (!pos) offset = -offset;
						tmp = vec[i].find("$" , vec[i].find("(")) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							Reg += vec[i][tmp];
							++tmp;
						}
						int ans = Word(registerArray[registerMap[Reg]] + offset , 'a').w;
						registerArray[registerMap[Rdest]] = ans;
					}
					else {
						string adrs;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							adrs += vec[i][tmp];
							++tmp;
						}
						int ans = Word(label[adrs] , 'a').w;
						registerArray[registerMap[Rdest]] = ans;
					}
				}
					
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//store
				if (vec[i].find("sb") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] !=  ' ' && vec[i][tmp] != ',') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("(") < vec[i].length()) {
						int offset = 0;
						string Reg;
						bool pos = true;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						}
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							offset = offset * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						if (!pos) offset = -offset;
						tmp = vec[i].find("$" , vec[i].find("(")) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							Reg += vec[i][tmp];
							++tmp;
						}
						mem[registerArray[registerMap[Reg]] + offset] = char(registerArray[registerMap[Rdest]]);
					}
					else {
						string adrs;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							adrs += vec[i][tmp];
							++tmp;
						}
						mem[label[adrs]] = char(registerArray[registerMap[Rdest]]);
					}
				}
				if (vec[i].find("sh") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] !=  ' ' && vec[i][tmp] != ',') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("(") < vec[i].length()) {
						int offset = 0;
						string Reg;
						bool pos = true;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '0') {
							pos = false;
							++tmp;
						}
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							offset = offset * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						if (!pos) offset = -offset;
						tmp = vec[i].find("$" , vec[i].find("(")) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							Reg += vec[i][tmp];
							++tmp;
						}
						short ans = registerArray[registerMap[Rdest]];
						int PD = registerArray[registerMap[Reg]] + offset;
						mem[PD++] = HalfWord(ans).c[0];
						mem[PD++] = HalfWord(ans).c[1];
					}
					else {
						string adrs;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							adrs += vec[i][tmp];
							++tmp;
						}
						short ans = registerArray[registerMap[Rdest]];
						int PD = label[adrs];
						mem[PD++] = HalfWord(ans).c[0];
						mem[PD++] = HalfWord(ans).c[1];
					}
				}
				if (vec[i].find("sw") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] !=  ' ' && vec[i][tmp] != ',') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					if (vec[i].find("(") < vec[i].length()) {
						int offset = 0;
						string Reg;
						bool pos = true;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						if (vec[i][tmp] == '-') {
							pos = false;
							++tmp;
						}
						while (vec[i][tmp] >= '0' && vec[i][tmp] <= '9') {
							offset = offset * 10 + (vec[i][tmp] - '0');
							++tmp;
						}
						if (!pos) offset = -offset;
						tmp = vec[i].find("$" , vec[i].find("(")) + 1;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							Reg += vec[i][tmp];
							++tmp;
						}
						int ans = registerArray[registerMap[Rdest]];
						int PD = registerArray[registerMap[Reg]] + offset;
						mem[PD++] = Word(ans).c[0];
						mem[PD++] = Word(ans).c[1];
						mem[PD++] = Word(ans).c[2];
						mem[PD++] = Word(ans).c[3];
					}
					else {
						string adrs;
						while (vec[i][tmp] == ' ' || vec[i][tmp] == ',' || vec[i][tmp] == '\0') ++tmp;
						while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\0' && vec[i][tmp] != ')' && tmp < vec[i].length()) {
							adrs += vec[i][tmp];
							++tmp;
						}
						int ans = registerArray[registerMap[Rdest]];
						int PD = label[adrs];
						mem[PD++] = Word(ans).c[0];
						mem[PD++] = Word(ans).c[1];
						mem[PD++] = Word(ans).c[2];
						mem[PD++] = Word(ans).c[3];
					}
				}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//data move
				if (vec[i].find("move") == 0) {
					string Rdest , Rsrc;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n') {
						Rdest += vec[i][tmp];
						++tmp;
					}
					tmp = vec[i].find("$" , tmp) + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp] != '\n' && tmp < vec[i].length()) {
						Rsrc += vec[i][tmp];
						++tmp;
					}
					registerArray[registerMap[Rdest]] = registerArray[registerMap[Rsrc]];
				}
				if (vec[i].find("mfhi") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp]!= '\n' && tmp < vec[i].length()) {
						Rdest += vec[i][tmp];
						++tmp;
					}
					registerArray[registerMap[Rdest]] = registerArray[registerMap["hi"]];
				}
				if (vec[i].find("mflo") == 0) {
					string Rdest;
					int tmp = vec[i].find("$") + 1;
					while (vec[i][tmp] != ' ' && vec[i][tmp] != ',' && vec[i][tmp]!= '\n' && tmp < vec[i].length()) {
						Rdest += vec[i][tmp];
						++tmp;
					}
					registerArray[registerMap[Rdest]] = registerArray[registerMap["lo"]];
				}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//special instruction
				if (vec[i].find("nop") == 0) {
					continue;
				} 
				if (vec[i].find("syscall") == 0) {
//cout << "*********************************************" << registerArray[registerMap["v0"]] << "\n";
					if (registerArray[registerMap["v0"]] == 1) {
//cerr << "the syscall type is 1\n";
						/*fstream fout;
						fout.open("output.txt" , ios::out);
						fout << registerArray[registerMap["a0"]] << "\n";
						fout.close();*/
						cout <<registerArray[registerMap["a0"]];
						continue;
					}
					if (registerArray[registerMap["v0"]] == 4) {
//cerr << "the syscall type is 4\n";
						int tmp = registerArray[registerMap["a0"]];
//cout << "the point is:" << tmp << "\n"; 
						/*fstream fout;
						fout.open("output.txt" , ios::out);
						while (mem[tmp] != '\0') {
							fout << mem[tmp];
							++tmp;
						}
						fout << "\0" << "\n";
						fout.close();*/
						while (mem[tmp] != '\0') {
							cout << mem[tmp];
							++tmp;
						}
						cout << "\0";
						continue;
//getchar();
					}
					if (registerArray[registerMap["v0"]] == 5) {
//cerr << "the syscall type is 5\n";
/*						fstream out;
						out.open("array_test1-mahaojun.in" , ios::in);
						int cnt = 0;
						while (!out.eof()) {
							out >> registerArray[registerMap["v0"]];
						}
						out.close();*/
						cin >> registerArray[registerMap["v0"]];
//cout << registerArray[registerMap["v0"]] << "\n";
						continue;
					}
					if (registerArray[registerMap["v0"]] == 8) {
//cerr << "the syscall type is 8\n";
						string s , tar;
					/*	fstream out;
						out.open("array_test1-mahaojun.in" , ios::in);
						getline(out , s);
						for (int k = 0; k < vec[i].length(); ++k) {
							tar += s[k];
							if (s[k] == '\0') break;
						}
						registerArray[registerMap["a1"]] = tar.length() + 1;
						registerArray[registerMap["a0"]] = ptr;
						for (int k = 0; k < tar.length(); ++k) {
							mem[ptr] = tar[k];
							++ptr;
						}*/
						getline(cin , s);
//cout << s << "\n";
						if (s.length() == 0) getline(cin , s); 
//cout << "reread" << s << " ******** " << s.length() << "\n";
						int k = 0;
						while (s[k] == '\0' || s[k] == '\n' || s[k] == ' ' || s[k] == '\t') ++k;
						for (; k < s.length() && tar.length() < registerArray[registerMap["a1"]] - 1; ++k) {
							if (s[k] == '\n' || s[k] == '\t' || s[k] == '\0' || s[k] == ' ') break;
							tar += s[k];
						}
						int _ptr;
						_ptr = registerArray[registerMap["a0"]];
						for (k = 0; k < tar.length(); ++k) {
							mem[_ptr] = tar[k];
							++_ptr;
						}
//cout << tar << "\n";
						mem[_ptr] = '\0';
						continue;
					}
					if (registerArray[registerMap["v0"]] == 9) {
//cerr << "the syscall type is 9\n";
						registerArray[registerMap["v0"]] = ptr;
						ptr += registerArray[registerMap["a0"]];
						continue;
					}
					if (registerArray[registerMap["v0"]] == 10) {
//cerr << "the syscall type is 10\n";
//						cout << 0;
						exit(0);
						break;
					}
					if (registerArray[registerMap["v0"]] == 17) {
//cerr << "the syscall type is 17\n";
			//			cout << 0;
						exit(registerArray[registerMap["a0"]]);
						break;
					}
				}
/*		for (int k = 0; k < ptr; ++k) {
			cout << k << ' ' << (int)mem[k] << "\n";;
		}
		cout << "\n";*/
/*		cout <<i <<' ' <<vec[i] <<endl;
		
		for (int k = 0; k < 34; k++) cout <<registerArray[k] <<'\t';
		cout <<endl<<endl;*/
//getchar();
//system("pause");
//cout << i << "\n";
/*++graham;
if (graham > 10000000) return;*/
	}
	return;
}



int main(int argc, char **argv) {
	int i , j , k , l;
	init();
	instruction_fetch();
	string s;
//	freopen ("array_test1-mahaojun.s" , "r" , stdin);                                      //testdata.txt
	ifstream infile(argv[1]);           //array_test2-mahaojun.s
	int cnt = 0;
	bool flag = false;
/*	while (!cin.eof()) {
		getline(cin , s);
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		++cnt;
		vec.push_back(s);
//cout << s << "\n";
	}*/
		getline(infile , s);
	while (!infile.eof()) {
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		++cnt;
		vec.push_back(s);
		getline(infile , s);
	}
	
//cout << "test fetch ok\n";
	decode_preparation();
	
	
	
	
	
	/*map <string, int>::iterator it;
	it = label.begin();
	for (;it != label.end(); it++) {
		cout << (*it).first << ' ' << (*it).second << endl;
	}
	cout << endl;*/
	
	
	
	
/*	for (i = 0; i < vec.size(); ++i) {
		cout << vec[i] << "\n";
	}*/
//cout << "test decode ok\n";
//freopen ("prime-5100309153-yanghuan.in" , "r" , stdin); //array_test1-mahaojun
//freopen ("ans.out" , "w" , stdout);
//cout << "**********************************************" << label["main"] << "\n";
/*	for (i = 0; i < ptr; ++i) {
		if (mem[i] == '\n') {
			cout << 'n';
			continue;
		}
		if (mem[i] == '\0') {
			cout << 'o';
			continue;
		}
		cout << mem[i];
	}
	cout << "\n";*/
	execution();
//cout << "test execution ok\n";

	return 0;
}
