# A demonstration makefile

VAR = $(shell ls)
VAR2 = 0 1 2 3 4

demo1:
	echo $(CXX)
	echo $$

demo2:
	echo Test1
	@echo test2
	-blah
	blah2
	blah3

demo3:
	cat subdir/test.txt
	cd subdir
	ls

demo4:
	echo $(VAR)

demo5:
	$(foreach var3,$(VAR2),echo $(var3); )

omp_test: omp_test.o
	g++ -fopenmp -o omp_test omp_test.o

omp_test.o: omp_test.cpp
	g++ -fopenmp -o omp_test.o -c omp_test.cpp

omp_test2: omp_test2.o
	g++ -fopenmp -o omp_test2 omp_test2.o

omp_test2.o: omp_test2.cpp
	g++ -fopenmp -o omp_test2.o -c omp_test2.cpp

mpi_test: mpi_test.o
	mpic++ -o mpi_test mpi_test.o

mpi_test.o: mpi_test.cpp
	mpic++ -o mpi_test.o -c mpi_test.cpp

clean:
	rm -f omp_test omp_test2 mpi_test *.o
