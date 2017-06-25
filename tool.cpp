#include "tool.h"
#include "task1.h"
#define random(x) (rand()%x)

int stringlen[MAX_NODE_NUM_L];

int Countlen(Edge *edges, int nodeNum, string* nodes, string start, int startid) {
	int k = nodes[0].length();

	int length = k;
	list<int>::iterator p = edges[startid].adjList.begin();

	int id = startid;
	while (p != edges[id].adjList.end()) {
		id = *p;
		length++;
		//cout << length << endl;
		if (length > MAX_LEN_L)
			break;
		p = edges[id].adjList.begin();
	}

	/*queue<int> qu;
	queue<int> len;

	qu.push(startid);
	len.push(k);
	int length = 0;*/

	/*while (!qu.empty()) {*/
		/*int idx = qu.front();
		qu.pop();
		length = len.front();
		len.pop();
		cout << length << endl;
		if (length > MAX_LEN_L)
			break;*/
		/*list<int>::iterator p = edges[idx].adjList.begin();*/
		/*while (p != edges[idx].adjList.end()) {
			qu.push(*p);
			len.push(length+1);
			p++;
		}*/

	/*}*/
	return length;
};

void Createlen(Edge *edges, int nodeNum, string* nodes) {
	ofstream fout("length.csv");
	for (int i = 0; i < nodeNum; i++) {
		int length = Countlen(edges, nodeNum, nodes, nodes[i], i);
		fout << i << ',' << length << endl;
		cout << i << ',' << length << endl;
		printf("%.2lf%%\r", (double)(i * 100.0 / nodeNum));
		cout << endl;
	}
	fout.close();

}

void Findpos(string a, string b, set<int> *argmin) {
	int m = a.length();
	int n = b.length();
	int **edit, **Ops;
	edit = new int*[m + 1];
	Ops = new int*[m + 1];
	for (int i = 0; i <= m; i++) {
		edit[i] = new int[n + 1]{ 0 };
		Ops[i] = new int[n + 1]{ 0 };
	}
	for (int i = 0; i <= m; i++)
		edit[i][0] = i;

	int op;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			int diff = (a[i - 1] == b[j - 1] ? 0 : 1);
			int DEL = edit[i - 1][j] + 1;
			int INS = edit[i][j - 1] + 1;
			int SUB = edit[i - 1][j - 1] + diff;

			if (DEL <= INS && DEL <= SUB) {
				edit[i][j] = DEL;
				op = 0;
			}
			else if (INS <= DEL && INS <= SUB) {
				edit[i][j] = INS;
				op = 1;
			}
			else {
				edit[i][j] = SUB;
				op = 2;
			}
			Ops[i][j] = op;

		}
	}
	
	/*int* cp = new int[n];*/
	//memcpy(cp, edit[m], n * sizeof(int));
	//sort(cp, cp + n);
	int min = *min_element(edit[m], edit[m]+n);
	//delete[] cp;

	int cnt = 0;
	int *temp = new int[MAX_LEN_L];
	for (int j = 0; j <= n; j++) {
		if (edit[m][j] == min) {
			temp[cnt++] = j;
		}
	}

	for (int k = 0; k < cnt; k++) {
		int pos = temp[k];
		op = Ops[m][pos];
		for (int i = m - 1; i > 0;) {
			if (op == 0) {
				i--;
				op = Ops[i][pos];
			}
			else if (op == 1) {
				pos--;
				op = Ops[i][pos];
			}
			else {
				i--;
				pos--;
				op = Ops[i][pos];
			}
		}
		argmin->insert(pos);
	}

	for (int i = 0; i <= m; i++) {
		delete[] edit[i];
		delete[] Ops[i];
	}
	delete[] edit;
	delete[] Ops;

	delete[] temp;
}


string Connect(string *nodes, string a, int nodeNum, Edge *edges) {
	set<int> *PosTable = new set<int>[nodeNum];
	int target = a.length();
	int k = nodes[0].length();
	string str;
	vector<int> start;
	for (int i = 0; i < nodeNum; i++) {
		int cnt;
		Findpos(nodes[i], a, &PosTable[i]);
		if (PosTable[i].find(0) != PosTable[i].end())
			start.push_back(i);
		printf("%.2lf%%\r", (double)(i * 100.0 / target));
	}

	cout << "Save file ..." << endl;
	ofstream fout("PosTable.txt");
	for (int i = 0; i < nodeNum; i++) {
		set<int>::iterator p = PosTable[i].begin();
		while (p != PosTable[i].end()) {
			fout << *p << " ";
			p++;
		}
		fout << endl;
	}

	// srand((int)time(0));
	// int pre;
	// for (int i = 0; i < target; i++) {
		// if (i == 0) {
			// int idx = random(start.size());
			// str = nodes[idx];
			// pre = idx;
		// }
		// list<int>::iterator p = edges[pre].adjList.begin();
		// int cnt = 0;
		// int whole = 0;
		// int next[4], total[4];
		// while (p != edges[pre].adjList.end()) {
			// if (PosTable[*p].find(i+1) != PosTable[*p].end()) {
				// next[cnt++] = *p;
			// }
			// total[whole++] = *p;
			// p++;
		// }
		// if (cnt) {
			// int idx = random(cnt);
			// str += nodes[next[idx]][k - 1];
			// pre = next[idx];
		// }
		// else if (whole) {
			// int idx = random(whole);
			// str += nodes[total[idx]][k - 1];
			// pre = total[idx];
		// }
		// else
			// break;
	// }
	cout << str << endl;
	return str;
}