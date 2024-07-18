#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

#include "TrivaQuestion.h"
#include "MakeTrivaQuestion.h"
#include "ExtraFunctions.h"

// Version 2.0 - Spring 2023

// Prepare the RandomNumber Generator for the Shuffle Command.
using namespace std;
unsigned mainseed = std::chrono::system_clock::now().time_since_epoch().count();
auto mainrng = std::default_random_engine {mainseed};

// This is the main loop.
int main()
{
    // Phase One,  File Reading.
    ifstream file;

    string fname;

    cout << "Please type in the name of the question bank you would like to open.   ";
    cin >> fname;

    if(fname.find(".txt") == std::string::npos)
    {
        fname += ".txt";
    }


    file.open(fname);

    if(!file)
    {
        cout << "File not found ("<<fname<<").   Exiting program" << endl;
        exit(-1);
    }

    vector<string> theList;
    string line;
    while (getline(file,line))
    {
        if (line.length() > 0)
            theList.push_back(line);
    }

    // Phase Two, build the TrivaQuestion vector from the list

    vector<TrivaQuestion*> questionList;

    for(string line : theList)
    {
        TrivaQuestion *TQ = makeQuestion(line);
        if (TQ != nullptr) questionList.push_back(TQ);
    }
    file.close();

    // DEBUG :: cout << questionList.size() << ": vector size." << endl;


    // Phase Three, play the game, ask the questions.

    int length;
    cout << "How long would you like the quiz to be?   ";
    cin >> length;

    std::shuffle(std::begin(questionList), std::end(questionList), mainrng);

    int total =0;
    int score = 0;
    for(int i = 0; i < length; i++)
    {
        score += questionList[i]->askQuestion();
        total += questionList[i]->getMax();
    }

    // Phase Four : Deliver Results.

    double s = 100.0 * score / total;
    cout << "Your final score is " << score << "/" << total << " or " << setprecision(2) << fixed << s <<"% ." << endl;

    // Phase Five : Clean

    for(TrivaQuestion* x : questionList)
        delete x;
}
