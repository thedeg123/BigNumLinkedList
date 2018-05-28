//David Gold
//4/22/18
//Program takes any positive number input and adds it to a running total

#include <string.h>
#include <stdbool.h>
#include "additup.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


struct MyLinkedList* num;
struct MyLinkedList* total; 

int main(){
    total= (struct MyLinkedList*)malloc(sizeof(struct MyLinkedList)); 
    if(!total){
    printf("Could not allocate memory.");
    exit(3);
    }
    initializeLL(total);
    char c= ' ';
    while(c!=EOF){
    num =(struct MyLinkedList*)malloc(sizeof(struct MyLinkedList));
    if(!num){
    printf("Could not allocate memory.");
    exit(3);
    }
    initializeLL(num);
    while((c=getchar()) !='\n'){
	if(c==EOF){
	break;
	}
	if(isspace(c)){
	    continue;
	}
	if(isdigit(c)){
	    add(c,num);
	}
    }
    if (c==EOF){
    break;
    }
    sum(num->tail->prev, total->tail->prev);
    printf("Total: "); 
    printNum(total->head->next);
    free(num);
    }
    freeAll(num->head->next,num);
    free(num);
    freeAll(total->head->next, total);
    free(total);
}

//Sets initial values for the linked list
void initializeLL(struct MyLinkedList *list){
    list->tail=(struct BigInt*)malloc(sizeof(struct BigInt));
    list->head=(struct BigInt*)malloc(sizeof(struct BigInt));
    list->head->digit=0;
    list->head->prev=NULL;
    list->tail->next=NULL;
    list->tail->digit=0;
    list->tail->prev=list->head;
    list->head->next=list->tail;
}

//Frees all elements in linked list. Why am I always freeing the previous? Because I can :)
struct BigInt * freeAll(struct BigInt *element, struct MyLinkedList *list){
    free(element->prev);
    //need both in the case of an empty list being sent to method
     if(element == list->tail){
	free(list->tail);
	return NULL;
    }
    return freeAll(element->next, list);
}
//Adds a new node to the linked list. Here c is the char number and *list is the linked list to add to
void add(char c, struct MyLinkedList *list){
    struct BigInt* new=(struct BigInt*)malloc(sizeof(struct BigInt));
    if(!new){
    printf("Could not allocate memory.");
    exit(3);
    }
    new->digit=c-'0';
    new->prev=list->tail->prev;
    new->next=list->tail;
    list->tail->prev=new;
    new->prev->next=new;
}
//inserts node at beginning of list after the head sentinal node. Here c is the char number and *list is the linked list to add to
void insert(char c, struct MyLinkedList *list){
    struct BigInt* new=(struct BigInt*)malloc(sizeof(struct BigInt));
    if(!new){
    printf("Could not allocate memory.");
    exit(3);
    }
    new->digit=c-'0';
    new->prev=list->head;
    new->next=list->head->next;
    list->head->next=new;
    new->next->prev=new;
}

//sums up two given numbers, passed in the last element of the linked list (pre sentinal node)
struct BigInt * sum(struct BigInt *nel, struct BigInt *tel){
    //In the case that the first input contains no numbers
    if(nel==num->head && nel->next==num->tail && tel==total->head &&  tel->next==total->tail){
    freeAll(num->head->next, num);
    return 0;
    }
    if(tel->prev==total->head && (nel->prev==num->head || nel==num->head)){
    	tel->digit+=nel->digit;
	if(tel->digit>9){
	tel->digit-=10;
	insert('1', total);
	}
	freeAll(num->head->next, num);
	return 0;
    }
    if(nel == num->head){
	//for the case of 999 have to carry digit each time
	if(tel->digit>9){
	 tel->digit-=10;
	    if(tel->prev==total->head){
		nel->prev->digit+=1;	
	    }
	    else{
		tel->prev->digit+=1;
		return sum(nel, tel->prev);
	    }

	}
	freeAll(num->head->next, num);
	return 0;
    }
    if(tel==total->head){
	free(nel->next);
	tel->next->prev=nel;
	nel->next=tel->next;
	num->head->next->prev=tel;
	tel->next=num->head->next;
	free(num->head);
    	return 0;
    }
    else{
	tel->digit+=nel->digit;
	if(tel->digit>9){
	    tel->digit-=10;
	    if(tel->prev==total->head){
		nel->prev->digit+=1;	
	    }
	    else{
		tel->prev->digit+=1;
	    }
	}
    free(nel->next);
    num->tail=nel;
    nel->digit=0;
    }
    return sum(nel->prev,tel->prev);
}
//Prints a given linked list starting with element. Ushally want to pass in list->head->next.
struct BigInt * printNum(struct BigInt *element){
    printf("%i", element->digit);
    if(element->next==total->tail || element==total->tail){
	printf("\n");
	return NULL;
    }
    return printNum(element->next);
}
