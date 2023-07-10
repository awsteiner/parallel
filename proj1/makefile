# Make sure to sleep for 10 seconds to ensure a different RNG
# seed between the non-parallel and parallel runs
anneal_nopara.txt: anneal_para anneal_nopara
	anneal_nopara > anneal_nopara.out
	sleep 10 
	mpirun -np 2 anneal_para > anneal_para.out

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


# A special target to help Andrew plot results
aws_plot:
	o2graph -subplots 1 5 sharex=True -set xlo 0 -set xhi 4 \
		-set ylo 0 -set yhi 3500 \
		-subadj right=0.99,top=0.95,wspace=0,hspace=0 \
		-selax 0 -generic table anneal_nopara.txt \
		-index -plot c1 N \
		-ttext 0.5 1.025 "nopara" \
		-selax 1 -generic table anneal_para_0.txt \
		-index -function "N/100%2" thread -list \
		-select-rows "thread<0.5" -list -delete-col N -index \
		-plot c1 N \
		-ttext 0.5 1.025 "t=0, r=0" \
		-modax "y_visible=False" \
		-selax 2 -generic table anneal_para_0.txt \
		-index -function "N/100%2" thread \
		-select-rows "thread>0.5" -delete-col N -index \
		-plot c1 N \
		-ttext 0.5 1.025 "t=1, r=0" \
		-modax "y_visible=False" \
		-selax 3 -generic table anneal_para_1.txt \
		-index -function "N/100%2" thread \
		-select-rows "thread<0.5" -delete-col N -index \
		-plot c1 N \
		-ttext 0.5 1.025 "t=0, r=1" \
		-modax "y_visible=False" \
		-selax 4 -generic table anneal_para_1.txt \
		-index -function "N/100%2" thread \
		-select-rows "thread>0.5" -delete-col N -index \
		-plot c1 N \
		-ttext 0.5 1.025 "t=1, r=1" \
		-modax "y_visible=False" \
		-save results.png -show

check:
	tail -n 1 anneal_nopara.out
	acol -set precision 10 -generic table anneal_nopara.txt -get-row 3063
	tail -n 2 anneal_para.out
	acol -set precision 10 -generic table anneal_para_0.txt -get-row 6370
	acol -set precision 10 -generic table anneal_para_1.txt -get-row 6713
