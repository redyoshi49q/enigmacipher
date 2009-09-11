/* offsets.cpp
 * The most fundamental type of game difficulty that uses basic encryption schemes.
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

#include "offsets.hpp"

Offsets::Offsets(int newS, int newD, int newV, int newB, int c) {
	
	s = newS;
	d = newD;
	v = newV;
	b = newB;
	
	index = 0;
	previous = 0;
	
	buffer.assign(b, 'a');
	
	setDomains(c);
	
}

Offsets::Offsets(int newS, int newD, int newV, int newB,
	vector<vector<string> > newDomains) {
	
	s = newS;
	d = newD;
	v = newV;
	b = newB;
	
	index = 0;
	previous = 0;
	
	buffer.assign(b, 'a');
	
	domains = newDomains;
	
}

Offsets::Offsets(int newS, int newD, int newV, int newB,
	vector<string> newDomains) {
	
	s = newS;
	d = newD;
	v = newV;
	b = newB;
	
	index = 0;
	previous = 0;
	
	buffer.assign(b, 'a');
	
	for (int i = 0; i < newDomains.size(); i++) {
		vector<string> addition;
		addition.assign(1, newDomains[i]);
		domains.push_back(addition);
	}
	
}

/*   This function is used if a number is passed in instead of a set of domains
 *   There are 24 prebuilt sets of domains, numbered from 0 to 23.  Each one is
 * a different set of domains made up of lower case letters, upper case letters,
 * numbers, and symbols.  The one without cycling between domains (which is good
 * for easy levels) is 0, and 0 is the default of the constructor.  Other common
 * (and slightly tricky yet relatively "tame") values include 6, 8, and 12; most
 * other values could potentially be tricky as letters may end up becoming
 * symbols.
 *   If a bad value is passed in for c, it is treated as if it is a 0.
 */

void Offsets::setDomains(int c) {
	
	vector<string> addition;
	addition.assign(1, LOWER);
	domains.assign(1, addition);
	
	if (c >= 24) c = 0;
	
	if (c < 6) {
		
		addition.assign(1, UPPER);
		domains.push_back(addition);
		
		if (c < 2) {
			
			addition.assign(1, NUMBER);
			domains.push_back(addition);
			
			if (c == 0) {
				addition.assign(1, SYMBOL);
				domains.push_back(addition);
			} else { //c == 1
				domains[2].push_back(SYMBOL);
			}
			
		} else if (c < 4) {
			
			domains[1].push_back(NUMBER);
			
			if (c == 2) {
				addition.assign(1, SYMBOL);
				domains.push_back(addition);
			} else { //c == 3
				domains[1].push_back(SYMBOL);
			}
			
		} else { //c < 6
			
			domains[1].push_back(SYMBOL);
			
			if (c == 4) {
				domains[1].push_back(NUMBER);
			} else { //c == 5
				addition.assign(1, NUMBER);
				domains.push_back(addition);
			}
			
		}
		
	} else if (c < 12) {
		
		domains[0].push_back(UPPER);
		
		if (c < 8) {
			
			addition.assign(1, NUMBER);
			domains.push_back(addition);
			
			if (c == 6) {
				addition.assign(1, SYMBOL);
				domains.push_back(addition);
			} else { //c == 7
				domains[1].push_back(SYMBOL);
			}
			
		} else if (c < 10) {
			
			domains[0].push_back(NUMBER);
			
			if (c == 8) {
				addition.assign(1, SYMBOL);
				domains.push_back(addition);
			} else { //c == 9
				domains[0].push_back(SYMBOL);
			}
			
		} else { // c < 12
			
			domains[0].push_back(SYMBOL);
			
			if (c == 10) {
				domains[0].push_back(NUMBER);
			} else { //c == 11
				addition.assign(1, SYMBOL);
				domains.push_back(addition);
			}
			
		}
		
	} else if (c < 18) {
		
		domains[0].push_back(NUMBER);
		
		if (c == 14 || c == 16) {
			
			addition.assign(1, UPPER);
			domains.push_back(addition);
			
			if (c == 14) {
				addition.assign(1, SYMBOL);
				domains.push_back(addition);
			} else { //c == 16
				domains[1].push_back(SYMBOL);
			}
			
		} else if (c == 12 || c == 17) {
			
			domains[0].push_back(UPPER);
			
			if (c == 12) {
				addition.assign(1, SYMBOL);
				domains.push_back(addition);
			} else { //c == 17
				domains[0].push_back(SYMBOL);
			}
			
		} else { //c == 13 || c == 15
			
			domains[0].push_back(SYMBOL);
			
			if (c == 13) {
				domains[0].push_back(UPPER);
			} else { //c == 15
				addition.assign(1, UPPER);
				domains.push_back(addition);
			}
			
		}
		
	} else { //c < 24
		
		domains[0].push_back(SYMBOL);
		
		if (c == 21 || c == 23) {
			
			addition.assign(1, UPPER);
			domains.push_back(addition);
			
			if (c == 21) {
				addition.assign(1, NUMBER);
				domains.push_back(addition);
			} else { //c == 23
				domains[1].push_back(NUMBER);
			}
			
		} else if (c == 19 || c == 22) {
			
			domains[0].push_back(UPPER);
			
			if (c == 19) {
				addition.assign(1, NUMBER);
				domains.push_back(addition);
			} else { //c == 22
				domains[0].push_back(NUMBER);
			}
			
		} else { //c == 18 || c == 20
			
			domains[0].push_back(NUMBER);
			
			if (c == 18) {
				domains[0].push_back(UPPER);
			} else { //c == 20
				addition.assign(1, UPPER);
				domains.push_back(addition);
			}
		
		}
		
	}
	
}

void Offsets::cycleChar(char &character) {
	
	for (int a = 0; a < domains.size(); a++) {
		for (int b = 0; b < domains[a].size(); b++) {
			for (int c = 0; c < domains[a][b].size(); c++) {
				if (character == domains[a][b][c]) {
					shiftChar(character, a, b, c, s+long(d*index)+(v*previous) );
					return;
				}
			}
		}
	}
	
}

void Offsets::shiftChar(char &character, int a, int b, long c, long shift) {
	
	c += shift;
	
	while (c >= int(domains[a][b].size() )) {
		c -= domains[a][b].size();
		b++;
		if (b == domains[a].size() ) { b = 0; }
	}
	
	while (c < 0) {
		b--;
		if (b == -1) { b = domains[a].size()-1; }
		c += domains[a][b].size();
	}
	
	buffer.push_back(domains[a][b][c]);
	character = buffer[0];
	buffer.pop_front();
	
	previous = c+1;
	index++;
	
}

void Offsets::bufferCycle(char &character) {
	
	srand(clock() + rand());
	
	deque<char> buffer;
	
	for (int a = 0; a < domains.size(); a++) {
		for (int b = 0; b < domains[a].size(); b++) {
			for (int c = 0; c < domains[a][b].size(); c++) {
				if (character == domains[a][b][c]) {
					
					int maxShift = 0;
					for (int i = 0; i < domains[a].size(); i++) {
						maxShift += domains[a][i].size();
					}
					int shift = rand() % maxShift;
					
					shiftChar(character, a, b, c, shift);
					return;
				}
			}
		}
	}
	
}

