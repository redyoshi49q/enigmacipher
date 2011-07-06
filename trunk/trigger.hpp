/* trigger.hpp
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
 
#ifndef TRIGGER_HPP
#define TRIGGER_HPP

	#include "layer.hpp"
	#include "global.hpp"

	#include <iostream>
	#include <string> //is this needed here?
	#include <cstdlib>
	#include <vector>
	#include <deque>
	#include <bitset>
	using namespace std;
	
	class Trigger {
		public:
			
			// word, reply, flag reply(opt), trips flag/win/easter egg as bitset
			
			// word, reply array, flag trip array, win array, easter egg array,
				// Layer array (opt)
			
			Trigger(string, string, bool, bool, bool);
			Trigger(string, string, string, bool, bool, bool);
			  //for some reason, default parameters DO NOT WORK HERE!
			    //constructor 1 gets called, even when constructor 2 is intended
			    //instead, use the bitset constructors below
			    
			Trigger(string, string, bitset<3> = bitset<3>(4ul) );
			Trigger(string, string, string, bitset<3> = bitset<3>(0ul) );
				//these constructors default bitsets are for enigma and help, respectively
			    //the appropriate bitset for a password is 2ul
			    //the bitset for an easter egg that isn't a password is 1ul
			    //and the bitset for an easter egg that is a password is 3ul
			    //note that by default, easter eggs and passwords do not get an
			     //easter egg/beat the level until the first flag is tripped.  To
			     //change this, use one of the vector constructors below.
			
			Trigger(string, vector<string>,
			   vector<bool>, vector<bool>, vector<bool>,
				vector<Layer*> = vector<Layer*>() );

			Trigger(string, vector<string>,
			   vector<bool>, vector<bool>, vector<bool>,
				Layer*);
			
			// Trigger(string, vector<string>,
			//	vector<int>, vector<bool>, vector<bool>,
			//	vector<Layer*> = vector<Layer*>() );
			
			// Trigger(string, vector<string>,
			//	vector<int>, vector<bool>, vector<bool>,
			//	Layer*);
			
			~Trigger();
			
			void activate(int&, bool&, bool&); //done
			
			bool checkTrigger(deque<char>); //done
			
			bool isNotNull(int &flag) { return (reply[min(flag, int(reply.size())-1)] != ""); }
			
			int getNumOfFlags(); //done
			
			int getLengthOfTrigger(); //done
			
			Layer* getLayer(int);
			
			int Trigger::getNumOfLayers() { return layerArray.size(); }
			
		private:
			
			string keyWord;
			vector<string> reply;
			vector<bool> flagTripArray;
			vector<bool> easterEggArray;
			vector<bool> victoryArray;
			vector<Layer*> layerArray;
			
	};
	
#endif //TRIGGER_HPP
