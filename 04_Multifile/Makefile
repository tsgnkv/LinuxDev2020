GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so
CFLAGS = -Wall

all: libs progs README

progs: prog prog-a prog-so

prog: const.o fun.o prog.o
	cc $^ -o $@

prog-a: prog.o liboutput_static.a
	cc -L. -loutput_static prog.o -o $@

prog-so: prog.o liboutput.so
	cc -L. -loutput prog.o -o $@

libs: liboutput_static.a liboutput.so

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

fun.o: outlib.h

test: test_0_param test_1_param test_3_param

test_0_param: prog prog-a prog-so
	@printf "[TEST 1] run with 0 parameter \n"
	cp prog prog_test
	./prog_test 2> output_0.txt
	cp prog-a prog_test
	./prog_test 2> output_0_a.txt
	cp prog-so prog_test
	./prog_test 2> output_0_so.txt
	rm prog_test
	cmp output_0.txt output_0_a.txt
	cmp output_0.txt output_0_so.txt
	rm output_0*
	@printf "[TEST 1] All outputs are equal \n"

test_1_param: prog prog-a prog-so
	@printf "[TEST 2] run with 1 parameter \n"
	./prog a > output_1.txt
	./prog-a a > output_1_a.txt
	./prog-so a > output_1_so.txt
	cmp output_1.txt output_1_a.txt
	cmp output_1.txt output_1_so.txt
	rm output_1*
	@printf "[TEST 2] All outputs are equal \n"

test_3_param: prog prog-a prog-so
	@printf "[TEST 3] run with 3 parameters \n"
	./prog a b c > output_3.txt
	./prog-a a b c > output_3_a.txt
	./prog-so a b c > output_3_so.txt
	cmp output_3.txt output_3_a.txt
	cmp output_3.txt output_3_so.txt
	rm output_3*
	@printf "[TEST 3] All outputs are equal \n"
		

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

