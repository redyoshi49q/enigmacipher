/* stack.cpp
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

#include "stack.hpp"

Stack::Stack(int newSize, ...) {
	
	layers.clear();
	
	va_list newLayers;
	va_start(newLayers, newSize);
	for (int i = 0; i < newSize; i++) {
		layers.push_back(va_arg(newLayers, Layer*));
	}
	va_end(newLayers);
	
	checking = false;
	
}

Stack::Stack(vector<Layer*> newLayers) {
	
	layers = newLayers;
	checking = false;
	
}

Layer& Stack::operator [](int index) {
	
	if (index < 0) { index = 0; }
	
	if (index >= layers.size() ) { index = layers.size() - 1; }
	
	return *layers[index];
	
}

Layer*& Stack::operator ()(int index) {
	
	if (index < 0) { index = 0; }
	
	while (layers.size() - 1 > index) { layers.push_back(NULL); }
	
	return layers[index];
	
}

void Stack::cycleChar(char& character) {
	
	for (int i = 0; i < layers.size(); i++) {
		layers[i]->cycleChar(character);
	}
	
}

void Stack::bufferCycle(char& character) {
	
	for (int i = 0; i < layers.size(); i++) {
		layers[i]->bufferCycle(character);
	}
	
}

bool Stack::needsBufferCycle() {
	
	if (checking == true) {
		return false;
		/* this prevents the function from going into infinite loops, and
		 *   the other branches of this will be checked in the function
		 *   call that set checking to true
		 */
	}
	
	checking = true;
	
	for (int i = 0; i < layers.size(); i++) {
		if (layers[i]->needsBufferCycle() == true) {
			checking = false;
			return true;
		}
	}
	
	checking = false;
	return false;
	
}

bool Stack::collectLayers(vector<Layer*> &layerList) {
	
	bool returned = Layer::collectLayers(layerList);
	
	if (returned == true) {
		for (int i = 0; i < layers.size(); i++) {
			layers[i]->collectLayers(layerList);
		}
	} // if false, just implicitly return
	
}
