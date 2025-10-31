#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define NUM_TERRITORIOS 5

struct Territorio {
    char nome[50];
    char corExercito[30];
    int numTropas;
};

// ------------------------------
// Funções auxiliares
// ------------------------------
int apenasLetras(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// Cadastra todos os territórios dinamicamente
void cadastrarTerritorios(struct Territorio *mapa, int n) {
    char entrada[20];
    int valido;

    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

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

        // Tropas — valida apenas números
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

        mapa[i].numTropas = atoi(entrada);
    }
}

// Exibe todos os territórios
void exibirMapa(struct Territorio *mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].corExercito);
        printf("Número de Tropas: %d\n", mapa[i].numTropas);
        printf("----------------------------\n");
    }
}

// Simula um ataque entre dois territórios
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    if (atacante->numTropas <= 1) {
        printf("⚠️  O território atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    // Gera dados de batalha aleatórios
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n🎲 Ataque: %s (%d tropas)\n", atacante->nome, atacante->numTropas);
    printf("🎯 Defesa: %s (%d tropas)\n", defensor->nome, defensor->numTropas);
    printf("Dados -> Ataque: %d | Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->numTropas--;

        if (defensor->numTropas <= 0) {
            printf("💥 %s conquistou o território %s!\n", atacante->nome, defensor->nome);
            defensor->numTropas = 1; // transfere uma tropa mínima
            strcpy(defensor->corExercito, atacante->corExercito);
        } else {
            printf("⚔️  O defensor perdeu 1 tropa!\n");
        }
    } else {
        atacante->numTropas--;
        printf("🛡️  O ataque falhou, o atacante perdeu 1 tropa!\n");
    }
}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    // Alocação dinâmica de memória para os territórios
    struct Territorio *mapa = (struct Territorio *)calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, NUM_TERRITORIOS);
    exibirMapa(mapa, NUM_TERRITORIOS);

    int opcao, atq, def;

    // Loop de ataques
    do {
        printf("\n=== Fase de Ataque ===\n");
        exibirMapa(mapa, NUM_TERRITORIOS);

        printf("Escolha o número do território atacante (0 para sair): ");
        scanf("%d", &atq);
        getchar(); // limpa buffer

        if (atq == 0) break;

        printf("Escolha o número do território defensor: ");
        scanf("%d", &def);
        getchar();

        if (atq < 1 || atq > NUM_TERRITORIOS || def < 1 || def > NUM_TERRITORIOS || atq == def) {
            printf("⚠️  Escolha inválida!\n");
            continue;
        }

        simularAtaque(&mapa[atq - 1], &mapa[def - 1]);

    } while (1);

    // Liberar memória
    free(mapa);
    printf("\nJogo encerrado. Memória liberada!\n");
    return 0;
}
