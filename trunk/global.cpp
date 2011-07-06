/* global.cpp
 * Holds the variables and functions that are used universally throughout
 *   the program.
 *
 *  Copyright (C) 2009  Ethan Warth (a.k.a. redyoshi49q)
 *
 *  This file is part of Enigma Cipher
 *
 *  Enigma Cipher is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Enigma Cipher is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Enigma Cipher.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "global.hpp"

ostream &out = cout, &g_out = cout, &t_out = cout;
istream &in = cin, &g_in = cin;

//int completed[6] = {0,0,0,0,0,0};


void cls() {
	
	#if defined(_WIN32)
		system("cls");
	#elif defined(linux)
		system("clear");
	#else
		//operating system isn't recognized, do nothing
		  //this isn't *really* necessary; other systems can live without this
		  //in the worst case scenario.
	#endif
	
		//this should distinguish between Windows and Linux
		//the above code should work, but it might not...
}

//this is a stub
int getInt() {
	
	string dummy;
	in >> dummy;
	in.ignore();
	int input = atoi(dummy.c_str() );
	return input;
	
}

int digits(int input) {

	input = abs(input);
	int digits = 0;
	
	while (input != 0) {
		input /= 10;
		digits++;
	}
	
	return digits;

}

void pauseOutput() {
	
	string dummy;
	getline(in, dummy); 
	
}

//this is a stub
void complain(string desired) {
	
	
	
}
