#include "task3.h"
#include "tool.h"

int f[BLOCKSIZE][MAX_NODE_NUM];
int pathF[BLOCKSIZE][MAX_NODE_NUM];
int preF[MAX_NODE_NUM];
int curF[MAX_NODE_NUM];

void writepath(int m, int n, string filename) {
	ofstream fout(filename, ios::ate);
	fout << ' ' << "Nodes" << endl;
	for (int i = 0; i < m; i++) {
		fout << i << ',';
		for(int j =0; j < n-1; j++)
			fout << pathF[i][j] << ",";
		fout << pathF[i][n - 1] << endl;;
	}
	fout.close();
}

void readinit(int m, int n, string filename) {
	ifstream fin(filename);
	char c;
	int t;
	string temp;
	getline(fin, temp);
	for (int i = 0; i < m; i++) {
		fin >> t >> c;
		for (int j = 0; j < n-1; j++)
			fin >> f[i][j] >> c;
		fin >> f[i][n-1];
	}
	fin.close();
}

void readpath(int m, int n, string filename) {
	ifstream fin(filename);
	char c;
	int t;
	string temp;
	getline(fin, temp);
	for (int i = 0; i < m; i++) {
		fin >> t >> c;
		for (int j = 0; j < n - 1; j++)
			fin >> pathF[i][j] >> c;
		fin >> f[i][n - 1];
	}
	fin.close();
}

string restr(int argmin, string a, string* nodes, int nodeNum) {
	char ch[MAX_LEN_L];

	int target = a.length();
	int k = nodes[0].length();
	int curid = argmin;
	
	int cnt = 0;
	int nowblock = -1;
	int blockNo = target / BLOCKSIZE;
	ch[cnt++] = nodes[curid][k - 1];
	for (int i = target; i > 0; ) {
		int imod = i % BLOCKSIZE;
		if (nowblock != blockNo) {
			readpath(BLOCKSIZE, nodeNum, to_string(blockNo) + ".csv");
			nowblock = blockNo;
		}
		else
			ch[cnt++] = nodes[curid][k - 1];

		while (i > 1 && imod >= 0 && pathF[imod][curid] == -1) {
			imod--;
			i--;
		}
		if (imod < 0) {
			blockNo--;
			continue;
		}
		if (i == 1)
			break;
		else {
			curid = pathF[imod][curid];
			i--;
		}
	}

	string str;
	if (pathF[1][curid] == -1) {
		str = nodes[curid];
		for (int i = cnt - 2; i >= 0; i--) {
			str += ch[i];
		}
	}
	else {
		str = nodes[curid];
		for (int i = cnt - 1; i >= 0; i--) {
			str += ch[i];
		}
	}
	return str;
}

int EditDis_inner_L(string a, string b, int** edit) {
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
	return dist;
};

