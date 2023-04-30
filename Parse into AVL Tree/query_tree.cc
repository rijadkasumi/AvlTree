// Rijad Kasumi (rijad.kasumi11@myhunter.cuny.edu)
// Date 09-10-2022
// CSCI 335 - Assignment 2
// Professor Anita Raja
// Main focus of this file is to create a parser to read in the database and construct an AVL tree.
// To perform the operations properly the file avl_tree.h is modified, where a find() function is added so we can find the node of the tree
// The class creates the parses and reads the db_filename which is reading the input from input_part2a.txt. The output should match output_part2a.txt
/* This file parses through the input of the input_part2a.txt where the input is:

AbsI 
AanI PsiI 
Not Found

and the output of is :

AbsI 
AanI PsiI 
Not Found


*/
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {


// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
	// Code for running Part2(a)
	// Parse input file @db_filename and feel tree @a_tree
	// Then prompt the user for exactly three strings (do a loop) and
	// provide the results of find() as described in the assignment.

	ifstream db_file; // Object to open the db_filename
	db_file.open(db_filename);
	string rec_Seq_Line;  // Reading the input line
	while(getline(db_file, rec_Seq_Line)){ 
			stringstream seq_line(rec_Seq_Line); // read the string line
			string enzyme_acronym; // fill the acronym
            getline(seq_line, enzyme_acronym, '/');
			string recognition_sequence;
			while (getline(seq_line, recognition_sequence, '/')){
				SequenceMap secObj{recognition_sequence, enzyme_acronym};
					a_tree.insert(secObj); // make new tree node 
			}
		}
		db_file.close(); 

	string input; 
   	while (cin >> input) {
    SequenceMap seq_Obj{ input, ""};
    if (a_tree.contains(seq_Obj)) { //if the tree contains the sequence
            a_tree.find(seq_Obj);  // print out the sequence, else "Not Found"
        }
        else{
            cout << "Not Found" << endl;
        }
    }
}

}  // namespace

int
main(int argc, char **argv) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	
	cout << "Input filename is " << db_filename << endl;
	AvlTree<SequenceMap> a_tree;
	QueryTree(db_filename, a_tree);

	return 0;
}
