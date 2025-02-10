#include "patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

//Definição da estrutura que representa o paciente
struct pacient
{
    int id;             // Variável responsável pelo ID do paciente.
    char cpf[15];       // Variável responsável pelo CPF do paciente.
    char name[100];     // Variável responsável pelo nome do paciente. 
    char age[5];        // Variável responsável pela idade do paciente. 
    char year[20];      // Variável responsável pela data de cadastro do paciente. **MUDAR NOME DA VARIÁVEL
};

// Definição da estrutura de uma lista encadeada.
struct list
{
    ListNode *first; // Variável que prepresenta o ponteiro para o primeiro nó da lista.
};

// Definição da estrutura para um nó na lista encadeada. 
struct list_node
{
    Pacient* info;      // Ponteiro que aponta para a estrutura do paciente.
    ListNode* next;     // Ponteiro que aponta para o próximo nó da lista.
};

// Função responsável pela criação de uma lista encadeada vazia e retorna um ponteiro.
LinkedList *ll_create()
{
    LinkedList* l = (LinkedList *)malloc(sizeof(LinkedList)); // Alocação de memória para a estrutura da lista encadeada.
    l->first = NULL;                                          // Inicializando o ponteiro 'first' para NULL, indicando que uma lista vazia.
    return l;                                                 // Retorna um ponteiro para a lista recém-criada.   
}                                               

//Função responsável pela formatação da string CPF (Ex: 12345678901 -> 123.456.789-01).
//void formatar_cpf(Pacient *patient)
char *formatar_cpf(Pacient *patient) {
    static char format_cpf[15];    //String que armazena o cpf formatado.
    int j = 0;              // Índice para a variável format_cpf.
    
    for (int i = 0; i < 11; i++) {
        format_cpf[j++] = patient->cpf[i];
        if (i == 2 || i == 5) {
            format_cpf[j++] = '.';
        } else if (i == 8) {
            format_cpf[j++] = '-';
        }
    }
    format_cpf[j] = '\0';

    //strcpy(patient->cpf, format_cpf);  // Copia a string contida em "format_cpf" para o campo "cpf" da estrutura do paciente.
    return format_cpf;
}
    

// Função responsável para a criação de um novo paciente.
Pacient* new_pacient(int id,LinkedList *l) {
    char cpf[15];
    Pacient* patient = (Pacient*)malloc(sizeof(Pacient));
    assert(patient != NULL);            // Garante que a alocação de memória foi bem-sucedida

    // Atribui o ID ao paciente
    patient->id = id;

    // Entrada do CPF
    printf("Digite o CPF: ");
    scanf("%11s", patient->cpf);// Limita a entrada para evitar buffer overflow
    if (ll_cpf_is_in(l, patient->cpf) == 1) {
        printf("Erro: CPF ja existe\n");
        return NULL;  // Retorna da função
    }
    getchar();                          // Consumir o '\n' do buffer
    //formatar_cpf(patient);

    // Entrada do Nome
    printf("Digite o Nome: ");
    fgets(patient->name, sizeof(patient->name), stdin);
    patient->name[strcspn(patient->name, "\n")] = 0;    // Remove o '\n'

    // Entrada da Idade
    printf("Digite a Idade: ");
    scanf("%4s", patient->age);
    getchar();  // Consumir o '\n' do buffer

    // Entrada do Ano de Cadastro
    printf("Digite o Ano de Cadastro: ");
    scanf("%11s", patient->year);
    getchar();  // Consumir o '\n' do buffer

    // Retorno da função new_pacient
    return patient;
}

