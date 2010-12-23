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

Stack::Stack(Layer* newA, Layer* newB) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	
}

Stack::Stack(Layer* newA, Layer* newB, Layer* newC) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	layers.push_back(newC);
	
}

Stack::Stack(Layer* newA, Layer* newB, Layer* newC, Layer* newD) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	layers.push_back(newC);
	layers.push_back(newD);
	
}

Stack::Stack(Layer* newA, Layer* newB, Layer* newC, Layer* newD, Layer* newE) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	layers.push_back(newC);
	layers.push_back(newD);
	layers.push_back(newE);
	
}

Stack::Stack(vector<Layer*> newLayers) {
	
	layers = newLayers;
	
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


