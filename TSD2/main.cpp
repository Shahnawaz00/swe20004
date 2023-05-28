#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <string>

#include "voter.h"
#include "candidate.h"

using namespace std;

const string VOTER_FILE = "voter.txt";
const string CANDIDATE_FILE = "candidate.txt";

vector<candidate_t> candidates = {};
vector<voter_t> voters = {};

char menu();
void reprint_menu();
void highest_candidate();
void lowest_candidate();
void add_votes();
void print_votes();
void read_candidates();
void read_voters();
void write_candidates();
void write_voters();



int main()
{
    read_voters();
    read_candidates();
    bool quit = false;

    while (!quit)
    {
        char userinput;
        userinput = menu();

        switch (toupper(userinput)) //toupper switches lowercase to upper case, so both will work
        {
        case 'P':
            print_votes();
            break;
        case 'A':
            add_votes();
            break;
        case 'S':
            lowest_candidate();
            break;
        case 'L':
            highest_candidate();
            break;
        case 'Q':
            write_voters();
            write_candidates();
            quit = true;
        }
    }
}

//writes the updated file information to the file when q (quit) is pressed
void write_voters()
{
    ofstream file;

    file.open(VOTER_FILE, ios::trunc); //trunc flag clears whole file before writing to it.
    for (int i = 0; i < voters.size(); ++i) {
        voter_t vote = voters[i];
        file << vote.voter_id << " " << vote.first_name << " " << vote.second_name << " " << vote.age << " "
            << vote.gender << " " << vote.suburb << " " << vote.state << " " << vote.date_of_birth << " " << vote.country_of_birth << " "
            << vote.candidate_choice << endl;
    }
}

void write_candidates()
{
    ofstream file;//declares an output file stream named 'file' that will be used to write data to a file
    
    file.open(CANDIDATE_FILE, ios::trunc);
    for (int i = 0; i < candidates.size(); ++i) {
        candidate_t cand = candidates[i];
        file << cand.id << " " << cand.first_name << " " << cand.last_name << " " << cand.age << " "
            << cand.gender << " " << cand.suburb << " " << cand.party << " "
            << cand.symbol << " " << cand.years_in_politics << " " << cand.count << endl;
    }
}

//reads the voter.txt file
void read_voters() {
    string line;

    ifstream file(VOTER_FILE);

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> voter_element;
            istringstream iss(line);
            for (string line; iss >> line;) {
                voter_element.push_back(line);
            }

            voter_t vote;
            vote.voter_id = stoi(voter_element[0]);
            vote.first_name = voter_element[1];
            vote.second_name = voter_element[2];
            vote.age = stoi(voter_element[3]);
            vote.gender = voter_element[4];
            vote.suburb = voter_element[5];
            vote.state = voter_element[6];
            vote.date_of_birth = voter_element[7];
            vote.country_of_birth = voter_element[8];
            vote.candidate_choice = voter_element[9];

            voters.push_back(vote);
        }
    }
}

//reads the candidate.txt file
void read_candidates() {
    string line;

    ifstream file(CANDIDATE_FILE);

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> candidate_element;
            istringstream iss(line);
            for (string line; iss >> line;) {
                candidate_element.push_back(line);
            } 

            candidate_t cand;
            cand.id = stoi(candidate_element[0]);
            cand.first_name = candidate_element[1];
            cand.last_name = candidate_element[2];
            cand.age = stoi(candidate_element[3]);
            cand.gender = candidate_element[4];
            cand.suburb = candidate_element[5];
            cand.party = candidate_element[6];
            cand.symbol = candidate_element[7];
            cand.years_in_politics = stoi(candidate_element[8]);
            cand.count = stoi(candidate_element[9]);

            candidates.push_back(cand);
        }
    }
}

//checks that each character in the string is an integer
bool check_input_number(string userinput)
{
    for (int i = 0; i < userinput.length(); i++)
    {
        if (isdigit(userinput[i]) == false) // check if each character in the string is a digit
        {
            return false;
        }
    }
    return true;
}

