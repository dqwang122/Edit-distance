#include "task2.h"

#define MAX_NODE 10000
#define MAX_LEN 10000

int CharNum;

int readfile2(string infile, string* a, string* nodes) {
	ifstream fin(infile);
	int nodeNum;
	fin >> *a >> nodeNum;
	for (int i = 0; i < nodeNum; i++) {
		fin >> nodes[i];
	}
	fin.close();
	return nodeNum;
};

void writefile2(string outfile, string s, int dist, int *Ops, char *Obj, int *Pos) {
	ofstream fout(outfile);
	fout << s << '\n';
	fout << dist << '\n';
	for (int i = dist - 1; i >= 0; i--) {
		int op;
		string outstr;
		op = Ops[i];
		if (op == 0 || op == -1)
			outstr = Operate[op] + ' ' + to_string(Pos[i]);
		else
			outstr = Operate[op] + ' ' + to_string(Pos[i]) + ' ' + Obj[i];
		fout << outstr << '\n';
	}
	fout.close();
}

void get_char(string a, char* c) {
	int cnt = 0;
	c[cnt++] = a[0];
	for (int i = 1; i < a.length() && cnt < 4; i++) {
		int k = 0;
		for (k = 0; k < cnt; k++) {
			if (a[i] == c[k])
				break;
		}
		if (k == cnt)
			c[cnt++] = a[i];
	}
	CharNum = cnt;
	c[cnt] = '\0';
}

// BKDR Hash 
unsigned int BKDRHash(const char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

map<int, int> CreatGraph(string *nodes, int nodeNum, char* Cset, Edge *edges) {
	map<int, int> HashNode;
	for (int i = 0; i < nodeNum; i++) {
		int key = BKDRHash(nodes[i].c_str());
		HashNode[key] = i;
	}
	for (int i = 0; i < nodeNum; i++) {
		string str = nodes[i];
		for (int k = 0; k < CharNum; k++) {
			string nstr = str.substr(1, str.length()) + Cset[k];
			int starthash = BKDRHash(nstr.c_str());
			/*if (nstr == str)
				continue;*/
			if (HashNode.find(starthash) != HashNode.end()) {
				int idx = HashNode.find(starthash) -> second;
				edges[i].adjList.push_back(idx);
			}
		}
	}
	return HashNode;
}

void Show(map<int, int> HashNode, Edge *edges, int nodeNum, string* nodes) {
	ofstream fout("edges.txt");
	for (int i = 0; i < nodeNum; i++) {
		list<int>::iterator p = edges[i].adjList.begin();
		while (p != edges[i].adjList.end()) {
			fout << nodes[i] << " -> ";
			string cur = nodes[*p];
			int hashvalue = BKDRHash(cur.c_str());
			if (HashNode.find(hashvalue) != HashNode.end()) {
				int end = HashNode.find(hashvalue)->second;
				fout << nodes[end] << '\n';
			}
			p++;
		}
	}
}

void showarray(int** a, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << ",";
		cout << endl;
	}
}

void EditDis_inner(string a, string b, int** edit) {
	int m = a.length();
	int n = b.length();
	for (int i = 0; i <= m; i++)
		edit[i][0] = i;
	for (int j = 0; j <= n; j++)
		edit[0][j] = j;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			int diff = (a[i - 1] == b[j - 1] ? 0 : 1);
			int DEL = edit[i - 1][j] + 1;
			int INS = edit[i][j - 1] + 1;
			int SUB = edit[i - 1][j - 1] + diff;
			if (DEL <= INS && DEL <= SUB) {
				edit[i][j] = DEL;
			}
			else if (INS <= DEL && INS <= SUB) {
				edit[i][j] = INS;
			}
			else {
				edit[i][j] = SUB;
			}
		}
	}
	int dist = edit[m][n];
}

