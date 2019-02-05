#ifndef H_LinkedListType
#define H_LinkedListType
 
#include <iostream>
#include <cassert>
using namespace std;
 
template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};
 
template<class Type>
class linkedListType
{
	template<class Type>
	friend ostream& operator<<(ostream&, const linkedListType<Type>&);
 
public:
    const linkedListType<Type>& operator = (const linkedListType<Type>&); 
		//Overload the assignment operator.
    void initializeList(); 
 		//Initializes the list to an empty state.
	    //condition: first = NULL, last = NULL, count = 0;
    bool isEmptyList();
 		//Function to determine whether the list is empty. 
		//condition: Returns true if the list is empty;
	int length();
		//Function to return the number of nodes in the list.
		//condition: The value of count is returned.
    void destroyList();
 		//Function to delete all the nodes from the list.
  		//Postcondition: first = NULL, last = NULL, count = 0
    Type front(); 
 		//Function to return the first element of the list.
 		//condition: The list must exist and must not be empty.
  		//condition: If the list is empty, then the program terminates; otherwise, the first element of the list returned.
    Type back(); 
       //Function to return the last element of the list.
		//condition: The list must exist and must be empty.
		//condition: If the list is empty, then the program terminates; otherwise, the last element of the list is returned.
    bool search(const Type& searchItem);
		//Function to determine whether searchItem is in the list.
		//condition: Returns true if searchItem is found in the list; otherwise, it returns false.
 	void insertFirst(const Type& newItem);
		//Function to insert newItem in the list.
		//condition: first points to the new list and newItem is inserted at the beginning of the list.
    void insertLast(const Type& newItem);
		//Function to return newItem at the end of the list.
	    //condition: first points to the new list, newItem is inserted at the end of the list, and last points to
		//           the last node in the list.
 
    void deleteNode(const Type& deleteItem);
  		//Function to delete deleteItem from the list.
 		//condition: If found, the node containing deleteItem is deleted from the list, first points to the first
		//           node, and last points to the last node of the updated list. 
 
	void deleteSmallest();
 
    linkedListType(); 
   		//default constructor
 		//Initializes the list to an empty state.
 		//condition: first = NULL, last = NULL, count = 0 
 
    linkedListType(const linkedListType<Type>& otherList); 
         //copy constructor
 
    ~linkedListType();   
    	//destructor
   		//Deletes all the nodes from the list.
    	//condition: The list object is destroyed. 
 
protected:
    int count;		//variable to store the number elements in the list
    nodeType<Type> *first; //pointer to the first node of the list
    nodeType<Type> *last;  //pointer to the last node the list 
private:
    void copyList(const linkedListType<Type>& otherList); 
		//Function to make a copy of otherList.
		//condition: A copy of otherList is created and assigned to this list.
};
 
template<class Type>
void linkedListType<Type>::deleteSmallest()
{
	Type smallest;
	//find the smallest value
	deleteNode(smallest);
}
 
template<class Type>
bool linkedListType<Type>::isEmptyList()
{
	return(first == NULL);
}
 
template<class Type>
linkedListType<Type>::linkedListType() // default constructor
{
	first = NULL;
	last = NULL;
	count = 0;
}
 
template<class Type>
void linkedListType<Type>::destroyList()
{
	nodeType<Type> *temp;   //pointer to deallocate the memory
							
	while(first != NULL)    
	{
	   temp = first;        
	   first = first->link; 
	   delete temp;         
	}
 
	last = NULL;	
	count = 0;
}
 
	
template<class Type>
void linkedListType<Type>::initializeList()
{
	destroyList(); //if the list has any nodes, delete them
}
 
template<class Type>
int linkedListType<Type>::length()
{
 	return count;
} 
 
template<class Type>
Type linkedListType<Type>::front()
{   
    assert(first != NULL);
   	return first->info; 
}
 
template<class Type>
Type linkedListType<Type>::back()
{   
	 assert(last != NULL);
   	 return last->info; 
}
 
template<class Type>
bool linkedListType<Type>::search(const Type& searchItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    bool found;
 	current = first;  
    found = false; 
 
    while(current != NULL && !found)		
        if(current->info == searchItem)     
           found = true;
        else
           current = current->link;
     
     return found;
}
 
template<class Type>
void linkedListType<Type>::insertFirst(const Type& newItem)
{
	nodeType<Type> *newNode; 
 
	newNode = new nodeType<Type>;
	assert(newNode != NULL);	
 
	newNode->info = newItem; 	   
	newNode->link = first;        
	first = newNode;             
	count++; 			   
	if(last == NULL)   
		last = newNode;
}
 
template<class Type>
void linkedListType<Type>::insertLast(const Type& newItem)
{
	nodeType<Type> *newNode; 
 
	newNode = new nodeType<Type>;
 
	assert(newNode != NULL);
	newNode->info = newItem;      
	newNode->link = NULL;         
 
	if(first == NULL)	
	{
		first = newNode;
		last = newNode;
		count++;		
	}
	else			
	{
		last->link = newNode; 
		last = newNode;   
		count++;		
	}
}
 
template<class Type>
void linkedListType<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type> *current; 
	nodeType<Type> *trailCurrent; 
	bool found;
 
	if(first == NULL)    
		cerr<<"Can not delete from an empty list.\n";
	else
	{
		if(first->info == deleteItem)  
		{
			current = first;
			first = first->link;
			count--;
			if(first == NULL)   
				last = NULL;
			delete current;
		}
		else 
		{
			found = false;
			trailCurrent = first;   
			current = first->link;
	
			while(current != NULL && !found)
			{
  				if(current->info != deleteItem) 
				{
					trailCurrent = current;
					current = current->link;
				}
				else
					found = true;
			} 
 
			if(found) //Case 3; if found, delete the node
			{
				trailCurrent->link = current->link;
				count--;
 
				if(last == current)    
					last = trailCurrent;
 
				delete current;  
			}
			else
				cout << "Item to be deleted is not in the list." << endl;
		} 
	}
} 
 
//Overloading the stream insertion operator
template<class Type>
ostream& operator<<(ostream& osObject, const linkedListType<Type>& list)
{
	nodeType<Type> *current;
 
	current = list.first;  
	while(current != NULL) 
	{
	   osObject<<current->info<<" ";
	   current = current->link;
	}
 
	return osObject;
}
 
template<class Type>
linkedListType<Type>::~linkedListType() // destructor
{
	destroyList(); 
}
 
template<class Type>
void linkedListType<Type>::copyList(const linkedListType<Type>& otherList) 
{
   nodeType<Type> *newNode; 
   nodeType<Type> *current;
   if(first != NULL)	
	  destroyList();
 
   if(otherList.first == NULL)
   {
		first = NULL;
		last = NULL;
 		count = 0;
   }
   else
   {
		current = otherList.first;  
		count = otherList.count;
		first = new nodeType<Type>;  
 
 		assert(first != NULL);
 
		first->info = current->info; 
		first->link = NULL;  	     
		last = first;    		     
		current = current->link;     
			//copy the remaining list
		while(current != NULL)
		{
			newNode = new nodeType<Type>;  
			assert(newNode!= NULL);
 
			newNode->info = current->info;	
			newNode->link = NULL;   	    
			last->link = newNode;
			last = newNode;   			
			current = current->link;
		}
	}
}
 
 
	//copy constructor
template<class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type>& otherList) 
{
	first = NULL;
 	copyList(otherList);
}
 
	//overload the assignment operator
template<class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(const linkedListType<Type>& otherList)
{ 
	if(this != &otherList) //avoid self-copy
		copyList(otherList);
 	return *this; 
}
 
#endif