#!/usr/bin/python

import sys
import random
import os
import subprocess

IGNORESYMBOLS = '#####:'
MYFILES = ["unittest1.gcov", "unittest3.gcov", "unittest4.gcov", "cardtest1.gcov",
"cardtest2.gcov", "cardtest3.gcov", "cardtest4.gcov", "random.gcov"]

#numOfLine = # of line
#numLines = totalPassed+totalFailed
#n = 100
def calcSuspicion(numOfLine, numLines, n):
	passed = sum([1 for i in numOfLine if i[0] == True])
	failed = sum([1 for i in numOfLine if i[0] == False])
	suspicionLevel = [[i + 1, 0] for i in range(numLines)]
	for i in range(len(suspicionLevel)):
		numPassed = 0
		numFailed = 0
		for check in numOfLine:
			if str(i + 1) in check[1]:
				if check[0]:
					numPassed += 1 
				else:
					numFailed += 1
		#ignore attempts to divide by 0
		try:
			numerator = (float(numFailed) / float(failed))
			denominator = (float(numPassed) / float(passed))
			suspicionLevel[i][1] = numerator / (numerator + denominator)
		except ZeroDivisionError:
			pass
	return sorted(suspicionLevel)

#take numbers of the lines where tests passed or failed
def getTotals(file):
	totalPassed = 0
	totalFailed = 0
	
	with open(file, 'r') as f:
		for line in file:
			if IGNORESYMBOLS in line:
				totalPassed += 1
			else:
				totalFailed += 1
	return totalPassed, totalFailed
	
#take the line number
def getLines(file):
	linesRan = dict()
	with open(file, 'r') as f:
		line = f.readline()
		while line != '':
			items = line.split()
			if items[0] not in IGNORESYMBOLS:
				linesRan[items[1].split(':')[0]] = True
			line = f.readline()
	return linesRan	
	
def main():
	i = 0
	x = ''
	linesRan = list()
	for i in xrange(len(MYFILES)):
		x = MYFILES[i]
		totalPassed, totalFailed = getTotals(x)
		
		buggyLines = calcSuspicion(linesRan,totalPassed+totalFailed,100)
		print str(i)+'\t\t'+str(buggyLines[i])

main();