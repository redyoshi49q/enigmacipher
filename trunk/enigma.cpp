/* enigma.cpp
 * A game that challenges the user to crack and manipulate codes by finding a
 *   correlation between their input and the game's output.
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
 * As written, this program requires the following files to complie:
 *   enigma.cpp
 *   enigma.hpp
 *   level.cpp
 *   level.hpp
 *   trigger.cpp
 *   trigger.hpp
 *   layer.cpp
 *   layer.hpp
 *   offsets.cpp
 *   offsets.hpp
 *   switch.cpp
 *   switch.hpp
 *   stack.cpp
 *   stack.hpp
 *   global.cpp
 *   global.hpp
 *   homebrew.cpp
 *   homebrew.hpp
 *   option.cpp
 *   option.hpp
 *
 * All other files that are a part of the project are not yet incorporated.
 *   They are in a usable (but untested) state, and no level has yet been
 *   written that uses them.  This will soon change, though.
 *
 * The files global.cpp/hpp are of particular use for players who want their
 *   scripts to interact with the game engine.  The stream references g_in and
 *   g_out are the ones that the game engine uses for I/O, and these can
 *   be changed from cin/cout to ones in a player written program.
 *   The game has yet to be tested in an environment where g_in and g_out refer
 *   to different streams than in and out, but nothing seems to indicate that this
 *   would break things.
 *
 * In a similar sense, the files homebrew.cpp/hpp are of particular use for those
 *   wanting to write their own levels for Enigma.  The main function calls the
 *   homebrew.cpp/hpp homebrew_main() function when the user chooses to play homebrew
 *   levels, which means that levels can be easily written for Enigma without
 *   affecting the main portion of the code.
 *
 * If you wish to write another Layer child class, please read the page at
 *   <http://www.bis.doc.gov/encryption/pubavailencsourcecodenofify.html> first.
 *   United States law requires exportation of encryption programs (including via
 *   the Internet) through free licenses to be preceded by a specific email to
 *   US government agencies.  Since the functionality of Layer child classes can
 *   be interpreted as a type of encryption program, it may be a good idea to send
 *   such an email to maintain compliance with this law.
 *
 * Revision History:
 *
 * r10:
 *   added garbage collection, changed some things to allow for circular Layer references
 *     added Stack and Scramble classes
 *   author: redyoshi49q (Ethan)
 *
 * r8-9:
 *   minor code changes
 *   author: eidolonlord (Jacob)
 *
 * r7:
 *   changed interface so that the user would go to the next level by default
 *   author: redyoshi49q (Ethan)
 *
 * r6:
 *   resubmission to *actually* include Option class
 *     Option class was excluded by accident in r5
 *   author:  redyoshi49q (Ethan)
 *
 * r5:
 *   changes to some variable locations, clean up of code and addition of Option class
 *     main menu interface changed and new levels added to form tutorial
 *   author: redyoshi49q (Ethan)
 *
 * r4:
 *   clean up of code in engine2()
 *   author: eidolonlord (Jacob)
 *
 * r3:
 *   addition of engine2()
 *   author: eidolonlord (Jacob)
 *
 * r2 (stable):
 *   original release, inclusion of 15 levels and a simple level builder
 *   author: redyoshi49q (Ethan)
 */

#include "enigma.hpp"

vector<bool> beaten;
int MAX_MENU_INDEX = 1; // this number will need to get changed when more level types are added.
int MAX_TEMP_LAYERS = 3; // increase this if more complicated levels are added later

