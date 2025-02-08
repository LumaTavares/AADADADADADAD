#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>

// Define the LinkedList and ListNode data structures
typedef struct list LinkedList;    // Represents a linked list
typedef struct list_node ListNode; // Represents a node in the linked list

typedef struct pacient Pacient;

// Create an empty linked list and return a pointer to it
LinkedList* ll_create();

Pacient* new_pacient(int id);

// Insert an element at the beginning of the linked list
void ll_insert(LinkedList *l, Pacient *pacients);

// Check whether the linked list is empty
int ll_is_empty(LinkedList *l);

// Display all elements of the linked list
void ll_print(LinkedList *l);

int get_id(Pacient *pacient);

void print_patient(Pacient *patient);

void escrever_arquivo(Pacient *patient,FILE *file);

//void ll_csv(FILE *file,LinkedList *l);

//int verificar_csv_vazio(FILE *file);//sla se precisa


#endif