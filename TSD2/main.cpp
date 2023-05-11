#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "voter.h"
#include "candidate.h"


using namespace std;

const string VOTER_FILE = "voter.txt";
const string CANDIDATE_FILE = "candidate.txt";


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

    while (true)
    {
        char choice;
        choice = menu();

        switch (choice)
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
            exit(0);
        default:
            menu();
        }
    }
}

void write_voters()
{
    ofstream file;
    
    file.open(VOTER_FILE, ios::trunc);
    for (int i = 0; i < 10; ++i) {
        voter_t v = voters[i];
        file << v.voter_id << " " << v.name << " " << v.age << " "
                << v.suburb << " " << v.date_of_birth << " " << v.candidate_selection << " "
                << v.electorate << " " << v.previously_voted << " " << v.salary << " " << v.retired << endl;
    }
}

void write_candidates()
{
    ofstream file;
    // truncate to simplify the implementatio
    file.open(CANDIDATE_FILE, ios::trunc);
    for (int i = 0; i < 10; ++i) {
        candidate_t c = candidates[i];
        file << c.id << " " << c.name << " " << c.age << " "
             << c.gender << " " << c.electorate << " " << c.party << " "
             << c.abbreviation << " " << c.political_position << " " << c.officer << " " << c.count << endl;
    }
}

void read_voters() {
    string line;
    string element;

    ifstream file(VOTER_FILE);

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> elements;
            istringstream iss(line);
            for (string line; iss >> line;) {
                elements.push_back(line);
            }

            voter_t v;
            v.voter_id = stoi(elements[0]);
            v.name = elements[1];
            v.age = stoi(elements[2]);
            v.suburb = elements[3];
            v.date_of_birth = elements[4];
            v.candidate_selection = stoi(elements[5]);
            v.electorate = elements[6];
            v.previously_voted = elements[7];
            v.salary = stoi(elements[8]);
            v.retired = elements[9];

            voters.push_back(v);
        }
    }
}

void read_candidates() {
    string line;
    string element;

    ifstream file(CANDIDATE_FILE);

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> elements;
            istringstream iss(line);
            for (string line; iss >> line;) {
                elements.push_back(line);
            }

            candidate_t c;
            c.id = stoi(elements[0]);
            c.name = elements[1];
            c.age = stoi(elements[2]);
            c.gender = elements[3];
            c.electorate = elements[4];
            c.party = elements[5];
            c.abbreviation = elements[6];
            c.political_position = elements[7];
            c.officer = elements[8];
            c.count = stoi(elements[9]);

            candidates.push_back(c);
        }
    }
}
void print_votes()
{
	int choice;

	cout << "Enter candidate ID: " << endl;
	cin >> choice;
	while (choice < 1 || choice > 10)
	{
	    cout << "Please enter a candidate ID between 1 and 10: " << endl;
	    cin >> choice;
	}
	cout << "Candidate " << candidates[choice - 1].id << " - " << candidates[choice - 1].name << " has " << candidates[choice - 1].count << " votes" << endl;
}

void add_votes()
{
	int votchoice, canchoice;

	cout << "Enter voter ID: " << endl;
	cin >> votchoice;

	while (votchoice > 10 || votchoice < 0)
	{
		cout << "Enter voter ID: " << endl;
		cin >> votchoice;
	}

	cout << "Enter candidate ID: " << endl;
	cin >> canchoice;

	while (canchoice > 10 || canchoice < 0)
	{
		cout << "Enter candidate ID: " << endl;
		cin >> canchoice;
	}

	voters[votchoice - 1].candidate_selection = canchoice;
	candidates[canchoice - 1].count += 1;
	cout << candidates[canchoice - 1].id << ". " << candidates[canchoice - 1].name << " now has " << candidates[canchoice - 1].count << " votes " << endl;
}


void lowest_candidate()
{
	int temp = candidates[0].count;
	for (int i = 0; i < 10; i++)
	{
		if (temp > candidates[i].count)
		{
			temp = candidates[i].count;
		}
	}

	// ugly hack solution for dealing with ties, could probably deal with this in
	// the loop one level higher but we're close to submission
	// FUTURE WORK: create more efficient logic
	for (int i = 0; i < 10; i++) {
	    if (temp == candidates[i].count) {
            cout << "The lowest amount of votes is Candidate " << candidates[i].id << ". "
                    << candidates[i].name << " with " << candidates[i].count << " votes" << endl;
        }
	}
}


void highest_candidate()
{
	int large;
	large = candidates[0].count;
	for (int i = 1; i < 10; i++) {
		if (candidates[i].count > large) {
			large = candidates[i].count;
		}
	}

    // ugly hack solution for dealing with ties, could probably deal with this in
    // the loop one level higher but we're close to submission
    // FUTURE WORK: create more efficient logic
    for (int i = 0; i < 10; i++) {
        if (large == candidates[i].count) {
            cout << "The highest amount of votes is Candidate " << candidates[i].id << ". "<< candidates[i].name << " with " << candidates[i].count
                 << " votes" << endl;
        }
    }
}

void reprint_menu(){
    cout << "Main menu:" << endl << "Please choose from the following" << endl;
    cout << "P - Display information on certain candidate" << endl;
    cout << "A - Add votes to candidate" << endl;
    cout << "S - Display candidate with smallest amount of votes" << endl;
    cout << "L - Display candidate with largest number of votes" << endl;
    cout << "Q - Quit" << endl << endl;
}


char menu()
{
	char choice;
	reprint_menu();
    cin >> choice;
    choice = toupper(choice);
    cout << endl;

    while (choice != 'P' && choice != 'A' && choice != 'S' && choice != 'L' && choice != 'Q')
    {
        cout << "Unknown Selection, Please Try Again" << endl;
        reprint_menu();
        cin >> choice;
        cout << endl << endl;
     }

	return choice;
}