int main() {
	
	initializeOptions();
	
	vector<Trigger> triggers;
	vector<Layer*> layers;
	vector<string> reply, replies;
	vector<bool> b1, b2, b3, tripsFlag, beatsLevel, easterEgg;
	
	Layer* tempLayers[MAX_TEMP_LAYERS];
	
	beaten.assign(int(SUBLEVELS), false);
	
	cls();
	welcome();
	
	string input;
	Level level;
	int type = 0, oldType = 0;
	char subtype = '?', oldSubtype = '?';
	int index = 0;
	
	while (true) { //an input of 'h' returns from the main function
	
		cls();

		triggers.clear();
		layers.clear();

		if (type == oldType && subtype == oldSubtype) {
			//this is executed if the user is returning to the menu.

		 	out << "Welcome to Enigma!\n"
				<< "Please choose one of the following options:\n"
				<< "(If you have never played before, you want option 1.)\n";

			switch (index) {
				case 0:
					out << "  1   : Practice Level (no encryption)\n"
						<< "  2a-b: Static Offset\n"
						<< "  3a-b: Buffer\n"
						<< "  4a-c: Static Offset with Buffer\n"
						<< "  5a-c: Dynamic Offset\n"
						<< "  6a-c: Simple Shuffle\n"
						<< "  7a-c: Variable Offset\n"
						<< "  8a-c: Easy Switch Level\n"
						<< "  9a-c: Easy Stack Level\n"
						<< " 10a-e: Advanced Offsets\n";
					break;

				case 1:
					out << " 11a-c: Advanced Stack Level (reserved for the persistent)\n"
						<< " 12   : Advanced Switch Level (reserved for the highly persistent)\n";
					#ifdef FALSE // I'm lazy.
					out	<< " 13   : Expert Level (reserved for the insane)\n"
						<< " 14   : Evil Level (reserved for the very insane)\n"
						<< " 15   : Furious Level (reserved for the particularly insane)\n";
					#else // FALSE; Again, I'm lazy.
					out << "\n\n\n"; // this prevents the letter based menu from moving
					#endif
					out	<< "\n\n\n\n\n"; //this prevents the letter based menu from moving
					break;

				default:
					out << "Something is seriously broken here...\n";
					//this case should never be called.
					break;

			}

			if (index > 0) {
				out << "  a: Show easier levels\n";
			} else if (MAX_MENU_INDEX > 1) {
				out << endl;
			}

			if (index < MAX_MENU_INDEX) {
				out << "  b: Show harder levels\n";
			} else if (MAX_MENU_INDEX > 1) {
				out << endl;
			}

			out << "  c: Simple Level Builder\n"
				<< "  d: Access homebrew levels (if any)\n"
				<< "  e: See license information again\n"
				<< "  f: List of references\n"
				<< "  g: Change game options\n"
				<< "  h: Exit\n"
				<< "Please enter your choice now:  ";

			in >> input;
			in.ignore();
			out << endl;

		}

		if (input[0] >= 'a' && input[0] <= 'h') switch (input[0]) {
			case 'a':
				if (index > 0) {
					index--;
				} else {
					out << "You are already viewing the easiest levels.\n"
						<< "Press enter to continue.";
					pauseOutput();
				}
				break;

			case 'b':
				if (index < MAX_MENU_INDEX) {
					index++;
				} else {
					out << "You are already viewing the hardest levels.\n"
						<< "Press enter to continue.";
					pauseOutput();
				}
				break;

			case 'c': {

				cls();

				int s, d, v, b, c;

				out << "Please input integers for s, d, v, b, and c "
					 << "in that order: ";

				s = getInt();
				d = getInt();
				v = getInt();
				b = getInt();
				c = getInt();

				cls();
				help();

				triggers.push_back(Trigger("\nenigma", " is the answer to everything.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nenigma is also the answer to life and the universe.") );
				triggers.push_back(Trigger("\n42", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));

				level = Level(new Offsets(s, d, v, b, c), triggers);

				runLevel(level, SIMPLE);

				} break;

			case 'd':
				cls();
				homebrew_main();
				break;

			case 'e':
				cls();
				welcome();
				break;

			case 'f':
				cls();
				referenced();
				break;

			case 'g':
				cls();
				changeOptions();
				break;

			case 'h':
				return 0;
				break;

			default:
				//this case should never happen
				break;

		} else {

			if (type == oldType && subtype == oldSubtype) {
				//this is executed if the user returned to the menu

				type = oldType = atoi(input.c_str() );
				if (input.size() > digits(type)) {
					subtype = oldSubtype= input[digits(type)];
				} else {
					subtype = oldSubtype = '?';
				}

			} else { //the user did not return to the menu

				oldType = type;
				oldSubtype = subtype;

			}
			
			out << "type is " << type << ", subtype is " << subtype << endl; // DEBUG
			pauseOutput();

			switch (type) {
				case 1:
					
					cls();
					
					out << "Hello, and welcome to Enigma!\n"
						<< "There are two primary challenges to this game, namely:\n"
						<< " * to figure out how to make the word \"enigma\" appear in the output, and\n"
						<< " * to figure out the password hinted by the clue \"enigma\" produces.\n"
						<< "Since this is a practice level, the output is the same as your input.\n"
						<< "Therefore, please type \"enigma\" (on a new line) and press enter.\n\n";
					
					triggers.push_back(Trigger("\nenigma", " is what you desire.\n\nNow that \"enigma\" has appeared, you can beat this level by making the\npassword appear.  In some levels, this hint is helpful enough to figure\nout the password.  In other levels (such as this one), this hint is not\nenough.  For an additional hint, you need to make \"help\" appear in the\noutput.  Since this is a practice level, you can make this happen by typing\n\"help\" (on a new line), so please do so now.\n") );
					
					reply.push_back(" cannot be given until \"enigma\" appears!");
					reply.push_back("\nJust type \"thesolutiontotheriddle\", already!\n\nNow that you have the hint given by making \"help\" appear, you should now\nhave a good idea as to what the password is.  If for some reason you don't,\nthe password is \"thesolutiontotheriddle\".  If you make this appear (on a new\nline), you will beat the practice level.\n");
					reply.push_back("\nJust type \"thesolutiontotheriddle\", already!\n\nNow that you have the hint given by making \"help\" appear, you should now\nhave a good idea as to what the password is.  If for some reason you don't,\nthe password is \"thesolutiontotheriddle\".  If you make this appear (on a new\nline), you will beat the practice level.\n");
					
					b1.clear();
					b1.push_back(false);
					b1.push_back(true);
					
					b3.clear();
					b3.assign(3, false);
					
					triggers.push_back(Trigger("\nhelp", reply, b1, b3, b3) );
					
					reply.assign(2, "");
					reply.push_back("\nAccess granted.\n");
					b1.assign(2, false);
					b2.clear();
					b2.assign(2, false);
					b2.push_back(true);
					
					triggers.push_back(Trigger("\nthesolutiontotheriddle", reply, b1, b2,
						b3) );
					
					triggers.push_back(Trigger("\neasteregg", "", "\n(*insert fanfare here*)\n",
						bitset<3>(1ul) ));
					
					reply.clear();
					
					level = Level(new Offsets(), triggers);
					
					if (runLevel(level, ONE) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 2, 'a');
					}
					
					break;
					
				case 2: switch (subtype) {
				case 'a':

					cls();

					out << "This is the first level of Enigma that has \"real\" game difficulty.\n"
						<< "In this level (and all future levels, the game's output will *not* be\n"
						<< "the same as your input.  \"enigma\", \"help\", and the password must appear\n"
						<< "in the game's output (which is now different from your input) in order to\n"
						<< "have any effect.  In this level, the game outputs the character that comes\n"
						<< "after the inputted character alphabetically.  Experiment to see what this\n"
						<< "means, then input \"dmhflz\" on a new line to continue.\n\n";

					triggers.push_back(Trigger("\nenigma", " is not up.\n\nNotice that typing \"dmhflz\" produces \"enigma\" in the output.  Since the game\nchanges every inputted character to the one after it alphabetically, \"dmhflz\"\nwas chosen as an input because each character in \"dmhflz\" comes alphabetically\nbefore the corresponding character in \"enigma\".  At this point, you can either\nfigure out what the password is and make it appear, or you can type \"gdko\" to\nmake \"help\" appear for a second hint for the password.\n") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nWhat is the opposite of \"up\"?\n\nAs you can probably guess, the password is \"down\".  In order to make \"down\"\nappear, you need to type in the characters that come alphabetically before \"d\",\n\"o\", \"w\", and \"n\".  These characters are \"c\", \"n\", \"v\", and \"m\", which means\nthat typing \"cnvm\" will make \"down\" appear and beat the level.") );
					triggers.push_back(Trigger("\ndown", "", "\nAccess granted.\n", bitset<3>(2ul) ));

					level = Level(new Offsets(1), triggers);

					if (runLevel(level, TWO_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 2, 'b');
					}

					break;

				case 'b': //type == 2

					cls();

					out << "This level is the same difficulty as the previous level, but unlike\n"
						<< "the previous level, you will not be told how the letters are changing\n"
						<< "or how to make any of the keywords appear.  Remember, you will get your\n"
						<< "first password hint when \"enigma\" appears in the game output.\n\n"
						<< "If you find yourself unable to beat this level, you can escape this level\n"
						<< "(or any level, for that matter) and return to the main menu by typing\n";

					if (Options[ENGINE_VERSION] == "Delayed" && Options[CLEAR_IN_GAME] == "Enabled") {
						out << "tab and then enter.  You can also clear the screen by typing enter twice.\n\n";
					} else if (Options[ENGINE_VERSION] == "Delayed") { //OPTIONS[CLEAR_IN_GAME] == "Disabled"
						out << "tab and then enter.\n\n";
					} else if (Options[CLEAR_IN_GAME] == "Enabled") { //Options[ENGINE_VERSION] == "Immediate"]
						out << "backspace three times.  You can also clear the screen by typing tab three times.\n\n";
					} else { //Options[ENGINE_VERSION] == "Immediate" && Options[CLEAR_IN_GAME] == "Disabled"
						out << "backspace three times.\n\n";
					}

					triggers.push_back(Trigger("\nenigma", " is neither end.\n\nIf you know what the password is, make it appear to beat the level.  If not,\nmake \"help\" appear for an additional hint.\n") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nIf enigma is neither end, then it's obviously the ------.") );
					triggers.push_back(Trigger("\nmiddle", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));

					level = Level(new Offsets(-1), triggers);

					if (runLevel(level, TWO_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 3, 'a');
					}

					break;

				default: //type == 2

					out << "Please input \"2a\" or \"2b\".\n"
						<< "Press enter to continue.";

					pauseOutput();

					break;

					}

					break;


				case 3: switch (subtype) {
				case 'a':

					cls();

					out << "Not all levels will use the same encryption as the previous ones.\n"
						<< "The previous levels used a \"static offset\"; you will now face a\n"
						<< "\"buffer\".  In this level, the characters you type will *not* be changed,\n"
						<< "but each character will be delayed by two spaces.  The first two outputted\n"
						<< "characters are random.  For example, if you were to type \"greetings!\" as\n"
						<< "your first characters, the output would be two random characters followed by\n"
						<< "\"greeting\".  Note that the \"s!\" would not appear until you inputted your\n"
						<< "next two characters.\n\n"
						<< "Remember that \"enigma\" must appear at the beginning of a line to have any\n"
						<< "effect.  To make that happen, type \"en\" at the end of one line and \"igma\"\n"
						<< "followed any two characters on the next.\n\n";

					triggers.push_back(Trigger("\nenigma", " = (toes - limbs) / eyes\n\nNow that you have the hint for the password, you need to either make the\npassword appear OR make \"help\" appear for an additional hint to the\npassword.  Remember, you need to type the first two letters of what you want\nto appear on the previous line, and you need to type to extra characters on\nthe next line\n") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nHow many toes do you have?\nHow many limbs do you have?\nHow many eyes do you have?\nSubtract, divide, and conquer! (in that order)") );
					triggers.push_back(Trigger("\n3", "", "\nNice try, but no.\nTry \"three\" instead.") );
					triggers.push_back(Trigger("\nthree", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));


					level = Level(new Offsets(0, 0, 0, 2), triggers);

					if (runLevel(level, THREE_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 3, 'b');
					}

					break;

				case 'b': //type == 3

					cls();

					out << "This level also uses a buffer, but you will not be told how big this buffer\n"
						<< "is.  You will need to compare your input with the game's output in order to\n"
						<< "figure out how large the buffer is.  Once you do so, simply compensate for\n"
						<< "the buffer to make \"enigma\" and the password appear.\n\n";

					triggers.push_back(Trigger("\nenigma", "\nSmile! :)") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nAll you have to do is make \":)\" appear.\nBe glad there's no offset for this level...") );
					triggers.push_back(Trigger("\n:)", "",
						"\nAccess granted.\n",
						bitset<3>(2ul) ));

					level = Level(new Offsets(0, 0, 0, 5), triggers);

					if (runLevel(level, THREE_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 4, 'a');
					}

					break;

				default: //type == 3

					out << "Please input \"3a\" or \"3b\".\n"
						<< "Press enter to continue.";

					pauseOutput();

					break;

					}

					break;

				case 4: switch (subtype) {
				case 'a':

					cls();

					out << "This level has both a static offset and a buffer.  Inuptted characters are\n"
						<< "shifted two back alphabetically AND delayed by one character in the output.\n"
						<< "Make sure you account for both of these things when you try to make \"enigma\"\n"
						<< "appear!\n\n";

					triggers.push_back(Trigger("\nenigma",
						" looks and quacks like itself.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nIf it looks like a ---- and quacks like a ----, then it's a ----.") );
					triggers.push_back(Trigger("\nduck", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));

					level = Level(new Offsets(-2, 0, 0, 1), triggers);

					if (runLevel(level, FOUR_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 4, 'b');
					}

					break;

				case 'b': //type == 4

					cls();

					out << "Once again, this level is the same type as the previous level.  Once again,\n"
						<< "you will need to figure out how this level works yourself.  If you need a\n"
						<< "place to start, it is much easier to figure out what the buffer is than\n"
						<< "anything else in this game, so it is usually a good idea to figure out the\n"
						<< "size of the buffer first.  Because there is both a buffer and an offset,\n"
						<< "you will have to use creative means in order to find out what the buffer's\n"
						<< "size is.  Since enigma can process any character visible on a standard QWERTY\n"
						<< "keyboard, you may find it helpful to type a line of lower case letters with\n"
						<< "a single upper case letter, number, or symbol;  doing this is one way to find\n"
						<< "out the size of the buffer.\n\n";

					triggers.push_back(Trigger("\nenigma", " is where the grass is never less green.") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nThe grass is always greener on --- ----- ----.") );
					triggers.push_back(Trigger("\ntheotherside", "\nAccess granted.\n", bitset<3>(2ul) ));

					level = Level(new Offsets(3, 0, 0, 4), triggers);

					if (runLevel(level, FOUR_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 4, 'c');
					}

					break;

				case 'c': //type == 4

					cls();

					out << "Sometimes, the hints given out by making \"enigma\" appear are not\n"
						<< "riddles, but are rather cultural references.  Sometimes, you may\n"
						<< "already know the reference, in which case you can guess the password.\n"
						<< "There are times, though, when the use of an online search engine may be\n"
						<< "necessary to guess the password.  This level is one such level.  After\n"
						<< "you make \"enigma\" appear, try doing an online search with some of the\n"
						<< "words given to you in the hint.\n\n";

					triggers.push_back(Trigger("\nenigma", "\nThere's a speck...\nThere's a speck\n...There's a speck on the flea on the tail on the frog on the bump\non the log in the hole in the bottom of enigma!" ) );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nIt's from a Sesame Street song.\n(Yes, you will actually have to do an internet search...)") );

					triggers.push_back(Trigger("\nsea", "", "\nIt's not just \"sea\", it's enigma!") );

					triggers.push_back(Trigger("\nthesea", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));

					level = Level(new Offsets(-5, 0, 0, 4), triggers);

					if (runLevel(level, FOUR_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 5, 'a');
					}

					break;

				default: //type == 4

					out << "Please input \"4a\", \"4b\", or \"4c\".\n"
						<< "Press enter to continue.";

					pauseOutput();

					break;

					}

					break;

				case 5: switch (subtype) {
				case 'a': 
					
					cls();
					
					out << "You can consider this level to be the graduating exam for the tutorial.\n"
						<< "This level introduces another new concept called the dynamic offset.  You\n"
						<< "will not be told how this concept works; you need to figure this out\n"
						<< "yourself.  You can do so by studying the relationship between your inputted\n"
						<< "characters and the game's outputted characters.  Once you know this\n"
						<< "relationship, compensate for the change in your input to make \"enigma\"\n"
						<< "appear.\n\n"
						<< "Note that in future levels, you may not be told whether the level is based\n"
						<< "on previous levels or if the level introduces a new concept.  You will need\n"
						<< "to consider both cases if you want to conquer enigma\n\n";
					
					triggers.push_back(Trigger("\nenigma", " is equal to itself.",
						"\nAccess granted.\n\nCongratulations!  You have completed the tutorial for enigma!\nGood luck with the harder levels!  (You'll need it...)", bitset<3>(6ul) ));
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nLook up the reflexive property.\nSometimes, one can expect different results\nfrom doing the same thing...") );
					
					level = Level(new Offsets(0, -1), triggers);
					
					if (runLevel(level, FIVE_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 5, 'b');
					}
					
					break;
					
				case 'b': //type == 5
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", " is\nenigma is\n enigma is a perfect place!") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nFarquaad's a tad delusional, if his singing puppets are any indication...") );
					triggers.push_back(Trigger("\nduloc", "", "\nAccess granted.\n",
						bitset<3>(2ul) )); 
					
					level = Level(new Offsets(5, -2), triggers);
					
					if (runLevel(level, FIVE_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 5, 'c');
					}
					
					break;
					
				case 'c': //type == 5
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", " is no place.") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nNo place is a enigma.\n(it's a Greek pun, if you didn't know that before)") );
					triggers.push_back(Trigger("\nutopia", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Offsets(-2, -3, 0, 4), triggers);
					
					if (runLevel(level, FIVE_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 6, 'a');
					}
					
					break;
					
				default: //type == 5
					
					out << "Please input \"5a\", \"5b\", or \"5c\".\n"
						<< "Press enter to continue.";

					pauseOutput();

					break;
					
					}
					
					break;
					
				case 6: switch (subtype) {
				case 'a':
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", "\nSpeak, friend, and enter.") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nHere's a hint: The answer is in Tolkien's Elvish") );
					triggers.push_back(Trigger("\nfriend", "",
						"\nRight idea, wrong language...\n(make \"help\" appear if you don't understand)") );
					triggers.push_back(Trigger("\nmellon", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Shuffle(3,  0, 2, 1), triggers);
					
					if (runLevel(level, SIX_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 6, 'b');
					}
					
					break;
					
				case 'b': //type == 6
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", "\n5603248534") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"You really should look at your keyboard more often.\n(or borrow somebody else's QWERTY keyboard)") );
					triggers.push_back(Trigger("\ntypewriter", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Shuffle(5,  4, 3, 2, 1, 0), triggers);
					
					if (runLevel(level, SIX_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 6, 'c');
					}
					
					break;
					
				case 'c': //type == 6
				
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", " for the laughter, enigma for the tears") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nDream until your dreams come true!") );
					triggers.push_back(Trigger("\nsing", "", "\nAccess granted\n",
						bitset<3>(2ul) ));
					
					level = Level(new Shuffle(9,  4, 3, 7, 1, 8, 0, 2, 6, 5), triggers);
					
					if (runLevel(level, SIX_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 7, 'a');
					}
					
					break;
					
				default: //type == 6
					
					out << "Please input \"6a\", \"6b\", or \"6c\".\n"
						<< "Press enter to continue.";
					
					pauseOutput();
					
					break;
					
					}
					
					break;
					
				case 7: switch (subtype) {
				case 'a':
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", " is a capital letter.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nThe password is \"acapitalletter\".  Have fun!") );
					triggers.push_back(Trigger("\nacapitalletter", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					triggers.push_back(Trigger("\nA", "", "\nVery funny...\n", bitset<3>(1ul) ));
					
					level = Level(new Offsets(0, 0, 1), triggers);
					
					if (runLevel(level, SEVEN_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 7, 'b');
					}
					
					break;
					
				case 'b': //type == 7
				
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", " could be used as a footstool\nor a table to play Scrabble on") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nWe could use him as a footstool\nor a table to play Scrabble on,\n then tie him up,\n then beat him up,\nthen throw him out of Babylon!") );
					triggers.push_back(Trigger("\ndaniel", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Offsets(3, 0, -2), triggers);
					
					if (runLevel(level, SEVEN_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 7, 'c');
					}
					
					break;
					
				case 'c': //type == 7
				
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", "\nqw_ ws_ cf_ ng_ ds_ ,l_ mk_ jk_ 3w_ bg_ po_ mk_ vb_") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nYou really should look at your keyboard more often.\n(or borrow somebody else's QWERTY keyboard)") );
					triggers.push_back(Trigger("\nextrapolation", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Offsets(-4, 0, 4, 3), triggers);
					
					if (runLevel(level, SEVEN_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 8, 'a');
					}
					
					break;
					
				default:
					
					out << "Please input \"7a\", \"7b\", or \"7c\".\n"
						<< "Press enter to continue.";
					
					pauseOutput();
					
					break;
					
					}
					
					break;
					
				case 8: switch (subtype) {
				case 'a':

					cls();
					help();

					triggers.push_back(Trigger("\nenigma",
						" is occasionally literal.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nThe password is \"occasionallyliteral\".\nAs you can see, enigma is occasionally literal.") );
					triggers.push_back(Trigger("\noccasionallyliteral", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));

					level = Level(new Switch(2,
						new Offsets(3), new Offsets(-4, 0, 0, 3) ),
						triggers);

					if (runLevel(level, EIGHT_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 8, 'b');
					}

					break;
					
				case 'b': //type == 8
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma",
						" is a tiny country within a country.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nIt also happens to be the smallest country in the world...") );
					triggers.push_back(Trigger("\nvaticancity", "", "\nAccess Granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Switch(2,
						new Offsets(0, 3, 0, 4), new Offsets(0, 0, -2, 6) ),
						triggers);
					
					if (runLevel(level, EIGHT_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 8, 'c');
					}
					
					break;
					
				case 'c': //type == 8
				
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", "\nThe developer got lazy.\nThe password is \"word\".") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\n...Seriously?  You seriously need help?!?") );
					triggers.push_back(Trigger("\nword", "", "\n...meh, you won...\n",
						bitset<3>(2ul) ));
					
					tempLayers[0] = new Shuffle(6,  3, 5, 1, 4, 0, 2);
					
					level = Level(new Switch(4, 
						new Offsets(0, 1, 0, 3),
						tempLayers[0],
						new Offsets(3, 0, -1, 2),
						tempLayers[0]) , triggers);
					
					if (runLevel(level, EIGHT_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 5, 'c');
					}
					
					break;
					
				default: //type == 8
					
					out << "Please input \"8a\", \"8b\", or \"8c\".\n"
						<< "Press enter to continue.";
					
					pauseOutput();
					
					break;
					
					}
					
					break;
					
				case 9: switch (subtype) {
				case 'a':
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma",
						" is an annulus of information.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nTry pressing the \"eject\" button on your computer.\nYou may want to consider fetching a dictionary if you still don't get it...") );
					triggers.push_back(Trigger("\ncd", "", "\nCheck your capitalization...") );
					triggers.push_back(Trigger("\nCD", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Stack(2,
						new Offsets(6, 0, 0, 4), new Offsets(6, 0, 0, 0, 6) ),
						triggers);
					
					if (runLevel(level, NINE_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 9, 'b');
					}
					
					break;
					
				case 'b': //type == 9
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma",
						" was what hurts the most.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nYou need to listen to Rascal Flatts (or use an online search engine).") );
					triggers.push_back(Trigger("\nwasbeingsoclose", "",
						"\nYou're close enough...\nAccess granted.\n", bitset<3>(2ul) ));
					triggers.push_back(Trigger("\nbeingsoclose", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					layers.push_back(new Offsets(6, -1, 0, 4) );
					layers.push_back(new Offsets(6, 1, 0, 0, 6) );
					
					level = Level(new Stack(2,
						new Offsets(6, -1, 0, 4), new Offsets(6, 1, 0, 0, 6) ),
						triggers);
					
					if (runLevel(level, NINE_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 9, 'c');
					}
					
					break;
					
				case 'c': //type == 9
				
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", " is needed by dancers.") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nThe painter needs a ladder and brush.\nThe artist needs an easel.") );
					triggers.push_back(Trigger("\nafiddlerstwo", "", "\nSorry, not quite.  Keep looking!") );
					triggers.push_back(Trigger("\nafiddlerstune", "", "\nAccess granted\n",
						bitset<3>(2ul) ));
					
					level = Level(new Switch(3,
						new Offsets(0, -1, 0, 0, 6),
						new Shuffle(8,   4, 7, 0, 2, 3, 5, 1, 6),
						new Offsets(0, 0, 1, 2) ),
						triggers);
					
					if (runLevel(level, NINE_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 10, 'a');
					}
					
					break;
					
				default:
					
					out << "Please input \"9a\", \"9b\", or \"9c\".\n"
						<< "Press enter to continue.";
					
					pauseOutput();
					
					break;
					
					}
					
					break;
					
				case 10: switch (subtype) {
				case 'a':
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma",
						" is a mode of transportation defined by three points.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nThree points define a -----.\nIt's time to go back to geometry class...") );
					triggers.push_back(Trigger("\nplane", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					level = Level(new Offsets(-7, -2, 1), triggers);
					
					if (runLevel(level, TEN_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 10, 'b');
					}
					
					break;
					
				case 'b': //type == 10
				
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", "\nThe developer got lazy.\nThe password is \"word\".") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\n...Seriously?  You seriously need help?!?") );
					triggers.push_back(Trigger("\nword", "", "\n...meh, you won...\n",
						bitset<3>(2ul) ));
					
					level = Level(new Offsets(-3, 2, 0, 4, 13), triggers);
					
					if (runLevel(level, TEN_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 10, 'c');
					}
					
					break;
					
				case 'c': //type == 10
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma",
						" stands alone 'twixt water and stone.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nYou need to read a few more Redwall books!\n(Alternatively, you could creatively use an internet search engine...)\n  \"'Twixt water and stone I stand alone\n   Sounding burnt, but alive I survive!\"") );
					triggers.push_back(Trigger("\nash", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					out << "You should know what to do by now...\n\n";
					
					level = Level(new Offsets(14, -1, -2, 3, 6), triggers);
					
					if (runLevel(level, TEN_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 10, 'd');
					}
					
					break;
					
				case 'd': //type == 10
				
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", "\nThe developer got lazy.\nThe password is \"word\".") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\n...Seriously?  You seriously need help?!?") );
					triggers.push_back(Trigger("\nword", "", "\n...meh, you won...\n",
						bitset<3>(2ul) ));
					
					level = Level(new Offsets(5, -1, 4, 8, 20), triggers);
					
					if (runLevel(level, TEN_D) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 10, 'e');
					}
					
					break;
					
				case 'e': //type == 10
					
					cls();
					help();

					triggers.push_back(Trigger("\nenigma",
						"\n128-10-93-85-10-128-98-112-6-6-25-126-39-1-68-78") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nIt appears that you've never read Digital Fortress...\n(You could also use an internet search engine if you'd like.)") );
					triggers.push_back(Trigger("\nwearewatchingyou", "",
						"\nAccess granted.\n", bitset<3>(2ul) ));

					out << "You should know what to do by now...\n\n";

					level = Level(new Offsets(107, -84, 34, 37, 17), triggers);

					if (runLevel(level, TEN_E) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 11, 'a');
					}

					break;
					
				default:
					
					out << "Please input \"10a\", \"10b\", \"10c\", \"10d\", or \"10e\".\n"
						<< "Press enter to continue.";
					
					pauseOutput();
					
					break;
					
					}
					
					break;
					
				case 11: switch (subtype) {
				case 'a':
					
					cls();
					help();
					
					replies.clear();
					tripsFlag.clear(); beatsLevel.clear(); easterEgg.clear();
					
					for (int i = 0; i < 3; i++) {
						replies.push_back(" is broken.  Please try again later.");
					}
					for (int i = 3; i < 10; i++) {
						replies.push_back(" is still broken.  Are you sure you fixed it?");
					}
					replies.push_back(" is where your voice is heard without words.\n");
					
					tripsFlag.assign(12, false);
					tripsFlag[0] = true;
					tripsFlag[3] = true;
					tripsFlag[10] = true;
					
					beatsLevel.assign(1, false);
					easterEgg.assign(1, false);
					
					//layers should be given some stuff here...
					
					triggers.push_back(Trigger("\nenigma", replies, tripsFlag, beatsLevel, easterEgg, layers) );
					
					replies.assign(1, " cannot be given until \"enigma\" appears!");
					for (int i = 1; i < 3; i++) {
						replies.push_back("\nWhat are you looking for, anyway?");
					}
					replies.push_back("\nIt seems enigma should be fixed now.\nWhy don't you make \"enigma\" appear again?");
					replies.push_back("\nIf at first you don't succeed, repair enigma again.");
					for (int i = 5; i < 9; i++) {
						replies.push_back("\nBrute force fixes everything (even the password utility).");
					}
					replies.push_back("\nYou fixed the password utility...  but did you ever fix enigma?");
					replies.push_back("\nenigma really has been fixed this time...  seriously!");
					replies.push_back("\nClawing up my eyes,\nI'm feeling your arms around me\nOn enigma.\nIt's time to go,\nI'm hearing your voice without words\nOn enigma.\n(If you don't get it, use a search engine.)");
					
					tripsFlag.assign(7, false);
					tripsFlag[1] = true;
					tripsFlag[5] = true;
					
					//layers should be given some stuff here...
					
					triggers.push_back(Trigger("\nhelp", replies, tripsFlag, beatsLevel, easterEgg, layers) );
					
					replies.assign(2, "");
					replies.push_back("\nYes, but what *is* the solution to the riddle?");
					replies.push_back("");
					tripsFlag.assign(1, false);
					
					//layers should be given some stuff here...
					
					triggers.push_back(Trigger("\nthesolutiontotheriddle", replies, tripsFlag, beatsLevel, easterEgg, layers) );
					
					replies.assign(2, "");
					for (int i = 2; i < 4; i++) {
						replies.push_back("\nenigma has been fixed.");
					}
					for (int i = 4; i < 6; i++) {
						replies.push_back(" is broken.  Please try again later.");
					}
					replies.push_back(" is still very broken.");
					replies.push_back(" is still quite broken.");
					replies.push_back("\nAfter a less-than-gentle love tap, the password utility\nhas been returned to full functionality.");
					replies.push_back("\nenigma has been fixed.\nThank you for using the password utility.\nHave a nice day!");
					replies.push_back("");
					
					tripsFlag.assign(11, false);
					tripsFlag[2] = true;
					tripsFlag[4] = true;
					for (int i = 6; i < 10; i++) {
						tripsFlag[i] = true;
					}
					
					//layers should be given some stuff here...
					
					triggers.push_back(Trigger("\npassword", replies, tripsFlag, beatsLevel, easterEgg, layers) );
					
					replies.assign(12, "");
					replies[11] = "\nYou're close enough...\nAccess granted.\n";
					
					tripsFlag.assign(1, false);
					
					beatsLevel.assign(12, false);
					beatsLevel[11] = true;
					
					layers = vector<Layer*>();
					
					triggers.push_back(Trigger("\nontheotherside", replies, tripsFlag, beatsLevel, easterEgg, layers) );
					
					replies[11] = "\nAccess granted.\n";
					
					triggers.push_back(Trigger("\ntheotherside", replies, tripsFlag, beatsLevel, easterEgg, layers) );
					
					out << "You *really* should know what to do by now...\n\n";
					
					level = Level(new Stack(2,
						new Offsets(12, 3, 6, 5, 7), new Offsets(51, -2, 3, 4, 5) ),
						triggers);
					
					if (runLevel(level, ELEVEN_A) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 11, 'b');
					}
					
					break;
					
				case 'b': //type == 11
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma",
						" speaks its only word nevermore.") );
					triggers.push_back(Trigger("\nhelp",
						" cannot be given until \"enigma\" appears!",
						"\nWhile I nodded, nearly napping, suddenly there came a tapping,\nAs of some one gently rapping, rapping at my chamber door.\n\"'Tis some visitor,\" I muttered, \"tapping at my chamber door.\nEnigma's this, and nothing more.\"") );
					triggers.push_back(Trigger("\nraven", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					out << "You *really* should know what to do by now...\n\n";
					
					level = Level(new Stack(3,
						new Offsets(-32, 21, 15, 12, 5), new Offsets(12, -2, 15, 5, 17),
						new Offsets(2, 30, -30, 8, 6) ),
						triggers);
					
					if (runLevel(level, ELEVEN_B) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 11, 'c');
					}
					
					break;
					
				case 'c': //type == 11
					
					cls();
					help();
					
					triggers.push_back(Trigger("\nenigma", "\nThe developer got lazy.\nThe password is \"word\".") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\n...Seriously?  You seriously need help?!?") );
					triggers.push_back(Trigger("\nword", "", "\n...meh, you won...\n",
						bitset<3>(2ul) ));
					
					level = Level(new Stack(3,
						new Shuffle(6,  5, 1, 2, 4, 0, 3), new Offsets(3, 5, -7, 4, 4),
						new Shuffle(5,  3, 1, 0, 4, 2) ),
						triggers);
					
					if (runLevel(level, ELEVEN_C) % 2 == 1) { // is either 1 or 3 if level was won
						nextLevel(type, subtype, 12, 'a');
					}
					
					break;
					
				default:
					
					out << "Please input \"11a\", \"11b\", or \"11c\".\n"
						<< "Press enter to continue.";
					
					pauseOutput();
					
					break;
					
					}
					
					break;
					
				case 12:
					
					cls();
					
					triggers.push_back(Trigger("\nenigma", ", enigma,\nYou have to know your enigma!") );
					triggers.push_back(Trigger("\nhelp", " cannot be given until \"enigma\" appears!",
						"\nYou have to remember\nWhich one is who\nAnd remember his birthday\nAnd the size of his shoe!\n(Yes, this is hard.  Have fun!)") );
					triggers.push_back(Trigger("\nhistory", "", "\nAccess granted.\n",
						bitset<3>(2ul) ));
					
					out << "Happy!\n"; // DEBUG
					
					tempLayers[0] =
					new Switch(3,
						new Switch(2,
							new Offsets(1),
							new Offsets(26, 0, 0, 0, 6) ),
						new Switch(1,
							new Offsets(-2) ),
						new Switch(2,
							new Offsets(-4),
							new Offsets(8) ) );
							
					(*tempLayers[0])[0](2) = new Stack(2, &( (*tempLayers[0])[1] ), &( (*tempLayers[0])[2] ) );
					(*tempLayers[0])[1](1) = new Stack(2, &( (*tempLayers[0])[2] ), &( (*tempLayers[0])[0] ) );
					(*tempLayers[0])[2](2) = &( (*tempLayers[0])[2][0] );
					(*tempLayers[0])[2](3) = new Stack(2, &( (*tempLayers[0])[0] ), &( (*tempLayers[0])[1] ) );
					
					level = Level(tempLayers[0], triggers);
					
					if (runLevel(level, TWELVE) % 2 == 1) { // is either 1 or 3 if level is won
						nextLevel(type, subtype, 12, 'b');
					}
					
					break;
					
				#ifdef FALSE // I'm lazy.
				case 13:
				
					break;
				
				case 14:
					
					break;
					
				case 15:
					
					break;
				#endif // FALSE; Again, I'm lazy.
				
				default:
					
					out << "Please enter a valid input (i.e., \"1\", \"2b\", \"h\", etc.)\n"
						<< "Press enter to continue:";
					
					pauseOutput();
					
					break;
					
			}
		
		}
	
	}
	
}

