#include "patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

struct pacient
{
    int id;
    char cpf[12];
    char name[100];
    char age[5];
    char year[20];
};

// Define a structure for the linked list.
struct list
{
    ListNode *first; // A pointer to the first node in the linked list.
};

// Define a structure for a node in the linked list.
struct list_node
{
    Pacient* info;       // An integer value stored in the node.
    ListNode* next; // A pointer to the next node in the linked list.
};

// Function to create an empty linked list and return a pointer to it.
LinkedList *ll_create()
{
    LinkedList* l = (LinkedList *)malloc(sizeof(LinkedList)); // Allocate memory for the list structure.
    l->first = NULL;                                          // Initialize the 'first' pointer to NULL, indicating an empty list.
    return l;  
}                                               // Return a pointer to the newly created list.
// Função para ler os dados de CPF, nome, idade e ano
/*  Função para dividir os dados de entrada
void dadoss(char *input, char *cpf, char *name, char *age, char *year) {
    strcpy(cpf, strtok(input, ","));
    strcpy(name, strtok(NULL, ","));
    strcpy(age, strtok(NULL, ","));
    strcpy(year, strtok(NULL, ","));
} */

// Função para criar um novo paciente
// Função para criar um novo paciente
Pacient* new_pacient(int id) {
    Pacient* patient = (Pacient*)malloc(sizeof(Pacient));
    assert(patient != NULL);  // Garante que a alocação de memória foi bem-sucedida

    // Atribui o ID ao paciente
    patient->id = id;

    // Entrada do CPF
    printf("Digite o CPF: ");
    scanf("%11s", patient->cpf);  // Limita a entrada para evitar buffer overflow
    getchar();  // Consumir o '\n' do buffer

    // Entrada do Nome
    printf("Digite o Nome: ");
    fgets(patient->name, sizeof(patient->name), stdin);
    patient->name[strcspn(patient->name, "\n")] = 0;  // Remove o '\n'

    // Entrada da Idade
    printf("Digite a Idade: ");
    scanf("%4s", patient->age);
    getchar();  // Consumir o '\n' do buffer

    // Entrada do Ano de Cadastro
    printf("Digite o Ano de Cadastro: ");
    scanf("%9s", patient->year);
    getchar();  // Consumir o '\n' do buffer

    // Exibe os dados para confirmação
    printf("\n--- Paciente Criado ---\n");
    printf("ID: %d\nCPF: %s\nNome: %s\nIdade: %s\nAno de Cadastro: %s\n", 
           patient->id, patient->cpf, patient->name, patient->age, patient->year);

    return patient;
}

void print_patient(Pacient *patient)
{
   printf("Patient ID: %d, CPF: %s, Name: %s, Idade: %s, Data_Cadastro: %s\n", patient->id, patient->cpf, patient->name, patient->age,patient->year); // Print patient details
}

// Function to check whether the linked list is empty.
int ll_is_empty(LinkedList *l)
{
    return l->first == NULL; // Check if the 'first' pointer is NULL, indicating an empty list.
}

// Function to insert an element at the beginning of the linked list.
void ll_insert(LinkedList* l, Pacient* patient)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode)); // Allocate memory for a new node.
    node->info = patient;                                        // Set the 'info' field of the new node to the provided value.
    node->next = l->first;                                 // Make the new node point to the current first node.
    l->first = node;                                       // Update the 'first' pointer to point to the new node.
}

int get_id(Pacient *pacient)
{
    return pacient->id;
}

int ll_nome_is_in(LinkedList *l, char *nome)//verifica se existem os nomes na lista
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (strstr(p->info->name, nome) != NULL){//nome pode está está contindo na string
            print_patient(p->info);}
        p = p->next;
    }
    return 0;
}

int ll_cpf_is_in(LinkedList *l,char *cpf){//veriica se o cpf existe
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (strcmp(p->info->cpf, cpf) == 0){ //cpf precisam ser iguais
            print_patient(p->info);}
        p = p->next;
    }
    return 0;
}


void ll_print(LinkedList *l)
    {
        for (ListNode *p = l->first; p != NULL; p = p->next)
        {   
            if (ll_is_empty(l)) {
            printf("The list is empty.\n");
            return;
            }
            print_patient(p->info);
            
        }
        printf("\n"); // Print a newline character to separate the output.
}

int contar_id() {
    char ch;
    int line_count = 0;
    FILE *file;
    
    // Abrir o arquivo CSV
    file = fopen("bd_paciente.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
            return -1; // Retorne um valor de erro apropriado
     }

    // Ler o arquivo caractere por caractere
     while ((ch = fgetc(file)) != EOF) {
        // Incrementar a contagem sempre que encontrar uma nova linha
        if (ch == '\n') {
               line_count++;
         }
      }
    
    // Fechar o arquivo
    line_count++;
    fclose(file);
    return line_count;
}

int escrever_arquivo_csv(Pacient *patient){
    FILE *file;
    file = fopen("bd_paciente.csv", "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(file, "%d,%s,%s,%s,%s\n", patient->id, patient->cpf, patient->name, patient->age, patient->year);
    fclose(file);  // Fechar o arquivo após terminar a manipulação
    return 0;
}


int inserir_dados_csv(LinkedList *l) {
    FILE *file = fopen("bd_paciente.csv", "r");  // Modo de leitura do arquivo
    if (file == NULL) {
        printf("Banco de dados vazio");
        return 1;  // Retorna erro se não for possível abrir o arquivo
    }

    char line[1024];  // Buffer para armazenar cada linha do arquivo

    // Ler e ignorar a primeira linha (cabeçalho)
    fgets(line, sizeof(line), file);

    // Ler o arquivo linha por linha
    while (fgets(line, sizeof(line), file)) {
        Pacient *patient = malloc(sizeof(Pacient));  // Alocar memória para o paciente
        if (patient == NULL) {
            printf("Erro ao alocar memória para paciente!\n");
            fclose(file);  // Fechar o arquivo antes de retornar
            return 1;  // Retorna erro se não for possível alocar memória
        }

        // Usando strtok para separar os valores na linha
        char *token = strtok(line, ",");  // Lê o primeiro valor (id)
        if (token != NULL) {
            patient->id = atoi(token);  // Converte o id para inteiro
        }

        token = strtok(NULL, ",");  // Lê o CPF
        if (token != NULL) {
            strncpy(patient->cpf, token, sizeof(patient->cpf) - 1);
        }

        token = strtok(NULL, ",");  // Lê o nome
        if (token != NULL) {
            strncpy(patient->name, token, sizeof(patient->name) - 1);
        }

        token = strtok(NULL, ",");  // Lê a idade
        if (token != NULL) {
            strncpy(patient->age, token, sizeof(patient->age) - 1);
        }

        token = strtok(NULL, ",");  // Lê o ano
        if (token != NULL) {
            strncpy(patient->year, token, sizeof(patient->year) - 1);
        }

        // Inserir o paciente na lista vinculada
        ll_insert(l, patient); 
    }

    fclose(file);  // Fechar o arquivo após a leitura
    return 0;  // Retorna sucesso
}