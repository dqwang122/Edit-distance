#ifndef TASK2_H
#define TASK2_H

#include "task1.h"
#include <cstdlib>
#include <map>
#include <list>
#include <queue>

struct Edge {
	int node,weight;
	list<int> adjList;
};

int readfile2(string infile, string* a, string* nodes);
void writefile2(string outfile, string s, int dist, int *Ops, char *Obj, int *Pos);
void get_char(string a, char* c);
unsigned int BKDRHash(const char *str);
map<int, int> CreatGraph(string *nodes, int nodeNum, char* Cset, Edge *edges);
void Show(map<int, int> HashNode, Edge *edges, int nodeNum, string* nodes);
void EditDis_inner(string a, string b, int** edit);
int Findmin(Edge *edges, int nodeNum, string* nodes, string a, string start, string *curminstr, int startid);
string MinEdit(Edge *edges, int nodeNum, string* nodes, string a);
void Task2(string infile, string outfile);

#endif