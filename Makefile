output.exe: code.o ; g++ code.o -o output.exe
code.o: code.cpp ; g++ -c code.cpp
clean: 
	rm -f *.o output
