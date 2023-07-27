#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// chave guia (abc)
// mensagem

void removeWordWrap( char* word );
void criptografarMensagem( char* mens, char guia[4] );

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

    char mensagem[50];
    char chaveGuia[4];
    int chase;
    printf("What do you wanna do? \n[01] Cript \n[02] Uncript\n");
    scanf("%i", &chase);

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif

    if(chase == 1) {
        printf("Escreva a sua mensagem para ser criptografado: (Sem acentuação) \n");
        getchar();
        fgets(mensagem, sizeof(mensagem), stdin);
        removeWordWrap(mensagem);

        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #else
            system("clear");
        #endif

        printf("Defina uma palavra guia agora, nas seguintes condições: \n01.Toda minuscula \n02.De a até z. \n03.Contenha no máximo 3 caracteres. \n04.Sem sinais ou acentução\n");
        fgets(chaveGuia, sizeof(chaveGuia), stdin);
        // removeWordWrap(chaveGuia);
        // printf("Strlen: %zu Sizeof: %zu S: %s\n", strlen(chaveGuia), sizeof(chaveGuia), chaveGuia);

        criptografarMensagem(mensagem, chaveGuia);
        // printf("S: %s Size: %zu Len: %zu\n", mensagem, sizeof(mensagem), strlen(mensagem));
        char mensagemCriptografada[strlen(mensagem)];
        strcpy(mensagemCriptografada, mensagem);
        // printf("Size: %zu Len: %zu SMC: %s SM: %s\n", sizeof(mensagemCriptografada), strlen(mensagemCriptografada), mensagemCriptografada, mensagem);

        char arquivoEnvio[100];
        strcat(arquivoEnvio, "Mensagem Criptografada: ");
        strcat(arquivoEnvio, mensagemCriptografada);
        strcat(arquivoEnvio, "\nChave-guia: ");
        strcat(arquivoEnvio, chaveGuia);
        strcat(arquivoEnvio, "\n\n\n");

        size_t TamArq = strlen(arquivoEnvio);
        size_t enviado = fwrite(arquivoEnvio, 1, TamArq, arquivo);

        if(enviado != TamArq) {
            printf("Erro no envio da mensagem ao arquivo!\n");
        } else {
            printf("Mensagem enviada ao arquivo com sucesso!\n");
        }
    }

    fclose(arquivo);

    return 0;
}

void removeWordWrap( char* word ) {
    word[strcspn(word, "\n")] = '\0';
}

void criptografarMensagem( char* mens, char guia[4] ) {
    int x;
    size_t tamGUIA = strlen(guia);
    unsigned int interval[tamGUIA];
    for( x = 0 ; x < tamGUIA; x++ ) {
        interval[x] = guia[x] - 96;
    }

    size_t tamMSG = strlen(mens);
    int aux = 0;
    for( x = 0 ; x < tamMSG ; x++ ) {
        const unsigned word = mens[x];
        unsigned int newWord = newWord = word + interval[aux];;
        if(word == 32) newWord = 35;

        if(newWord > 122) newWord -= 57;

        if(newWord > 90 && newWord < 97) newWord += (97 - newWord);
        mens[x] = newWord;
        aux++;
        if(aux > 2) aux = 0;
    }
}