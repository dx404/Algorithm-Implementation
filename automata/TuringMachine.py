
# A Python and SQLite Turing Machine simulator

import sqlite3

transitionTable=[
	['q0', '0', 'q1', '0', 'R'],
	['q0', '1', 'q1', '0', 'R'],
	['q0', 'B', 'q1', '0', 'R'],
	['q1', '0', 'q1', '1', 'R'],
	['q1', '0', 'q2', '0', 'L'],
	['q1', '1', 'q1', '1', 'R'],
	['q1', '1', 'q2', '1', 'L'],
	['q1', 'B', 'q1', '1', 'R'],
	['q1', 'B', 'q2', 'B', 'L'],
	['q2', '0', 'qf', '0', 'R'],
	['q2', '1', 'q2', '1', 'L']
]


class TuringMachine:
	def __init__(self):
         self.db=sqlite3.connect(':memory:')
         cursor=self.db.cursor()
         cursor.execute('''
         	create table transitionTable (
         		state text, 
         		readSymbol varchar(1), 
         		nextState text, 
         		writeSymbol varchar(1),
         		move varchar(1)
         	)''')
         cursor.execute('''
         	create table trace (
         		step integer, 
         		tapeData text,
         		state text,
         		headPos integer
         	)''')


	def setTable(self, t):
		self.transitionTable=t
		cursor = self.db.cursor()
		for row in self.transitionTable:
			cursor.execute('insert into transitionTable values (?, ?, ?, ?, ?)', row)

	def setFinal(self, finalState):
		self.finalState = finalState

	def getAction(self, state, readSymbol):
		cursor = self.db.cursor()
		cursor.execute('''
			select 
				nextState, writeSymbol, move 
			from 
				transitionTable
			where 
				state = ? and readSymbol = ?
			''', [state, readSymbol])
		return cursor.fetchall()

	def extend_or_trim(self, tapeData, headPos):
		newTapeData, newHeadPos = tapeData, headPos
		n = len(tapeData)
		if headPos < 0:
			newTapeData = 'B' * (-headPos) + tapeData
			newHeadPos = 0
		elif headPos >= n:
			newTapeData = tapeData + 'B' * (headPos - n + 1)
		else:
			i, j = 0, n-1
			while (i < headPos and tapeData[i] == 'B'): 
				i+=1
			while (j > headPos and tapeData[j] == 'B'): 
				j-=1
			newTapeData = tapeData[i:j+1]
			newHeadPos -= i
		return newTapeData, newHeadPos

	def run(self, tapeData, state, headPos=0, stepCap=200):
		cursor = self.db.cursor()
		cursor.execute('''
				insert into trace values (0, ?, ?, ?)
			''', [tapeData, state, headPos])

		self.nextID = []
		for t in xrange(1, stepCap):
			cursor.execute('''
					select 
						tapeData, state, headPos 
					from 
						trace 
					where 
						step=? ''', [t-1])
			for tapeData, state, headPos in cursor.fetchall():
				n = len(tapeData)
				tapeData, headPos = self.extend_or_trim(tapeData, headPos)

				readSymbol = tapeData[headPos]
				for nextState, writeSymbol, move in self.getAction(state, readSymbol):
					newTapeData = tapeData[:headPos] + writeSymbol + tapeData[headPos+1:]
					if move == 'L':
						newHeadPos = headPos - 1
					elif move == 'R':
						newHeadPos = headPos + 1
					else :
						newHeadPos = headPos
					newTapeData, newHeadPos = self.extend_or_trim(newTapeData, newHeadPos)
					cursor.execute('''
						insert into trace values (?, ?, ?, ?)
						''', [t, newTapeData, nextState, newHeadPos]
					)
					# print tapeData, state, headPos, nextState, writeSymbol, move
					# print newTapeData, nextState, newHeadPos
					# print '->', state, readSymbol, nextState, writeSymbol, move


	def printDBTable(self, name):
		cursor = self.db.cursor()
		result = cursor.execute('select * from {}'.format(name))
		for row in result:
			print row

	def printStep(self, i):
		cursor = self.db.cursor()
		cursor.execute('select * from trace where step=?', [i])
		for row in cursor:
			print row

	def printFinal(self):
		cursor = self.db.cursor()
		cursor.execute('''
				select * from trace where state='qf'
			''')
		for row in cursor:
			print row


if __name__=="__main__":
	print "Hello, Welcome to Duo's single-taple Turing Machine implementation"
	TM = TuringMachine()
	TM.setTable(transitionTable)
	TM.setFinal('qf')
	# TM.printDBTable()
	TM.run('1010', 'q0', 0)
	# TM.printFinal()
	TM.printStep(5)
	# TM.printDBTable('trace')
