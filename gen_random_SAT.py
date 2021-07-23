#!/usr/bin/python

import sys
import random

clauses = None
literals = None

if len(sys.argv) == 3: # The file name with two arguments
	clauses = int(sys.argv[1])
	literals = int(sys.argv[2])

if literals == None:
	print('Random SAT Generator')
	clauses = int(input('How many clauses? '))
	literals = int(input('How many literals per? '))

numVars = clauses * literals

file = open('random_SAT.cnf', 'w')

file.write('c random_SAT.cnf\n')
file.write('c\n')
file.write(f'p cnf {numVars} {clauses}\n')

for clause in range(clauses):
	line = ''
	for literal in range(literals):
		v = random.randint(1, numVars)
		if random.randint(0, 1) == 0: v = -v
		line += str(v) + ' '
	line += '0'
	file.write(line + '\n')

file.close()

print('Successfully generated "random_SAT.cnf".')