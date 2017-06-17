#ifndef TASK2_H
#define TASK2_H

#include "task1.h"
#include <cstdlib>
#include <map>
#include <list>
#include <queue>
// #include <Windows.h>
#include<cstring>

#define MAX_NODE_NUM 10000
#define MAX_LEN 10000
#define MAX_NODE_NUM_L 1000000

struct Edge {
	int node,weight;
	list<int> adjList;
};

int readfile2(string infile, string* a, string* nodes);
void writefile2(string outfile, string s, int dist, int *Ops, char *Obj, int *Pos);
void get_char(string a, char* c);
unsigned int BKDRHash(const char *str);
map<int, int> CreatGraph(string *nodes, int nodeNum, char* Cset, Edge *edges);
void showarray(int* a, int m);
void Show(map<int, int> HashNode, Edge *edges, int nodeNum, string* nodes);
void EditDis_inner(string cur, string a, int* ppre, int* curedit);
int Findmin(Edge *edges, int nodeNum, string* nodes, string a, string start, string *curminstr, int startid);
int MinEdit(Edge *edges, int nodeNum, string* nodes, string a, string *s);
void Task2(string infile, string outfile);

#endif