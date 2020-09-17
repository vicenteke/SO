make:
	g++ main.cc main_class.cc cpu.cc -o s
	./s

valgrind:
	g++ main.cc main_class.cc cpu.cc -o s -v
	valgrind ./s

clear:
	rm -f *.o *~
	clear
