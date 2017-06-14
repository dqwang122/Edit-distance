from difflib import *

def printarray(a):
	m = len(a)
	n = len(a[0])
	for i in range(m):
		for j in range(n):
			print(a[i][j]),
		print('\n')

def diff():
	file_1 = open("origin.in")
	file_2 = open("result.in")
	s_1 = file_1.read()
	s_2 = file_2.read()
	s = HtmlDiff.make_file(HtmlDiff(),s_1,s_2)
	out = open(r"res.html","w")
	out.write(s)