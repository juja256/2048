#include "2048.h"
#include <cstdlib>
#include <ctime>

using namespace std;

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

int field::get_score() {
	return score;
}

field::field(ostream& os_, istream& is_): os(os_), is(is_), score(0) {
		srand(time(NULL));
		vector<cell*> empty = get_empty();
		int x = rand() % empty.size();
		int d = (rand() % 2 + 1) * 2;
		empty[x]->init(d);
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
	os<<"Score: "<<score<<"\n"<<"+--------+\n";
	for (int j=SIZE-1; j>=0; j--) {
		os<<" ";
		for (int i=0; i<SIZE; i++)
			os<<map[i][j].get_value()<<" ";
		os<<" \n";
	}
	os<<"+--------+\n";
}

void field::print_locked() {
	os<<"LOCKED\n";
	for (int j=SIZE-1; j>=0; j--) {
		os<<" ";
		for (int i=0; i<SIZE; i++)
			os<<map[i][j].is_locked()<<" ";
		os<<" \n";
	}
	os<<"LOCKED\n";
}

bool field::begin() {
	bool ok = true; 
	int c; 
	os<<"WELCOME\n2048 the game!\nLet's start: \n'r' - move right\n'l' - move left\n't' -move top\n'b' -move bottom\n'q' - exit\n";
	render();
	while (ok) {
		is>>cur_command;
		
		switch (cur_command) {
			case 'l': c = go_left(); break;
			case 'r': c = go_right(); break;
			case 't': c = go_top(); break;
			case 'b': c = go_bottom(); break;
			case 'q': ok = false; break;
			default: os<<"Your command is wrong, type valid command.\n"; continue; break; 
		}
		if (!ok) break;
		#ifdef DEBUG
		print_locked();
		#endif
		unlock();
		vector<cell*> empty = get_empty();
		if (empty.size() == 0) { 
			os<<"Game Over!\n"; 
			return false;
		} 
		if (c == TARGET)
			os<<"You won!\n";
		if (c != 0) {
			int x = rand() % empty.size();
			int d = (rand() % 2 + 1) * 2;
			empty[x]->init(d);
		}
		render();
	}
	return true;
}

int field::go_left() {
	int c = 0;
	for (int i=1; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			if ((map[i][j].get_value() != EMPTY) && (!map[i][j].is_locked())) {
				if ((map[i-1][j].get_value() == map[i][j].get_value()) && (!map[i-1][j].is_locked())) {
					map[i-1][j].pow();
					score += map[i-1][j].get_value();
					if (map[i-1][j].get_value() == TARGET) 
						return TARGET; // victory
					map[i-1][j].lock();
					map[i][j].init(EMPTY);
					c++;
				}
				if (map[i-1][j].get_value() == EMPTY) {
					map[i-1][j].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
					if ((i==SIZE-1) || (map[i+1][j].get_value() == EMPTY)) go_left();
					c++;
				}
			}	
		}
	}

	return c;
}

int field::go_right() {
	int c = 0;
	for (int i=SIZE-2; i>=0; i--) {
		for (int j=0; j<SIZE; j++) {
			if ((map[i][j].get_value() != EMPTY) && (!map[i][j].is_locked())) {
				if ((map[i+1][j].get_value() == map[i][j].get_value()) && (!map[i+1][j].is_locked())) {
					map[i+1][j].pow();
					score += map[i+1][j].get_value();
					if (map[i+1][j].get_value() == TARGET) 
						return TARGET;
					map[i+1][j].lock();
					map[i][j].init(EMPTY);
					c++;
				}
				if (map[i+1][j].get_value() == EMPTY) {
					map[i+1][j].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
					if ((i==0) || (map[i-1][j].get_value() == EMPTY)) go_right();
					c++;
				}
			}	
		}
	}
	return c;
}

int field::go_top() {
	int c = 0;
	for (int j=SIZE-2; j>=0; j--) {
		for (int i=0; i<SIZE; i++) {
			if ((map[i][j].get_value() != EMPTY) && (!map[i][j].is_locked())) {
				if ((map[i][j+1].get_value() == map[i][j].get_value()) && (!map[i][j+1].is_locked())) {
					map[i][j+1].pow();
					score += map[i][j+1].get_value();
					if (map[i][j+1].get_value() == TARGET) 
						return TARGET;
					map[i][j+1].lock();
					map[i][j].init(EMPTY);
					c++;
				}
				if (map[i][j+1].get_value() == EMPTY) {
					map[i][j+1].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
					if ((j==0) || (map[i][j-1].get_value() == EMPTY)) go_top();
					c++;
				}
			}	
		}
	}
	return c;
}

int field::go_bottom() {
	int c = 0;
	for (int j=1; j<SIZE; j++) {
		for (int i=0; i<SIZE; i++) {
			if ((map[i][j].get_value() != EMPTY) && (!map[i][j].is_locked())) {
				if ((map[i][j-1].get_value() == map[i][j].get_value()) && (!map[i][j-1].is_locked())) {
					map[i][j-1].pow();
					score += map[i][j-1].get_value();
					if (map[i][j-1].get_value() == TARGET) 
						return TARGET;
					map[i][j-1].lock();
					map[i][j].init(EMPTY);
					c++;
				}
				if (map[i][j-1].get_value() == EMPTY) {
					map[i][j-1].init(map[i][j].get_value());
					map[i][j].init(EMPTY);
					if ((j==SIZE-1) || (map[i][j+1].get_value() == EMPTY)) go_bottom();
					c++;
				}
			}	
		}
	}
	return c;
}
