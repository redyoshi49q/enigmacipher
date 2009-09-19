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

	#include "level.hpp"		//modified by Jacob
	#include "trigger.hpp"
	#include "layer.hpp"
	#include "offsets.hpp"
	#include "switch.hpp"
	//#include "disk.hpp" //this should work, but it isn't incorporated yet
	//#include "flipdisk.hpp" //this should work, but it isn't incorporated yet
	#include "global.hpp"		//Modified by Jacob
	#include "homebrew.hpp"
	
	#include <iostream> //this may no longer be necessary here
	#include <string>
	#include <cstdlib> //this may no longer be necessary here
	#include <vector>
	#include <bitset>
	using namespace std;

	extern bool engineVersion;
	
	int main();
	void runLevel(Level&, vector<bool>&, int);
	void welcome();
	void menu();
	void help();
	void about();
	void exit();
	void referenced(vector<bool>&);

#endif //ENIGMA_HPP
