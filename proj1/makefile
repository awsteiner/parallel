anneal_nopara.txt: anneal_para anneal_nopara
	anneal_nopara
	mpirun -np 2 anneal_para

anneal_nopara: anneal_nopara.o
	$(CXX) -DNO_PARA -o anneal_nopara anneal_nopara.o

anneal_nopara.o:
	$(CXX) -I/usr/local/include -DNO_PARA \
		-o anneal_nopara.o -c anneal_para.cpp

anneal_para: anneal_para.o
	mpic++ -fopenmp -o anneal_para anneal_para.o

anneal_para.o:
	mpic++ -fopenmp -I/usr/local/include \
		-o anneal_para.o -c anneal_para.cpp

clean:
	rm -f *.o anneal_nopara anneal_para anneal_nopara.txt
