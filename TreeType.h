#ifndef TREETYPE_H
#define TREETYPE_H

#include <string>
#include <fstream>
#include "QueType.h"

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

template <class ItemType>
struct TreeNode;

template <class ItemType>
class TreeType
{
public:
  TreeType();                     // constructor
 ~TreeType();                    // destructor
  TreeType(const TreeType <ItemType> &originalTree); 
  void operator=(const TreeType <ItemType> &originalTree);
  // copy constructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order); 
  ItemType GetNextItem(OrderType order, bool& finished);
  void LevelOrderPrint();
  void Print() const;
  void PreOrderPrint();
  void InOrderPrint();
  void PostOrderPrint();
  void Ancestors(ItemType value);
  TreeType <ItemType> MirrorImage();
  void MakeTree(ItemType array[]);
private:
  TreeNode <ItemType> *root;
  QueType <ItemType> preQue;
  QueType <ItemType> inQue;
  QueType <ItemType> postQue;
};

#endif