int runLevel(Level &level, int index) {
	
	int returned;
	
	returned = ( (Options[ENGINE_VERSION] == "Delayed")?level.engine():level.engine2() );
	
	if (returned % 2 == 1) { //returned == 1 || returned == 3
		beaten[index] = true;
	}
	
	if (returned == 3) {
		out << "\nYou got the easter egg!";
	}
	
	return returned;
	
}

void welcome() {
	
	out << "Enigma Cipher  Copyright (C) 2009  Ethan Warth (a.k.a. redyoshi49q)\n\n"
		 << "Enigma Cipher is free software: you can redistribute it and/or modify\n"
		 << "it under the terms of the GNU General Public License as published by\n"
		 << "the Free Software Foundation, either version 3 of the License, or\n"
		 << "(at your option) any later version.\n\n"
		 << "Enigma Cipher is distributed in the hope that it will be useful,\n"
		 << "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		 << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
		 << "GNU General Public License for more details.\n\n"
		 << "You should have received a copy of the GNU General Public License\n"
		 << "along with Enigma Cipher as the file \"copying.txt\".  If not, see\n"
		 << "<http://www.gnu.org/licenses/>.\n\nPress enter to continue.";

	pauseOutput();
	cls();
	
	out << "Enigma Cipher  Copyright (C) 2009  Ethan Warth (a.k.a. redyoshi49q)\n\n"
		 << "It is believed that references to copyrighted materials in the riddles\n"
		 << "incorporated in this program are a small proportion of their respective\n"
		 << "works, and do not inhibit the copyright holders' abilitiy to market their\n"
		 << "works.  It is for these reasons that the reference to copyrighted materials\n"
		 << "in Enigma Cipher is considered fair use under United States law.  If you\n"
		 << "as a copyright holder of a referenced material believe that the use of\n"
		 << "your material violates copyright, please email me at <redyoshi49q AT gmail\n"
		 << "DOT com> so that the material in Enigma Cipher can be made compliant with\n"
		 << "your copyright(s).\n\nPress enter to continue.";
	
	pauseOutput();
	cls();
	
}

