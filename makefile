main: main.cpp bf.cpp bf.h
	g++ -o main.elf main.cpp bf.cpp
clean:
	rm -rf *.elf
