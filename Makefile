menmath: menmath.cpp
	g++ -std=c++17 menmath.cpp -o menmath
clear:
	rm -rfv menmath menmath.o
deb: menmath
	cp -v -p doc/menmath pkg/menmath_1-1_all/usr/local/man/man1/menmath.1
	cp -v -p menmath pkg/menmath_1-1_all/usr/local/bin
	dpkg --build pkg/menmath_1-1_all
