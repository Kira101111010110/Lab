#include <stdio.h>
#include <string.h>

struct studentNode {
	
 char name[ 20 ] ;
 int age ;
 char sex ;
 float gpa ;
 studentNode *next ;
 
} ; //end struct studentNode

class LinkedList {
	
 protected :
  struct studentNode *start, **now ;
  
 public :
  LinkedList() ; 
  ~LinkedList() ; 
  void InsNode( char n[ 20 ], int a, char s, float g ) ; 
  void DelNode() ; 
  void GoNext() ;
  virtual void ShowNode() ; 
  
} ; //end class LinkedList

class NewList : public LinkedList {
	
 public :
  void GoFirst() ; 
  void ShowNode() ; 
  void InsertNode( char n[ 20 ], int a, char s, float g ) ; 
  
} ; //end class NewList

LinkedList::LinkedList( ) : start( NULL ), now( NULL ) { } //end LinkedList::LinkedList

LinkedList::~LinkedList( ) {
	
    struct studentNode *current = start ;
    while ( current != NULL ) {
        struct studentNode *next = current->next ;
        delete current ;
        current = next ;
    }
    start = NULL ;
    now = NULL ;
    
} //end LinkedList::~LinkedList

void LinkedList::InsNode( char n[20], int a, char s, float g ) {
	
    struct studentNode *newNode = new struct studentNode ;
    strncpy( newNode->name, n, sizeof( newNode->name ) ) ;
    newNode->age = a ;
    newNode->sex = s ;
    newNode->gpa = g ;
    newNode->next = NULL ;

    if ( start == NULL ) {
        start = newNode ;
        now = &start ;
    } else {
        (*now)->next = newNode;
        now = &( (*now)->next ) ;
    }
    
} //end LinkedList::InsNode function

void LinkedList::DelNode( ) {
	
    if ( *now == NULL ) {
        printf( "No node to delete.\n" ) ;
        return ;
    }

    struct studentNode *temp = *now ;
    *now = temp->next ;
    delete temp ;
    
} //end LinkedList::DelNode function

void LinkedList::GoNext( ) {
	
    if ( *now != NULL ) {
        now = &( (*now)->next ) ;
    }
    
} //end LinkedList::GoNext function

void LinkedList::ShowNode( ) {
	
    if ( *now != NULL ) {
        printf( "\n LinkedList : \n  Name: %s\n  Age: %d\n  Sex: %c\n  GPA: %.2f\n", (*now)->name, (*now)->age, (*now)->sex, (*now)->gpa ) ;
    } else {
        printf( "\n LinkedList : No node to display.\n" ) ;
    }
    
} //end LinkedList::ShowNode function

void NewList::GoFirst( ) {
	
    now = &start ;
    
} //end NewList::GoFirst function

void NewList::ShowNode( ) {
	
    if ( *now != NULL ) {
        printf( "\n NewList : \n  Name: %s\n  Age: %d\n  Sex: %c\n  GPA: %.2f\n\n", (*now)->name, (*now)->age, (*now)->sex, (*now)->gpa );
    } else {
        printf( " No node to display.\n" ) ;
    }
    
} //end NewList::ShowNode function

void NewList::InsertNode( char n[20], int a, char s, float g ) {
	
    struct studentNode *newNode = new struct studentNode ;
    strncpy( newNode->name, n, sizeof(newNode->name) ) ;
    newNode->age = a ;
    newNode->sex = s ;
    newNode->gpa = g ;
    newNode->next = start ;
    start = newNode ;
    now = &start ;
    
} //end NewList::InsertNode function

int main() {
	
 LinkedList listA ;
 NewList listB ;
 LinkedList *listC ;

 printf( "[ListA]\n" ) ;
 listA.InsNode( "one", 1, 'A', 1.1 ) ;
 listA.InsNode( "two", 2, 'B', 2.2 ) ;
 listA.InsNode( "three", 3, 'C', 3.3 ) ;
 //listA.GoNext() ;
 listA.ShowNode() ;

 printf( "\n[ListB]\n" ) ;
 listB.InsertNode( "four", 4, 'D', 4.4 ) ;
 listB.InsertNode( "five", 5, 'E', 5.5 ) ;
 listB.InsertNode( "six", 6, 'F', 6.6 ) ;
 listB.GoNext() ;
 listB.DelNode() ;
 listB.ShowNode() ;

 printf( "[ListC]\n" ) ;
 listC = &listA;
 listC->GoNext() ;
 listC->ShowNode() ;
 
 listC = &listB ;
 listC->ShowNode() ;

 return 0 ;
 
} //end main function