#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_TERRITORIOS 5

struct Territorio {
    char nome[50];
    char corExercito[30];
    int numTropas;
};

// Função para validar apenas letras e espaços
int apenasLetras(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ') {
            return 0; // contém caractere que não é letra
        }
    }
    return 1; // só tem letras (e espaços)
}

int main() {
    struct Territorio mapa[NUM_TERRITORIOS];
    char entrada[20];
    int i, valido;

    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("=== Cadastro do Território %d ===\n", i + 1);

        // Nome
        do {
            printf("Nome: ");
            fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
            mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;
            if (!apenasLetras(mapa[i].nome))
                printf("⚠️  Use apenas letras.\n");
        } while (!apenasLetras(mapa[i].nome));

        // Cor do Exército
        do {
            printf("Cor do Exército: ");
            fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
            mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;
            if (!apenasLetras(mapa[i].corExercito))
                printf("⚠️  Use apenas letras.\n");
        } while (!apenasLetras(mapa[i].corExercito));

        // Número de Tropas — aceita apenas números
        do {
            printf("Número de Tropas: ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = 0;

            valido = 1;
            for (int j = 0; entrada[j] != '\0'; j++) {
                if (!isdigit((unsigned char)entrada[j])) {
                    valido = 0;
                    break;
                }
            }

            if (!valido || strlen(entrada) == 0)
                printf("⚠️  Digite apenas números válidos!\n");

        } while (!valido);

        mapa[i].numTropas = atoi(entrada); // converte para int
        printf("\n");
    }

    // Exibir estado atual
    printf("\n=== Estado Atual do Mapa ===\n");
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].corExercito);
        printf("Número de Tropas: %d\n", mapa[i].numTropas);
        printf("----------------------------\n");
    }

    return 0;
}
