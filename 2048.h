#ifndef TWENTYFOURTYEIGHT_H
#define TWENTYFOURTYEIGHT_H

#define SIZE 4
#define EMPTY 0
#define TARGET 2048

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
	ostream& os;
	istream& is;
	int score;

	int go_top();
	int go_left();
	int go_right();
	int go_bottom();
	void render();
	void unlock();
	vector<cell*> get_empty();
	void print_locked();
public:
	int get_score();
	field(ostream& os, istream& is);
	bool begin();
};



#endif
