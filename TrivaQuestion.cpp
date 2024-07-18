// Odin Lindal , CS132, Spring 2024
// Trivia Questions Programming Assignment, 5/25/24
// 
// This program allows the user to open a textfile of questions and answers, and creates a randomised trivia game with different types of questions.

//Include all necessary headerfiles
#include "TrivaQuestion.h"
#include <vector>
#include <algorithm>
#include <iostream>

//Constructor for Fill In the Blank question
FIB::FIB(int p, std::string q, std::string a)
{
	setPoints(p); //Set the points
	setQuestion(q); //Set the question string
	setAnswers(a); //Send the answer string to the setAnswers function
}

//Function to fill the answers vector with the answers
void FIB::setAnswers(std::string a)
{
	answers.push_back(a); //Add the answer to the vector answers
	setRight(answers.front()); //Set the first element of the answer vector to be the right answer
}

//Function to ask the question and get user input, then check if the answer is right
int FIB::askQuestion()
{
	//Print out the question and prompt the user to input their answer
	std::cout << "This is a fill in the blank question worth " << getMax() << " points." << std::endl << std::endl;
	std::cout << "Question: " << getQuestion() << std::endl;
	std::cout << std::endl << "Fill in the blank: ";

	//Call checkAnswer to get user input and check if the answer is correct, then return however many points it returns
	return checkAnswer(getRight(), getMax());
}

//Constructor for Multiple Choice question with 3 choices
MC3::MC3(int p, std::string q, std::string a)
{
	setPoints(p); //Set the points
	setQuestion(q); //Set the question string
	setAnswers(a); //Send the answer string to the setAnswers function
}

//Function to set the 3 answers for the Multiple Choice 3 question
//Parameter is the answer string which contains all 3 answers
void MC3::setAnswers(std::string a)
{
	//Add to vector: from start of string to first colon
	answers.push_back(trim(a.substr(0, a.find_first_of(':'))));
	//Add to vector: from the character after the first colon of the string up to the next colon
	answers.push_back(trim(a.substr(a.find_first_of(':')+1, (a.find_last_of(':') - a.find_first_of(':')-1))));
	//Add to vector: from the character after the last colon until the end of the string
	answers.push_back(trim(a.substr(a.find_last_of(':')+1)));
	//All the strings added to the vector are trimmed to remove whitespaces at start and end

	setRight(answers.front()); //Set the first element of the vector as the right answer
	shuffleVector(answers); //Shuffle the order of the elements in the vector, so the right answer isn't always the first choice
}

//Function to ask the question for the Multiple Choice 3 question
int MC3::askQuestion()
{
	//Ask the question and let the user know how many points it is worth
	std::cout << "This is a Multiple Choice question with 3 choices worth " << getMax() << " points." << std::endl << std::endl;
	std::cout << "Question: " << getQuestion() << std::endl;

	//Initialize variables needed for the list of answers
	int count = 0;
	int rightIndex = 0;
	std::string ra = getRight(); //Set string ra to the right answer

	//Print out all answers led by an index number (1-3)
	std::for_each(answers.begin(), answers.end(), [&count, &rightIndex, &ra](std::string x) {
		std::cout << ++count << ". " << x << std::endl;
		if (x == ra) { rightIndex = count; } //If the element printed off matches the right answer, set rightIndex to the index of that answer
	});
	std::cout << std::endl << "Enter answer(1-3): "; //Prompt user to input a number from 1 to 3

	//Call checkAnswer to get user input and check if the answer is correct, then return however many points it returns
	return checkAnswer(std::to_string(rightIndex), getMax()); //Pass the string version of the right index as the right answer to the function
}

MC4::MC4(int p, std::string q, std::string a)
{
	setPoints(p); //Set the points
	setQuestion(q); //Set the question string
	setAnswers(a); //Send the answer string to the setAnswers function
}

void MC4::setAnswers(std::string a)
{
	//Adding the 4 answers to the answers vector
	//Add to vector: from start of string to first colon
	answers.push_back(trim(a.substr(0, a.find_first_of(':'))));
	//Add to vector: from first colon to the second colon
	answers.push_back(trim(a.substr(a.find_first_of(':') + 1, a.find_first_of(':', a.find_first_of(':') + 1) - a.find_first_of(':') - 1)));
	//Add to vector: from second colon to third colon
	answers.push_back(trim(a.substr(a.find_first_of(':', a.find_first_of(':') + 1) + 1, (a.find_last_of(':') - a.find_first_of(':', a.find_first_of(':') + 1) - 1))));
	//Add to vector: from the character after the last colon until the end of the string
	answers.push_back(trim(a.substr(a.find_last_of(':') + 1)));

	setRight(answers.front()); //Set the first element of the vector as the right answer
	shuffleVector(answers); //Shuffle the order of the elements in the vector, so the right answer isn't always the first choice
}

