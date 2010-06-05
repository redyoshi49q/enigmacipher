/* option.hpp
 * Contains the functionality of in game options as class objects
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

#ifndef OPTION_HPP
#define OPTION_HPP
	
	#include "global.hpp"
	
	#include <vector>
	#include <string>
	using namespace std;
	
	enum {ENGINE_VERSION = 0, CLEAR_IN_GAME};
	
	void initializeOptions();
	void changeOptions();
	
	class Option {
		public:
		
			Option(string, vector<string>, vector<string>, int = 0);
			Option(string, string, vector<string>, vector<string>, int=0);
			Option(string, vector<string>, vector<string>, string);
			Option(string, string, vector<string>, vector<string>, string);
				//the second constructor is preferable; it has a description
				  //and it allows for a default option to be given by its text
			
			string name() { return Name; }
			string description() { return Description; }
			
			string settingName() { return choices[setting]; }
			int settingNum() { return setting; }
			
			void change();
			
			void shift(int other) { *this += other; }
			void set(string other) { *this = other; }
			void set(int other) { *this = other; }
			
			void operator =(string);
			void operator =(int);
			
			bool operator ==(string other) { return (choices[setting] ==
				other ); } //this needs toUpper() calls, but they're stubborn
			bool operator ==(int other) { return (setting == other); }
				//the equality operator that uses strings is preferable, because
				  //if options are removed from the game to allow platform
				  //compatibility, the number of the option might change.
			
			Option operator +=(int);
			Option operator -=(int other) { return (*this += (-other) ); }
			
		private:
			
			string Name, Description;
			vector<string> choices, descriptions;
			int setting, defaultSetting;
			
			
	};
	
	extern vector<Option> Options;
	
	
#endif //OPTION_HPP
