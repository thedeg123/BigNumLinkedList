#ifndef additup
#define additup
struct BigInt{
    int digit;
    struct BigInt *next, *prev;
};
struct MyLinkedList{
    struct BigInt *head, *tail;
};
struct BigInt *  sum(struct BigInt *nel, struct BigInt *tel);
void add(char c, struct  MyLinkedList *list);
struct BigInt * freeAll(struct BigInt *element, struct MyLinkedList *list); 
void initializeLL(struct MyLinkedList *list); 
struct BigInt * printNum(struct BigInt *element);
#endif
