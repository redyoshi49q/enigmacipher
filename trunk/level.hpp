/* level.hpp
 * Contains the functionality of each game level as a class object.
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
 
#ifndef LEVEL_HPP
#define LEVEL_HPP

	#include "trigger.hpp"
	#include "layer.hpp"
	#include "global.hpp"

	#include <iostream>
	#include <vector>
	#include <deque>
	#include <bitset>

	#include <conio.h>		//Jacob's Code
	#include <process.h>	//Jacob's Code
	#include <sstream>		//Jacob's Code

	using namespace std;

	class Level {
		public:
			Level(); //this allows for uninitialized levels, but
				//UNINITIALIZED LEVELS SHOULD NOT BE USED!!!
			
			Level(Layer*, vector<Trigger>); //done
			Level(vector<Layer*>, vector<Trigger>); //done
			
			~Level();
			
			int engine();
			int engine2();  //Jacob's Code
			
			int getBuffer(int i) { return layers[i]->getBuffer(); } //done
			int size() { return layers.size(); }
			
			int getMaxTriggerLength(); //done
			
			int checkTriggers(); //done
			
			void activateTrigger(int, bool&, bool&); //done

			void cycleChar(char);
			void shiftTriggerBuffer(char);
			
			void setBuffers();
			
		private:
			
			vector<Layer*> layers;
			
			vector<Trigger> triggers;
			
			deque<char> triggerBuffer;
			
			int flags;
			
	};

#endif //LEVEL_HPP
