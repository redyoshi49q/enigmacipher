/* enigma.hpp
 * A game that challenges the user to crack and manipulate codes by finding a
 *   correlation between their input and the game's output.
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

#ifndef ENIGMA_HPP
#define ENIGMA_HPP

	#include "level.hpp"
	#include "trigger.hpp"
	#include "layer.hpp"
	#include "offsets.hpp"
	#include "switch.hpp"
	#include "stack.hpp"
	//#include "disk.hpp" //this should work, but it isn't incorporated yet
	//#include "flipdisk.hpp" //this should work, but it isn't incorporated yet
	#include "option.hpp"
	#include "global.hpp"
	#include "homebrew.hpp"
	
	#include <iostream> //this may no longer be necessary here
	#include <string>
	#include <cstdlib> //this may no longer be necessary here
	#include <vector>
	#include <bitset>
	using namespace std;
	
	extern vector<bool> beaten;
	extern int MAX_MENU_INDEX; //do I need to make this an extern?
	
	int main();
	int runLevel(Level&, int);
	void welcome();
	void help();
	void referenced();
	void nextLevel(int&, char&, int, char);

#endif //ENIGMA_HPP
