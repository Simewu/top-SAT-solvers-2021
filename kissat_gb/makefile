all:
	$(MAKE) -C "/home/bitcoin/Desktop/top-SAT-solvers-2021/kissat_gb/build"
clean:
	rm -f "/home/bitcoin/Desktop/top-SAT-solvers-2021/kissat_gb"/makefile
	-$(MAKE) -C "/home/bitcoin/Desktop/top-SAT-solvers-2021/kissat_gb/build" clean
	rm -rf "/home/bitcoin/Desktop/top-SAT-solvers-2021/kissat_gb/build"
coverage:
	$(MAKE) -C "/home/bitcoin/Desktop/top-SAT-solvers-2021/kissat_gb/build" coverage
indent:
	$(MAKE) -C "/home/bitcoin/Desktop/top-SAT-solvers-2021/kissat_gb/build" indent
test:
	$(MAKE) -C "/home/bitcoin/Desktop/top-SAT-solvers-2021/kissat_gb/build" test
.PHONY: all clean coverage indent test
