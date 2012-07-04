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
	#include "shuffle.hpp"
	#include "disk.hpp" //this should work, but it isn't incorporated yet
	#include "flipdisk.hpp" //this should work, but it isn't incorporated yet
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
	extern int MAX_MENU_INDEX; // should I make this an extern?  I don't think so, but oh well...
	
	enum sublevel {ONE = 0, TWO_A, TWO_B, THREE_A, THREE_B, FOUR_A, FOUR_B, FOUR_C, FIVE_A, FIVE_B, FIVE_C, SIX_A, SIX_B, SIX_C,
		SEVEN_A, SEVEN_B, SEVEN_C, EIGHT_A, EIGHT_B, EIGHT_C, NINE_A, NINE_B, NINE_C, TEN_A, TEN_B, TEN_C, TEN_D, TEN_E,
		ELEVEN_A, ELEVEN_B, ELEVEN_C, TWELVE, THIRTEEN, FOURTEEN, FIFTEEN, SIMPLE, SUBLEVELS};
	
	int main();
	int runLevel(Level*, int);
	void welcome();
	void help();
	void referenced();
	void nextLevel(int&, char&, int, char);

#endif //ENIGMA_HPP
