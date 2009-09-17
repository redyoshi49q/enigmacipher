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
 *   global.cpp
 *   global.hpp
 *   homebrew.cpp
 *   homebrew.hpp
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
 */

#include "enigma.hpp"

extern bool engineVersion;

int main() {
	
	int input = -1;
	Level level;
	
	vector<Trigger> triggers;
	vector<Layer*> layers;
	
	vector<bool> beaten;
	beaten.assign(16, false);
	
	cls();
	welcome();
	
	while (true) { //case 20 returns from the main function

		cls();
		
		triggers.clear();
		layers.clear();
	
    	out << "Welcome to Enigma!\n"
			 << "Please choose one of the following options:\n"
			 << "  1: Test Level (no encryption)\n"
			 << "  2: Second Level (easiest encryption possible)\n"
			 << "  3: Fifth Level\n"
			 << "  4: Sixth Level (beginner encryption)\n"
			 << "  5: Dynamic Offset\n"
			 << "  6: Variable Offset\n"
			 << "  7: Easy Switch Level\n"
			 << "  8: Intermediate Level\n"
			 << "  9: Easy Stacked Level\n"
			 << " 10: Hard Switch Level\n"
			 << " 11: Advanced Level (reserved for the persistent)\n"
			 << " 12: Hard Stacked Level (reserved for the highly persistent)\n"
			 << " 13: Expert Level (reserved for the insane)\n"
			 << " 14: Evil Level (reserved for the very insane)\n"
			 << " 15: Furious Level (reserved for the particularly insane)\n"
			 << " 16: Simple Level Builder\n"
			 << " 17: Access homebrew levels (if any)\n"
			 << " 18: See license information again\n"
			 << " 19: List of references\n"
			 << " 20: Exit\n"
			 << " 21: Toggle alternate engine version (current version is " //Jacob's Code
			 << (engineVersion?"standard)\n":"alternate)\n")				//Jacob's Code
			 << "Please enter your choice now:  ";
      
		input = getInt();
		out << endl;
		cls();
		
		switch (input) {
			
			case 1: {
				
				triggers.push_back(Trigger("\nenigma", " is what you desire.") );		//Modified by Jacob

				vector<string> reply;
				reply.push_back(" cannot be given until \"enigma\" appears!");			//Modified by Jacob
				reply.push_back("\nJust type \"thesolutiontotheriddle\", already!");	//Modified by Jacob
				reply.push_back("\nJust type \"thesolutiontotheriddle\", already!");	//Modified by Jacob
				
				vector<bool> b1;
				b1.push_back(false);
				b1.push_back(true);
				vector<bool> b3;
				b3.assign(3, false);
				
				triggers.push_back(Trigger("\nhelp", reply, b1, b3, b3) );

				reply.assign(2, "");
				reply.push_back("\nAccess granted.\n");
				b1.assign(2, false);
				vector<bool> b2;
				b2.assign(2, false);
				b2.push_back(true);
				
				triggers.push_back(Trigger("\nthesolutiontotheriddle", reply, b1, b2,
					b3) );
				
				triggers.push_back(Trigger("\neasteregg", "", "\n(*insert fanfare here*)\n",
					bitset<3>(1ul) ));
				
				help();
				
				level = Level(new Offsets(), triggers);
				
				runLevel(level, beaten, 0);
				
				}
				
				break;
			
			case 2: {
				
				triggers.push_back(Trigger("\nenigma", " is not up.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nWhat is the opposite of \"up\"?") );
				triggers.push_back(Trigger("\ndown", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				help();
				
				level = Level(new Offsets(1), triggers);
				
				runLevel(level, beaten, 1);
				
				}
				
				break;
				
			case 3: {
				
				triggers.push_back(Trigger("\nenigma", " is neither end.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nIf enigma is neither end, then it's obviously the ------.") );
				triggers.push_back(Trigger("\nmiddle", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				help();
				
				level = Level(new Offsets(0, 0, 0, 2), triggers);
				
				runLevel(level, beaten, 2);
				
				}
				
				break;

			case 4: {
				
				triggers.push_back(Trigger("\nenigma",
					" looks and quacks like itself.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nIf it looks like a ---- and quacks like a ----, then it's a ----.") );
				triggers.push_back(Trigger("\nduck", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				help();
				
				level = Level(new Offsets(-2, 0, 0, 1), triggers);
				
				runLevel(level, beaten, 3);
				
				}
				
				break;
				
			case 5: {
				
				triggers.push_back(Trigger("\nenigma", " is equal to itself.",
					"\nAccess granted.\n", bitset<3>(6ul) ));
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nLook up the reflexive property.\nSometimes, one can expect different results\nfrom doing the same thing...") );
				
				help();
				
				level = Level(new Offsets(0, -1), triggers);
				
				runLevel(level, beaten, 4);
				
				}
				
				break;
			
			case 6: {
				
				triggers.push_back(Trigger("\nenigma", " is a capital letter.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nThe password is \"acapitalletter\".  Have fun!") );
				triggers.push_back(Trigger("\nacapitalletter", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				triggers.push_back(Trigger("\nA", "", "\nVery funny...\n", bitset<3>(1ul) ));
				
				help();
				
				level = Level(new Offsets(0, 0, 1), triggers);
				
				runLevel(level, beaten, 5);
				
				}
				
				break;
				
			case 7: {
				
				triggers.push_back(Trigger("\nenigma",
					" is occasionally literal.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nThe password is \"occasionallyliteral\".\nAs you can see, enigma is occasionally literal.") );
				triggers.push_back(Trigger("\noccasionallyliteral", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
					
				help();
				
				level = Level(new Switch(
					new Offsets(3), new Offsets(-4, 0, 0, 3) ),
					triggers);
				
				runLevel(level, beaten, 6);
				
				}
				
				break;
				
			case 8: {
				
				triggers.push_back(Trigger("\nenigma",
					" is a mode of transportation defined by three points.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nThree points define a -----.\nIt's time to go back to geometry class...") );
				triggers.push_back(Trigger("\nplane", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				help();
				
				level = Level(new Offsets(-7, -2, 1), triggers);
				
				runLevel(level, beaten, 7);
				
				}
				
				break;
				
			case 9: {
				
				triggers.push_back(Trigger("\nenigma",
					" is an annulus of information.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nYou may want to consider fetching a dictionary...") );
				triggers.push_back(Trigger("\ncd", "", "\nCheck your capitalization...") );
				triggers.push_back(Trigger("\nCD", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				layers.push_back(new Offsets(6, 0, 0, 4) );
				layers.push_back(new Offsets(6, 0, 0, 0, 6) );
				
				help();
				
				level = Level(layers, triggers);
				
				runLevel(level, beaten, 8);
				
				}
				
				break;
				
			case 10: {
				
				triggers.push_back(Trigger("\nenigma",
					" is a tiny country within a country.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nIt also happens to be the smallest country in the world...") );
				triggers.push_back(Trigger("\nvaticancity", "", "\nAccess Granted.\n",
					bitset<3>(2ul) ));
				
				help();
				
				level = Level(new Switch(
					new Offsets(0, 3, 0, 4), new Offsets(0, 0, -2, 6) ),
					triggers);
				
				runLevel(level, beaten, 9);
				
				}
				
				break;
				
			case 11: {
				
				triggers.push_back(Trigger("\nenigma",
					" stands alone 'twixt water and stone.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nYou need to read a few more Redwall books!\n(Alternatively, you could creatively use an internet search engine...)\n  \"'Twixt water and stone I stand alone\n   Sounding burnt, but alive I survive!\"\n(This one is quite hard, even with searching!)") );
				triggers.push_back(Trigger("\nash", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				out << "You should know what to do by now...\n\n";
				
				level = Level(new Offsets(14, -1, -2, 3, 6), triggers);
				
				runLevel(level, beaten, 10);
				
				}
				
				break;
				
			case 12: {
				
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
				
				help();
				
				level = Level(layers, triggers);
				
				runLevel(level, beaten, 11);
				
				}
				
				break;
				
			case 13: {
				
				triggers.push_back(Trigger("\nenigma",
					"\n128-10-93-85-10-128-98-112-6-6-25-126-39-1-68-78") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nIt appears that you've never read Digital Fortress...\n(You could also use an internet search engine if you'd like.)") );
				triggers.push_back(Trigger("\nwearewatchingyou", "",
					"\nAccess granted.\n", bitset<3>(2ul) ));
				
				out << "You should know what to do by now...\n\n";
				
				level = Level(new Offsets(107, -84, 34, 37, 17), triggers);
				
				runLevel(level, beaten, 12);
				
				}
				
				break;
				
			case 14: {
			
				vector<string> replies;
				vector<bool> tripsFlag, beatsLevel, easterEgg;
				
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
				
				layers.assign(1, new Offsets(12, 3, 6, 5, 7) );
				layers.push_back(new Offsets(51, -2, 3, 4, 5) );
				
				out << "You *really* should know what to do by now...\n\n";
				
				level = Level(layers, triggers);
				
				runLevel(level, beaten, 13);
				
				}
				
				break;
				
			case 15: {
			
				layers.push_back(new Offsets(-32, 21, 15, 12, 5) );
				layers.push_back(new Offsets(12, -2, 15, 5, 17) );
				layers.push_back(new Offsets(2, 30, -30, 8, 6) );
			
				triggers.push_back(Trigger("\nenigma",
					" speaks its only word nevermore.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nWhile I nodded, nearly napping, suddenly there came a tapping,\nAs of some one gently rapping, rapping at my chamber door.\n\"'Tis some visitor,\" I muttered, \"tapping at my chamber door.\nEnigma's this, and nothing more.\"") );
				triggers.push_back(Trigger("\nraven", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				out << "You *really* should know what to do by now...\n\n";
				
				level = Level(layers, triggers);
				
				runLevel(level, beaten, 14);
				
				}
			
				break;
			
			case 16: { //this should be expanded, or a copy should be expanded
				
				int s, d, v, b, c;
				
				out << "Please input integers for s, d, v, b, and c "
					 << "in that order: ";
				
				s = getInt();
				d = getInt();
				v = getInt();
				b = getInt();
				c = getInt();
				
				cls();
	
				triggers.push_back(Trigger("\nenigma", " is the answer to everything.") );
				triggers.push_back(Trigger("\nhelp",
					" cannot be given until \"enigma\" appears!",
					"\nenigma is also the answer to life and the universe.") );
				triggers.push_back(Trigger("\n42", "", "\nAccess granted.\n",
					bitset<3>(2ul) ));
				
				help();
				
				level = Level(new Offsets(s, d, v, b, c), triggers);
				
				runLevel(level, beaten, 15);
				
				}
				
				break;
			
			case 17:
				
				homebrew_main();
				break;
			
			case 18:
				
				welcome();
				break;
			
			case 19:
				
				referenced(beaten);
				break;
				
			case 20:
				
				return 0;

			case 21:  //Jacob's Code
				if (engineVersion)
					engineVersion = false;
				else
					engineVersion = true;
				break;
				
			default:
				
				out << "\nPlease enter a number between 1 and 20"
					 << "\nPress enter to continue:";
				
				pause();
				
				break;
			
		}
		
	}
	
}

void runLevel(Level &level, vector<bool> &beaten, int index) {

	int returned = (engineVersion?level.engine():level.engine2());  //Jacob modified this code
	
	if (returned == 1 || returned == 3) {
		beaten[index] = true;
	}
	
	if (returned == 3) {
		out << "\nYou got the easter egg!";
	}
	
	out << "\nPress enter to continue.";
	
	pause();
	
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
		 << "<http://www.gnu.org/licenses/>.\n\n"
		 << "It is believed that references to copyrighted materials in the riddles\n"
		 << "incorporated in this program are a small proportion of their respective\n"
		 << "works, and do not inhibit the copyright holders' abilitiy to market their\n"
		 << "works.  It is for these reasons that the reference to copyrighted materials\n"
		 << "in Enigma Cipher is considered fair use under United States law.  If you\n"
		 << "as a copyright holder of a referenced material believe that the use of\n"
		 << "your material violates copyright, please email me at <redyoshi49q AT gmail\n"
		 << "DOT com> so that the material in Enigma Cipher can be made compliant with\n"
		 << "your copyright(s).\n\n"
		 << "Press enter to continue.";
	
	pause();
	cls();
	
}

void menu() {
	
	
}

void help() {
	
	if (engineVersion)
		out << "Welcome to Enigma!\n"
			 << "Type a line of text, then press enter.\n"
			 << "If \"enigma\" appears in the generated text on its own line,\n"
			 << "you will get a password hint.\n"
			 << "If you need more help,\n"
			 << "get \"help\" to appear in the generated text on its own line.\n"
			 << "To beat the level, get the password to appear!\n\n";
	else
		out << "Welcome to Enigma!\n"
			<< "If \"enigma\" appears in the generated text on its own line,\n"
			 << "you will get a password hint.\n"
			 << "If you need more help,\n"
			 << "get \"help\" to appear in the generated text on its own line.\n"
			 << "To beat the level, get the password to appear!\n"
			 << "Press ~ three times to clear the screen or press\n\"ESC\" three times to return to the menu.\n\n";
			//this is merely so that alpha/beta testers will have some idea
				//as to what they're supposed to do...
}

void about() {
	
	
	
}

void exit() {
	
	//nuke dynamically set arrays, display ending message
	
}

void referenced(vector<bool> &beaten) {
	
	vector<string> unsolved;
	out << "Solved riddles are paired with their referenced material (if any).\n"
		 << "Authors of referenced material in unsolved levels are shown at the\n"
		 << "end of the list in a randomized order.\n\n";
	
	for (int i = 0; i < 3; i++) {
		if (beaten[i] == true) {
			out << "Level  " << (i+1) << ":  This level does not reference any material.\n";
		}
	}
	
	if (beaten[3] == true) {
		out << "Level  4:  This level references the \"duck test\".\n";
	}
	
	if (beaten[4] == true) {
		out << "Level  5:  This level references the reflexive property from algebra.\n";
	}
	
	for (int i = 5; i < 7; i++) {
		if (beaten[i] == true) {
			out << "Level  " << (i+1) << ":  This level does not reference any material.\n";
		}
	}
	
	if (beaten[7] == true) {
		out << "Level  8:  This level references the definition of \"plane\" in geometry.\n";
	}
	
	if (beaten[8] == true) {
		out << "Level  9:  This level does not reference any material.\n";
	}
	
	if (beaten[9] == true) {
		out << "Level 10:  This level references Vatican City (as you already know).\n";
	}
	
	if (beaten[10] == true) {
		out << "Level 11:  This level references a riddle in the book \"Taggerung\" by\n"
			 << "   Brian Jacques.  The solution to the referenced part of the riddle was\n"
			 << "   the ash tree in the abbey.\n";
	} else {
		unsolved.push_back("Brian Jacques\n");
	}
	
	if (beaten[11] == true) {
		out << "Level 12:  This level references the chorus of the song \"What Hurts\n"
			 << "   the Most\" by Rascal Flatts.\n";
	} else {
		unsolved.push_back("Rascall Flatts\n");
	}
	
	if (beaten[12] == true) {
		out << "Level 13:  This level references the simple code that appears at the end\n"
			 << "   of the the book \"Digital Fortress\" by Dan Brown.\n";
	} else {
		unsolved.push_back("Dan Brown\n");
	}
	
	if (beaten[13] == true) {
		out << "Level 14:  This level references the chorus of the song \"Unspoken\"\n"
			 << "   by Lacuna Coil.\n";
	} else {
		unsolved.push_back("Lacuna Coil\n");
	}
	
	if (beaten[14] == true) {
		out << "Level 15:  This level references the beginning stanza of the poem\n"
			 << "   \"The Raven\" by Edgar Allen Poe.\n";
	} else {
		unsolved.push_back("Edgar Allen Poe\n");
	}
	
	if (beaten[15] == true) {
		out << "Level 16:  This level references The Answer to Life, the Universe,\n"
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
	
	pause();
	cls();
	
}

