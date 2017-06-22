#ifndef TASK1_H
#define TASK1_H

#include "tool.h"

const vector<string> Operate = { "DEL", "INS", "SUB" };

void readfile(string infile, string* lines);
void Task1(string infile, string outfile);
int EditDis(string a, string b, int *Ops, char *Obj, int *Pos);
void writefile(string outfile, int dist, int *Ops, char *Obj, int *Pos);


#endif
