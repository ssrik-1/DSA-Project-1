#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include "AVLTree.h"
using namespace std;

//Functions to check for input validity according to project guidelines
	bool nameValid(std::string name) {
		if(name.empty()) {
			return false;
		}
		for(char c : name) {
			if (!isalpha(c) && c != ' ') {
				return false;
			}
		}
		return true;
	}

	bool ufidValid(std::string ufid) {
		if (ufid.empty() || ufid.length() != 8) {
				return false;
		}
		for(char c : ufid) {
			if (!isdigit(c)) {
				return false;
			}
		}
		return true;
	}
    void inputLength(std::string command) {
	if(command.length() < 6 || command.length() > 1000) {
			std::cout << "unsuccessful" << std::endl;
		}
	}

//Main function
int main(){
	AVLTree t;
	std::string numCommands;
	std::getline(std::cin, numCommands);

	for (int i = 0; i < std::stoi(numCommands); i++) {

		//read one line of input from cin 
		std:string line;
		std::getline(std::cin, line);
		
		//create an input stream from that line
		std::istringstream inStream(line);

		std::string command;
		std::getline(inStream, command, ' ');

		if (command == "insert") { 
			std::string name, ufid;
			std::cin.ignore();
			std::getline(inStream, name, '"');
			std::getline(inStream, name, '"');
			std::getline(inStream, ufid);

			if (nameValid(name) == true && ufidValid(ufid) == true) {
				t.insert(name, ufid);
				std::cout << "successful" <<std::endl;
			} else {
				std::cout << "unsuccessful" << std::endl;
			}

		} else if (command == "remove") {
			std::string ufid;
			std::getline(inStream, ufid);

			if(!ufidValid(ufid)) {
				std::cout << "unsuccessful" <<std::endl;
			}

			t.removeID(ufid);
			std::cout << "successful" <<std::endl;

		} else if (command == "search") {
			std::string data;
			std::getline(inStream, data);
			
			if (data.size() == 8 && isdigit(data[0])) {
			    bool promptSearch = ufidValid(data);
			    if (promptSearch) {
			        t.searchID(data);
			    } else {
			        std::cout << "unsuccessful" <<std::endl;
			    }
			 } else {
			    bool promptSearch2 = nameValid(data);
			    if (promptSearch2) {
			        t.searchName(data);
			    } else {
			        std::cout << "unsuccessful" <<std::endl;
			    }
			}
			
		} else if (command == "printInorder") {
			t.printInorder();

		} else if (command == "printPreorder ") {
			t.printPreorder();

		} else if (command == "printPostorder") {
			t.printPostorder();

		} else if (command == "printLevelCount"){
			t.printLevelCount();

		} else if (command == "removeInorder") {
			std::string position;
			std::getline(inStream, position);


			if(position.empty()) {
				int result;
				result = std::stoi(position); 
				if(t.removeInorder(result)) {
					std::cout << "successful" <<std::endl;
				} else {
					std::cout << "unsuccessful" <<std::endl;
				}
			} else {
				std::cout << "unsuccessful" <<std::endl;
			}

		} else {
			 std::cout << "unsuccessful" <<std::endl;
		}
		
	}
	
	return 0;
}