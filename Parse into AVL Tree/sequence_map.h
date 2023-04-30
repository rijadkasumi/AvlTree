// Rijad Kasumi (rijad.kasumi11@myhunter.cuny.edu)
// Date 09-10-2022
// CSCI 335 - Assignment 2
// Professor Anita Raja
// The main purpose of this file(sequence_map.h) is to define the class SequenceMap so we can use it throughout the program
// For this class the Big 5 is implemented as default
// Overloaded operators bool operator<,bool operator> are implemented
// Overloaded operators operator<< and operator>> are implemented
// The implementation of the Merge function merges the other_sequence.enzyme_acronym_ with the object’s enzyme_acronym_
// Implementation  of Sequence_map.h
// SequenceMap will be used on the program to read the enzyme acronym assosiated with the recognition sequence
//
#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include "avl_tree.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;



class SequenceMap {
    public:
    //Big 5 implementation start...

    // Default constructor
    SequenceMap () = default;
    // Copy Constructor
    SequenceMap(const SequenceMap &rhs) = default;
    // Copy Assigment
    SequenceMap & operator=(const SequenceMap &rhs) = default;
    // Move constructor
    SequenceMap( SequenceMap &&rhs)= default;
    // Move Assignment
    SequenceMap & operator=(SequenceMap &&rhs) = default;
    // Deconstructor
    ~SequenceMap()= default;

    // Ending of Big 5 implementation.

    // Creating class SequenceMap
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    // Overloading the operator bool <
    bool operator<(const SequenceMap &rhs) const {
        return recognition_sequence_ <rhs.recognition_sequence_;
    }

    // Overloading the operator bool >
    bool operator>(const SequenceMap &rhs) const {
        return recognition_sequence_ > rhs.recognition_sequence_;
    }

    //Overloading the operator <<
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &some_points) {
        for(int i = 0; i <some_points.enzyme_acronyms_.size(); i++ ){
        out<< some_points.enzyme_acronyms_[i] << " ";
    }
    return out;
    }

    // Overloading the operator >>
    friend std::istream &operator>>(std::istream &in, SequenceMap &some_points) {
        std::string newstring;
        in >> newstring;
        some_points.recognition_sequence_= newstring;
        return in ;
        }
    //Member function Merge which merges othersequence with the object of enzyme acronym
    // the other_sequences wont be affected
    void Merge(const SequenceMap &other_sequence){
        for (int i=0; i<other_sequence.enzyme_acronyms_.size(); i++){
          enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
          }
          }
    //Two private member data
    private:
        string recognition_sequence_;
        std::vector<string> enzyme_acronyms_;


};





#endif //SEQUENCE_MAP_H
