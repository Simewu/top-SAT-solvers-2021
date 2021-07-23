import os
import sys
import re

def terminal(cmd):
	return os.popen(cmd).read()


def run(clauses, literals, num_vars):
	terminal(f'python3 gen_random_SAT.py {clauses} {literals} {num_vars}')
	output = terminal('./kissat_gb/build/kissat random_SAT.cnf | grep process-time:')
	
	match = re.match('c process-time:\s+[^\s]+\s+([0-9\.]+)', output)
	time = float(match.group(1))
	
	return time

def header():
	line = 'Clauses,'
	line += 'Literals per clause,'
	line += 'Variables,'
	line += 'Time (s),'
	return line

def log(clauses, literals, num_vars, time):
	line = str(clauses) + ','
	line += str(literals) + ','
	line += str(num_vars) + ','
	line += str(time) + ','
	return line

output = open('experiment_output.csv', 'w')
output.write(header() + '\n')

total_clauses = 1000
total_literals = 1000
total_variables = 1000

step = 100

count = 0
num_samples = (total_clauses / step) * (total_literals / step) * (total_variables / step)

for clauses in range(step, total_clauses, step):
	for literals in range(step, total_literals, step):

		for num_vars in range(step, total_variables, step):
			if(count % 10 == 0): print(f'Progress: {count / num_samples}')
			count += 1

			time = run(clauses, literals, num_vars)
			output.write(log(clauses, literals, num_vars, time) + '\n')

output.close()

print('SUCCESS!')			