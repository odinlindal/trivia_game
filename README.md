# Trivia Game

## Overview

This project is a trivia game that allows users to create, store, and play trivia questions. The game supports various functionalities including adding questions, displaying questions, and playing the trivia game.

### Features

- Create and store trivia questions
- Display trivia questions
- Play a trivia game with stored questions

## File Structure

- `ExtraFunctions.cpp`: Contains additional helper functions for the trivia game.
- `ExtraFunctions.h`: Header file for `ExtraFunctions.cpp`.
- `MakeTrivaQuestion.cpp`: Contains functions to create trivia questions.
- `MakeTrivaQuestion.h`: Header file for `MakeTrivaQuestion.cpp`.
- `TrivaGameMain.cpp`: Main file to run the trivia game.
- `TrivaQuestion.cpp`: Contains implementations for trivia question functionalities.
- `TrivaQuestion.h`: Header file for `TrivaQuestion.cpp`.

## Usage

When you run the program, you are met with a menu asking if you want to:
1. Make a question bank
2. Play a question bank
3. Exit

### Make a Question Bank

If you choose to make a question bank, you can:
- Choose how many questions to create
- Specify the type of questions
- Type in each question and its corresponding answer

The questions and answers are saved in a user-defined text file.

### Play a Question Bank

If you choose to play a question bank, you can:
- Input the name of the text file you want to open
- Specify the number of questions you want to play

The questions and answers are shuffled, and the user receives instant feedback on whether their answer was correct.
