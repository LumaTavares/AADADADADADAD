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
    char nome[100];
    char cpf[12];

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

            int opcao;
            printf("deseja procurar o úsuario pelo cpf ou nome?\n");
            printf("para nome digite 1 e cpf 2\n");
            scanf("%d", &opcao);
            if(opcao==1){
                printf("digite o nome desejado:\n ");
        
                // Garantir que qualquer caractere de nova linha remanescente seja consumido
                getchar();  // Remove o '\n' do buffer

                fgets(nome, sizeof(nome), stdin); // Lê o nome completo, incluindo espaços
                nome[strcspn(nome, "\n")] = 0;    // Remove o '\n' no final, caso exista
                ll_nome_is_in(list,nome);
            }if(opcao==2){
                printf("digite o cpf desejado:\n ");
        
                // Garantir que qualquer caractere de nova linha remanescente seja consumido
                getchar();  // Remove o '\n' do buffer

                fgets(cpf, sizeof(cpf), stdin); // Lê o nome completo, incluindo espaços
                cpf[strcspn(cpf, "\n")] = 0;    // Remove o '\n' no final, caso exista
                ll_cpf_is_in(list,cpf);

            }else{
                printf("opcap invalida\n");
            }
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
