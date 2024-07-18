// Odin Lindal , CS132, Spring 2024
// Trivia Questions Programming Assignment, 5/25/24
// 
// This program allows the user to open a textfile of questions and answers, and creates a randomised trivia game with different types of questions.

#pragma once
#include "TrivaQuestion.h"
#include <string>

//Prototype for making a question, pass a whole line from the question bank as a string
TrivaQuestion* makeQuestion(const std::string);