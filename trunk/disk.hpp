/* disk.hpp
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

#ifndef DISK_HPP
#define DISK_HPP
	
	#include "layer.hpp"
	#include "global.hpp"
	
	#include <vector>
	#include <string>
	using namespace std;
	
	class Disk : public Layer {
		public:
			
			Disk(int, vector<string>, int = 1);
			Disk(vector<string>, int, int = 1);
			Disk(vector<string>, vector<string>, int = 1);
		
			void cycleChar(char&);
			void bufferCycle(char& character) { cycleChar(character); }
			
			//int getBuffer() { return 0; }
			
			static Layer* getLayers();
				//this function is in getlayers.cpp
			
			Disk flip() { return Disk(end, begin, (forward?-delay:delay) ); }
			Disk reverse() { return Disk(begin, end, (forward?-delay:delay) ); }
				//these are useful for making complementary Disk objects
					//the first acts as an inverse to the called disk
					//the second shifts in the opposite direction

		private:
			
			void setDomains(int, vector<string>&);
			
			int index, delay, shift;
			bool forward, fixed;
			
			vector<string> begin, end;
			
	};
	
#endif //DISK_HPP
