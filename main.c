#include "patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int id;
int main(void)
{  
    //Criação da lista e arquivo vinculado a mesma
    LinkedList* list = ll_create();
    FILE *filename;
    filename = fopen("bd_paciente.csv", "a");
    if (filename == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    inserir_dados_csv(list);
    id = random_id(list);

    char escolha;
    int sair = 0;
    char opcao_menu;
    char nome[100];
    char cpf[12];

    while(sair == 0)
    while(sair == 0)
{
    print_menu(); // Mostra o menu

    scanf(" %c", &opcao_menu);
    getchar();  // Limpa o buffer após a leitura do caractere

    if (opcao_menu == '1') {   
        int escolha;
        printf("Escolha o modo de consulta:\n");
        printf("1 - Por nome\n");
        printf("2 - Por CPF\n");
        printf("3 - Retornar ao menu principal\n\n");

        scanf("%d", &escolha);
        getchar();  // Limpa o buffer

        if(escolha == 1) {
            printf("Digite o nome:\n ");
            fgets(nome, sizeof(nome), stdin); // Lê o nome completo
            nome[strcspn(nome, "\n")] = 0;    // Remove o '\n'
            ll_nome_is_in(list, nome);
        } 
        else if (escolha == 2) {
            printf("Digite o CPF:\n ");
            fgets(cpf, sizeof(cpf), stdin);
            cpf[strcspn(cpf, "\n")] = 0;
            ll_cpf_is_in(list, cpf);
        }
    } 
    else if (opcao_menu == '2') {
        int id_patient;
        ll_print(list);
        printf("Digite o ID do registro a ser atualizado:\n");
        scanf("%d", &id_patient);
        getchar(); // Limpa o buffer

        if (ll_is_in(list, id_patient) != NULL) {
            Pacient* patient = update_patient(list, id_patient);
            print_patient(patient);
            printf("Confirma os novos valores para o registro acima? (S/N): ");
            scanf(" %c", &escolha);
            getchar(); // Limpa o buffer

            if (escolha == 'S' || escolha == 's') {
                ll_remove(list, id_patient);
                ll_insert(list, patient);
                escrever_arquivo_csv(patient);
                //fflush(filename);
                printf("Registro atualizado com sucesso.\n");
            }
        } else {
            printf("ID não existe.\n");
        }
    } 
    else if (opcao_menu == '3') {
        int excluir_id;
        printf("Digite o ID do registro a ser removido: ");
        scanf("%d", &excluir_id);
        getchar(); // Limpa o buffer
        
        if (ll_id_is_in(list, excluir_id) == 0) {
            printf("Tem certeza de que deseja excluir o registro abaixo? (S/N): ");
            scanf(" %c", &escolha);
            getchar(); // Limpa o buffer
            
            if (escolha == 'S' || escolha == 's') {
                ll_remove(list, excluir_id);
                printf("Registro removido com sucesso.\n");
            } else {
                printf("Processo cancelado.\n");
            }
        } else {
            printf("ID nao existe.\n");
        }
    } 
    else if (opcao_menu == '4') {
        printf("\n");
        Pacient* patient = new_pacient(id, list);
        if (patient != NULL) {
            printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
            print_patient(patient);
            scanf(" %c", &escolha);
            getchar(); // Limpa o buffer

            if (escolha == 'S' || escolha == 's') {
                ll_insert(list, patient);
                escrever_arquivo_csv(patient);
                //fflush(filename);
                printf("O registro foi inserido com sucesso.\n");
                id = random_id(list);
            }
        }
    } 
    else if (opcao_menu == '5') {
        ll_print(list);
    } 
    else if (opcao_menu == 'Q' || opcao_menu == 'q') {
        ll_free(list);
        sair = 1;
    } 
    else {
        printf("opcao invalida! Tente novamente.\n");//nao ficar abrindo toda hora o menu
    }

    printf("\n");
}
    fclose(filename);  // Fechar o arquivo após terminar a manipulação
    return 0;
} 