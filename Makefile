all: menmath doc deb

menmath: menmath.cpp
	g++ -std=c++17 -O2 menmath.cpp -o menmath

doc: doc/menmath
	man doc/menmath > README

deb: menmath doc
	mkdir -vp pkg/menmath_1-1_all/usr/local/man/man1
	cp -v doc/menmath pkg/menmath_1-1_all/usr/local/man/man1/menmath.1
	mkdir -vp pkg/menmath_1-1_all/usr/local/bin
	cp -v menmath pkg/menmath_1-1_all/usr/local/bin
	dpkg --build pkg/menmath_1-1_all

install: deb
	sudo dpkg -i pkg/menmath_1-1_all.deb

remove:
	sudo dpkg -r menmath

clear:
	rm -rfv menmath menmath.o pack/menmath_1-1_all.deb
