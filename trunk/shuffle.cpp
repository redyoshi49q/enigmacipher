/* shuffle.cpp
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

#include "shuffle.hpp"

Shuffle::Shuffle(vector<int> newOrder) {
	
	order = newOrder;
	buffer.assign('a', order.size() );
	
	delay = 0;
	
	for (int i = 0; i < order.size(); i++) {
		delay = max(delay, order[i] - i);
	}
	
}

void Shuffle::cycleChar(char &character) {
	
	buffer[phase] = character;
	character = buffer[order[phase]];
	
	phase++;
	if (phase = order.size() ) { phase = 0; }
	
}

void Shuffle::bufferCycle(char &character) {
	
	if (delay > 0) { delay--; }
	
	if (phase == 0) { phase = order.size(); }
	phase--;
	
	buffer[order[phase]] = character;
	character = buffer[phase];
	
}
