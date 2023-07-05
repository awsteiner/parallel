# A demonstration makefile

demo1:
	echo Test1
	@echo test2
	-blah
	blah2
	blah3

demo2:
	cat subdir/test.txt
	cd subdir
	ls

