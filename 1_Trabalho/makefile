make:
	g++ main.cc main_class.cc cpu.cc -o s -g
	./s

valgrind:
	g++ main.cc main_class.cc cpu.cc -o s -v
	valgrind ./s --track-origins=yes

clean:
	rm -f *.o s
	clear
