#!/usr/bin/python

import sys
import random

clauses = None
literals = None
num_vars = None

if len(sys.argv) == 4: # The file name with two arguments
	clauses = int(sys.argv[1])
	literals = int(sys.argv[2])
	num_vars = int(sys.argv[3])

if num_vars == None:
	print('Random SAT Generator')
	clauses = int(input('How many clauses? '))
	literals = int(input('How many literals per? '))
	literals = int(input('How many variable values? '))

file = open('random_SAT.cnf', 'w')

file.write('c random_SAT.cnf\n')
file.write('c\n')
file.write(f'p cnf {num_vars} {clauses}\n')

for clause in range(clauses):
	line = ''
	for literal in range(literals):
		v = random.randint(1, num_vars)
		if random.randint(0, 1) == 0: v = -v
		line += str(v) + ' '
	line += '0'
	file.write(line + '\n')

file.close()

print('Successfully generated "random_SAT.cnf".')