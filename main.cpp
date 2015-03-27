#include <iostream>
#include "2048.h"
#include <fstream>

using namespace std;

int main() {
	ofstream of("2048.out");
	field f(cout, cin);
	f.begin();		
	return 0;
}
