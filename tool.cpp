#include "tool.h"

int stringlen[MAX_NODE_NUM_L];

int Countlen(Edge *edges, int nodeNum, string* nodes, string start, int startid) {
	int k = nodes[0].length();

	queue<int> qu;
	queue<int> len;

	qu.push(startid);
	len.push(k);
	int length = 0;

	while (!qu.empty()) {
		int idx = qu.front();
		qu.pop();
		length = len.front();
		len.pop();
		list<int>::iterator p = edges[idx].adjList.begin();
		while (p != edges[idx].adjList.end()) {
			qu.push(*p);
			len.push(length+1);
			p++;
		}
	}
	return length;
};

void Createlen(Edge *edges, int nodeNum, string* nodes) {
	int length[MAX_NODE_NUM_L];
	ofstream fout("length.txt");
	for (int i = 0; i < nodeNum; i++) {
		length[i] = Countlen(edges, nodeNum, nodes, nodes[i], i);
		fout << i << '\t' << length[i] << endl;
	}
	fout.close();

}