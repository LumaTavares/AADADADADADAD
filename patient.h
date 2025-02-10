#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>

// Define the LinkedList and ListNode data structures
typedef struct list LinkedList;    // Represents a linked list
typedef struct list_node ListNode; // Represents a node in the linked list

//Definção da estrutura Pacient
typedef struct pacient Pacient; 

//Definição da função de criação da lista encadeada.
LinkedList* ll_create();

//Definição da função de criação do paciente.
Pacient* new_pacient(int id,LinkedList *l); //mexi

//Definição da função de impressão da interface do menu.
void print_menu();

//Definição da função de formatação de string correspondente ao CPF do paciente
char *formatar_cpf(Pacient *patient);

//Definição da função de atualização do paciente
Pacient* update_patient(LinkedList *l, int id);

//Definição da função de desalocar memória da lista encadeada
void ll_free(LinkedList *l);

// Insert an element at the beginning of the linked list
void ll_insert(LinkedList *l, Pacient *pacients);

// Check whether the linked list is empty
int ll_is_empty(LinkedList *l);

// Display all elements of the linked list
void ll_print(LinkedList *l);

//Definição da função de obter id do paciente. 
int get_id(Pacient *pacient);

//Definição da função da formatação e impressão da saída de dados do paciente
void print_patient(Pacient *patient);

//Definição da função que faz verficação se o nome do paciente está contido na lista ou não
int ll_nome_is_in(LinkedList *l, char *nome);

//Definição da função que faz verficação se o cpf do paciente está contido na lista ou não
int ll_cpf_is_in(LinkedList *l,char *cpf);

int escrever_arquivo_csv(Pacient *patient);

// int contar_id();

int random_id(LinkedList *l);

int inserir_dados_csv(LinkedList *l);

//Definição da função de remoção de um elemento da lista encadeada.
int ll_remove(LinkedList *l, int id);//lista e id 

int csv_remove(LinkedList *l, int id);

int ll_id_is_in(LinkedList *l,int id);

//Definição da função se o paciente está contido na lista ou não
Pacient* ll_is_in(LinkedList *l, int v);

#endif
