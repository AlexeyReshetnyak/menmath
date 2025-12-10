menmath: menmath.cpp
	g++ -std=c++17 menmath.cpp -o menmath
clear:
	rm -rfv menmath menmath.o
deb: menmath
	mkdir -vp pkg/menmath_1-1_all/usr/local/man/man1
	cp -v doc/menmath pkg/menmath_1-1_all/usr/local/man/man1/menmath.1
	mkdir -vp pkg/menmath_1-1_all/usr/local/bin
	cp -v menmath pkg/menmath_1-1_all/usr/local/bin
	dpkg --build pkg/menmath_1-1_all
