#include "patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Declaração da função escrever_arquivo
void escrever_arquivo(Pacient *patient, FILE *file);

int id = 1;

int main(void)
{  
    LinkedList* list = ll_create();
    const char *filename = "bd_paciente.csv";

    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    char escolha;
    int sair = 0;
    char opcao_menu;

    while(sair == 0)
    {
        printf("Healthy Sys \n");
        printf("\n");
        printf("1 - Consultar paciente\n");
        printf("2 - Atualizar paciente\n");
        printf("3 - Remover paciente\n");
        printf("4 - Inserir paciente\n");
        printf("5 - Imprimir lista de paciente\n");
        printf("Q - Sair\n");
        scanf(" %c", &opcao_menu);

        if (opcao_menu == '1')
        {
            /* Consulta */
        }
        if (opcao_menu == '2')
        {
            /* Atualizar*/
        }
        if (opcao_menu == '3')
        {
            /* Remover */
        }
        if (opcao_menu == '4')
        {
            Pacient* patient = new_pacient(id);
            printf("Confirma os novos valores para o registro abaixo? (S/N)\n");
            print_patient(patient);
            scanf(" %c", &escolha);  // A correção aqui é o espaço antes de %c
            if (escolha == 'S')
            {
                ll_insert(list, patient);
                escrever_arquivo(patient, file);
                fflush(file);  // Garante que o conteúdo seja gravado imediatamente no arquivo
                printf("Registro atualizado com sucesso.\n");
                id++;
            }
        }
        if (opcao_menu == '5')
        {
            ll_print(list);
        }
        if (opcao_menu == 'Q')
        {
            sair = 1;
        }
        printf("\n");
    }

    fclose(file);  // Fechar o arquivo após terminar a manipulação
    return 0;
}
