#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// 🔹 Constantes
#define NUM_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 30

// 🔹 Estrutura principal
typedef struct {
    char nome[MAX_NOME];
    char corExercito[MAX_COR];
    int numTropas;
    int conquistado; // 0 = não, 1 = sim
} Territorio;

// 🔹 Protótipos
void cadastrarTerritorios(Territorio *mapa, int qtd);
void exibirMapa(const Territorio *mapa, int qtd);
void simularAtaque(Territorio *mapa, int qtd);
void menuPrincipal(Territorio *mapa, int qtd, const char *missao);
void verificarMissao(const Territorio *mapa, int qtd, const char *missao);
const char* gerarMissao();

// 🔹 Funções utilitárias
int apenasLetras(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// 🔹 Cadastra territórios
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

        // Nome
        do {
            printf("Nome: ");
            fgets(mapa[i].nome, MAX_NOME, stdin);
            mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;
            if (!apenasLetras(mapa[i].nome))
                printf("⚠️  Use apenas letras.\n");
        } while (!apenasLetras(mapa[i].nome));

        // Cor
        do {
            printf("Cor do Exército: ");
            fgets(mapa[i].corExercito, MAX_COR, stdin);
            mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;
            if (!apenasLetras(mapa[i].corExercito))
                printf("⚠️  Use apenas letras.\n");
        } while (!apenasLetras(mapa[i].corExercito));

        // Tropas
        do {
            printf("Número de Tropas: ");
            scanf("%d", &mapa[i].numTropas);
            getchar();
            if (mapa[i].numTropas <= 0)
                printf("⚠️  Deve haver pelo menos 1 tropa.\n");
        } while (mapa[i].numTropas <= 0);

        mapa[i].conquistado = 0;
    }
}

// 🔹 Exibe o estado do mapa
void exibirMapa(const Territorio *mapa, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].corExercito);
        printf("Tropas: %d\n", mapa[i].numTropas);
        printf("Conquistado: %s\n", mapa[i].conquistado ? "✅ Sim" : "❌ Não");
        printf("----------------------------\n");
    }
}

// 🔹 Simula um ataque entre territórios
void simularAtaque(Territorio *mapa, int qtd) {
    int atacante, defensor;
    srand(time(NULL));

    printf("\nEscolha o território atacante (1-%d): ", qtd);
    scanf("%d", &atacante);
    getchar();

    printf("Escolha o território defensor (1-%d): ", qtd);
    scanf("%d", &defensor);
    getchar();

    if (atacante < 1 || atacante > qtd || defensor < 1 || defensor > qtd || atacante == defensor) {
        printf("⚠️  Escolha inválida!\n");
        return;
    }

    atacante--; defensor--;

    if (mapa[atacante].numTropas <= 1) {
        printf("⚠️  O atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    // 🎲 Rolagem dos dados
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n🎲 Dado Ataque: %d | 🎯 Dado Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        mapa[defensor].numTropas--;
        printf("✅ Ataque bem-sucedido! O defensor perdeu 1 tropa.\n");
        if (mapa[defensor].numTropas <= 0) {
            mapa[defensor].conquistado = 1;
            printf("🏆 O território '%s' foi conquistado!\n", mapa[defensor].nome);
        }
    } else {
        mapa[atacante].numTropas--;
        printf("❌ Ataque falhou! O atacante perdeu 1 tropa.\n");
    }
}

// 🔹 Gera uma missão aleatória
const char* gerarMissao() {
    srand(time(NULL));
    int tipo = rand() % 2;
    if (tipo == 0)
        return "Destruir o exército Verde";
    else
        return "Conquistar 3 territórios";
}

// 🔹 Verifica cumprimento da missão
void verificarMissao(const Territorio *mapa, int qtd, const char *missao) {
    if (strcmp(missao, "Destruir o exército Verde") == 0) {
        for (int i = 0; i < qtd; i++) {
            if (strcasecmp(mapa[i].corExercito, "Verde") == 0 && mapa[i].numTropas > 0) {
                printf("🚫 Missão ainda não cumprida! Exército Verde ainda resiste.\n");
                return;
            }
        }
        printf("🏆 Missão cumprida! Todos os exércitos verdes foram derrotados!\n");
    } else if (strcmp(missao, "Conquistar 3 territórios") == 0) {
        int conquistas = 0;
        for (int i = 0; i < qtd; i++) {
            if (mapa[i].conquistado)
                conquistas++;
        }
        if (conquistas >= 3)
            printf("🏆 Missão cumprida! Você conquistou 3 territórios!\n");
        else
            printf("🚫 Ainda faltam %d territórios para completar a missão.\n", 3 - conquistas);
    }
}

// 🔹 Menu principal
void menuPrincipal(Territorio *mapa, int qtd, const char *missao) {
    int opcao;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Atacar\n");
        printf("2. Verificar Missão\n");
        printf("3. Exibir Mapa\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: simularAtaque(mapa, qtd); break;
            case 2: verificarMissao(mapa, qtd, missao); break;
            case 3: exibirMapa(mapa, qtd); break;
            case 0: printf("👋 Saindo do jogo...\n"); break;
            default: printf("⚠️  Opção inválida!\n");
        }
    } while (opcao != 0);
}

// 🔹 Função principal
int main() {
    Territorio *mapa = (Territorio*) calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== 🗺️ JOGO DE TERRITÓRIOS ===\n");
    cadastrarTerritorios(mapa, NUM_TERRITORIOS);

    const char *missao = gerarMissao();
    printf("\n🎯 Sua Missão: %s\n", missao);

    menuPrincipal(mapa, NUM_TERRITORIOS, missao);

    free(mapa);
    return 0;
}
