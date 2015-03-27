#ifndef TWENTYFOURTYEIGHT_H
#define TWENTYFOURTYEIGHT_H

#define SIZE 4

#include <vector>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class cell {
	int value;
	bool locked;
public:
	cell();
	int init(int value);
	int pow();
	int get_value();
	bool is_locked();
	void lock();
	void unlock();
};

class field {
	char cur_command;
	cell map[SIZE][SIZE];
	cell* cur;
	ostream& os;
	istream& is;
	void go_top();
	void go_left();
	void go_right();
	void go_bottom();
	void render();
	void unlock();
	vector<cell*> get_empty();
public:
	field(ostream& os, istream& is);
	bool begin();
};



#endif
