import sys
# total number of states and obseravations 
_totalG=26
_totalP=0

# phoneme map with index
_symbMap=dict()
_phonemeMap=[]

# total SEQ in data file
_totalSEQ=0

#grapheme and phoneme states list
_Gstates=[]
_Pstates=[]

#path sequence 
possible_path=[]

# a class node in trellis
class _aNode:
	def __init__(self):
		self._start=0
		self._end=0
		self._totalOc=0
		self._transition=[]
		self._emission=[]

# init functions for emission and transition list
def _init(lstate,nos,noe):
	for i in range(0,nos):
		anode=_aNode()
		anode._emission=[0 for j in range(0,noe)]
		anode._transition=[0 for j in range(0,nos)]
		lstate.append(anode)
	return
	
# open cmu data files
_g2pFile=open("bufferedGPS.txt",'r')
_sFile=open("UniQSymb.txt",'r')

# insert values into phoneme map
for line in _sFile:
	l=line.split()
	_symbMap[l[0]]=_totalP
	_phonemeMap.append(l[0])
	_totalP=_totalP+1

#graphemes are the states; initialize the transition and emission prob
_init(_Gstates,_totalG,_totalP)

#graphemes are the states; initialize the transition and emission prob
_init(_Pstates,_totalP,_totalG)

# when graphemes are the states calculate the transition probability
def _transitionG(seqstr):
	k=len(seqstr)
	a=ord(seqstr[0])-65
	
	_Gstates[a]._start=_Gstates[a]._start+1
	_Gstates[a]._totalOc=_Gstates[a]._totalOc+1

	for i in range(1,k):
		a=ord(seqstr[i-1])-65
		b=ord(seqstr[i])-65
		_Gstates[a]._transition[b]=_Gstates[a]._transition[b]+1
		_Gstates[b]._totalOc=_Gstates[b]._totalOc+1

	a=ord(seqstr[k-1])-65
	_Gstates[a]._end=_Gstates[a]._end+1	
	return
	
# when phonemes are the states calculate the transition probability
def _transitionP(seqstr):
	k=len(seqstr)
	a=_symbMap[seqstr[0]]

	_Pstates[a]._start=_Pstates[a]._start+1
	_Pstates[a]._totalOc=_Pstates[a]._totalOc+1

	for i in range(1,k):
		a=_symbMap[seqstr[i-1]]
		b=_symbMap[seqstr[i]]
		_Pstates[a]._transition[b]=_Pstates[a]._transition[b]+1
		_Pstates[b]._totalOc=_Pstates[b]._totalOc+1

	a=_symbMap[seqstr[k-1]]	
	_Pstates[a]._end=_Pstates[a]._end+1		
	return
	
# calculate the emission probability 
#(it does not matter which of grapheme or phoneme are states because of 1-to-1 relation)
def _emissionGP(gpseq):
	k=len(gpseq[0])
	for i in range(0,k):
		a=ord(gpseq[0][i])-65
		b=_symbMap[gpseq[1+i]]
		_Gstates[a]._emission[b]=_Gstates[a]._emission[b]+1
		_Pstates[b]._emission[a]=_Pstates[b]._emission[a]+1
	return
	
for line in _g2pFile:
	lstr=line.split()
	_totalSEQ=_totalSEQ+1
	_transitionG(lstr[0])
	
	rstr=[]
	k=len(lstr)
	for i in range(1,k):
		rstr.append(lstr[i])
	_transitionP(rstr)
	_emissionGP(lstr)

# IMPLEMENT THE VITERBI ALGO
def viterbiGP(pstates,gseq):
	# list to keep track of the max_prob of each state after each obs
	tpState=[]
	no_obs=len(gseq)-1
	
	# store the possible paths
	global possible_path
	possible_path=[[[] for j in range(0,_totalP)] for i in range(0,no_obs+1)]

	# calculate the start-to-state prob on epmty obs
	for i in range(0,_totalP):
		possible_path[0][i].append(-1)
		tpState.append(pstates[i]._start*1.0/_totalSEQ)

	# update the tpStates: intermediate transition	
	for i in range(0,no_obs):		
		a=ord(gseq[i])-65
		levelMax=[]						# store the temp max of prob
		for j in range(0,_totalP):
			tpmax=[]					     # store the states that give max_prob for each prob
			probmax=-1			
			for k in range(0,_totalP):			
				if pstates[k]._totalOc:				# temperory condition
					tprob=1.0*pstates[k]._transition[j]*pstates[k]._emission[a]/(pow(pstates[k]._totalOc,2))
					tprob=tpState[k]*tprob
					if tprob==probmax:				
						tpmax.append(k)
					elif tprob>probmax:
						probmax=tprob
						tpmax[:]=[]
						tpmax.append(k)
			levelMax.append(probmax)
			possible_path[i+1][j]=tpmax
		for j in range(0,_totalP):
			tpState[j]=levelMax[j]
	
	a=ord(gseq[no_obs])-65
	#update the tpState : final transition, state-to-end
	tpmax=[]
	probmax=-1
	levelMax=[]
	for k in range(0,_totalP):
		if pstates[k]._totalOc:			# temperory condition
			tprob=1.0*pstates[k]._end*pstates[k]._emission[a]/(pstates[k]._totalOc*_totalSEQ)
			tprob=tpState[k]*tprob
			if probmax==tprob:
				tpmax.append(k)
			elif probmax<tprob:
				tpmax[:]=[]
				tpmax.append(k)
				probmax=tprob
		levelMax.append(probmax)
	# print probmax
	return tpmax

