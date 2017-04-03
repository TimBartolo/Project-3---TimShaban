#include <cstddef> 
#include <iostream>
#include <iomanip>
#include "TreeType.h"

using namespace std;

template <class ItemType>
struct TreeNode
{
  ItemType info;
  TreeNode <ItemType> *left;
  TreeNode <ItemType> *right;
};

template <class ItemType>
bool TreeType <ItemType>::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode <ItemType> *location;
  try
  {
    location = new TreeNode <ItemType>;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

template <class ItemType>
bool TreeType <ItemType>::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

template <class ItemType>
int CountNodes(TreeNode <ItemType> *tree);

template <class ItemType>
int TreeType <ItemType>::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
  return CountNodes(root);
}

template <class ItemType>
int CountNodes(TreeNode <ItemType> *tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else 
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template <class ItemType>
void Retrieve(TreeNode <ItemType> *tree, ItemType &item, bool &found);

template <class ItemType>
ItemType TreeType <ItemType>::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

template <class ItemType>
void Retrieve(TreeNode <ItemType> *tree, ItemType &item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item = tree->info;                 // item is found.
    found = true;
   }
} 

template <class ItemType>
void Insert(TreeNode <ItemType> *&tree, ItemType item);

template <class ItemType>
void TreeType <ItemType>::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

template <class ItemType>
void Insert(TreeNode <ItemType> *&tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode <ItemType>;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
} 

template <class ItemType>
void DeleteNode(TreeNode <ItemType> *&tree);

template <class ItemType>
void Delete(TreeNode <ItemType> *&tree, ItemType item);

template <class ItemType>
void TreeType <ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool found = false;
	GetItem(item, found);
	if (found)
		Delete(root, item);
	else
		cout << item << "is not in tree\n";
}


template <class ItemType>
void Delete(TreeNode <ItemType> *&tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

template <class ItemType>
void GetPredecessor(TreeNode <ItemType> *tree, ItemType& data);

template <class ItemType>
void DeleteNode(TreeNode <ItemType> *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  //ItemType data;
  TreeNode <ItemType> *tempPtr;

  tempPtr = tree;

  if(tree -> right == NULL){
    tree = tree -> left;
    delete tempPtr;
  } //if
  else if(tree -> left == NULL){
    tree = tree -> right;
    delete tempPtr;
  } //else if
  else{
    tempPtr = PtrToSuccessor(tree);
    tree -> info = tempPtr -> info;
    Delete(tree -> right, tempPtr -> info);
  } //else
}

template <class ItemType>
void GetPredecessor(TreeNode <ItemType> *tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

template <class ItemType>
void PrintTree(TreeNode <ItemType> *tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    PrintTree(tree->left);   // Print left subtree.
    cout << tree->info<<"  ";
    PrintTree(tree->right);  // Print right subtree.
  }
}

template <class ItemType>
void TreeType <ItemType>::Print() const
// Calls recursive function Print to print items in the tree.
{
  PrintTree(root);
}

template <class ItemType>
TreeType <ItemType>::TreeType()
{
  root = NULL;
}

template <class ItemType>
void Destroy(TreeNode <ItemType> *&tree);

template <class ItemType>
TreeType <ItemType>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

template <class ItemType>
void Destroy(TreeNode <ItemType> *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

template <class ItemType>
void TreeType <ItemType>::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}

template <class ItemType>
void CopyTree(TreeNode <ItemType> *&copy, const TreeNode <ItemType> *originalTree);

template <class ItemType>
TreeType <ItemType>::TreeType(const TreeType <ItemType> &originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

template <class ItemType>
void TreeType <ItemType>::operator=(const TreeType <ItemType> &originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
  }

}

template <class ItemType>
void CopyTree(TreeNode <ItemType> *&copy, const TreeNode <ItemType> *originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode <ItemType>;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}
// Function prototypes for auxiliary functions.

template <class ItemType>
void PreOrder(TreeNode <ItemType> *, QueType <ItemType> &);
// Enqueues tree items in preorder.

template <class ItemType>
void InOrder(TreeNode <ItemType> *, QueType <ItemType> &);
// Enqueues tree items in inorder.

template <class ItemType>
void PostOrder(TreeNode <ItemType> *, QueType <ItemType> &);
// Enqueues tree items in postorder.

template <class ItemType>
void TreeType <ItemType>::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
  switch (order)
  { 
  case PRE_ORDER:    preQue.MakeEmpty();
		             PreOrder(root, preQue);
                     break;
  case IN_ORDER:     inQue.MakeEmpty();
					 InOrder(root, inQue);
                     break;
  case POST_ORDER:  postQue.MakeEmpty();
					PostOrder(root, postQue);
                     break;
  }
}

