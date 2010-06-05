/* disk.cpp
 * A type of game difficulty that acts as a changing one-to-one cipher.
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

#include "disk.hpp"

Disk::Disk(int c, vector<string> newEnd, int newDelay) {
	
	setDomains(c, begin);
	end = newEnd;
	
	if (newDelay < 0) {
		forward = false;
		fixed = false;
		delay = -newDelay;
	} else if (newDelay == 0) {
		forward = true; //this value doesn't matter here; it just needs to be valid
		fixed = true;
		delay = 0; //this value doesn't matter here; it just needs to be valid
	} else { //newDelay > 0
		forward = true;
		fixed = false;
		delay = newDelay;
	}
	
	index = 0;
	shift = 0;
	
}

Disk::Disk(vector<string> newBegin, int c, int newDelay) {
	
	begin = newBegin;
	setDomains(c, end);
	
	if (newDelay < 0) {
		forward = false;
		fixed = false;
		delay = -newDelay;
	} else if (newDelay == 0) {
		forward = true; //this value doesn't matter here; it just needs to be valid
		fixed = true;
		delay = 0; //this value doesn't matter here; it just needs to be valid
	} else { //newDelay > 0
		forward = true;
		fixed = false;
		delay = newDelay;
	}
		
	index = 0;
	shift = 0;
	
}

Disk::Disk(vector<string> newBegin, vector<string> newEnd, int newDelay) {
	
	begin = newBegin;
	end = newEnd;
	
	if (newDelay < 0) {
		forward = false;
		fixed = false;
		delay = -newDelay;
	} else if (newDelay == 0) {
		forward = true; //this value doesn't matter here; it just needs to be valid
		fixed = true;
		delay = 0; //this value doesn't matter here; it just needs to be valid
	} else { //newDelay > 0
		forward = true;
		fixed = false;
		delay = newDelay;
	}
	
	index = 0;
	shift = 0;
	
}

void Disk::cycleChar(char &character) {
	
	for (int a = 0; a < begin.size(); a++) {
		for (int b = 0; b < begin[a].size(); b++) {
			if (character == begin[a][b]) {
				if (fixed == true) {
					//skips to the code below
				} else {
					if (forward == true) {
						b += shift;
						while (b >= begin[a].size() ) {
							b -= begin[a].size();
						}
					} else { //forward == false
						b -= shift;
						while (b < 0) {
							b += begin[a].size();
						}
					}
					index++;
					if (index == delay) {
						index = 0;
						shift++;
					}
				}
				character = end[a][b];
				return;
			}
		}
	}
	
}

/*   This function is used if a number is passed in instead of a set of domains
 *   There are 24 prebuilt domain sets, numbered from 0 to 23.  Each one is
 * a different set of domains made up of lower case letters, upper case letters,
 * numbers, and symbols.  The one with completely separate domains (which is good
 * for easy levels) is 0, and 0 is the default of the constructor.  Other common
 * (and slightly tricky yet relatively "tame") values include 6, 8, and 12; most
 * other values could potentially be tricky as letters may end up becoming
 * symbols.
 *   If a bad value is passed in for c, it is treated as if it is a 0.
 */

void Disk::setDomains(int c, vector<string> &domains) {
	
	domains.assign(1, LOWER);
	
	if (c >= 24) c = 0;
	
	if (c < 6) {
		
		domains.push_back(UPPER);
		
		if (c < 2) {
			
			domains.push_back(NUMBER);
			
			if (c == 0) {
				domains.push_back(SYMBOL);
			} else { //c == 1
				domains[2].append(SYMBOL);
			}
			
		} else if (c < 4) {
			
			domains[1].append(NUMBER);
			
			if (c == 2) {
				domains.push_back(SYMBOL);
			} else { //c == 3
				domains[1].append(SYMBOL);
			}
			
		} else { //c < 6
			
			domains[1].append(SYMBOL);
			
			if (c == 4) {
				domains[1].append(NUMBER);
			} else { //c == 5
				domains.push_back(NUMBER);
			}
			
		}
		
	} else if (c < 12) {
		
		domains[0].append(UPPER);
		
		if (c < 8) {
			
			domains.push_back(NUMBER);
			
			if (c == 6) {
				domains.push_back(SYMBOL);
			} else { //c == 7
				domains[1].append(SYMBOL);
			}
			
		} else if (c < 10) {
			
			domains[0].append(NUMBER);
			
			if (c == 8) {
				domains.push_back(SYMBOL);
			} else { //c == 9
				domains[0].append(SYMBOL);
			}
			
		} else { // c < 12
			
			domains[0].append(SYMBOL);
			
			if (c == 10) {
				domains[0].append(NUMBER);
			} else { //c == 11
				domains.push_back(SYMBOL);
			}
			
		}
		
	} else if (c < 18) {
		
		domains[0].append(NUMBER);
		
		if (c == 14 || c == 16) {
			
			domains.push_back(UPPER);
			
			if (c == 14) {
				domains.push_back(SYMBOL);
			} else { //c == 16
				domains[1].append(SYMBOL);
			}
			
		} else if (c == 12 || c == 17) {
			
			domains[0].append(UPPER);
			
			if (c == 12) {
				domains.push_back(SYMBOL);
			} else { //c == 17
				domains[0].append(SYMBOL);
			}
			
		} else { //c == 13 || c == 15
			
			domains[0].append(SYMBOL);
			
			if (c == 13) {
				domains[0].append(UPPER);
			} else { //c == 15
				domains.push_back(UPPER);
			}
			
		}
		
	} else { //c < 24
		
		domains[0].append(SYMBOL);
		
		if (c == 21 || c == 23) {
			
			domains.push_back(UPPER);
			
			if (c == 21) {
				domains.push_back(NUMBER);
			} else { //c == 23
				domains[1].append(NUMBER);
			}
			
		} else if (c == 19 || c == 22) {
			
			domains[0].append(UPPER);
			
			if (c == 19) {
				domains.push_back(NUMBER);
			} else { //c == 22
				domains[0].append(NUMBER);
			}
			
		} else { //c == 18 || c == 20
			
			domains[0].append(NUMBER);
			
			if (c == 18) {
				domains[0].append(UPPER);
			} else { //c == 20
				domains.push_back(UPPER);
			}
		
		}
		
	}
	
}