def viterbiPG(gstates,pseq):
	# list to keep track of the max_prob of each state after each obs
	tpState=[]
	no_obs=len(pseq)-1
	
	# store the possible paths
	global possible_path
	possible_path=[[[] for j in range(0,_totalG)] for i in range(0,no_obs+1)]

	# calculate the start-to-state prob on epmty obs
	for i in range(0,_totalG):
		possible_path[0][i].append(-1)
		tpState.append(gstates[i]._start*1.0/_totalSEQ)
	
	# update the tpStates: intermediate transition	
	for i in range(0,no_obs):
		a=_symbMap[pseq[i]]
		levelMax=[]						# store the temp max of prob
		for j in range(0,_totalG):
			tpmax=[]					# store the states that give max_prob for each prob
			probmax=-1
			for k in range(0,_totalG):			
				if gstates[k]._totalOc:				# temperory condition
					tprob=1.0*gstates[k]._transition[j]*gstates[k]._emission[a]/(pow(gstates[k]._totalOc,2))
					tprob=tpState[k]*tprob
					if tprob==probmax:		# temperory condition
						tpmax.append(k)
					elif tprob>probmax:
						probmax=tprob
						tpmax[:]=[]
						tpmax.append(k)
			levelMax.append(probmax)
			possible_path[i+1][j]=tpmax
		for j in range(0,_totalG):
			tpState[j]=levelMax[j]
	
	a=_symbMap[pseq[no_obs]]	
	#update the tpState : final transition, state-to-end
	tpmax=[]
	probmax=-1
	levelMax=[]	
	for k in range(0,_totalG):
		if gstates[k]._totalOc:			# temperory condition
			tprob=1.0*gstates[k]._end*gstates[k]._emission[a]/(gstates[k]._totalOc*_totalSEQ)
			tprob=tpState[k]*tprob
			if probmax==tprob:
				tpmax.append(k)
			elif probmax<tprob:
				tpmax[:]=[]
				tpmax.append(k)
				probmax=tprob
		levelMax.append(probmax)			
	# print probmax
	return tpmax

# print ti debug
def printdebug(obs,sta):
	for i in range(0,sta):
		sys.stdout.write("%d >> "%i)
		for j in range(0,obs):
			k=len(possible_path[j][i])
			for l in range(0,k):
				sys.stdout.write("%d "%possible_path[j][i][l])
			sys.stdout.write(" | ")
		print
			
def printGP(lmax,obs,sta,tphoneme):
	if obs<0:
		k=len(tphoneme)-1
		while k>-1:
			sys.stdout.write("%s "%tphoneme[k])
			k=k-1
		print	
		return 
	k=len(lmax)
	for i in range(0,k):
		tphoneme.append(_phonemeMap[lmax[i]])
		printGP(possible_path[obs][lmax[i]],obs-1,sta,tphoneme)
	return 
				
def printPG(lmax,obs,sta,tgrapheme):
	if obs<0:
		k=len(tgrapheme)-1
		while k>-1:
			sys.stdout.write("%c"%tgrapheme[k])
			k=k-1
		print
		return 
	k=len(lmax)
	for i in range(0,k):
		tgrapheme.append(chr(lmax[i]+65))
		printPG(possible_path[obs][lmax[i]],obs-1,sta,tgrapheme)
	return
			
gp=input()
if gp:
	testcase=input()
	while testcase>0 :
		gseq=raw_input()
		seqs=viterbiGP(_Pstates,gseq)
		tphoneme=[]
		#~ sys.stdout.write("%s "%gseq)
		printGP(seqs,len(gseq)-1,_totalG,tphoneme)
		possible_path[:]=[]
		testcase=testcase-1	
else:
	testcase=input()
	while testcase :
		pseq=raw_input().split()
		seqs=viterbiPG(_Gstates,pseq)
		tgrapheme=[]
		printPG(seqs,len(pseq)-1,_totalP,tgrapheme)
		possible_path[:]=[]
		testcase=testcase-1