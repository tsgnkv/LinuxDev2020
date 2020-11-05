GENERATES = ldunl.so
TEST_FILES = FIX_me file

all: ldunl.so

ldunl.so: ldunl.c
	gcc -shared -fPIC ldunl.c -o ldunl.so -ldl

test: ldunl.so 
	touch FIX_me
	LD_PRELOAD=`pwd`/ldunl.so rm FIX_me 2> /dev/null; ([ $$? -eq 1 ] && echo "success!")
	rm FIX_me
	touch file
	LD_PRELOAD=`pwd`/ldunl.so rm file 2> /dev/null; ([ $$? -eq 0 ] && echo "success!")

clean:
	rm -rf  $(GENERATES) $(TEST_FILES)
