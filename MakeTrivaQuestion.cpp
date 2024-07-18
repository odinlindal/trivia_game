// Odin Lindal , CS132, Spring 2024
// Trivia Questions Programming Assignment, 5/25/24
// 
// This program allows the user to open a textfile of questions and answers, and creates a randomised trivia game with different types of questions.

//include necessary headerfiles
#include "MakeTrivaQuestion.h"
#include "TrivaQuestion.h"
#include <string>

//Function for creating a type of question, dictated by the first 3 letters of the string passed to it,
//amount of points, chosen by the number after the question type, the question itself, 
//and the answer or answers. Returns a pointer to the newly created question
TrivaQuestion* makeQuestion(const std::string s)
{
	//Parse the passed string into type, points, question, answers
	std::string t = s.substr(0, 3); //Get the first three letters of the string
	int p = stoi(trim(s.substr(3, s.find_first_of(' ', 3)))); //Start after the first 3 chars, then get everything until a space is found and turn into an int
	//For the question, get everything from the first space until a colon
	std::string q = trim(s.substr(s.find_first_of(' ', 4), (s.find_first_of(':') - s.find_first_of(' ', 4))));
	std::string a = trim(s.substr(s.find_first_of(':')+1)); //The answer(s) are everything after the colon

	//Check the type of question and new the appropriate object using points, question and answers parameters
	if (t == "FIB") { return new FIB(p, q, a); }
	else if (t == "MC3") { return new MC3(p, q, a); }
	else if (t == "MC4") { return new MC4(p, q, a); }
	else if (t == "TOF") { return new TOF(p, q, a); }
	else if (t == "NUM") { return new NUM(p, q, a); }
	//If the first 3 letters of the passed string don't match any of the question types, return a nullptr
	return nullptr;

}