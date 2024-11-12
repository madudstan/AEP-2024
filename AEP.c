#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

//AEP 20224 - ESOFT2S NA

//24055202-2 Maria Eduarda de Castro Lachimia
//24062631-2 Heloisa Sayuri Silva Saito 
//24124854-2 João Guilherme de Souza Campagnoli

char nomes[100][50];
char senhas[100][20];
int contador = 0;

 int validacao(char *senha) {
    int maiuscula = 0, numero = 0, especial = 0;

    if (strlen(senha) < 8) {
        printf("\nERRO!\nA senha deve ter pelo menos 8 caracteres.\n");
        return 0;
    }

    for (int i = 0; senha[i] != '\0'; i++) {
        if (isupper(senha[i])) maiuscula = 1;
        else if (isdigit(senha[i])) numero = 1;
        else if (!isalnum(senha[i])) especial = 1;
    }

    if (!maiuscula) {
        printf("\nERRO!\nA senha deve ter pelo menos uma letra maiuscula.\n");
        return 0;
    }
    if (!numero) {
        printf("\nERRO!\nA senha deve ter pelo menos um numero.\n");
        return 0;
    }
    if (!especial) {
        printf("\nERRO!\nA senha deve ter pelo menos um caractere especial.\n");
        return 0;
    }

    return 1;
}

 void codifica(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] % 3 == 0) {
            str[i] = str[i] + 3;
        } else if (str[i] % 3 == 1) {
            str[i] = str[i] - 2;
        } else if (str[i] % 3 == 2) {
            str[i] = str[i] - 1;
        }
    }
}

 void decodifica(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] % 3 == 0) {
            str[i] = str[i] - 3;
        } else if (str[i] % 3 == 2) {
            str[i] = str[i] + 2;
        } else if (str[i] % 3 == 1) {
            str[i] = str[i] + 1;
        }
    }
}

 void salvar_dados() {
    FILE *arquivo;
    arquivo = fopen("cadastro.txt", "w");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para salvar!\n");
        return;
    }

    
    for (int i = 0; i < contador; i++) {
        fprintf(arquivo, "usuario: %s | senha: %s\n", nomes[i], senhas[i]);
    }

    fclose(arquivo);
}

 void cadastro() {
	
	printf("\nDigite o nome do usuario:\n");
    scanf("%s", nomes[contador]);

    printf("\nREQUISITOS:\n(Minimo 8 caracteres, com uma letra maiuscula, um numero e um caractere especial)\n");
    do {
        printf("\nDigite a senha: ");
        scanf("%s", senhas[contador]);

        if (!validacao(senhas[contador])) {
        } else {
            break;
        }
    } while (1);
    
	codifica(nomes[contador]);
    codifica(senhas[contador]);

    contador++;
    printf("\nUsuario adicionado!\nPressione qualquer tecla para continuar!\n");
    getch();
    
    salvar_dados();
}

 void alteracao() {
    char nome[50], senha[20];

    while (1) {
        printf("\nDigite o nome do usuario a ser alterado:\n");
        scanf("%s", nome);

        
        for (int i = 0; i < contador; i++) {
            decodifica(nomes[i]);
            if (strcmp(nomes[i], nome) == 0) {
                printf("\nDigite a senha do usuario:\n");
                scanf("%s", senha);
                decodifica(senhas[i]);
                
                
                if (strcmp(senhas[i], senha) == 0) {
                    
                    printf("\nDigite o novo nome do usuario:\n");
                    scanf("%s", nomes[i]);

                    do {
                        printf("\nDigite a nova senha:\n");
                        scanf("%s", senhas[i]);

                        if (!validacao(senhas[i])) {
                            
                        } else {
                            break;
                        }
                    } while (1);

                    
                    codifica(nomes[i]);
                    codifica(senhas[i]);

                    printf("\nUsuario alterado com sucesso!\nPressione qualquer tecla para continuar\n");
                    getch();
                    
                
                    salvar_dados();

                    
                    return;
                } else {
                    printf("\nERRO!\nSenha incorreta.\n");
                }
            	codifica(senhas[i]);
            }
            codifica(nomes[i]);
        }

       
        int submenuOpcao = 1;

        while (1) {
            system("cls");
            printf("\nERRO!\nUsuario nao encontrado.\n\n");
            printf("Escolha uma opcao:\n");
            printf("%s 1. Tentar novamente\n", submenuOpcao == 1 ? "->" : "  ");
            printf("%s 2. Voltar ao menu principal\n", submenuOpcao == 2 ? "->" : "  ");

            int tecla = getch();
            if (tecla == 0 || tecla == 224) {
                tecla = getch();
                if (tecla == 72 && submenuOpcao > 1) submenuOpcao--; 
                else if (tecla == 80 && submenuOpcao < 2) submenuOpcao++; 
            } else if (tecla == 13) { 
                if (submenuOpcao == 1) {
                    break;  
                } else {
                    return; 
                }
            }
        }
    }
}


 void exclusao() {
    char nome[50], senha[20];
    
    printf("\nDigite o nome do usuario a ser excluido: ");
    scanf("%s", nome);

    for (int i = 0; i < contador; i++) {
        
        decodifica(nomes[i]);
        
        if (strcmp(nomes[i], nome) == 0) {
            
            while (1) {
                printf("\nDigite a senha do usuario a ser excluido: ");
                scanf("%s", senha);
                
                decodifica(senhas[i]);
                
                if (strcmp(senhas[i], senha) == 0) {
                    for (int j = i; j < contador - 1; j++) {
                        
                        strcpy(nomes[j], nomes[j + 1]);
                        strcpy(senhas[j], senhas[j + 1]);
                    }
                    
                    contador--; 

                    printf("\nUsuario excluido com sucesso!\nPressione qualquer tecla para continuar...\n");
                    getch();
                    salvar_dados(); 
                    return;
                } else {
                    
                    printf("\nERRO! Senha incorreta.\n");
                    
                    int opcao = 1;
                    while (1) {
                        system("cls");
                        printf("\nERRO! Senha incorreta.\n");
                        printf("\nEscolha uma opcao:\n");
                        printf("%s 1. Tentar novamente\n", opcao == 1 ? "->" : "  ");
                        printf("%s 2. Voltar ao menu principal\n", opcao == 2 ? "->" : "  ");

                        int tecla = getch();
                        if (tecla == 0 || tecla == 224) {
                            tecla = getch();
                            if (tecla == 72 && opcao > 1) opcao--; 
                            else if (tecla == 80 && opcao < 2) opcao++; 
                        } else if (tecla == 13) {
                            if (opcao == 1) {
                                break;  
                            } else {
                                return;  
                            }
                        }
                    }
                }
                codifica(senhas[i]);
            }
        }
		
		codifica(nomes[i]);
    }

    int submenuOpcao = 1;

    while (1) {
        system("cls");
        printf("\nERRO!\nUsuario nao encontrado.\n\n");
        printf("Escolha uma opcao:\n");
        printf("%s 1. Tentar novamente\n", submenuOpcao == 1 ? "->" : "  ");
        printf("%s 2. Voltar ao menu principal\n", submenuOpcao == 2 ? "->" : "  ");

        int tecla = getch();
        if (tecla == 0 || tecla == 224) {
            tecla = getch();
            if (tecla == 72 && submenuOpcao > 1) submenuOpcao--; 
            else if (tecla == 80 && submenuOpcao < 2) submenuOpcao++; 
        } else if (tecla == 13) {
            if (submenuOpcao == 1) {
                exclusao(); 
                break; 
            } else {
                return; 
            }
        }
    }
}

 void listagem() {
    system("cls");
    printf("\n--- Lista de Usuarios Cadastrados ---\n");
    
    for (int i = 0; i < contador; i++) {
        decodifica(nomes[i]);
        printf("\nUsuario %d: %s", i + 1, nomes[i]);
        codifica(nomes[i]);  
    }

    printf("\n\nAperte qualquer tecla para voltar ao Menu Principal.\n");
    
    getch();
}

 void carregar_dados() {
    FILE *arquivo;
    arquivo = fopen("cadastro.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum cadastro encontrado.\n");
        return;
    }

    while (fscanf(arquivo, "usuario: %s | senha: %s\n", nomes[contador], senhas[contador]) != EOF) {
        contador++;
    }

    fclose(arquivo);
}

 void menu() {
    int opcao = 1;

    while (1) {
        system("cls");
        printf("+-------------------------+\n");
    	printf("|          MENU           |\n");
    	printf("+-------------------------+\n\n");
        printf("%s 1. Cadastrar usuario\n", opcao == 1 ? "->" : "  ");
        printf("%s 2. Alterar usuario\n", opcao == 2 ? "->" : "  ");
        printf("%s 3. Excluir usuario\n", opcao == 3 ? "->" : "  ");
        printf("%s 4. Listar usuarios\n", opcao == 4 ? "->" : "  ");
        printf("%s 5. Sair\n", opcao == 5 ? "->" : "  ");

        int tecla = getch();
        if (tecla == 0 || tecla == 224) {
            tecla = getch();
            if (tecla == 72 && opcao > 1) opcao--;
            else if (tecla == 80 && opcao < 5) opcao++;
        } else if (tecla == 13) {
            switch (opcao) {
                case 1:
                    cadastro();
                    break;
                case 2:
                    alteracao();
                    break;
                case 3:
                    exclusao();
                    break;
                case 4:
                    listagem();
                    break;
                case 5:
                    exit(0);
            }
        }
    }
}

 int main() {
	carregar_dados();
	menu();
    return 0;
}
