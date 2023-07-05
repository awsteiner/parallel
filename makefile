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
