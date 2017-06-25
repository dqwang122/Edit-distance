import argparse
import types
import time
from tools import *

Operate = ["DEL", "INS", "SUB"]

# Read standard File
# Input: 
	# filename: str
# Output: lines
	# lines: list of str
def readfile(filename):
	file = open(filename, 'r')
	lines = file.readlines()
	lines = [x.strip() for x in lines]
	lines = [x for x in lines if x]
	file.close()
	return lines

# Calculate the Edit Distance
# Input:
	# a, b: str, a to b
# Output:
	# dist: int, the edit distance of a to b
	# Ops: list of int, Operate idx
		# if Op == 1 or 2, the element will be (2, 'A')
	# Pos: list of int, position of a
def EditDis(a, b):
	m = len(a)
	n = len(b)
	edit = [[0 for col in range(n+1)] for row in range(m+1)]
	path = [[0 for col in range(n+1)] for row in range(m+1)]
	# Ops = [[0 for col in range(n)] for row in range(m)]
	# Pos = [[0 for col in range(n)] for row in range(m)]
	Ops = []
	Pos = []
	for i in range(m+1):
		edit[i][0] = i
	for j in range(n+1):
		edit[0][j] = j
	for i in range(1, m+1):
		for j in range(1, n+1):
			diff = 0 if (a[i-1] == b[j-1]) else 1
			DEL = edit[i-1][j] + 1
			INS = edit[i][j-1] + 1
			SUB = edit[i-1][j-1] + diff
			temp = [DEL, INS, SUB]
			edit[i][j] = min(temp)
			op = temp.index(min(temp))
			if op == 2 and diff == 0:
				path[i][j] = -1
			else:
				path[i][j] = op
	dist = edit[m][n]
	# RePath(a, b, path, m, n, Ops, Pos)
	i = m
	j = n
	while(i != 0 or j != 0):
		if path[i][j] == -1:
			i = i - 1
			j = j - 1
		elif path[i][j] == 0: # DEL
			Ops.append(0)
			Pos.append(i-1)
			i = i - 1
		elif path[i][j] == 1: # INS
			Ops.append((1, b[j-1]))
			Pos.append(i)
			j = j - 1
		elif path[i][j] == 2: # SUB
			Ops.append((2, b[j-1]))
			Pos.append(i-1)
			i = i - 1
			j = j - 1
	print edit
	return dist, Ops, Pos	

# Write standard File
# Input:
	# outfile: str
	# dist: int, the edit distance of a to b
	# Ops: list of int, Operate idx
	# if Op == 1 or 2, the element will be (2, 'A')
	# Pos: list of int, position of a
# Output:
	# None
def writefile(outfile, dist, Ops, Pos):
	out = open(outfile, 'w')
	out.write(str(dist) + '\n')
	# print(str(dist) + '\n')
	for i in range(dist-1, -1, -1):
		op = Ops[i]
		if type(op) is types.IntType:
			outstr = Operate[op] + ' ' + str(Pos[i]) + '\n'
		else:
			outstr = Operate[op[0]] + ' ' + str(Pos[i]) +  ' ' + op[1] + '\n'
		# print(outstr)
		out.write(outstr)
	out.close()
	

	
# Task 1: read infile and write result to outfile
# Input:
	# infile: str
	# outfile: str
# Output:
	# None
def Task1(infile, outfile):
	lines = readfile(infile)
	if len(lines) != 2:
		print("Input lines overflow!")
		return
	a = lines[0]
	b = lines[1]
	[dist, Ops, Pos] = EditDis(a,b)
	writefile(outfile, dist, Ops, Pos)
	
if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument('-i', metavar='infile')
	parser.add_argument('-o', metavar='outfile')
	args = parser.parse_args()

	start = time.clock()
	Task1(args.i, args.o)
	end = time.clock()
	
	print("Running time is : " + str(end-start))

# a = 'ABCDABADBDC'
# b = 'BCDBBCC'
# a = 'kitten'
# b = 'sitting'
# [dist, Ops, Pos] = EditDis(a,b)
# writefile('out.txt', dist, Ops, Pos)

	