//Função responsável pela funcionalidade de atualizar o paciente.
Pacient* update_patient(LinkedList *l, int id)
{
    
    Pacient* patient = (Pacient*)malloc(sizeof(Pacient));
    assert(patient != NULL);  // Garante que a alocação de memória foi bem-sucedida

    printf("Digite o novo valor para os campos CPF (apenas digitos), Nome, Idade e Data_Cadastro (para manter o valor atual de um campo, digite '-'):\n");
    
    patient = ll_is_in(l,id);                //Busca e seleciona o paciente na lista tendo como critério o ID fornecido.
    if (patient != NULL){
        char new_cpf[15];
        char new_name[100];
        char new_age[5];
        char new_year[20];

        scanf("%11s", new_cpf);              // Entrada de dados do novo cpf para atualização.
        getchar();
        if (ll_cpf_is_in(l, new_cpf) == 1) {
            printf("Erro: CPF ja existe\n");
            return NULL;  // Retorna da função
        }                           // Consume o '\n'(Limpeza do Buffer)

        if (strcmp(new_cpf, "-") != 0)          // Verificação caso o usuário deseja ou não atualizar o CPF do paciente.
        {
            strcpy(patient->cpf, new_cpf);
            //formatar_cpf(patient);
        }

        fgets(new_name, sizeof(new_name), stdin);       // Entrada de dados do novo cpf para atualização.
        new_name[strcspn(new_name, "\n")] = 0;          // Remove o '\n' (Limpeza do Buffer)
        if (strcmp(new_name, "-") != 0)                 // Verificação caso o usuário deseja ou não atualizar o nome do paciente.
        {
            strcpy(patient->name, new_name);
        }

        scanf("%4s", new_age);                          // Entrada de dados da nova idade para atualização.
        getchar();                                      //Remove o '\n' (Limpeza do Buffer)
        if (strcmp(new_age, "-") != 0)
        {
            strcpy(patient->age, new_age);
        }

        scanf("%11s", new_year);                        // Entrada de dados da nova data de cadastro para atualização.
        getchar();                                      // Remove o '\n' (Limpeza do Buffer)
        if (strcmp(new_year, "-") != 0)
        {
            strcpy(patient->year, new_year);
        }
        
        return patient;     //Retorno da função update_patient.
    }
    return NULL;            //Retorna NULL caso não encontre nenhum paciente com ID informado pelo usuário.
}

//Função responsável pela saída de dados formatada dos dados do paciente.
void print_patient(Pacient *patient)
{
    char *cpf_formatado;
    cpf_formatado=formatar_cpf(patient);
    printf("%-3s %-15s %-20s %-10s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro"); // Print patient details
    printf("%-3d %-15s %-20s %-10s %-12s\n", patient->id, cpf_formatado, patient->name, patient->age, patient->year);
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

//Função que obtem o ID do paciente.
int get_id(Pacient *pacient)
{
    return pacient->id;
}

Pacient* ll_is_in(LinkedList *l, int v)
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (p->info->id == v){
            return p->info;
        }
        p = p->next;
    }
    return NULL;
}

int ll_nome_is_in(LinkedList *l, char *nome)//verifica se existem os nomes na lista
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (strstr(p->info->name, nome) != NULL) //nome pode está está contindo na string
        {
            print_patient(p->info);
        }
        p = p->next;
    }
    return 0;
}

int ll_cpf_is_in(LinkedList *l,char *cpf){//veriica se o cpf existe
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (strcmp(p->info->cpf, cpf) == 0){ //cpf precisam ser iguais
            print_patient(p->info);
            return 1;
        }
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

//Função responsável pela impressão da interface do menu.
void print_menu()
{
    printf("Healthy Sys \n");
    printf("\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de paciente\n");
    printf("Q - Sair\n");
    printf("\n");

}

// Function to free the memory used by the linked list.
void ll_free(LinkedList *l)
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        ListNode *t = p->next; // Store a reference to the next node.
        free(p);               // Free the memory allocated for the current node.
        p = t;                 // Move to the next node.
    }
    free(l); // Free the memory allocated for the list structure itself.
}

int ll_id_is_in(LinkedList *l,int id){//veriica se o id existe
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (p->info->id==id){ //id precisam ser iguais
            print_patient(p->info);}
        p = p->next;
    }
    return 0;
}

