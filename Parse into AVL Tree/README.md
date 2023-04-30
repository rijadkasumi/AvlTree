# Rijad Kasumi - rijad.kasumi11@myhunter.cuny.edu
# Date 10-10-2022
# Assignment 2
# CSCI 335 Software Analysis and Design 3
# The main focus of this program is the creating to parse into a database and construct a tree.

# Feedback and difficulties I encountered working on this assignment #

# In Part 1 of this project was to create a cclass SequenceMap which will include Big 5 by default. Implementation of the bool <> operators and the out << and in >> operators.(Extra Credit EC1). Implementation of function merge().

# In Part 2a of the assignemnt I encountered a lot of difficulties parsing into the database and constructing an Avl tree. After going back to some notes from 235 and also referring to the pseudoco provided by the assignment I finally got to read the file and have some output(just testing). Then the other issue I was having was with implementing the find() function to traverse into the tree. After I implemtened the find() function and started to test my query_tree.cc file I kept not getting the desired output. My output wouldn't match the expected output I was just outputing the first enzyme of the sequence and not the duplicates. After doing couple of testing I realized that I forgot to add the X.Merge function as part of the functionality of the insert() function. After finishing with these steps I run query_tree.cc file locally and the output matched the expcepted out(output_part2a.txt). While working on this part of the project the avl_tree.h file was modified. The find() was added and the function insert() was modified. I tested the program using the command ./query_tree rebase210.txt < input_part2a.txt
# File avl_tree.h - file is modified for Part 2a, where the find() function is implemented and also X Merge is added as part of the functionality of the insert() function.

# In Part 2b of the assignment it was required to create a test routine for test_tree.cc. To parse into the database and construct a search tree and then to print the number of nodes in the tree, to compute the average depth, the ratio of the average depth, to find the number of total queries and to print the average number of recursion calls, to print the total number of succesful removes and the average number of recursion calls. I encounterted a lot of difficulites while working on this part because it required the most of work. I needed to add a couple of new function and also modife current function so I can get the expected result. The function I added is the function to count the number of nodes in a tree CountNodes(), the function tree_Path() to find the lenght of the path of the tree. I needed to modify the function find() so I can find the number of succesful queries, therefore, I can print the average number of recursion call. I also modifed the function remove() so I can find the number of succesful removes and also print the average number of recursion calls which results from diving the total number of recursion calls with the number of remove calls. The hardest part was the part 5b which requieres to print the average number of recursion calls. Fort part 5b been I haven't been to match the expected output. Besides that this part of the project was very challening but in the same time I found very rewarding and very helpful to understand the functions provided in avl_tree in more depth. I tested the program using the command ./test_tree rebase210.txt < sequences.txt
# File avl_tree.h - is modifed fort part 2b, function such as CountNodes(),treePath() are implemented and function like find () and remove are modified.

# In Part 2c the main focus was to implement double rotations directly instead of doing two single rotations. The solution to this was to modify the function doubleWithLeftChild and doubleWithRightChild. This was possible while assigning the child nodes the double rotatins left child first doubleWithLeftChild and then readjusting the height of the tree and seting the new root. And the same for doubleWithRightChild first seting the right child and then updating the heights and setting the new root. I created a new file avl_tree_p2c.h which is a copy of avl_tree.h with modification in the function doubleWithLeftChild() and doubleWithRightChild(). I tested the program using the command ./test_tree_mod rebase210.txt sequences.txt

# Extra Credit Questions
# EC1 : Operator overloading << and >> are implemented in SequenceMap and work as expected.
# EC2 : To transofrm any binary search tree T1 ( with greater than 3 nodes) to another search tree T2(with the same items) via AVL single rotations it can be done with the left rotation and right rotation. In our case with greater than 3 nodes we try T2 left single rotation which will start by the parent node of the right child of the unbalanced tree which moves to become the left child of the current right child and then the T1 left child  moves of the right child(previous) and after performing this operations the tree will still be a binary search tree with greater than 3 nodes and with the same items. The other case is to try right single rotation which can be done with the T1 right rotation which will start by the parent node of the left child of the unbalanced tree which will become the right child of the current left child and then the T2 right child of the right child(previous) and after the opreations the tree will end un as a binary search tree with the same items and greater than 3 nodes.
# EC3 : Since the binary search tree rotations take O(N) time and the single rotations on the Avl tree take O(logN) time. The total complecity of these operations will take O(N)*O(logN) which will result O(NLogN) time.



[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8635587&assignment_repo_type=AssignmentRepo)
# Assignment 2

You will use this exact `Makefile` for your Homework 2. Failure to do so will result in *deduction* of points. Replace this file with a `README.md` for your own project. You can move these instructions to the bottom of the file if you wish.

To compile on terminal, type:

```bash
make
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make query_tree
```

To delete executables and object files, type:

```bash
make clean
```
