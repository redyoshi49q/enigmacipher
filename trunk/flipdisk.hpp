/* flipdisk.hpp
 * A type of game difficulty that acts (or should act) as a reversible
 *   one-to-one cipher.
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

#ifndef FLIPDISK_HPP
#define FLIPDISK_HPP
	
	#include "layer.hpp"
	#include "global.hpp"
	
	#include <vector>
	#include <string>
	#include <cstdlib>
	using namespace std;
	
	class FlipDisk : public Layer {
		public:
			
			FlipDisk(vector<string>, vector<vector<int> >, int = 1);
			FlipDisk(int, vector<vector<int> >, int = 1);
			FlipDisk(vector<string>, int = 1);
			FlipDisk(int = 0, int = 1); //the bottom 2 constructors create a partially random FlipDisk
				//use the top 2 constructors if you want to guarantee a consistent level
				//(i.e. for predefined levels)
			
			void cycleChar(char&);
			void bufferCycle(char &character) { cycleChar(character); }
			
			//int getBuffer() { return 0; }
			
			static Layer* getLayer();
				//this function is in getlayers.cpp
			
			FlipDisk reverse() { return FlipDisk(domains, shifts, (forward?-delay:delay) ); }
			
		private:
			
			void setDomains(int);
			void randomShifts();
			
			int index, delay, shift;
			bool fixed, forward;
			
			vector<vector<int> > shifts;
			vector<string> domains;
	};
	
#endif //FLIPDISK_HPP
