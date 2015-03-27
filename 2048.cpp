#include "2048.h"
#include <cstdlib>

using namespace std;

#define EMPTY 0
/* cell class */

cell::cell() : value(EMPTY), locked(false) {}

int cell::init(int v) {
	value = v; 
	return value;
}

int cell::pow() {
	value*=2;
	return value;
}

int cell::get_value() {
	return value;
}

bool cell::is_locked() {
	return locked;
}

void cell::lock() {
	locked = true;
}

void cell::unlock() {
	locked = false;
}
/* field class */

void field::unlock() {
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			map[i][j].unlock();
}

field::field(ostream& os_, istream& is_): os(os_), is(is_) {
	int x = rand() % SIZE-1;
	int y = rand() % SIZE-1;
	map[x][y].init(2);
}

vector<cell*> field::get_empty(){
	vector<cell*> empty;
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			if (map[i][j].get_value() == EMPTY) 
				empty.push_back(&map[i][j]);
	return empty;
}

void field::render() {
	os<<"+----+\n";
	for (int j=SIZE-1; j>=0; j--)
	{
		os<<" ";
		for (int i=0; i<SIZE; i++)
			os<<map[i][j].get_value();
		os<<" \n";
	}
	os<<"+----+\n";
}

bool field::begin() {
	os<<"WELCOME\n2048 the game!\nLet's start: type the letter('r','l','t','b')\n";
	render();
	while (1) {
		is>>cur_command;
		switch (cur_command) {
			case 'l': go_left(); break;
			case 'r': go_right(); break;
			case 't': go_top(); break;
			case 'b': go_bottom(); break;
			default: os<<"Your char is wrong, type smth else.\n"; break; 
		}
		unlock();
		vector<cell*> empty = get_empty();
		int x = rand() % empty.size();
		empty[x]->init(2);
		render();
	}
}

void field::go_left() {
	for (int i=SIZE-1; i>0; i--) {
		for (int j=0; j<SIZE; j++) {
			if ((map[i][j].get_value() != 0) && (!map[i][j].is_locked())) {
				if (map[i-1][j].get_value() == map[i][j].get_value()) {
					map[i-1][j].pow();
					map[i-1][j].lock();
					map[i][j].init(EMPTY);
				}
				if (map[i-1][j].get_value() == EMPTY) {
					map[i-1][j].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
				}
			}	
		}
	}
}

void field::go_right() {
	for (int i=0; i<SIZE-1; i++) {
		for (int j=0; j<SIZE; j++) {
			if ((map[i][j].get_value() != 0) && (!map[i][j].is_locked())) {
				if (map[i+1][j].get_value() == map[i][j].get_value()) {
					map[i+1][j].pow();
					map[i+1][j].lock();
					map[i][j].init(EMPTY);
				}
				if (map[i+1][j].get_value() == EMPTY) {
					map[i+1][j].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
				}
			}	
		}
	}
}

void field::go_top() {
	for (int j=0; j<SIZE-1; j++) {
		for (int i=0; i<SIZE; i++) {
			if ((map[i][j].get_value() != 0) && (!map[i][j].is_locked())) {
				if (map[i][j+1].get_value() == map[i][j].get_value()) {
					map[i][j+1].pow();
					map[i-1][j].lock();
					map[i][j].init(EMPTY);
				}
				if (map[i][j+1].get_value() == EMPTY) {
					map[i][j+1].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
				}
			}	
		}
	}
}

void field::go_bottom() {
	for (int j=SIZE-1; j>0; j--) {
		for (int i=0; i<SIZE; i++) {
			if ((map[i][j].get_value() != 0) && (!map[i][j].is_locked())) {
				if (map[i][j-1].get_value() == map[i][j].get_value()) {
					map[i][j-1].pow();
					map[i-1][j].lock();
					map[i][j].init(EMPTY);
				}
				if (map[i][j-1].get_value() == EMPTY) {
					map[i][j-1].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
				}
			}	
		}
	}
}