template <class ItemType>
void PreOrder(TreeNode <ItemType> *tree, QueType <ItemType> &preQue)
// Post: preQue contains the tree items in preorder.
{
  if (tree != NULL)
  {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue);
    PreOrder(tree->right, preQue);
  }
}

template <class ItemType>
void InOrder(TreeNode <ItemType> *tree, QueType <ItemType> &inQue)
// Post: inQue contains the tree items in inorder.
{
  if (tree != NULL)
  {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}

template <class ItemType>
void PostOrder(TreeNode <ItemType> *tree, QueType <ItemType> &postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL)
  {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}

template <class ItemType>
ItemType TreeType <ItemType>::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  finished = false;
  ItemType item;
  switch (order)
  {
    case PRE_ORDER  : preQue.Dequeue(item);
                      if (preQue.IsEmpty())
                        finished = true;
                      break;
    case IN_ORDER   : inQue.Dequeue(item);
                      if (inQue.IsEmpty())
                        finished = true;
                      break;
    case  POST_ORDER: postQue.Dequeue(item);
                      if (postQue.IsEmpty())
                        finished = true;
                      break;
  }
  return item;
}

template <class ItemType>
void TreeType <ItemType>::LevelOrderPrint(){

  TreeNode <ItemType> *temp_roots[200] = {nullptr};
  TreeNode <ItemType> *temp_leaves[200] = {nullptr};
  TreeNode <ItemType> *null_node;

  int indent = 40;
  int temp_indent;
  int j, t , i;
  int cnt = 1;
  bool more_to_print = true;
  bool no_node = false;
  

  if(IsEmpty()) //no nodes
    cout << "LevelOrderPrint: Tree is empty\n";
  else{
    temp_roots[0] = root;
    while(more_to_print){
      t = 0;
      i = 0;
      indent -= 4;
      temp_indent = 0;
      cout << setw(indent) << ""; //initial indentation
      while((temp_roots[t] != nullptr) && (t < 200)){ //print out the current roots
	if(temp_roots[t] == null_node){
	  t++;
	  cnt++;
	  no_node = true;
	  if(cnt%2 == 0)
	    temp_indent += 3;
	  else
	    temp_indent += 6;
	  continue;
	} //if
     
	if(!no_node){
	  if(cnt%2 == 0)
	    temp_indent += 3;
	  else if(cnt != 1)
	    temp_indent += 6;
	} //if
	//cout << "indent(" << temp_indent << ")";
	cout << setw(temp_indent) << temp_roots[t] -> info;
	temp_indent = 0;
	t++;
	cnt++;
	no_node = false;
      } //while
  
      cout << "\n";
      j = 0;
      temp_indent = 0;
      cout << setw(indent - 2) << "";

      while((temp_roots[i] != nullptr) && (i < 200)){ //populate array with the to-be roots
	if(temp_roots[i] == null_node){
	  /*temp_leaves[j] = null_node;
	  j++;
	  temp_leaves[j] = null_node;
	  j++; */
	  temp_indent += 9;
	  i++;
	  continue;
	} //if

	if(temp_roots[i] -> left == NULL){
	  temp_leaves[j] = null_node;
	  temp_indent += 5;
	  j++;
	} //if
	else{
	  cout << setw(temp_indent) << "/";
	  temp_indent = 5;
	  temp_leaves[j] = temp_roots[i] -> left;
	  j++;
	} //else
	
	if(temp_roots[i] -> right == NULL){
	  temp_indent = 3;
	  temp_leaves[j] = null_node;
	  j++;
	} //if
	else{
	  cout << setw(temp_indent) << "\\";
	  temp_indent = 3;
	  temp_leaves[j] = temp_roots[i] -> right;
	  j++;
	} //else
	i++;
      } //while
      
      cout << "\n";
      more_to_print = false;

      for(int w = 0; w < 200; w++) //clean out roots array for new values
	temp_roots[w] = nullptr;
       
      for(int k = 0; k < 200; k++){ //copy leaves to roots array and clean out leaves array
	temp_roots[k] = temp_leaves[k];
	temp_leaves[k] = nullptr;
	if(temp_roots[k] != nullptr && temp_roots[k] != null_node)
	  more_to_print = true;
      } //for
    } //while
  } //else 
} //LevelOrderPrint

