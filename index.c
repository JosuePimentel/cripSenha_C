#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// chave guia (abc) & chave senha (abcde) 
// mensagem

void removeWordWrap( char* mens );
void criptografarSenha( char mens[50], char* mensCript, char guia[4] );

int main( ) {

    FILE* arquivo = fopen("SenhasClientes.txt", "a+");

    if(arquivo == NULL) {
        printf("Abertura do arquivo falhou!\n");
        return 1;
    }

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif

    int chase;
    printf("What do you wanna do?\n [01] Cript\n [02] Uncript\n");
    scanf("%i", &chase);

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif

    char mensagem[50];
    char chaveGuia[4];
    if( chase == 1 ) {
        printf("Escreva a mensagem que vc quer criptgrafar:\n");
        getchar();
        fgets(mensagem, sizeof(mensagem), stdin);
        removeWordWrap( mensagem );
        char mensagemCriptografada[strlen(mensagem)];

        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #else
            system("clear");
        #endif

        printf("Defina uma chave guia nas seguintes condições: \n01.Contenha 3 caracteres. \n02.Todos eles sem sinais ou acentuação. \n03.Todos minusculos. \n04.De a até z \n");
        
        while( 1 ) {
            fgets(chaveGuia, 4, stdin);
            removeWordWrap(chaveGuia);
            if(strlen(chaveGuia) >= 3) break;
            else printf("Chave guia fora dos padrões\n");
        }

        criptografarSenha( mensagem, mensagemCriptografada, chaveGuia );
        char arquivoEnvioOne[50];
        char arquivoEnvioTwo[50]; 
        printf("%zu", strlen(mensagemCriptografada));
        strcat(arquivoEnvioOne, "\n\nSenha criptografada: ");
        strcat(arquivoEnvioOne, mensagemCriptografada);

        strcat(arquivoEnvioTwo, "\nchave-guia: ");
        strcat(arquivoEnvioTwo, chaveGuia);
        strcat(arquivoEnvioTwo, "\n");

        size_t tamArqOne = strlen(arquivoEnvioOne);
        size_t envioOne = fwrite(arquivoEnvioOne, 1, tamArqOne-1, arquivo);

        size_t tamArqTwo = strlen(arquivoEnvioTwo);
        size_t envioTwo = fwrite(arquivoEnvioTwo, 1, tamArqTwo, arquivo);

        if(envioOne != tamArqOne && envioTwo != tamArqTwo) {
            printf("Erro no envio da mensagem!\n");
        } else {
            printf("Mensagem enviada com sucesso\n");
        }
    }

    fclose(arquivo);

    return 0;
}

void removeWordWrap( char* mens ) {
    mens[strcspn(mens, "\n")] = '\0';
}

void criptografarSenha( char mens[50], char* mensCript, char guia[4] ) {
    int x;
    size_t tamMsg = strlen(mens);
    size_t tamGuia = strlen(guia);
    unsigned int interval[tamGuia];

    for( x = 0 ; x < tamGuia ; x++ ) {
        interval[x] = guia[x] - 96;
    }

    int aux = 0;
    for( x = 0 ; x < tamMsg ; x++ ) {
        unsigned int word = mens[x];
        char newWord = word + interval[aux];
        if(newWord > 122) newWord -= 57;
        mensCript[x] = newWord;
        aux++;
        if(aux > 2) aux = 0;
    }
}