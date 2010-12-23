/* stack.hpp
 * A type of game difficulty that logically binds several other layers of
 *   difficulty (this is meant to be used with switches)
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

#ifndef STACK_HPP
#define STACK_HPP

	#include "layer.hpp"
	#include "global.hpp"

	#include <vector>
	using namespace std;

	class Stack : public Layer {
		public:
			
			Stack(Layer*, Layer*);
			Stack(Layer*, Layer*, Layer*);
			Stack(Layer*, Layer*, Layer*, Layer*);
			Stack(Layer*, Layer*, Layer*, Layer*, Layer*);
			Stack(vector<Layer*>);
			
			void cycleChar(char&);
			void bufferCycle(char&);
			
			static Layer* getLayer();
			
		private:
			
			vector<Layer*> layers;
			
	};
	
#endif //STACK_HPP
