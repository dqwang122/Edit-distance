#include <time.h>
#include "stdio.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

using namespace std;

int main()
{
	string infile, outfile;
	int task;
	cout << "infile: ";
	cin >> infile;
	cout << "outfile: ";
	cin >> outfile;
	cout << "Task(input 1 / 2 / 3):";
	cin >> task;

	// infile = "test.txt";
	// outfile = "out.txt";
	
	clock_t start = clock();

	if(task == 1)
		Task1(infile, outfile);
	else if(task==2)
		Task2(infile, outfile);
	else if(task==3)
		Task3(infile, outfile);
	else
		cout << "Wrong input!" << endl;

	clock_t end = clock();

	cout << "Running time is : " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}