//checks for errors in input, if passes, reads chosen candidates vote count
void print_votes()
{
    int choice;
    string userinput;
    bool validinput = false;

	cout << "Enter the candidate ID number: " << endl;
    while (!validinput) // while we do not have a vaid input
    {
	    cin >> userinput;// get input
        if (check_input_number(userinput)) { // check if input is a number
            choice = stoi(userinput); //convert string to int
            if (choice >= 1 && choice <= 10) // check if number is between range
            {
                validinput = true;//set valid input to true
	            cout << "Candidate " << candidates[choice - 1].id << " - " << candidates[choice - 1].last_name << " has " << candidates[choice - 1].count << " votes" << endl;
            }
            else
            {
                cout << "Please enter the candidate ID number between 1 and 10: " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else
        {
            cout << "Please enter the candidate ID number between 1 and 10: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

//checks for errors in input, if passes, candidate will gain vote from voter
void add_votes()
{
	int voterschoice, candidatechoice;
    string uservoteinput, usercandidateinput;
    bool votevalidinput = false;
    bool candidatevalidinput = false;

	cout << "Enter the voter ID number: " << endl;
    while (!votevalidinput) 
    {
        cin >> uservoteinput;
        if (check_input_number(uservoteinput)) { 
            voterschoice = stoi(uservoteinput); 
            if (voterschoice >= 1 && voterschoice <= voters.size()) 
            {
                votevalidinput = true;
            }
            else
            {
                cout << "Please enter the voter ID number between 1 and 10: " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else
        {
            cout << "Please enter the voter ID number between 1 and 10: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

	cout << "Enter the candidate ID number: " << endl;
    while (!candidatevalidinput) // while we do not have a vaid input
    {
        cin >> usercandidateinput;// get input
        if (check_input_number(usercandidateinput)) { // check if input is a number
            candidatechoice = stoi(usercandidateinput); //convert string to int
            if (candidatechoice >= 1 && candidatechoice <= candidates.size()) // check if number is between range
            {
                candidatevalidinput = true;//set valid input to true
            }
            else
            {
                cout << "Please enter the candidate ID number between 1 and 10: " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else
        {
            cout << "Please enter the candidate ID number between 1 and 10: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    voters[voterschoice - 1].candidate_choice = candidatechoice;
	candidates[candidatechoice - 1].count += 1;
	cout << candidates[candidatechoice - 1].id << ". " << candidates[candidatechoice - 1].last_name << " now has " << candidates[candidatechoice - 1].count << " votes " << endl;
}

//checks for candidate with the lowest vote count
void lowest_candidate()
{
    int temp = candidates[0].count;
    for (int i = 0; i < candidates.size(); i++)
    {
        if (temp > candidates[i].count)
        {
            temp = candidates[i].count;
        }
    }


    for (int i = 0; i < candidates.size(); i++) {
        if (temp == candidates[i].count) {
            cout << "The lowest amount of votes is Candidate " << candidates[i].id << ". "
                << candidates[i].last_name << " with " << candidates[i].count << " votes" << endl;
        }
    }
}

//checks for candidate with the highest vote count
void highest_candidate()
{
    int large;
    large = candidates[0].count;
    for (int i = 1; i < candidates.size(); i++) {
        if (candidates[i].count > large) {
            large = candidates[i].count;
        }
    }


    for (int i = 0; i < candidates.size(); i++) {
        if (large == candidates[i].count) {
            cout << "The highest amount of votes is Candidate " << candidates[i].id << ". " << candidates[i].last_name << " with " << candidates[i].count
                << " votes" << endl;
        }
    }
}

//function used to reprint menu after every selection
void reprint_menu(){
    cout << "Main menu:" << endl << "Please choose from the following" << endl;
    cout << "P - Candidate number of votes" << endl;
    cout << "A - Add number of votes to a candidate" << endl;
    cout << "S - Display the smallest number of votes candidate" << endl;
    cout << "L - Display the largest number of votes candidate" << endl;
    cout << "Q - Quit and data to database" << endl;
}


char menu()
{
	char choice;
	reprint_menu();
    cin >> choice;
    choice = toupper(choice);
    cout << endl;
    //another error check
    while (choice != 'P' && choice != 'A' && choice != 'S' && choice != 'L' && choice != 'Q')
    {
        cout << "Seletion is not valid, please choose an option from the menu." << endl;
        reprint_menu();
        cin >> choice;
        choice = toupper(choice);
        cout << endl;
     }

	return choice;
}

