// Odin Lindal , CS132, Spring 2024
// Trivia Questions Programming Assignment, 5/25/24
// 
// This program allows the user to open a textfile of questions and answers, and creates a randomised trivia game with different types of questions.

#pragma once
#include "ExtraFunctions.h"

class TrivaQuestion
{
public:
	TrivaQuestion() { points = 0; } //Default constructor

	//Settors
	virtual void setPoints(int p) { points = p; } //Set the points the question is worth
	virtual void setQuestion(std::string q) { question = q; } //Set the question
	virtual void setAnswers(std::string a) = 0; //Set the answerss. Abstract method
	virtual void setRight(std::string r) { rightAnswer = r; } //Set the right answer

	//Gettors
	virtual std::string getQuestion() { return question; } //Returns the question string
	virtual std::string getRight() { return rightAnswer; } //Returns the right answer
	virtual int getMax() { return points; } //Returns the points

	//Method to ask the question. Abstract
	virtual int askQuestion() = 0;

	//Vector to hold the answer strings
	std::vector<std::string> answers;

private:
	//Necessary variables for each question
	int points;
	std::string question;
	std::string rightAnswer;

};

//Fill in the blank question class
class FIB : public TrivaQuestion
{
public:
	FIB(int, std::string, std::string); //Constructor
	virtual int askQuestion(); //Method to ask question
	virtual void setAnswers(std::string a); //Method to add the answer to the answer vector
};

//Multiple Choice 3 question class
class MC3 : public TrivaQuestion
{
public:
	MC3(int, std::string, std::string); //Constructor
	virtual int askQuestion(); //Method to ask question
	virtual void setAnswers(std::string a); //Method to add answers to the answer vector
};

//Multiple Choice 4 question class
class MC4 : public TrivaQuestion
{
public:
	MC4(int, std::string, std::string); //Constructor
	virtual int askQuestion(); //Method to ask the question
	virtual void setAnswers(std::string a); //Method to add answers to the answer vector
};

//True or False question class
class TOF : public TrivaQuestion
{
public:
	TOF(int, std::string, std::string); //Constructor 
	virtual int askQuestion(); //Method to ask the question
	virtual void setAnswers(std::string a); //Method to add the answer to the answer vector
};

//Numeric question class
class NUM : public TrivaQuestion
{
public:
	NUM(int, std::string, std::string); //Constructor
	virtual int askQuestion(); //Method to ask the question
	virtual void setAnswers(std::string a); //Method to add the answer to the answer vector
};

int checkAnswer(const std::string, int); //Method to have the user input their answer and check if it's right
