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
	#include "option.hpp"
	#include "global.hpp"

	#include <iostream>
	#include <vector>
	#include <deque>
	#include <bitset>

	#if defined(_WIN32)
		#include <conio.h>
		#include <process.h>
	#elif defined(linux)
		#include <stdio.h>
        #include <termios.h>
        #include <unistd.h>
	#endif
	
	#include <sstream>

	using namespace std;

	class Level {
		public:
			Level(); //this allows for uninitialized levels, but
				//UNINITIALIZED LEVELS SHOULD NOT BE USED!!!

			Level(Layer*, vector<Trigger>); //done

			~Level();

			int engine();
			int engine2();
			
		private:
			
			#ifdef linux
                int mygetch();
			#endif

			int getMaxTriggerLength(); //done

			int checkTriggers(); //done

			void activateTrigger(int, bool&, bool&); //done
			bool isNotNull(int x) { return triggers[x].isNotNull(flags); }

			void cycleChar(char);
			void shiftTriggerBuffer(char);

			void setBuffers();

			bool needsBufferCycle();
			
			Layer *layer;
			vector<Layer*> layerList;

			vector<Trigger> triggers;

			deque<char> triggerBuffer;

			int flags;

	};

#endif //LEVEL_HPP
