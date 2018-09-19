files = testtable.c sstable.c

testtable: $(files)
	gcc -o $@ $^

testdebugger: $(files)
	gcc -g $^ -o $@
