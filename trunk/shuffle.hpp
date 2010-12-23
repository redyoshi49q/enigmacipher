/* shuffle.hpp
 * Rearranges the order of input according to set parameters.
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

#ifndef SHUFFLE_HPP
#define SHUFFLE_HPP
	
	#include "layer.hpp"
	#include "global.hpp"
	
	#include <vector>
	using namespace std;
	
	class Shuffle : public Layer {
		public:
			
			Shuffle(vector<int>);
			
			void cycleChar(char&);
			void bufferCycle(char&);
			bool needsBufferCycle() { return (delay > 0); };
			
			static Layer* getLayer();
			
		private:
			int phase;
			int delay;
			
			vector<int> order;
			vector<char> buffer;
			
	};
	
#endif // SHUFFLE_HPP
