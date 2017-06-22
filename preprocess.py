import pandas as pd
import time

total = 7699
block = 128
# total = 14
# block = 2

cnt = 0
start = time.time()
for i in range(total/block + 1):
	cols = range(i * block, i * block + min(block, total - cnt))
	# print cols
	df = pd.read_csv('pre.csv', header=None, sep=',',usecols=cols)
	dff = df.transpose()
	dff.to_csv(str(i) + '.csv')
	cnt = cnt + block
	# print cnt
end = time.time()
print "Running time is : "  + str((end - start))