int MC4::askQuestion()
{
	//Ask the question and let the user know how many points it is worth
	std::cout << "This is a Multiple Choice question with 4 choices worth " << getMax() << " points." << std::endl << std::endl;
	std::cout << "Question: " << getQuestion() << std::endl;

	//Initialize variables needed for the list of answers
	int count = 0;
	int rightIndex = 0;
	std::string ra = getRight(); //Set string ra to the right answer

	//Print out all answers led by an index number (1-4)
	std::for_each(answers.begin(), answers.end(), [&count, &rightIndex, ra](std::string x) {
		std::cout << ++count << ". " << x << std::endl;
		if (x == ra) { rightIndex = count; } //If the element printed off matches the right answer, set rightIndex to the index of that answer
	});
	std::cout << std::endl << "Enter answer(1-4): "; //Prompt user to input their answer from 1-4

	//Call checkAnswer to get user input and check if the answer is correct, then return however many points it returns
	return checkAnswer(std::to_string(rightIndex), getMax()); //Pass the string version of the right index as the right answer to the function
}

TOF::TOF(int p, std::string q, std::string a)
{
	setPoints(p); //Set the points
	setQuestion(q); //Set the question string
	setAnswers(a); //Send the answer string to the setAnswers function
}

void TOF::setAnswers(std::string a)
{
	//Add to answers vector: the answer string
	answers.push_back(trim(a)); //Since there is only one answer option, add the whole string to the vector without the need to look for colons
	setRight(answers.front()); //Set the right answer
}

int TOF::askQuestion()
{
	//Ask the question and let the user know how many points it is worth
	std::cout << "This is a True or False question worth " << getMax() << " points." << std::endl << std::endl;
	std::cout << "Question: " << getQuestion() << std::endl;

	std::cout << std::endl << "Enter answer(True or False): "; //Prompt the user to enter their answer

	//Call checkAnswer to get user input and check if the answer is correct, then return however many points it returns
	return checkAnswer(getRight(), getMax()); //Pass the right answer from the getRight() function
}

NUM::NUM(int p, std::string q, std::string a)
{
	setPoints(p); //Set the points
	setQuestion(q); //Set the question string
	setAnswers(a); //Send the answer string to the setAnswers function
}

void NUM::setAnswers(std::string a)
{
	//Add to answers vector: the answer string
	answers.push_back(trim(a)); //Since there is only one answer option, add the whole string to the vector without the need to look for colons
	setRight(answers.front()); //Set the right answer
}

int NUM::askQuestion()
{
	//Ask the question and let the user know how many points it is worth
	std::cout << "This is a Numeric question worth " << getMax() << " points." << std::endl << std::endl;
	std::cout << "Question: " << getQuestion() << std::endl;
	std::cout << std::endl << "Enter answer(number): "; //Prompt the user to enter their answer

	//Call checkAnswer to get user input and check if the answer is correct, then return however many points it returns
	return checkAnswer(getRight(), getMax()); //Pass the right answer from the getRight() function
}

//Function to get user input and check if the answer is correct,
//parameters are the right answer and the amount of points the question is worth
int checkAnswer(const std::string ra, int points)
{
	//Create a string for the user's answer
	std::string useranswer;
	//Get the user's answer
	std::getline(std::cin, useranswer);

	std::string right = ra; //Temporary string to hold right answer

	//Convert both strings to uppercase to avoid case-sensitive
	std::transform(useranswer.begin(), useranswer.end(), useranswer.begin(), ::toupper);
	std::transform(right.begin(), right.end(), right.begin(), ::toupper);

	//If the users input matches the right answer, return the points the question is worth
	if (trim(useranswer) == trim(right)) //The trim function is used so any whitespaces don't affect right/wrong
	{
		//Print "Correct"
		std::cout << "Correct!" << std::endl << std::endl;
		return points;
	}
	else //If the users input does not match the answer, return 0
	{
		//Print "Wrong" and the right answer
		std::cout << "Wrong! The answer was: " << ra << "." << std::endl << std::endl;
		return 0;
	}
}