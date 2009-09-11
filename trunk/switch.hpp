/* switch.hpp
 * A type of game difficulty that cycles between different level configurations.
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

#ifndef SWITCH_HPP
#define SWITCH_HPP

	#include "layer.hpp"
	#include "global.hpp"
	
	#include <vector>
	using namespace std;
	
	class Switch : public Layer {
		public:
			
			Switch(Layer*, Layer*);
			Switch(Layer*, Layer*, Layer*);
			Switch(Layer*, Layer*, Layer*, Layer*);
			Switch(Layer*, Layer*, Layer*, Layer*, Layer*);
			Switch(vector<Layer*>);
		
			void cycleChar(char&);
			void bufferCycle(char&);
			
			int getBuffer();

		private:
			
			int index;
			
			vector<Layer*> layers;
			
	};
	

#endif //SWITCH_HPP
