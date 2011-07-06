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
	
	srand(clock() + rand());
	
	order = newOrder;
	buffer.assign(order.size(), char('a' + (rand() % 26) ));
	
	delay = 0;
	phase = 0;
	
	for (int i = 0; i < order.size(); i++) {
		delay = max(delay, order[i] - i);
	}
	
}

Shuffle::Shuffle(int newSize, ...) {
	
	order.clear();
	
	va_list newOrder;
	va_start(newOrder, newSize);
	for (int i = 0; i < newSize; i++) {
		order.push_back(va_arg(newOrder, int));
	}
	va_end(newOrder);
	
	buffer.assign(order.size(), 'a');
	
	delay = 0;
	phase = 0;
	
	for (int i = 0; i < order.size(); i++) {
		delay = max(delay, order[i] - i);
	}
	
}

void Shuffle::cycleChar(char &character) {
	
	buffer[phase] = character;
	character = buffer[order[phase]];
	
	phase++;
	if (phase == order.size() ) { phase = 0; }
	
}

void Shuffle::bufferCycle(char &character) {
	
	if (delay > 0) { delay--; }
	cycleChar(character);
	
}