void help() {

	out << "Welcome to Enigma!\n"
		<< "Type a line of text, then press enter.\n"
		<< "If \"enigma\" appears in the generated text on its own line,\n"
		<< "you will get a password hint.\n"
		<< "If you need more help,\n"
		<< "get \"help\" to appear in the generated text on its own line.\n"
		<< "To beat the level, get the password to appear!\n";

	if (Options[ENGINE_VERSION] == "Delayed" && Options[CLEAR_IN_GAME] == "Enabled") {
		out << "Press enter twice consecutively to clear the screen, or\n"
			<< "press tab and then enter to exit the level.\n\n";
	} else if (Options[ENGINE_VERSION] == "Delayed") { //OPTIONS[CLEAR_IN_GAME] == "Disabled"
		out << "Press tab and then enter to exit the level.\n\n";
	} else if (Options[CLEAR_IN_GAME] == "Enabled") { //Options[ENGINE_VERSION] == "Immediate"]
		out << "Press TAB three times to clear the screen or press\n\"Backspace\" three times to return to the menu.\n\n";
	} else { //Options[ENGINE_VERSION] == "Immediate" && Options[CLEAR_IN_GAME] == "Disabled"
		out << "Press \"Backspace\" three times to return to the menu.\n\n";
	}
			//this is merely so that alpha/beta testers will have some idea
				//as to what they're supposed to do...

}

