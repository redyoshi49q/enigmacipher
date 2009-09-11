/* homebrew.hpp
 * Acts as an interface for homebrew coders to make their own levels.
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

#ifndef HOMEBREW_HPP
#define HOMEBREW_HPP
	
	#include "level.hpp"
	#include "trigger.hpp"
	#include "layer.hpp"
	//include desired layer children here
	#include "global.hpp"
	
	#include <vector>
	#include <bitset>
	using namespace std;
	
	void homebrew_main();
	
#endif //HOMEBREW_HPP
