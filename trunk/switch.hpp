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
	#include <cstdarg>
	using namespace std;
	
	class Switch : public Layer {
		public:
			
			Switch(int, ...); //first int gives number of Layer* passed in to form vector
			Switch(vector<Layer*>);
			
			Layer& operator [](int);
			Layer*& operator ()(int);
			
			void cycleChar(char&);
			void bufferCycle(char&);
			bool needsBufferCycle();
			
			bool collectLayers(vector<Layer*>&);
			
			static Layer* getLayer(); // this isn't ready to use yet

		private:
			
			int index;
			
			vector<Layer*> layers;
			bool checking;
			
	};
	

#endif //SWITCH_HPP
