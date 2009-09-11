/* trigger.cpp
 * Contains the functionality of each key word in Enigma levels as a class
 *   object.
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
 
#include "trigger.hpp"

/* Trigger constructor, used for triggers independent of flags (i.e. "enigma")
 *   when only 1 flag exists.
 */

Trigger::Trigger(string word, string newReply, bool tripsFlag, bool beatsLevel,
	bool easterEgg) {
	
	keyWord = word;
	
	reply.assign(2, newReply);
	
	flagTripArray.push_back(tripsFlag);
	
	victoryArray.push_back(false);
	victoryArray.push_back(beatsLevel);
	
	easterEggArray.push_back(false);
	easterEggArray.push_back(easterEgg);
		
}

/* Trigger constructor, used for triggers dependent on flags (i.e. "help",
 *   passwords) when only 1 flag exists.
 */

Trigger::Trigger(string word, string newReply, string flagReply, bool tripsFlag,
	bool beatsLevel, bool easterEgg) {
	
	keyWord = word;
	
	reply.push_back(newReply);
	reply.push_back(flagReply);
	
	flagTripArray.push_back(tripsFlag);
	
	victoryArray.push_back(false);
	victoryArray.push_back(beatsLevel);
	
	easterEggArray.push_back(false);
	easterEggArray.push_back(easterEgg);
		
		
}

Trigger::Trigger(string word, string newReply, bitset<3> levelBits) {
	
	keyWord = word;
	
	reply.assign(2,newReply);
	
	flagTripArray.push_back(levelBits[2]);
	
	victoryArray.push_back(false);
	victoryArray.push_back(levelBits[1]);
	
	easterEggArray.push_back(false);
	easterEggArray.push_back(levelBits[0]);
		
}

/* Trigger constructor, used for triggers dependent on flags (i.e. "help",
 *   passwords) when only 1 flag exists.
 */

Trigger::Trigger(string word, string newReply, string flagReply,
	bitset<3> levelBits) {
	
	keyWord = word;
	
	reply.push_back(newReply);
	reply.push_back(flagReply);
		
	flagTripArray.push_back(levelBits[2]);
	
	victoryArray.push_back(false);
	victoryArray.push_back(levelBits[1]);
	
	easterEggArray.push_back(false);
	easterEggArray.push_back(levelBits[0]);
		
}

/* Trigger constructor, used when multiple levels of flags exist.
 */

Trigger::Trigger(string word, vector<string> replies, vector<bool> newFlagArray,
	vector<bool> beatsLevelArray, vector<bool> newEasterEggArray,
	vector<vector<Layer*> > newLayerArray) {
	
	keyWord = word;
	
	reply = replies;
	
	flagTripArray = newFlagArray;
	
	victoryArray = beatsLevelArray;
	
	easterEggArray =  newEasterEggArray;
	
	layerArray = newLayerArray;
	
}

Trigger::Trigger(string word, vector<string> replies, vector<bool> newFlagArray,
	vector<bool> beatsLevelArray, vector<bool> newEasterEggArray,
	vector<Layer*> newLayerArray) {
	
	keyWord = word;
	
	reply = replies;
	
	flagTripArray = newFlagArray;
	
	victoryArray = beatsLevelArray;
	
	easterEggArray =  newEasterEggArray;
	
	for (int i = 0; i < newLayerArray.size(); i++) {
		vector<Layer*> addition;
		addition.assign(1, newLayerArray[i]);
		layerArray.push_back(addition);
	}
	
}

Trigger::~Trigger() {} //nothing needs to be done here right now...

void Trigger::activate(int &flag, bool &victory, bool &easterEgg) {
	
	out << reply[min(flag, int(reply.size())-1)];
	
	victory = victory || victoryArray[min(flag,int(victoryArray.size())-1)];
	easterEgg = easterEgg || easterEggArray[min(flag,int(easterEggArray.size())-1)];
	
	if (flag < int(flagTripArray.size()) && flagTripArray[flag]==true) { flag++; }
	
}

bool Trigger::checkTrigger(deque<char> testChars) {
	
	for (int i = 0; i < keyWord.size(); i++) {
		
		if (testChars[testChars.size() - i - 1] !=
			keyWord[keyWord.size() - i - 1]) { return false; }	
		
	}
	
	return true;
	
}

int Trigger::getNumOfFlags() { return max(max(max(max(reply.size()-1,
	flagTripArray.size() ), easterEggArray.size()-1),
	victoryArray.size()-1 ), layerArray.size()-1 ); }
	//do I still need this function?

int Trigger::getLengthOfTrigger() {return keyWord.size();}

vector<Layer*> Trigger::getLayers(int flag) {
	
	if (flag > int(layerArray.size() )-1) { return vector<Layer*>(); }
	
	return layerArray[flag];
	
}
