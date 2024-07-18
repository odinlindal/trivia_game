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
    //Create a choice string for the user to select their menu choice
    string choice = "0";
 do{
    //Display the menu to the user and ask for their choice
    cout << "Do you want to: " << endl;
    cout << "1. Open a question bank" << endl;
    cout << "2. Create a question bank" << endl;
    cout << "3. Exit program." << endl;
    cout << "----> ";
    getline(cin, choice);

    choice = "0" + choice;

    //If the choice is numeric and is 1, open the question bank
    if (stoi(choice) == 1)
    {
        // Phase One,  File Reading.
        ifstream file;

        string fname;

        cout << "Please type in the name of the question bank you would like to open.   ";
        getline(cin, fname);

        //Check if the user input does not contain ".txt", 
        if (fname.find(".txt") == std::string::npos)
        {
            fname += ".txt"; //Add ".txt" to the filename
        }

        file.open(fname); //Open the file
        
        if (!file) //If file is not found
        {
            //Exit the program
            cout << "File not found (" << fname << ").   Exiting program" << endl;
            exit(-1);
        }

        //Read every line from the file into a string vector
        vector<string> theList;
        string line;
        while (getline(file, line))
        {
            if (line.length() > 0)
                theList.push_back(line);
        }

        // Phase Two, build the TrivaQuestion vector from the list

        vector<TrivaQuestion*> questionList; //Create the vector

        //Loop through the list of strings from the file
        for (string line : theList)
        {
            //For every line in the vector, create a question
            TrivaQuestion* TQ = makeQuestion(line);
            //Add the question object to the question vector unless the object is not created
            if (TQ != nullptr) questionList.push_back(TQ);
        }
        file.close(); //Close the file

        // DEBUG :: cout << questionList.size() << ": vector size." << endl;


        // Phase Three, play the game, ask the questions.

        //Ask user how long they want the quiz to be
        string length;
        do {
            cout << "How long would you like the quiz to be?   ";
            getline(cin, length); //Get the user's choice
            length = "0" + length;
            if (stoi(length) <= 0) //If the string is not numeric, output error
            {
                cout << "Invalid choice! Enter only positive numbers!" << endl;
            }
        } while (stoi(length) <= 0); //Do this for as long as the input is not numeric

        //Shuffle the question list
        shuffle(begin(questionList), end(questionList), mainrng);

        //cin.ignore(1, '\n'); //Ignore a newline character

        //Initialize the total and score counters
        int total = 0;
        int score = 0;
        //Loop through however many questions the user wanted
        for (int i = 0; i < stoi(length); i++)
        {
            score += questionList[i]->askQuestion(); //Call the method to ask question for each question
            total += questionList[i]->getMax(); //Add the amount of points each question is worth to the total
        }

        // Phase Four : Deliver Results.

        double s = 100.0 * score / total; //Calculate the percentage score
        //Output the final score
        cout << "Your final score is " << score << "/" << total << " or " << setprecision(2) << fixed << s << "% ." << endl;

        // Phase Five : Clean

        //Delete all the objects
        for (TrivaQuestion* x : questionList)
            delete x;
    }
    //If user wants to create a question bank, choice is 2
    else if (stoi(choice) == 2)
    {
        string filename; //String for filename
        //Ask the user for the name they want for the file
        cout << "Please enter a name for the question bank: ";
        getline(cin, filename);
        //Check if the user input does not contain ".txt", 
        if (filename.find(".txt") == std::string::npos)
        {
            filename += ".txt"; //Add ".txt" to the filename
        }
        ofstream outFile;
        outFile.open(filename, ios_base::app); //Open the file and append to the next empty line

        string numQ = "0"; //String for amount of questions
        do {
            //Ask user for the amount of questions they want
            cout << "Please enter the amount of questions: ";
            getline(cin, numQ);
            numQ = "0" + numQ;
            if (stoi(numQ) <= 0) cout << "Amount must be greater than 0!" << endl;
        } while (stoi(numQ) <= 0); //Do this for as long as the input is smaller than 0.

            for (int i = 1; i <= stoi(numQ); i++)
            {
                string s; //String that will be written to file
                string typeChoice = "0"; //User choice input string
                string qType; //Type of question
                string points = "0"; //User input for amount of points question is worth
                string question; //User input for the question
                
                do {
                    //Ask user what type of question number i is
                    cout << "What type of question is question " << i << "?\n";
                    cout << "1. Fill in the blank\n" << "2. Multiple Choice 3 choices\n" << "3. Multiple Choice 4 choices\n"
                         << "4. True or False\n" << "5. Numeric\n";
                    cout << "----> ";
                    getline(cin, typeChoice); //User input
                    typeChoice = "0" + typeChoice;

                    //Check if typeChoice equals any of the menu choices, and if so, set qType string to appropriate value
                    if (stoi(typeChoice) == 1) qType = "FIB";
                    else if (stoi(typeChoice) == 2) qType = "MC3";
                    else if (stoi(typeChoice) == 3) qType = "MC4";
                    else if (stoi(typeChoice) == 4) qType = "TOF";
                    else if (stoi(typeChoice) == 5) qType = "NUM";
                    else { typeChoice = "0"; cout << "Invalid choice!" << endl; }
                } while (stoi(typeChoice) <= 0 || stoi(typeChoice) > 5); //Keep doing this while the menu choice is not valid
                do {
                    //Ask user how many points question i is worth
                    cout << "How many points are question " << i << " worth?: ";
                    getline(cin, points);
                    points = "0" + points;

                    if (stoi(points) <= 0) //Check if user input is negative or 0
                    {
                        cout << "Please enter only integers bigger than 0." << endl; //Output error message
                    }
                } while (stoi(points) <= 0); //Keep doing this while points is smaller than or equal to 0
                
                bool containColon = false;
                do {
                    //Ask user to enter their question
                    cout << "Enter the question: ";
                    getline(cin, question); //Get user input into the question string

                    if (question.find(':') != string::npos) //Check if the question string contains a colon, this would mess with the parsing
                    {
                        cout << "Question can not contain \':\'. Try again. " << endl;
                        containColon = true;
                    }
                    else containColon = false;
                } while (containColon == true); //Keep prompting user to change question as long as it contains a colon

                //Append the question type, points worth, question to the output string
                s.append(qType);
                s.append(" "); //Formatting
                s.append(trim(points));
                s.append(" "); //Formatting
                s.append(trim(question));
                s.append(" : "); //Formatting

                //Check what type of question the user wanted
                if (trim(qType) == "MC3") //Multiple Choice 3 choices
                {
                    cout << "Please enter the correct answer as the first answer.\n";
                    
                    for (int i = 1; i <= 3; i++) //Loop 3 times, to get the 3 choices
                    {
                        string temp; //Temporary output string
                        cout << "Enter answer #" << i << ": ";
                        getline(cin, temp); //Get user input for choice
                        s.append(trim(temp)); //Append the answer to the output string
                        if (i != 3) s.append(" : "); //Add a colon after the first 2 choices, but not the last one
                    }
                }
                else if (trim(qType) == "MC4") //Multiple Choice 4 choices
                {
                    cout << "Please enter the correct answer as the first answer\n";
                    
                    for (int i = 1; i <= 4; i++) //Loop 4 times, to get the 4 choices
                    {
                        string temp; //Temporary output string
                        cout << "Enter answer #" << i << ": ";
                        getline(cin, temp); //Get user input for choice
                        s.append(trim(temp)); //Append the answer to the output string
                        if (i != 4) s.append(" : "); //Add a colon after the first 3 choices, but not the last one
                    }
                }
                else //Fill in the blank, Numeric, or True or False type questions
                {
                    string temp; //Temporary output string
                    cout << "Enter correct answer: ";
                    getline(cin, temp); //Get user input for the correct answer
                    s.append(trim(temp)); //Append the answer to the output string
                }

                outFile << s << endl; //Write the output string to the file
            }

            outFile.close(); //Close the output file
        }
    else if(stoi(choice) == 3) cout << "Thank you! Exiting program" << endl; //If user choice is 3, exit program
    else //If user coice does not match any choices
    {
        cout << "Invalid choice!" << endl; //Output error
    }
 }while (stoi(choice) !=  3); //Keep doing this as long as the user choice is not 3 to exit
}