/* global.hpp
 * Holds the variables and functions that are used universally throughout
 *   the program.
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

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

	#include <iostream>
	#include <cstdlib>
	#include <string>
	using namespace std;

	//extern int completed[6]; //this will be used for story mode (when it is written)
	extern istream &in;
	extern istream &g_in;
	extern ostream &out; 
	extern ostream &g_out;
	
	void cls();
	int getInt();
	void pause();
	void complain(string);

#endif //GLOBAL_HPP
