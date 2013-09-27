main: main.cpp bf.cpp bf.h
	g++ -g -o main.elf main.cpp bf.cpp
cnf: cnf.cpp bf.cpp bf.h
	g++ -g -o cnf.elf cnf.cpp bf.cpp
nf: nf.cpp bf.cpp bf.h
	g++ -g -o nf.elf nf.cpp bf.cpp
nap: nap.cpp bf.cpp bf.h
	g++ -g -o nap.elf nap.cpp bf.cpp
walsh: walsh.cpp bf.cpp bf.h
	g++ -g -o walsh.elf walsh.cpp bf.cpp
autocor: autocor.cpp bf.cpp bf.h
	g++ -g -o autocor.elf autocor.cpp bf.cpp
deg: deg.cpp bf.cpp bf.h
	g++ -g -o deg.elf deg.cpp bf.cpp
anf: anf.cpp bf.cpp bf.h
	g++ -g -o anf.elf anf.cpp bf.cpp
weight: weight.cpp bf.cpp bf.h
	g++ -g -o weight.elf weight.cpp bf.cpp
mobius: mobius.cpp bf.cpp bf.h
	g++ -g -o mobius.elf mobius.cpp bf.cpp
cor: cor.cpp bf.cpp bf.h
	g++ -g -o cor.elf cor.cpp bf.cpp
pc: pc.cpp bf.cpp bf.h
	g++ -g -o pc.elf pc.cpp bf.cpp
test: test.cpp bf.cpp bf.h
	g++ -g -o test.elf test.cpp bf.cpp
clean:
	rm -rf *.elf
