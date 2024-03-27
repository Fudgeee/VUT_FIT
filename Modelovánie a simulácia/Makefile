all:
	g++ main.cpp -o main -lsimlib -lm
clean:
	rm -f *.out
	rm -f main
run:
	./main
output:
	cat main.out | grep Average\ utilization\ = > filtered.out
	cat main.out | grep Number\ of\ requests | tail -1 >> filtered.out
