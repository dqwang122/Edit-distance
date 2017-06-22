#include "task1.h"

void readfile(string infile, string* lines) {
	ifstream fin(infile);
	fin >> lines[0] >> lines[1];
	fin.close();
};

int EditDis(string a, string b, int *Ops, char *Obj, int *Pos) {
	int m = a.length();
	int n = b.length();
	int **edit, **path;
	edit = new int*[m + 1];
	path = new int*[m + 1];
	for (int i = 0; i <= m; i++) {
		edit[i] = new int[n + 1]{ 0 };
		path[i] = new int[n + 1]{ 0 };
	}
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

			int op;
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

			if (op == 2 && diff == 0)
				path[i][j] = -1;
			else
				path[i][j] = op;
		}
	}
	int dist = edit[m][n];
	int i = m;
	int j = n;
	int cnt = 0;
	while (i != 0 || j != 0) {
		switch (path[i][j]) {
		case 0:
			Ops[cnt] = 0;
			Obj[cnt] = '-';
			Pos[cnt] = i - 1;
			cnt++;
			i--;
			break;
		case 1:
			Ops[cnt] = 1;
			Obj[cnt] = b[j - 1];
			Pos[cnt] = i;
			cnt++;
			j--;
			break;
		case 2:
			Ops[cnt] = 2;
			Obj[cnt] = b[j - 1];
			Pos[cnt] = i - 1;
			cnt++;
			i--;
			j--;
			break;
		default:
			i--;
			j--;
			break;
		}
	}
	return dist;
}

void writefile(string outfile, int dist, int *Ops, char *Obj, int *Pos) {
	ofstream fout(outfile);
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

void Task1(string infile, string outfile) {
	string *lines = new string[2];
	readfile(infile, lines);
	string a = lines[0];
	string b = lines[1];
	int dist;
	int *Ops, *Pos;
	char *Obj;
	Ops = new int[10000];
	Pos = new int[10000];
	Obj = new char[10000];
	dist = EditDis(a, b, Ops, Obj, Pos);
	writefile(outfile, dist, Ops, Obj, Pos);
}