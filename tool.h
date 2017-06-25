#ifndef TOOL_H
#define TOOL_H

#include "stdio.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include<cstring>
#include<set>
#include<time.h>

using namespace std;

#define MAX_NODE_NUM 10000
#define MAX_LEN 10000
#define MAX_NODE_NUM_L 1000000

#define MAX_LEN_L 100000
#define MAX_NODE_NUM_L 1000000
//#define BLOCKSIZE 128
#define BLOCKSIZE 2

struct Edge {
	int node, weight;
	list<int> adjList;
};

int Countlen(Edge *edges, int nodeNum, string* nodes, string start, int startid);
void Createlen(Edge *edges, int nodeNum, string* nodes);
string Connect(string *nodes, string a, int nodeNum, Edge *edges);

#endif
