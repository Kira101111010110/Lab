#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct studentNode {
	
	char name[ 20 ] ;
	int age ;
	char sex ;
	float gpa ;
	struct studentNode *next ;
	
} ;

class LinkedList {
	
	protected :
		struct studentNode *start, **now ;
	public :
		LinkedList() ;
		~LinkedList() ;
		void InsNode( char n[], int a, char s, float g ) ;
		void DelNode() ;
		void GoNext() ;
		void GoFirst() ;
		void GoLast() ;
		void ShowAll() ;
		int FindNode( char n[] ) ;
		struct studentNode *NowNode() ;
		void EditNode( char n[], int a, char s, float g ) ;
		
} ; //end class

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

void LinkedList::ShowAll( ) {
	
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

int LinkedList::FindNode( char n[] ) {
    struct studentNode *current = start ;
    int index = 0 ;

    while ( current != NULL ) {
        
        if ( strcmp( current->name, n ) == 0 ) {
        	
            return index ;
            
        }
        
        current = current->next ;
        index++ ;
        
    }

    return -1 ;
    
} //end NewList::FindNode function

void LinkedList::EditNode( char n[], int a, char s, float g ) {
    struct studentNode *current = start ;

    while ( current != NULL ) {
    	
        if ( strcmp(current->name, n) == 0 ) {
        	
            current->age = a ;
            current->sex = s ;
            current->gpa = g ;
            return ;

        }

        current = current->next ;
    }

    printf( "Student '%s' not found. No data is edited.\n", n ) ;
    
}//end NewList::FEditNode function

void EditData( LinkedList *ll ) ;
void AddData( LinkedList *ll ) ;
void FindData( LinkedList *ll ) ;
void readfile( LinkedList *ll ) ;
void writefile( LinkedList *ll ) ;

int main() {
	
	LinkedList listA ;
	int menu ;
	readfile( &listA ) ;
	printf( "  Menu - (1) Add (2) Edit (3) Delete (4) Find (5) Show (0) Edit : " ) ;
	scanf( "%d", &menu ) ;
	while( menu != 0 ) {
		switch( menu ) {
			case 1 : AddData( &listA ) ; break ;
			case 2 : EditData( &listA ) ; break ;
			case 3 : listA.DelNode() ; break ;
			case 4 : FindData( &listA ) ; break ;
			case 5 : listA.ShowAll() ; break ;
 		}//end switch
		printf( "  Menu - (1) Add (2) Edit (3) Delete (4) Find (5) Show (0) Edit : " ) ;
		scanf( "%d", &menu ) ;
 	}//end while
	writefile( &listA ) ;
	return 0 ;
	
}//end function 

void writefile( LinkedList *ll ) {
	
	FILE *fp;
	fp = fopen( "C:/Users/hieng/Desktop/student.dat", "w" ) ;
	if( fp == NULL ) {
		
		printf( "Can't open file!" ) ;
		exit( 0 ) ;
		
	}
	
	char name[ 20 ], sex ;
	int age, i ;
	float gpa ;
	for( i = 0 ; i < 2 ; i++ ) {
		
		printf( "Enter Name, Sex, Age and GPA: " ) ;
		scanf( "%s %c %d %f", name, &sex, &age, &gpa ) ;
		fprintf( fp, "%s %c %d %f\r\n", name, sex, age, gpa ) ;
				
	}
	
	fclose( fp ) ;
	
}// end void writefile function

void readfile( LinkedList *ll ) {
	
	FILE *fp ;
	fp = fopen( "C:/Users/hieng/Desktop/student.dat", "r" ) ;
	if( fp == NULL ) {
		printf( "Can't open file!" ) ;
		exit( 0 ) ; 
	}
	
	char name[ 20 ], sex ;
	int age, i ;
	float gpa ;
	for( i = 0 ; i < 20 ; i++ ) {
		if( fscanf( fp, "%s %c %d %f", name, &sex, &age, &gpa ) == EOF ) 
			break ;
		printf( "%d: %10s %2c %2d %4.2f\n", i, name, sex, age, gpa ) ;
	}
	
	fclose( fp ) ;
	
}//end void readfile function

void EditData(LinkedList *ll) {
	
    char name[ 20 ] ;
    int age ;
    char sex ;
    float gpa ;

    printf( "Enter the name of the student to edit: " ) ;
    scanf( "%s", name ) ;

    int index = ll->FindNode(name) ;
    if ( index == -1 ) {
    	
        printf( "Student '%s' not found.\n", name ) ;
        return ;
        
    }

    printf( "Enter new data for the student (Name, Sex, Age, GPA): " ) ;
    scanf( "%s %c %d %f", name, &sex, &age, &gpa ) ;

    ll->EditNode( name, age, sex, gpa ) ;

    printf( "Student data updated successfully.\n" ) ;
    
}//end void EditData function

void AddData( LinkedList *ll ) {
    char name[ 20 ] ;
    int age ;
    char sex ;
    float gpa ;

    printf( "Enter new student data (Name, Sex, Age, GPA): " ) ;
    scanf( "%s %c %d %f", name, &sex, &age, &gpa ) ;

    ll->InsNode( name, age, sex, gpa ) ;

    printf( "Student added successfully.\n" ) ;
    
}//end void AddData function

void FindData(LinkedList *ll) {
	
    char name[ 20 ];

    printf( "Enter the name of the student to find: " ) ;
    scanf( "%s", name ) ;

    int index = ll->FindNode( name );
    if ( index == -1 ) {
    	
        printf("Student '%s' not found.\n", name) ;
        
    } else {
    	
        printf("Student '%s' found at index %d.\n", name, index) ;
        
    }
    
}//end void FindData function