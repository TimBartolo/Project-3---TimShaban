// Test driver
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include "TreeType.h"
#include "TreeType.cpp"
#include "QueType.cpp"

using namespace std;

int main()
{

  ifstream inFile;       // file containing operations
  ofstream outFile;      // file containing output
  string inFileName;     // input file external name
  string outFileName;    // output file external name
  string outputLabel;     
  string command;        // operation to be executed
  
  char item;
  string orderItem;
  TreeType <int> tree;
  OrderType order;
  bool found;
  bool finished;
  int numCommands;

  
  tree.PutItem(20);
  tree.PutItem(15);
  tree.PutItem(25);
  tree.PutItem(14);
  tree.PutItem(16);
  tree.PutItem(24);
  tree.PutItem(30);

  /*tree.LevelOrderPrint();
  tree.PutItem(16);
  cout << "\n\n";
  tree.LevelOrderPrint(); */

  /*  tree.PutItem(4);
  tree.PutItem(3);
  tree.PutItem(6);
  tree.PutItem(15);
  tree.PutItem(16);
  tree.PutItem(18);
  tree.PutItem(17); */
  
  int array[20] = {0};

  array[0] = 4;
  array[1] = 6;
  array[2] = 10;
  array[3] = 11;
  array[4] = 12;
  array[5] = 15;
  array[6] = 16;
  array[7] = 20;
  array[8] = 30;
  array[9] = 31;

  //cout << "size:n " << sizeof(array)/sizeof(array[0]);
  TreeType <int> tree2;

  tree2.MakeTree(array);
  tree2.LevelOrderPrint();
  cout << "\n\n";
  TreeType <int> tree3;
  tree3 = tree2.MirrorImage();

  tree3.LevelOrderPrint();

  /*  TreeType <int> tree2;
  tree2 = tree.MirrorImage();
  
  tree.LevelOrderPrint();
  cout << "\n\n";
  tree2.LevelOrderPrint(); */
  
  //tree2.LevelOrderPrint();
  
  //tree.PutItem('N');

  /*tree.LevelOrderPrint();
  cout << "\n\n";

  tree2 = tree.MirrorImage();
  tree2.LevelOrderPrint();
  cout << "\n\n"; */

  /* tree.PreOrderPrint();
  tree.InOrderPrint();
  tree.PostOrderPrint(); */

  //tree.Ancestors('C');

  /*  // Prompt for file names, read file names, and prepare files
  cout << "Enter name of input command file; press return." << endl;
  cin  >> inFileName;
  inFile.open(inFileName.c_str());

  cout << "Enter name of output file; press return." << endl;
  cin  >> outFileName;
  outFile.open(outFileName.c_str());

  cout << "Enter name of test run; press return." << endl;
  cin  >> outputLabel;
  outFile << outputLabel << endl;

  inFile >> command;

  numCommands = 0;
  while (command != "Quit")
  { 
    cout << command;
    if (command == "PutItem")
    {
      inFile >> item; 
      tree.PutItem(item);
      outFile << item;
      outFile << " is inserted" << endl;
    }
    else if (command == "DeleteItem")
    {
      inFile >> item;
      tree.DeleteItem(item);
      outFile << item;
      outFile << " is deleted" << endl;
    }
    else if (command == "GetItem")
    {
      inFile >> item;

      item = tree.GetItem(item, found);
      if (found)
        outFile << item << " found in list." << endl;
      else outFile << item  << " not in list."  << endl;  
    } 
    else if (command == "GetLength")  
      outFile << "Number of nodes is " << tree.GetLength() << endl;
    else if (command == "IsEmpty")
      if (tree.IsEmpty())
        outFile << "Tree is empty." << endl;
      else outFile << "Tree is not empty."  << endl;  
  
    else if (command == "PrintTree")
    {
      //tree.Print(outFile);
      outFile << endl;
    }  
    else if (command == "ResetTree")
    {
      inFile >> orderItem;
      if (orderItem == "PRE_ORDER")
        order = PRE_ORDER;
      else if (orderItem == "IN_ORDER")
        order = IN_ORDER;
      else order = POST_ORDER;    
         
      tree.ResetTree(order);
    }
    else if (command == "GetNextItem")
    {
      inFile >> orderItem;
      if (orderItem == "PRE_ORDER")
        order = PRE_ORDER;
      else if (orderItem == "IN_ORDER")
        order = IN_ORDER;
      else order = POST_ORDER;    
      item = tree.GetNextItem(order,finished);
      outFile << "Next item is: " << item << endl;
      if (finished)
        outFile << orderItem << " traversal is complete." << endl;
    }     
    else if (command == "IsFull")
      if (tree.IsFull())
        outFile << "Tree is full."  << endl;
      else outFile << "Tree is not full." << endl;  
    else if (command == "MakeEmpty")
    {
      tree.MakeEmpty();
      outFile << "Tree has been made empty." << endl;
    }  
	else cout << " Command not recognized." << endl;
    numCommands++;
    cout <<  " Command is completed."  << endl;
    inFile >> command;
  }
 
  cout << "Testing completed."  << endl;
  inFile.close();
  outFile.close();
  return 0; */
}




