#include <iostream>
#include <string>
#include "Vigenere.h"

using namespace std;

Vigenere::Vigenere(string new_key) {
	key = "";
	for (char& c : new_key) {
		key += tolower(c);
	}
}

string Vigenere::encrypt(string message) {
	string encrypted = "";
	int index_key = 0;

	for (char& c : message) {
		c = tolower(c);

		if (c < 'a' || c > 'z') {
			encrypted += c;
			continue;
		}

		encrypted += 'a' + ((c + key.at(index_key)) % 'a') %  26;
		index_key = ++index_key % key.length();
	}

	return encrypted;
}

string Vigenere::decrypt(string message) {
	string decrypted = "";
	int index_key = 0;

	for (char& c : message){
		c = tolower(c);

		if (c < 'a' || c > 'z') {
			decrypted += c;
			continue;
		}

		decrypted += 'a' + ((c - key.at(index_key) + 26) % 'a') % 26;
		index_key = ++index_key % key.length();
	}

	return decrypted;
}