template <class ItemType>
TreeNode <ItemType> * PtrToSuccessor(TreeNode<ItemType> *&tree);

template <class ItemType> 
TreeNode <ItemType> * PtrToSuccessor(TreeNode<ItemType> *&tree){
  
  TreeNode <ItemType> *temp_tree;

  temp_tree = tree -> right;

  while(temp_tree -> left != NULL)
    temp_tree = temp_tree -> left;
  return temp_tree;
} //PtrToSuccessor

template <class ItemType>
void TreeType <ItemType>::PreOrderPrint(){
  
  ItemType item;
  bool finished = false;
  OrderType order = PRE_ORDER;

  preQue.MakeEmpty();
  PreOrder(root, preQue);
  
  cout << "PreOrderPrint: ";
  while(!finished){
    item = GetNextItem(order, finished);
    cout << item << " ";
  } //while
  
  cout << "\n";
} //PreOrderPrint

template <class ItemType>
void TreeType <ItemType>::InOrderPrint(){
  
  ItemType item;
  bool finished = false;
  OrderType order = IN_ORDER;

  inQue.MakeEmpty();
  InOrder(root, inQue);
  
  cout << "InOrderPrint: ";
  while(!finished){
    item = GetNextItem(order, finished);
    cout << item << " ";
  } //while
  
  cout << "\n";

} //InOrderPrint

template <class ItemType>
void TreeType <ItemType>::PostOrderPrint(){
  
  ItemType item;
  bool finished = false;
  OrderType order = POST_ORDER;

  postQue.MakeEmpty();
  PostOrder(root, postQue);
  
  cout << "PostOrderPrint: ";
  while(!finished){
    item = GetNextItem(order, finished);
    cout << item << " ";
  } //while
  
  cout << "\n";

} //PostOrderPrint

template <class ItemType>
void TreeType <ItemType>::Ancestors(ItemType value){
  
  bool found = false;
  ItemType item;
  TreeNode <ItemType> *temp_node;

  GetItem(value, found);

  if(found){ //value exists in tree
    temp_node = root;
    if(temp_node -> info == value)
      cout << value << " has no ancestors\n";
    else{
      while(temp_node -> info != value){
	cout << temp_node -> info << " ";;
	if(temp_node -> info > value)
	  temp_node = temp_node -> left;
	else
	  temp_node = temp_node -> right;
      } //while
      cout << "\n";
    } //else
  } //if
  else cout << value << " is not in tree\n";
} //Ancestors  

template <class ItemType>
void Mirror(TreeNode <ItemType> *&temp_root);

template <class ItemType>
TreeType <ItemType> TreeType <ItemType>:: MirrorImage(){
  
  TreeType <ItemType> mirror_tree(*this);

  Mirror(mirror_tree.root);
  
  return mirror_tree;
} //MirrorImage

template <class ItemType>
void Mirror(TreeNode <ItemType> *&temp_root){

  if (temp_root == NULL) 
    return;  
  else{
      TreeNode <ItemType> *temp_node;
     
      Mirror(temp_root -> left);
      Mirror(temp_root -> right);
 
      temp_node = temp_root -> left;
      temp_root -> left  = temp_root -> right;
      temp_root -> right = temp_node; 
    } //else
} //Mirror

template <class ItemType>
void RecurseMakeTree(int min, int max, ItemType array[], TreeNode <ItemType> *&root);

template <class ItemType>
void TreeType <ItemType>::MakeTree(ItemType array[]){

  int min = 0;
  int max = 0;

  for(int i = 0; i < 200; i++){ //find length of array
    if(array[i] == 0)
      break;
    else
      max++;
  } //for
  
  RecurseMakeTree(min, max - 1, array, root);
} //end

template <class ItemType>
void RecurseMakeTree(int min, int max, ItemType array[], TreeNode <ItemType> *&root){
  
  int midpoint = (min + max)/2;
  int temp_max = max;

  if(max < min)
    return;
  else{
    Insert(root, array[midpoint]);
    max = midpoint - 1;
    RecurseMakeTree(min, max, array, root);
    max = temp_max;
    min = midpoint + 1;
    RecurseMakeTree(min, max, array, root);
  } //else
} //RecurseMakeTree
