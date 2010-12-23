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

Switch::Switch(Layer* newA, Layer* newB) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	
	index = 0;
	
}

Switch::Switch(Layer* newA, Layer* newB, Layer* newC) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	layers.push_back(newC);
	
	index = 0;
	
}

Switch::Switch(Layer* newA, Layer* newB, Layer* newC, Layer* newD) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	layers.push_back(newC);
	layers.push_back(newD);
	
	index = 0;
	
}

Switch::Switch(Layer* newA, Layer* newB, Layer* newC, Layer* newD, Layer* newE) {
	
	layers.push_back(newA);
	layers.push_back(newB);
	layers.push_back(newC);
	layers.push_back(newD);
	layers.push_back(newE);
	
	index = 0;
	
}

Switch::Switch(vector<Layer*> newLayers) {
	
	layers = newLayers;
	index = 0;
	
}

void Switch::bufferCycle(char &character) {
		
	layers[index]->bufferCycle(character);
	
	index++;
	if (index == layers.size() ) index = 0;
	
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
	
}
