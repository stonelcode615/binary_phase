#! /usr/bin/python
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
import sys

print 'Number of arguments:', len(sys.argv)
print 'Argument List: ', str(sys.argv)

plt.ion()

def file_reading(file_name):
    f = file(file_name)
    row = []
    for line in f.readlines():
        row_item = line.split()
        content = [ float(i) for i in row_item]
        row.append(content)
    return row, len(row),len(content)

total=[]
index=0
for name in sys.argv[1:]:
    total.append([])
    index = index + 1


for i in range(index):
    total[i].append([])
    total[i].append([])

plt.figure()

for i in range(index):
    name=sys.argv[i+1]
    content, line_num, cont_num = file_reading(name)
    for j in range(line_num):
        print content[j][0], content[j][1]
        total[i][0].append(content[j][0])
        total[i][1].append(content[j][1])
    if i==0:
        plt.plot(total[i][0], total[i][1], 'bo', label='exp')
    else: 
        plt.plot(total[i][0], total[i][1], label='fit')

plt.legend()
plt.show()

exit=raw_input('enter any key to exit')

