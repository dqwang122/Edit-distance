#include <time.h>
#include "stdio.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

using namespace std;

int main()
{
	string infile, outfile;
	//cout << "infile: ";
	//cin >> infile;
	//cout << "outfile: ";
	//cin >> outfile;

	infile = "Task2/task2.in";
	outfile = "out.txt";
	
	clock_t start = clock();

	//Task1(infile, outfile);
	Task3(infile, outfile);

	clock_t end = clock();

	cout << "Running time is : " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}

