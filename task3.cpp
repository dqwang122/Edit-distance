#include "task3.h"

int f[MAX_LEN][MAX_NODE_NUM];

void writetemp(int* a, int m, string filename) {
	ofstream fout(filename, ios::ate);
	for (int i = 0; i < m; i++) {
			fout << a[i] << " ";
	}
	fout << '\n';
}

void readtemp(int** a, int m, int n, string filename) {
	ifstream fin(filename);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			fin >> a[i][j];
	}
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

int MinEdit_L(Edge *edges, int nodeNum, string* nodes, string a) {
	int k = nodes[0].length();
	int target = a.length();
	//int min = 0.3 * target;
	int min = k - 1 + MAX_LEN;

	queue<int> update;

	for (int i = 1; i <= target; i++) {
		string str = a.substr(0, i);

		// if i % BLOCKSIZE == 0, read the file of i/BLOCKSIZE into f[BLOCKSIZE][TAREGT + 1]

		for (int j = 0; j < nodeNum; j++) {
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
				int DEL = f[i - 1][*p] + 1;
				int INS = f[i][idx] + 1;
				int SUB = f[i - 1][idx] + diff;
				if (DEL <= INS && DEL <= SUB) {
					temp = DEL;
				}
				else if (INS <= DEL && INS <= SUB) {
					temp = INS;
				}
				else {
					temp = SUB;
				}

				if (f[i][*p] > temp) {
					update.push(*p);
					f[i][*p] = temp;
				}
				p++;
			}
		}
		printf("%.2lf%%\r", i * 100.0 / target);
	}

	for (int i = 0; i < nodeNum; i++) {
		if (min > f[target][i])
			min = f[target][i];
	}
	return min;
};

void initArray(int nodeNum, string* nodes, string a) {
	int k = nodes[0].length();
	int target = a.length();

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
		/*ofstream fout("pre_"+ to_string(j) +".out");
		for (int i = 0; i <= target; i++) {
			fout << edit[i][k] << " ";
		}*/

		for (int i = 0; i <= target; i++) {
			f[i][j] = edit[i][k];
		}

		for (int i = 0; i <= target; i++) {
			delete[] edit[i];
		}
		delete[] edit;
		
		//fout << '\n';
		//fout.close();
	}
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
	// Show(HashNode, edges, nodeNum, nodes);
	cout << "Create Graph complete." << endl;

	int k = nodes[0].length();
	int target = a.length();
	for (int j = 0; j < nodeNum; j++)
		f[0][j] = k;
	initArray(nodeNum, nodes, a);
	cout << "Init F[i][j] complete." << endl;


	int dist;
	dist = MinEdit_L(edges, nodeNum, nodes, a);
	cout << dist << endl;

	//int *Ops, *Pos;
	//char *Obj;
	//Ops = new int[dist];
	//Pos = new int[dist];
	//Obj = new char[dist];
	//dist = EditDis(a, s, Ops, Obj, Pos);
	//writefile2(outfile, s, dist, Ops, Obj, Pos);
};