int MinEdit_L(Edge *edges, int nodeNum, string* nodes, string a, int* argmin) {
	int k = nodes[0].length();
	int target = a.length();
	//int min = 0.3 * target;
	int min = k - 1 + MAX_LEN;

	queue<int> update;

	for (int i = 1; i <= target; i++) {
		string str = a.substr(0, i);

		int imod = i % BLOCKSIZE;
		if (i == 1 || imod == 0) {
			int No = i / BLOCKSIZE;
			readinit(BLOCKSIZE, nodeNum, to_string(No) + ".csv");
		}

		if (i == 1) {
			memcpy(&preF, &f[0], sizeof(int) * nodeNum);
			memcpy(&curF, &f[1], sizeof(int) * nodeNum);
		}
		else {
			memcpy(&preF[0], &curF[0], sizeof(int) * nodeNum);
			memcpy(&curF[0], &f[imod][0], sizeof(int) * nodeNum);
		}

		for (int j = 0; j < nodeNum; j++) {
			pathF[imod][j] = -1;
			update.push(j);
		}
		while (!update.empty()) {
			string pre;
			string cur;
			int idx = update.front();
			update.pop();
			pre = nodes[idx];
			list<int>::iterator p = edges[idx].adjList.begin();
			while (p != edges[idx].adjList.end()) {
				//relax
				char c = nodes[*p][k - 1];
				char now = str[i - 1];

				//EditDis_inner(cur, str, preedit, curedit);
				int temp;
				int diff = (c == now ? 0 : 1);
				int DEL = preF[*p] + 1;
				int INS = curF[idx] + 1;
				int SUB = preF[idx] + diff;
				if (DEL <= INS && DEL <= SUB) {
					temp = DEL;
				}
				else if (INS <= DEL && INS <= SUB) {
					temp = INS;
				}
				else {
					temp = SUB;
				}

				if (curF[*p] > temp) {
					update.push(*p);
					curF[*p] = temp;
					pathF[imod][*p] = idx; //save pre nodeid
				}
				p++;
			}
		}

		// save the path
		if (i == target || imod == BLOCKSIZE - 1) {
			int No = i / BLOCKSIZE;
			if (i != target) {
				writepath(BLOCKSIZE, nodeNum, to_string(No) + ".csv");
			}
			else
				writepath(imod + 1, nodeNum, to_string(No) + ".csv");
		}

		printf("%.2lf%%\r", (double)(i * 100.0 / target));
	}
	printf("\n");

	for (int i = 0; i < nodeNum; i++) {
		if (min > curF[i]) {
			min = curF[i];
			*argmin = i;
		}
	}
	return min;
};

void initArray(int nodeNum, string* nodes, string a) {
	int k = nodes[0].length();
	int target = a.length();

	ofstream fout("pre.csv");
	for (int j = 0; j < nodeNum; j++) {
		// for the node itself as start  
		string node = nodes[j];		
		
		int **edit;
		edit = new int*[target + 1];
		for (int i = 0; i <= target; i++) {
			edit[i] = new int[k + 1]{ 0 };
		}

		int dist = EditDis_inner_L(a, node, edit);
		
		// Todo: save edit!
		for (int i = 0; i <= target; i++) {
			fout << edit[i][k] << ",";
		}
		fout << endl;

		/*for (int i = 0; i <= target; i++) {
			f[i][j] = edit[i][k];
		}*/

		for (int i = 0; i <= target; i++) {
			delete[] edit[i];
		}
		delete[] edit;
		printf("%.2lf%%\r", (double)(j * 100.0 / nodeNum));
		
	}
	printf("\n");
	fout.close();
}

void Task3(string infile, string outfile) {
	string a, s;
	int nodeNum;
	string *nodes = new string[MAX_NODE_NUM_L];
	nodeNum = readfile2(infile, &a, nodes);

	char *Charset = new char[5];
	get_char(a, Charset);
	Edge *edges = new Edge[MAX_NODE_NUM_L];
	map<int, int> HashNode = CreatGraph(nodes, nodeNum, Charset, edges);
	//Show(HashNode, edges, nodeNum, nodes);
	cout << "Create Graph complete." << endl;

	int k = nodes[0].length();
	int target = a.length();
	for (int j = 0; j < nodeNum; j++)
		f[0][j] = k;
	initArray(nodeNum, nodes, a);
	cout << "Init F[i][j] complete." << endl;

	// string str;
	// int dist;
	// str = Connect(nodes, a, nodeNum, edges);

	int dist;
	int argmin = -1;
	dist = MinEdit_L(edges, nodeNum, nodes, a, &argmin);
	cout << dist << endl;
	cout << argmin << endl;
	cout << nodes[argmin] << endl;

	string str = restr(argmin, a, nodes, nodeNum);
	cout << str << endl;
	ofstream fout("string.txt");
	fout << str << endl;
	fout.close();

	int *Ops, *Pos;
	char *Obj;
	Ops = new int[MAX_LEN_L];
	Pos = new int[MAX_LEN_L];
	Obj = new char[MAX_LEN_L];
	dist = EditDis(a, str, Ops, Obj, Pos);
	writefile2(outfile, str, dist, Ops, Obj, Pos);
};