void referenced() {

	vector<string> unsolved;
	out << "Solved riddles are paired with their referenced material (if any).\n"
		 << "Authors of referenced material in unsolved levels are shown at the\n"
		 << "end of the list in a randomized order.\n\n";

	if (beaten[ONE] == true) {
		out << "Level  1 :  This level does not reference any material.\n";
	}

	if (beaten[TWO_A] == true) {
		out << "Level  2a:  This level does not reference any material.\n";
	}

	if (beaten[TWO_B] == true) {
		out << "Level  2b:  This level does not reference any material.\n";
	}

	if (beaten[THREE_A] == true) {
		out << "Level  3a:  This level does not reference any material.\n";
	}

	if (beaten[THREE_B] == true) {
		out << "Level  3b:  This level does not reference any material.\n";
	}

	if (beaten[FOUR_A] == true) {
		out << "Level  4a:  This level references the \"duck test\".\n";
	}

	if (beaten[FOUR_B] == true) {
		out << "Level  4b:  This level references the phrase \"The grass is always greener\n"
			<< "   on the other side.\n";
	}

	if (beaten[FOUR_C] == true) {
		out << "Level  4c:  This level references the song \"Hole in the Bottom of the Sea\"\n"
			<< "   from Sesame Street.";
	} else {
		unsolved.push_back("Sesame Street\n");
	}

	if (beaten[FIVE_A] == true) {
		out << "Level  5a:  This level references the reflexive property from algebra.\n";
	}
	
	if (beaten[FIVE_B] == true) {
		out << "Level  5b:  This level references a song from the movie Shrek.\n";
	} else {
		unsolved.push_back("Dreamworks\n");
	}
	
	if (beaten[FIVE_C] == true) {
		out << "Level  5c:  This level references a pun for the word \"utopia\";\n"
			<< "   the word could either mean \"no place\" or \"good place\".\n";
	}
	
	if (beaten[SIX_A] == true) {
		out << "Level  6a:  This level references a scene from \"The Lord of the Rings\"\n";
	} else {
		unsolved.push_back("J. R. R. Tolkien\n");
	}
	
	if (beaten[SIX_B] == true) {
		out << "Level  6b:  This level does not reference any material.\n";
	}
	
	if (beaten[SIX_C] == true) {
		out << "Level  6c:  This level references the song \"Dream On\" by Aerosmith.\n";
	} else {
		unsolved.push_back("Aerosmith\n");
	}
	
	if (beaten[SEVEN_A] == true) {
		out << "Level  7a:  This level does not reference any material.\n";
	}
	
	if (beaten[SEVEN_B] == true) {
		out << "Level  7b:  This level references a song from Veggie Tales.\n";
	} else {
		unsolved.push_back("Phil Vischer\n");
		unsolved.push_back("Mike Nawrocki\n");
	}
	
	if (beaten[SEVEN_C] == true) {
		out << "Level  7c:  This level does not reference any material\n";
	}
	
	if (beaten[EIGHT_A] == true) {
		out << "Level  8a:  This level does not reference any material.\n";
	}

	if (beaten[EIGHT_B] == true) {
		out << "Level  8b:  This level references Vatican City (as you already know).\n";
	}
	
	if (beaten[EIGHT_C] == true) {
		out << "Level  8c:  ...\n";
	}

	if (beaten[NINE_A] == true) {
		out << "Level  9a:  This level does not reference any material.\n";
	}
	
	if (beaten[NINE_B] == true) {
		out << "Level  9b:  This level references the chorus of the song \"What Hurts\n"
			<< "   the Most\" by Rascal Flatts.\n";
	} else {
		unsolved.push_back("Rascall Flatts\n");
	}
	
	if (beaten[NINE_C] == true) {
		out << "Level  9c:  This level references several of the many variants of \"Pop Goes the Weasel\","
			<< "   one of which is featured on Barney.\n";
	} else {
		unsolved.push_back("Barney");
	}

	if (beaten[TEN_A] == true) {
		out << "Level 10a:  This level references the definition of \"plane\" in geometry.\n";
	}
	
	if (beaten[TEN_B] == true) {
		out << "Level 10b:  ...\n";
	}
	
	if (beaten[TEN_C] == true) {
		out << "Level 10c:  This level references a riddle in the book \"Taggerung\" by\n"
			 << "   Brian Jacques.  The solution to the referenced part of the riddle was\n"
			 << "   the ash tree in the abbey.\n";
	} else {
		unsolved.push_back("Brian Jacques\n");
	}
	
	if (beaten[TEN_D] == true) {
		out << "Level 10d:  ...\n";
	}
	
	if (beaten[TEN_E] == true) {
		out << "Level 10e  This level references the simple code that appears at the end\n"
			 << "   of the the book \"Digital Fortress\" by Dan Brown.\n";
	} else {
		unsolved.push_back("Dan Brown\n");
	}
	
	if (beaten[ELEVEN_A] == true) {
		out << "Level 11a:  This level references the chorus of the song \"Unspoken\"\n"
			<< "   by Lacuna Coil.\n";
	} else {
		unsolved.push_back("Lacuna Coil\n");
	}
	
	if (beaten[ELEVEN_B] == true) {
		out << "Level 11b:  This level references the beginning stanza of the poem\n"
			<< "   \"The Raven\" by Edgar Allen Poe.\n";
	} else {
		unsolved.push_back("Edgar Allen Poe\n");
	}
	
	if (beaten[ELEVEN_C] == true) {
		out << "Level 11c:  ...\n";
	}
	
	if (beaten[TWELVE] == true) {
		out << "Level 12 :  This level references the song \"The Things You Have to Know\"\n"
			<< "   from the movie \"The Hoober Bloob Highway\" by Dr. Seuss.\n";
	} else {
		unsolved.push_back("Dr. Seuss\n");
	}

	if (beaten[THIRTEEN] == true) {
	}

	if (beaten[FOURTEEN] == true) {
	}

	if (beaten[FIFTEEN] == true) {
	}

	if (beaten[SIMPLE] == true) {
		out << "Level Builder:  This level references The Answer to Life, the Universe,\n"
			 << "   and Everything, which is a joke from \"The Hitchhiker's Guide by\n"
			 << "   Douglas Adams.\n";
	} else {
		unsolved.push_back("Douglas Adams\n");
	}

	if (unsolved.size() != 0) {
		out << "\nUnsolved level credits:\n";
		while (unsolved.size() != 0) {
			int i = rand() % unsolved.size();
			out << unsolved[i];
			unsolved.erase(unsolved.begin()+i);
		}
	}

	out << "\nPress enter to continue.";

	pauseOutput();
	cls();

}

void nextLevel(int &type, char &subtype, int nextType, char nextSubtype) {

	out << "Press enter to continue or press \"n\" and then enter to return to the menu.";

	string input;

	getline(in, input);

	if (input != "n") {
		type = nextType;
		subtype = nextSubtype;
	}

}

