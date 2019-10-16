#include <string>
using namespace std;

class Vigenere {
private:
	string key;
public:
	Vigenere(string new_key);
	
	string encrypt(string message);
	string decrypt(string message);
};