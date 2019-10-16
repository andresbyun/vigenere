#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "vigenere.h"

using namespace std;

void print_specification();

int main(int argc, char** argv) {
	string inname = "";
	string mode = "";
	string key = "";
	string outname = "";

	vector<string> cmd_args(&argv[1], &argv[argc]);

	if (argc <= 1) {
		print_specification();
		return 0;
	}
	else {
		for (int i = 0; i < cmd_args.size(); i++) {			
			if (cmd_args[i].compare("-h") == 0 || cmd_args[i].compare("--help") == 0) {
				print_specification();
				return 0;
			}

			if(cmd_args[i].compare("-k") == 0) {
				key = cmd_args[i + 1];
			}
			else if (cmd_args[i].compare("-i") == 0) {
				inname = cmd_args[i + 1];
			}
			else if (cmd_args[i].compare("-o") == 0) {
				outname = cmd_args[i + 1];
			}
			else if (cmd_args[i].compare("-d") == 0) {
				if (mode.compare("") != 0) {
					cout << "ERROR: More than one mode specified.\n";
					print_specification();
					return 0;
				}
				mode = "d";
			}
			else if (cmd_args[i].compare("-e") == 0) {
				if (mode.compare("") != 0) {
					cout << "ERROR: More than one mode specified.\n";
					print_specification();
					return 0;
				}
				mode = "e";
			}
		}
	}

	if (key.compare("") == 0 || inname.compare("") == 0 || outname.compare("") == 0 || mode.compare("") == 0) {
		cout << "ERROR: One or more elements not found.\n";

		cout << "Size of args: " << cmd_args.size() << endl;
		cout << "Input: " << inname << endl;
		cout << "Output: " << outname << endl;
		cout << "Key: " << key << endl;

		print_specification();
		return 0;
	}

	cout << "Trying to open " << inname << "\n";

	ifstream infile;
	infile.open(inname);

	ofstream outfile(outname);

	if (infile.is_open()) {
		Vigenere cipher(key);
		string line;

		if (mode.compare("d") == 0) {
			while (getline(infile, line)){
				outfile << cipher.decrypt(line);
			}
		}
		else if (mode.compare("e") == 0) {
			while (getline(infile, line)) {
				outfile << cipher.encrypt(line);
			}
		}

		infile.close();
		outfile.close();

		string temp = !mode.compare("d") ? "decryption." : "encryption.";
		cout << outname << " generated for " << temp << "\n";
	}
	else cout << "ERROR: Unable to find file : \"" << inname << "\".";

	return 0;
}

void print_specification() {
	cout << "\nVigenere Cipher." << "\n\n";

	cout << "Usage:\n";
	cout << "\tvigenere_cipher -d -k <key> -i <plaintext> -o <ciphertext>\n";
	cout << "\tvigenere_cipher -e -k <key> -i <ciphertext> -o <plaintext>\n";
	cout << "\tvigenere_cipher -h | --help\n";
	cout << "\n";

	cout << "Options:\n";
	cout << "\t-k\t\tSet the key for the cipher.\n";
	cout << "\t-i\t\tFile with the contents that want to be decrypted/encrypted.\n";
	cout << "\t-o\t\tFile with the contents of the decrypted/encrypted message.\n";
	cout << "\t-d\t\tSet decryption mode for the file.\n";
	cout << "\t-e\t\tSet encryption mode for the file.\n";
	cout << "\t-h --help\tShow this screen.\n\n";
}