/* option.cpp
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

#include "option.hpp"

vector<Option> Options;

void initializeOptions() {
	
	vector<string> choices, descriptions;
	
	//these options need to be in the same order as enum OPTIONS; else the program
	  //will call the wrong options
	
	//ENGINE_VERSION
		#ifdef _WIN32 //this does *not* yet work on linux
			choices.push_back("Immediate");
			descriptions.push_back("Game output is generated on a character-by-character basis.\nIn game user input is not displayed;  only game output is displayed.\nThe backspace key does not delete inputted characters.");
		#endif
		
		choices.push_back("Delayed");
		descriptions.push_back("Game output is generated when the enter key is pressed.\nIn game text alternates between user input and game output\n  on a line-by-line basis.\nThe backspace key can be used to delete characters on the current line.");
		
		Options.push_back(Option("Game Engine", "Determines how the game processes input and output.", choices, descriptions, "Delayed") );
		
		choices.clear();
		descriptions.clear();
	
	//CLEAR_IN_GAME
		choices.push_back("Enabled");
		descriptions.push_back("Allows the screen to be cleared during a game.\nThe controls to do so will depend on the game engine.");
		
		choices.push_back("Disabled");
		descriptions.push_back("Disables the controls that clear the screen.");
		
		Options.push_back(Option("Screen Clearing", "Determines whether the player can clear the screen\nduring game play.", choices, descriptions, "Enabled") );
		
		choices.clear();
		descriptions.clear();
		
}

void changeOptions() {
	
	int index = 0, choice;
	string input;
	bool complain;
	
	while (true) { //function returns when 0 is inputted
		
		cls();
		complain = false;
		
		out << "Please choose one of the following options:\n"
			<< "   0: Return to the main menu.\n";
		
		for (int i = 0; i <= 9 && (index*10) + i < Options.size(); i++) {
			
			out << "  ";
			if (index != 0 || i == 9) {
				//do not output anything
			} else {
				out << " ";
			}
			out << (index*10 + i+1) << ": " << Options[index*10+i].name()
				<< "\n        " ;
			
			string description = Options[i].description();
			
			for (int j = 0; j < description.size(); j++) {
				out << description[j];
				if (description[j] == '\n') out << "        ";
			}
			
			out << endl;
		}
		
		if (index != 0) {
			out << "   a: Previous 10 options.\n";
		}
		
		if ( (index+1)*10 < Options.size() ) {
			out << "   b: Next 10 options.\n";
		}
		
		out << "Please input your choice now:  ";
		
		in >> input;
		in.ignore();
		out << endl;
		
		switch (input[0]) {
			case 'a':
				if (index != 0) {
					index--;
				} else {
					complain = true;
				}
				break;
				
			case 'b':
				if ( (index+1)*10 < Options.size() ) {
					index++;
				} else {
					complain = true;
				}
				break;
			
			default:
				choice = atoi(input.c_str() );
				if (choice == 0) {
					return;
				} else if (choice < 0 || choice > Options.size() ) {
					complain = true;
				} else {
					Options[choice-1].change();
				}
				break;
				
		}
		
		if (complain == true) {
			out << "Your input was invalid, or not currently applicable.\n"
				<< "(Valid inputs are either \"a\", \"b\", or a presented number.)\n"
				<< "Press enter to continue.";
			pauseOutput();
		}
		
	}
	
}

Option::Option(string newName, vector<string> newChoices, vector<string> newDescriptions, int newDefault) {
	
	Name = newName;
	Description = "This option needs a description.\nComplain at a coder, please.";
	choices = newChoices;
	descriptions = newDescriptions;
	
	defaultSetting = newDefault;
	setting = defaultSetting;
	
}

Option::Option(string newName, string newDescription, vector<string> newChoices, vector<string> newDescriptions, int newDefault) {
	
	Name = newName;
	Description = newDescription;
	choices = newChoices;
	descriptions = newDescriptions;
	
	defaultSetting = newDefault;
	setting = defaultSetting;
	
}

Option::Option(string newName, vector<string> newChoices, vector<string> newDescriptions, string newDefault) {
	
	Name = newName;
	Description = "This option needs a description.\nComplain at a coder, please.";
	choices = newChoices;
	descriptions = newDescriptions;
	
	for (int i = 0; i <= choices.size(); i++) {
		if (i == choices.size() ) {
			defaultSetting = 0; //make something usable out of bad data
			break;
		} else if (newDefault == choices[i]) { //toUpper
			defaultSetting = i;
			break;
		}
	}
	setting = defaultSetting;
	
}

Option::Option(string newName, string newDescription, vector<string> newChoices, vector<string> newDescriptions, string newDefault) {
	
	Name = newName;
	Description = newDescription;
	choices = newChoices;
	descriptions = newDescriptions;
	
	for (int i = 0; i <= choices.size(); i++) {
		if (i == choices.size() ) {
			defaultSetting = 0; //make something usable out of bad data
			break;
		} else if (newDefault == choices[i]) { //toUpper
			defaultSetting = i;
			break;
		}
	}
	setting = defaultSetting;
	
}

void Option::change() {
	
	int index = 0, choice;
	string input;
	bool complain;
	
	while (true) { //function returns when 0 is inputted
		
		cls();
		complain = false;
		
		out << "You are now changing the option " << Name << ".\n"
			<< "Please choose one of the following options:\n"
			<< "   0: Return to the main menu.\n";
		
		for (int i = 0; i <= 9 && (index*10) + i < choices.size(); i++) {
			
			out << "  ";
			if (index != 0 || i == 9) {
				//do not output anything
			} else {
				out << " ";
			}
			out << (index*10 + i+1) << ": " << choices[index*10+i]
				<< "\n        " ;
			
			string description = descriptions[i];
			
			for (int j = 0; j < description.length(); j++) {
				out << description[j];
				if (description[j] == '\n') out << "        ";
			}
			
			out << endl;
			
		}
		
		if (index != 0) {
			out << "   a: Previous 10 choices.\n";
		}
		
		if ( (index+1)*10 < Options.size() ) {
			out << "   b: Next 10 choices.\n";
		}
		
		out << "Please input your choice now:  ";
		
		in >> input;
		in.ignore();
		out << endl;
		
		switch (input[0]) {
			case 'a':
				if (index != 0) {
					index--;
				} else {
					complain = true;
				}
				break;
				
			case 'b':
				if ( (index+1)*10 < choices.size() ) {
					index++;
				} else {
					complain = true;
				}
				break;
			
			default:
				choice = atoi(input.c_str() );
				if (choice == 0) {
					return;
				} else if (choice < 0 || choice > choices.size() ) {
					complain = true;
				} else {
					setting = choice - 1;
					out << Name << " changed to " << choices[setting] << ".\n"
						<< "Press enter to continue.";
					pauseOutput();
					return;
				}
				break;
				
		}
		
		if (complain == true) {
			out << "Your input was invalid, or not currently applicable.\n"
				<< "(Valid inputs are either \"a\", \"b\", or a presented number.)\n"
				<< "Press enter to continue.";
			pauseOutput();
			cls();
		}
		
	}
	
}

void Option::operator =(string newSetting) {
	
	for (int i = 0; i < choices.size(); i++) {
		if (newSetting == choices[i]) { //toUpper
			setting = i;
			return;
		}
	}
	
	out << "Invalid setting, reverting to default setting.\n";
	setting = defaultSetting;
	
}

void Option::operator =(int newSetting) {
	
	if (newSetting < 0 || newSetting >= choices.size() ) {
		out << "Invalid setting number, reverting to default value.\n";
		setting = defaultSetting;
	} else {
		setting = newSetting;
	}
	
}

//this file is option.cpp
