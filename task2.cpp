#include "task2.h"


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
	ofstream fout;
	fout.open("edges.txt");
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
	fout.close();
}

void showarray(int* a, int m) {
	for (int i = 0; i < m; i++) {
		cout << a[i] << ",";
	}
	cout << endl;
}

void EditDis_inner(string cur, string a, int* ppre, int* curedit) {
	int target = a.length();
	curedit[0] = cur.length();
	char c = cur[cur.length() - 1];
	for (int h = 1; h <= target; h++) {
		int diff = (c == a[h - 1] ? 0 : 1);
		int DEL = ppre[h] + 1;
		int INS = curedit[h - 1] + 1;
		int SUB = ppre[h - 1] + diff;
		if (DEL <= INS && DEL <= SUB) {
			curedit[h] = DEL;
		}
		else if (INS <= DEL && INS <= SUB) {
			curedit[h] = INS;
		}
		else {
			curedit[h] = SUB;
		}
	}
}

int Findmin(Edge *edges, int nodeNum, string* nodes, string a, string start, string *curminstr, int startid) {
	int k = nodes[0].length();
	int target = a.length();
	
	int *curedit = new int[target + 1]{ 0 };
	int *pre = new int[target + 1]{ 0 };
	int cnt = 0;
	for (int* i = pre; i - pre <= target; i++, cnt++)
		*i = cnt;
	

	int* flag = new int[nodeNum] {0};

	string cur = start;
	int exlen = 0;
	int curmin;

	//showarray(pre, target + 1);
	for(int i = 1; i <= start.length(); i++){
		EditDis_inner(start.substr(0, i), a, pre, curedit);
		//showarray(curedit, target + 1);
		memcpy(pre, curedit, sizeof(int)*(target + 1));
	}
	//cout << endl;

	curmin = curedit[target];
	*curminstr = start;

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
		// memcpy(&curedit[0][0], &ppre[0], sizeof(int)*(target + 1));
		list<int>::iterator p = edges[idx].adjList.begin();
		while (p != edges[idx].adjList.end()) {
			exlen++;
			char c = nodes[*p][k-1];
			cur = s + c;

			EditDis_inner(cur, a, ppre, curedit);

			/*cout << endl;
			showarray(pre, target + 1);
			showarray(curedit, target + 1);*/


			if (flag[*p] == 0 || curmin > curedit[target]) {
				qu.push(*p);
				int *temp = new int[target + 1];
				memcpy(&temp[0], &curedit[0], sizeof(int)*(target + 1));
				preedit.push(temp);
				str.push(cur);
			}
			if (curmin > curedit[target]) {
				curmin = curedit[target];
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
	delete[] curedit;
	delete[] flag;
	return curmin;
}

int MinEdit(Edge *edges, int nodeNum, string* nodes, string a, string *minstr) {
	int k = nodes[0].length();
	int target = a.length();
	int min = k - 1 + MAX_LEN;
	//int min = 0.3 * target;
	*minstr = nodes[0];

	string curminstr;
	int curmin;

	for (int i = 0; i < nodeNum; i++) {
		string start = nodes[i];
		
		curmin = Findmin(edges, nodeNum, nodes, a, start, &curminstr, i);

		if (min > curmin) {
			min = curmin;
			*minstr = curminstr;
		}
		printf("%.2lf%%\r", i * 100.0 / nodeNum);
	}
	return min;
};

void Task2(string infile, string outfile) {
	string a, s;
	int nodeNum;
	string *nodes = new string[MAX_NODE_NUM_L];
	nodeNum = readfile2(infile, &a, nodes);

	char *Charset = new char[5];
	get_char(a, Charset);
	Edge *edges = new Edge[MAX_NODE_NUM_L];
	map<int, int> HashNode = CreatGraph(nodes, nodeNum, Charset, edges);
	// Show(HashNode, edges, nodeNum, nodes);
	cout << "Create Graph complete." << endl;

	int dist;
	dist = MinEdit(edges, nodeNum, nodes, a, &s);

	int *Ops, *Pos;
	char *Obj;
	Ops = new int[dist];
	Pos = new int[dist];
	Obj = new char[dist];
	dist = EditDis(a, s, Ops, Obj, Pos);
	writefile2(outfile, s, dist, Ops, Obj, Pos);
};