# Just a simple C++ makefile
#
# Use with `$ make`
# Run build binary with `$ ./a.out`


# No file association to the "clean" target.  Also no dependency.
# See more: https://stackoverflow.com/a/2145605/7498073
.PHONY: all
all: build
	./a.out < Medico-Paciente-Medicinas.txt > output.txt

.PHONY: build
build:
	g++ -g -lm *.cpp


.PHONY: clean
clean:
	rm *.o
