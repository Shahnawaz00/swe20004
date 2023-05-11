#include <fstream>
#include <vector>

using namespace std;

#ifndef ECVS_VOTER_H
#define ECVS_VOTER_H

struct voter_t {
    int voter_id;
    string name;
    int age;
    string suburb;
    string date_of_birth;
    int candidate_selection;
    string electorate;
    string previously_voted;
    int salary;
    string retired;
};

extern vector<voter_t> voters;

#endif //ECVS_VOTER_H