int Findmin(Edge *edges, int nodeNum, string* nodes, string a, string start, string *curminstr, int startid) {
	int k = nodes[0].length();
	int target = a.length();
	int **edit;
	edit = new int*[k + 1];

	for (int i = 0; i <= k; i++) {
		edit[i] = new int[target + 1]{ 0 };
	}

	int **curedit;
	curedit = new int*[2];
	curedit[0] = new int[target + 1]{ 0 };
	curedit[1] = new int[target + 1]{ 0 };
	int *pre = new int[target + 1];

	int* flag = new int[nodeNum] {0};

	string cur = start;
	int exlen = 0;
	int curmin;

	EditDis_inner(start, a, edit);
	//showarray(edit, k + 1, target + 1);
	curmin = edit[k][target];
	*curminstr = start;

	//for (int h = 0; h <= target; h++) {
	//	pre[h] = edit[k][h];
	//}
	memcpy(&pre[0], &edit[k][0], sizeof(int)*(target + 1));

	queue<int> qu;
	queue<int*> preedit;
	queue<string> str;

	flag[startid] = 1;
	qu.push(startid);
	preedit.push(pre);
	str.push(start);

	while (!qu.empty()) {
		int idx = qu.front();
		qu.pop();
		int *ppre = preedit.front();
		preedit.pop();
		string s = str.front();
		str.pop();
		memcpy(&curedit[0][0], &ppre[0], sizeof(int)*(target + 1));
		list<int>::iterator p = edges[idx].adjList.begin();
		while (p != edges[idx].adjList.end()) {
			exlen++;
			string c = nodes[*p].substr(k - 1, k);
			cur = s + c;

			curedit[1][0] = cur.length();
			for (int h = 1; h <= target; h++) {
				int diff = (cur[cur.length() - 1] == a[h - 1] ? 0 : 1);
				int DEL = curedit[0][h] + 1;
				int INS = curedit[1][h - 1] + 1;
				int SUB = curedit[0][h - 1] + diff;
				if (DEL <= INS && DEL <= SUB) {
					curedit[1][h] = DEL;
				}
				else if (INS <= DEL && INS <= SUB) {
					curedit[1][h] = INS;
				}
				else {
					curedit[1][h] = SUB;
				}
			}

			//cout << endl;
			//showarray(curedit, 2, target + 1);

			if (flag[*p] == 0 || curmin > curedit[1][target]) {
				qu.push(*p);
				int *temp = new int[target + 1];
				memcpy(&temp[0], &curedit[1][0], sizeof(int)*(target + 1));
				preedit.push(temp);
				str.push(cur);
			}
			if (curmin > curedit[1][target]) {
				curmin = curedit[1][target];
				*curminstr = cur;
			}

			exlen--;
			flag[*p] = 1;
			++p;

		}
		delete[] ppre;
		ppre = NULL;
		exlen++;

	}
	delete[] curedit[0];
	delete[] curedit[1];
	delete[] flag;
	return curmin;
}

string MinEdit(Edge *edges, int nodeNum, string* nodes, string a) {
	int k = nodes[0].length();
	int target = a.length();
	int min = k - 1 + MAX_LEN;
	//int min = 0.3 * target;
	string minstr = nodes[0];

	string curminstr;
	int curmin;

	for (int i = 0; i < nodeNum; i++) {
		string start = nodes[i];
		
		curmin = Findmin(edges, nodeNum, nodes, a, start, &curminstr, i);

		if (min > curmin) {
			min = curmin;
			minstr = curminstr;
		}
	}
	return minstr;
};

void Task2(string infile, string outfile) {
	string a, s;
	int nodeNum;
	string *nodes = new string[MAX_NODE];
	nodeNum = readfile2(infile, &a, nodes);

	char *Charset = new char[5];
	get_char(a, Charset);
	Edge *edges = new Edge[MAX_NODE];
	map<int, int> HashNode = CreatGraph(nodes, nodeNum, Charset, edges);
	Show(HashNode, edges, nodeNum, nodes);

	s = MinEdit(edges, nodeNum, nodes, a);

	int dist;
	int *Ops, *Pos;
	char *Obj;
	Ops = new int[MAX_LEN];
	Pos = new int[MAX_LEN];
	Obj = new char[MAX_LEN];
	dist = EditDis(a, s, Ops, Obj, Pos);
	writefile2(outfile, s, dist, Ops, Obj, Pos);
};