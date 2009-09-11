/* layer.hpp
 * Contains the functionality of each layer of game difficulty as an
 *   abstract class object.
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
 *
 * If you wish to write another Layer child class, please read the page at 
 *   <http://www.bis.doc.gov/encryption/pubavailencsourcecodenofify.html> first.
 *   United States law requires exportation of encryption programs (including via
 *   the Internet) through free licenses to be preceded by a specific email to
 *   US government agencies.  Since the functionality of Layer child classes can
 *   be interpreted as a type of encryption program, it may be a good idea to send
 *   such an email to maintain compliance with this law.
 */

#ifndef LAYER_HPP
#define LAYER_HPP

	#include "global.hpp"
	
	#include <string>
	using namespace std;
	
	extern string LOWER;
	extern string UPPER;
	extern string NUMBER;
	extern string SYMBOL;
	
	class Layer {
		public:
			
			virtual void cycleChar(char& character) = 0;
			virtual void bufferCycle(char&) = 0;
			
			virtual int getBuffer() = 0;
			
	};

#endif //LAYER_HPP