int random_id(LinkedList *l) {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios com a hora atual
    int min = 0, max = 1000;  // Define o intervalo de números aleatórios (entre 0 e 1000)
    int numero;  // Variável para armazenar o número gerado

    // Loop principal: continua até encontrar um número único
    while (1) {
        numero = min + rand() % (max - min + 1);  // Gera um número aleatório dentro do intervalo [min, max]

        ListNode *p = l->first;  // Ponteiro para percorrer a lista encadeada
        int encontrado = 0;  // Flag para verificar se o número já está na lista

        // Percorre a lista para verificar se o número já existe
        while (p != NULL) {
            if (p->info->id == numero) {  // Se o número já existir na lista
                encontrado = 1;  // Marca como encontrado
                break;  // Sai do loop
            }
            p = p->next;  // Avança para o próximo nó na lista
        }

        // Se o número não foi encontrado, sai do loop principal e retorna o número
        if (!encontrado) {
            break;  // Sai do loop principal
        }
    }
    
    return numero;  // Retorna o número único gerado
}

int escrever_arquivo_csv(Pacient *patient){
    //char *cpf_formatado;
    FILE *file;
    file = fopen("bd_paciente.csv", "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    //cpf_formatado = formatar_cpf(patient);
    fprintf(file, "%d,%s,%s,%s,%s\n", patient->id,patient->cpf, patient->name, patient->age, patient->year);
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

int ll_remove(LinkedList *l, int id)//lista e id 
{
    ListNode *p = l->first; // Pointer to the current node being examined
    ListNode *prev = NULL;  // Pointer to the previous node

    // Traverse the list
    while (p != NULL)
    {
        // Check if the current node contains the element to be removed
        if (p->info->id == id)
        {
            // If the element to be removed is at the beginning of the list
            if (prev == NULL)
                l->first = p->next; // Update the 'first' pointer to skip the first node
            // If the element to be removed is in the middle or end of the list
            else
                prev->next = p->next; // Update the 'next' pointer of the previous node

            
            csv_remove(l,id);
            free(p);  // Deallocate memory occupied by the removed node
            return 1; // retorna lista sem o elemento

        }
        else
        {
            prev = p;    // Update the 'prev' pointer
            p = p->next; // Move to the next node
        }
    }

    return 0; // Indicate that the element was not found
}

int csv_remove(LinkedList *l, int id){
    FILE *file = fopen("bd_paciente.csv", "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }
    fprintf(file,"ID,CPF,Nome,Idade,Data_cadastro\n");

    ListNode *p = l->first;
    
    while (p != NULL) {
        if (p->info->id != id) {  // Escreve todos os pacientes, exceto o que queremos remover
            fprintf(file, "%d,%s,%s,%s,%s\n", p->info->id, p->info->cpf, p->info->name, p->info->age, p->info->year);
        }
        p = p->next;
    }

    fclose(file);
    return 0;

}

// char linha[256];
//     int line_count = 1;
//     FILE *file;
    
//     // Abrir o arquivo CSV
//     file = fopen("bd_paciente.csv", "r");
//     if (file == NULL) {
//         printf("Erro ao abrir o arquivo.\n");
//         return -1;         // Retorne um valor de erro apropriado
//     }

//     // Ler o arquivo linha por linha
//     while (fgets(linha, sizeof(linha), file) != NULL) {
//         // Remove espaços em branco do início e do fim da linha
//         char *start = linha;
//         while (isspace((unsigned char)*start)) {
//             start++;
//         }
//         char *end = linha + strlen(linha) - 1;
//         while (end > start && isspace((unsigned char)*end)) {
//             end--;
//         }
//         *end = '\0';

//         // Incrementa a contagem se a linha não estiver vazia
//         if (strlen(start) > 0) {
//             line_count++;
//         }
//     }

//     // Fechar o arquivo
//     fclose(file);
//     printf("%d\n", line_count);
//     return line_count;