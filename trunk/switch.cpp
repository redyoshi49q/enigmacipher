/* switch.cpp
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

#include "switch.hpp"

Switch::Switch(int newSize, ...) {
	
	layers.clear();
	
	va_list newLayers;
	va_start(newLayers, newSize);
	for (int i = 0; i < newSize; i++) {
		layers.push_back(va_arg(newLayers, Layer*));
	}
	va_end(newLayers);
	
	index = 0;
	checking = false;
	
}

Switch::Switch(vector<Layer*> newLayers) {
	
	layers = newLayers;
	index = 0;
	checking = false;
	
}

Layer& Switch::operator [](int index) {
	
	if (index < 0) { index = 0; }
	
	if (index >= layers.size() ) { index = layers.size() - 1; }
	
	return *layers[index];
	
}

Layer*& Switch::operator ()(int index) {
	
	if (index < 0) { index = 0; }
	
	while (layers.size() - 1 > index) { layers.push_back(NULL); }
	
	return layers[index];
	
}

void Switch::bufferCycle(char &character) {
		
	layers[index]->bufferCycle(character);
	
	index++;
	if (index == layers.size() ) index = 0;
	
}

bool Switch::needsBufferCycle() {
	
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

void Switch::cycleChar(char &character) {
		
	layers[index]->cycleChar(character);
	
	index++;
	if (index == layers.size() ) index = 0;
	
}

Layer* Switch::getLayer() {
	
	//ask for next layer of switch layer
	
	//call getLayer() for that layer type
	
		//Layer* bob = Stack::getLayer();
	
	//append returned Layer* to a vector
	
	//return if user wants to
	
	//shove vector into new switch Layer*
	
	//return new switch Layer*
	
	return NULL; // this is a stub
	
}

bool Switch::collectLayers(vector<Layer*> &layerList) {
	
	bool returned = Layer::collectLayers(layerList);
	
	if (returned == true) {
		for (int i = 0; i < layers.size(); i++) {
			layers[i]->collectLayers(layerList);
		}
	} // if false, just implicitly return
	
}
