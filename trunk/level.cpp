/* level.cpp
 * Contains the functionality of each game level as a class object.
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

 #include "level.hpp"

/* Level constructors, used as a data warehouse for level data.
 * Note that most variables CANNOT be changed externally once the level has been
 *   initialized.
 */

Level::Level() {} //a level declared like this should not be used
	//until it is initialized by a different constructor.

Level::Level(Layer *newLayer, vector<Trigger> newTriggers) {

	layers.assign(1, newLayer);

	triggers = newTriggers;

	flags = 0;

}

Level::Level(vector<Layer*> newLayers, vector<Trigger> newTriggers) {

	layers = newLayers;

	triggers = newTriggers;

	flags = 0;

}

Level::~Level() {}

int Level::engine() {

	triggerBuffer.assign(getMaxTriggerLength(), '\n');

	setBuffers();

	char input, lastChar = 'a';
	bool victory = false;
	bool easterEgg = false;

	while (victory == false) {

		input = g_in.get();

		if (input == '\n' || input == ' ' || input == '\t') {

			shiftTriggerBuffer(input);

			if (input == '\n') {
				if (lastChar == '\n' && Options[CLEAR_IN_GAME] == "Enabled") {
					cls();
				} else if (lastChar == '\t') {
					out << "Level has been exited.\nPress enter to continue.";
					pauseOutput();
					cls();

					return (easterEgg * 2 + victory);
				}
			}

		} else { //if any other special characters are to be recognized, the code for
			//that needs to go as an else if clause before cycleChar() is called.
			//otherwise, things might break

			cycleChar(input);

		}

		lastChar = input;

		switch (int x = checkTriggers()) {

			case -1:
				break;

			default:

				bool newLine = isNotNull(x);

				activateTrigger(x, victory, easterEgg);

				if (newLine) { shiftTriggerBuffer('\n'); }

				break;

		}

	}

	g_in.ignore(100, '\n');

	return (easterEgg * 2 + victory);
		//0 for no victory
		//1 for victory
		//2 for easter egg, but no victory (do nothing)
		//3 for victory with easter egg

}

int Level::engine2() {

	int idx = 0, idx2 = 0;
	char ch;

	triggerBuffer.assign(getMaxTriggerLength(), '\n');
	setBuffers();

	bool victory = false;
	bool easterEgg = false;

	while(victory == false) {
		#ifdef _WIN32
			ch = _getch();
		#elif linux
			ch = mygetch();
		#endif

		switch(static_cast<int>(ch)) {
			case 224:
				#ifdef _WIN32
					ch = _getch(); //this discards the extra character in the buffer
				#elif linux
					ch = mygetch();
				#endif
				break;

			case 13:
				idx = idx2 = 0;
				shiftTriggerBuffer('\n');
				break;

			case static_cast<int>('\b'):
				idx++;
				idx2 = 0;
				if(idx == 3)
				{
					return 2;
				}
				break;

			case static_cast<int>(' '):
				idx = idx2 = 0;
				shiftTriggerBuffer(' ');
				break;

			case static_cast<int>('\t'):
				idx2++;
				idx = 0;
				if(idx2 == 3) {
					if (Options[CLEAR_IN_GAME] == "Enabled") { cls(); }
					idx2 = 0;
				}
				break;

			default:
				idx = idx2 = 0;
				cycleChar(ch);
				break;

		}

		switch(int x = checkTriggers() ) {
			case -1:
				break;

			default:
				bool newLine = isNotNull(x);
				activateTrigger(x, victory, easterEgg);
				if (newLine) { shiftTriggerBuffer('\n'); }
				break;	out << "\nPress enter to continue.";

	pauseOutput();
	cls();

		}

	}

	return (easterEgg * 2 + victory);

}
#ifdef linux
int Level::mygetch()
{
        struct termios oldt, newt;
        int ch;
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        return ch;
}
#endif

int Level::getMaxTriggerLength() {

	int maxTriggerLength = 0;

	for (int i = 0; i < triggers.size(); i++) {

		maxTriggerLength = max(maxTriggerLength,
			triggers[i].getLengthOfTrigger());

	}

	return maxTriggerLength;

}

int Level::checkTriggers() {

	for (int i = 0; i < triggers.size(); i++) {
		if (triggers[i].checkTrigger(triggerBuffer) ) {
			return i;
		}
	}

	return -1;

}


void Level::activateTrigger(int happiness, bool& victory, bool& easterEgg) {

	vector<Layer*> temp = triggers[happiness].getLayers(flags);
	if (temp.size() != 0) {
		layers = temp;
		setBuffers();
	}

	triggers[happiness].activate(flags, victory, easterEgg);

}



void Level::cycleChar(char character) {

	for (int i = 0; i < layers.size(); i++) {
		layers[i]->cycleChar(character);
	}

	shiftTriggerBuffer(character);

}

void Level::shiftTriggerBuffer(char input) {

	g_out << input;

	triggerBuffer.push_back(input);

	triggerBuffer.pop_front();

}

void Level::setBuffers() {

	char character;

	for (int depth = 0; depth < size(); depth++) {
		for (int a = 0; a < getBuffer(depth); a++) {
			character = 'a';
			for (int b = 0; b < size(); b++) {
				layers[b]->bufferCycle(character);
			}
		}
	}

}
