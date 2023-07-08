anneal_para_ts_nompi: anneal_para_ts_nompi.o
	$(CXX) -o anneal_para_ts_nompi anneal_para_ts_nompi.o

anneal_para_ts_nompi.o:
	$(CXX) -I/usr/local/include \
		-o anneal_para_ts_nompi.o -c anneal_para_ts.cpp

anneal_para_ts: anneal_para_ts.o
	mpic++ -DO2SCL_OPENMP -DO2SCL_MPI -fopenmp -o anneal_para_ts anneal_para_ts.o

anneal_para_ts.o:
	mpic++ -DO2SCL_OPENMP -DO2SCL_MPI -fopenmp -I/usr/local/include \
		-o anneal_para_ts.o -c anneal_para_ts.cpp

clean:
	rm -f *.o anneal_para_ts_nompi anneal_para_ts
