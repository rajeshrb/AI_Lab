import sys
from itertools import izip

#find accuracy
#~ avgacc=0
#~ i=1
#~ while i<6:
	#~ str1="inputgp"+str(i)+".txt"
	#~ str2="respg"+str(i)+".txt"
	#~ with  open(str1,'r') as wfile1, open(str2,'r') as wfile2:
		#~ totalg=0
		#~ totalmg=0
		#~ for x, y in izip(wfile2,wfile1):
			#~ x=x.split()
			#~ y=y.split()
			#~ xs=len(x)
			#~ totalg=totalg+xs
			#~ for j in range(0,xs):
				#~ if x[j]==y[j]:
					#~ totalmg=totalmg+1
		#~ avgacc=avgacc+totalmg*1.0/totalg
	#~ i=i+1
#~ print avgacc*20

						
# to buffere the given data
ll=[]
for line in sys.stdin.readlines():
	l=line.split()
	if '(' in l[0]:
		if (len(l[0])-3==(len(l)-1)) :
			if not ((line in ll) or ('.'  in line) or ('\'' in line) or ('-' in line) or ('_' in line)):
				ll.append(line)
	elif len(l[0])==(len(l)-1):
		if not ((line in ll) or ('.'  in line) or ('\'' in line) or ('-' in line) or ('_' in line)):
			ll.append(line)

for i in range(0, len(ll)):
	sys.stdout.write("%s"%ll[i])

# to partition the data 
#~ for line in sys.stdin.readlines():
	#~ l=line.split()
	#~ k=l[0]+"\n"
	#~ wfile2.write(k)
	#~ k=""
	#~ for i in range(1,len(l)-1):
		#~ k=k+l[i]+" "
	#~ k=k+l[len(l)-1]+"\n"
	#~ wfile1.write(k)
			
