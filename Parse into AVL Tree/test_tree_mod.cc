// Rijad Kasumi (rijad.kasumi11@myhunter.cuny.edu)
// Date 09-10-2022
// CSCI 335 - Assignment 2
// Professor Anita Raja
// Main focus of this file is to modify the doublerotations so they rotate directly instead of doing two single rotations.
// The file avl_tree.p2c is implemented to work with this fil because of double rotations functions for doublerotations with left and right are modified to perfom a double rotations instead of a single rotation.
// Main file for Part2(c) of Homework 2.


#include "avl_tree_p2c.h"
#include "avl_tree.h"
#include "sequence_map.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType> void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
	// Code for running Part2(c)


  	ifstream db_fileN; // Object to open the db_filename
	db_fileN.open(db_filename);
	string db_line;  // Reading the input line
	while(getline(db_fileN, db_line)){  // While there is a line keep reading
           if(!db_line.empty()) {
			stringstream seq_line(db_line); // read the string line
			string enzyme_acronym; // fill the acronym
            getline(seq_line, enzyme_acronym, '/');
			string recognition_sequence;
			while (getline(seq_line, recognition_sequence, '/') && (!recognition_sequence.empty())){// and if the sequence isn't empty
				SequenceMap secObj{recognition_sequence, enzyme_acronym};
					a_tree.insert(secObj); // make new tree node 
			}}
		}
		db_fileN.close(); 
    // Prints the number of nodes in the tree
    int num_Of_Nodes = a_tree.CountNodes();
    cout <<"2: "<< num_Of_Nodes << endl;
    // Prints the average depth of the tree
    float path_Length = a_tree.tree_Path();
    float average_Depth = path_Length / num_Of_Nodes;
    cout<<"3a: " << average_Depth << endl;
    // Prints the Average Ratio of the depth while diving the average depth with the number of nodes
    float average_Ratio = average_Depth / num_Of_Nodes;
    cout<<"3b: " << average_Ratio << endl;


   // 4
    ifstream inFile;
    inFile.open(seq_filename);
    string dbb_Line;
    int succesful_Queries = 0; // Initializing succesful queries starting at 0
    while(getline(inFile, dbb_Line)) { // While there is a line keep reading
    if(!dbb_Line.empty()) { 
    SequenceMap secObj( dbb_Line, ""), rec_Count;
    if (a_tree.find1(secObj,rec_Count)) {
      succesful_Queries++; //Increment the nubmer of succesful queries
          }
     }
    }
    // Prints the number of succesful queries in the tree
    cout<<"4a: " << succesful_Queries << endl;
    // Prints the total number of recursive calls in the tree(modified in find())
    cout<<"4b: " << a_tree.total_Recursion_Calls() /succesful_Queries<<endl;
    inFile.close();

    //5

    inFile.open(seq_filename);
    int counts_Rem = 0 ;  // counting the remove calls
    int succesful_Removes = 0; // number of succesful removes calss
    while(getline(inFile, dbb_Line)){// read file while there is a line left 
      if(counts_Rem % 2 == 0){   // if num of calls even    
        SequenceMap secObj{dbb_Line, ""};
        if(a_tree.contains(secObj)){ //if contains
          a_tree.remove(secObj);  // remove the sequence
          ++succesful_Removes;
        }
      }
     counts_Rem++; // increment the removes 
    }
    //Print the number of succesful remove calls
    cout<<"5a: "<< succesful_Removes<<endl;
    // Prints the average number of recursion calls
    cout<<"5b: "<<a_tree.remove_Call()/succesful_Removes<<endl;
    inFile.close();


    //Redoing steps 2 and 3 and checking for the output
    num_Of_Nodes = a_tree.CountNodes();
    // Printing the number of nodes on the tree
    cout <<"6a: "<< num_Of_Nodes << endl;
    // Printing the average depth of the tree
    path_Length = a_tree.tree_Path();
    average_Depth = path_Length / num_Of_Nodes;
    cout<<"6b: " << average_Depth << endl;
    // Printing the ratio of the average depth to n
    average_Ratio = average_Depth / num_Of_Nodes;
    cout<<"6c: " << average_Ratio << endl;


}

}  // namespace

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string seq_filename(argv[2]);
	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
	AvlTree<SequenceMap> a_tree;
	TestTree(db_filename, seq_filename, a_tree);

	return 0;
}
