menmath: menmath.cpp
	g++ -std=c++17 menmath.cpp -o menmath
clear:
	rm -rfv menmath menmath.o
deb:
	dpkg --build pkg/menmath_1-1_all
