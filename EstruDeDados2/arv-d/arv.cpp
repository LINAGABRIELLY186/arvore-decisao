#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char texto[100];
    struct No* sim;
    struct No* nao;
} No;

No* criarNo(const char* texto) {
    No* novo = (No*) malloc(sizeof(No));
    strcpy(novo->texto, texto);
    novo->sim = NULL;
    novo->nao = NULL;
    return novo;
}

int perguntaSimNao(const char* texto) {
    char resposta[10];
    while (1) {
        printf("%s (sim/nao): ", texto);
        scanf("%9s", resposta);
        if (strcmp(resposta, "sim") == 0) return 1;
        else if (strcmp(resposta, "nao") == 0) return 0;
        else printf("\033[31mResposta invalida! Digite 'sim' ou 'nao'.\033[31m\n");
    }
}

void percorrerArvore(No* no) {
    if (!no) return;

    if (no->sim == NULL && no->nao == NULL) {
        printf("\n\033[32m🍕 Sugerimos: %s\033[0m\n", no->texto);
        return;
    }

    int resposta = perguntaSimNao(no->texto);
    if (resposta == 1)
        percorrerArvore(no->sim);
    else
        percorrerArvore(no->nao);
}

No* criarArvorePizza() {
    No* pizzaDoce = criarNo("Romeu e Julieta🧀");
    No* pizzaCarneSol = criarNo("Maria Bonita🥩");
    No* pizzaFrangoCatupiry = criarNo("Frango com Catupiry🐔");
    No* pizzaCalabresa = criarNo("Calabresa🍖");

    No* gostaFrango = criarNo("	\033[33mPrefere pizza com frango?	\033[33m");
    gostaFrango->sim = pizzaFrangoCatupiry;
    gostaFrango->nao = pizzaCalabresa;

    No* gostaCarneSol = criarNo("\033[34mGosta de carne de sol?\033[34m");
    gostaCarneSol->sim = pizzaCarneSol;
    gostaCarneSol->nao = gostaFrango;

    No* querDoce = criarNo("\033[35mQuer pizza doce?\033[35m");
    querDoce->sim = pizzaDoce;
    querDoce->nao = gostaCarneSol;

    return querDoce;
}

int main() {
    No* raiz = criarArvorePizza();

    printf("\033[33m🍽 Árvore de decisão para escolha de pizza 🍽\033[33m\n");
    percorrerArvore(raiz);

    return 0;
}
