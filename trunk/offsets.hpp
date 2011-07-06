/* offsets.hpp
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

#ifndef OFFSETS_HPP
#define OFFSETS_HPP

	#include "layer.hpp"
	#include "global.hpp"
	
	#include <string>
	#include <vector>
	#include <deque>
	#include <cstdlib>
	using namespace std;
	
	class Offsets : public Layer {
		
		public:
			
			Offsets(int=0, int=0, int=0, int=0, int=0);
			Offsets(int, int, int, int, vector<string>);
			Offsets(int, int, int, int, vector<vector<string> >);
			
			void cycleChar(char&);
			void bufferCycle(char&);
			bool needsBufferCycle() { return (delay > 0); };
			
			//int getBuffer() { return b; };
			
			static Layer* getLayer();
		
		private:

			void setDomains(int);
			void shiftChar(char&, int, int, long, long);
		
			int s, d, v, b;
			int previous, index;
			int delay;
			
			deque<char> buffer;
			vector<vector<string> > domains;
			
	};

#endif //OFFSETS_HPP
