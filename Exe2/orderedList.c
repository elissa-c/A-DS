#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct node student;

struct node {
    int key;
    int ID;
    char firstName[13];
    //char lastName[13];
    student *next;
};

struct node *head = NULL;
struct node *current = NULL;

//find a link with given key
struct node* seek(int key) {

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}


//display the list
void printList() {
   struct node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d) ",ptr->key,ptr->ID);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert link at the first location
void insert(int key, int ID) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->ID = ID;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}


//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
struct node* delCertain(int key) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         previous = current;
         current = current->next;
      }
   }      
	
    if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}

//delete a link with given key
struct node* delete(int key) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}

void sort() {

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;
	
   int size = length();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if ( current->ID > next->ID ) {
            tempData = current->ID;
            current->ID = next->ID;
            next->ID = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}


int arr[10000000];
void main() {
    int itter = 0;
    int n = 5000;

    while(itter<15) {

      int z, noReturns = 50;
      float t = 0, t2 = 0, t3 = 0;

      for (z = 0; z<noReturns;z++) {
        
        clock_t start = clock();
        srand( time(0));  
        for (int i =0; i<n; i++){
            int number = 1000000 + rand()%1000;
            insert(i, number);
            arr[i] = number;
            //printf("%d,  %d\n", i, number);
        }

        clock_t end = clock();
        float t;
        t += (end-start);
        //printf("%f %d\n", t, n);

        
        clock_t start2 = clock();
        
        srand(time(0));
        for (int i = 0; i<n; i++) {
            int chosen = rand()%n+1;
            seek(chosen);
            //delete(arr[i]);
            //delete(i);
            //printf("%d  ", toDel);
        }

        clock_t end2 = clock();
        float t2;
        t2 += (end2-start2);
        //printf("%f %d\n", t2, n);

        clock_t start3 = clock();

        for (int i = 0; i<n; i++) {
            //int chosen = rand()%n+1;
            //seek(chosen);
            //delCertain(toDel);
            delete(i);
            //printf("%d  ", toDel);
        }

        clock_t end3 = clock();
        float t3;
        t3 += (end3-start3);
        //printf("%f %d\n", t3, n);


        n +=5000;
        itter++;
      }
      

    }


}