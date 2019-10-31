import sys
import matplotlib.pyplot as plt

x = []
y = []

i = 1
uniq_tids = {}
tid_count = 1
with open(sys.argv[1],'r') as file:
    for line in file:
        x.append(i)
        tid = int(line)
        if tid not in uniq_tids:
        	uniq_tids[tid] = tid_count
        	tid_count += 1
        y.append(uniq_tids[tid])
        i += 1

plt.plot(x,y,',b')
plt.xlabel('tid')
plt.ylabel('Time (s)')
plt.title('Scheduling Distribution')
plt.show()
plt.savefig(sys.argv[1]+'.png')
