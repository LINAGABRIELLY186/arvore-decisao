#include <iostream>
#include <algorithm>
using namespace std;

// Estrutura de um nó da árvore AVL
struct Node {
    int valor;       // Valor armazenado no nó
    Node* esq;       // Ponteiro para o filho esquerdo
    Node* dir;       // Ponteiro para o filho direito
    int altura;      // Altura do nó (usada para balanceamento)
};

// Retorna a altura de um nó, ou 0 se for nulo
int altura(Node* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

// Calcula o fator de balanceamento de um nó
// FB = altura da subárvore esquerda - altura da subárvore direita
int fatorBalanceamento(Node* n) {
    if (n == nullptr) return 0;
    return altura(n->esq) - altura(n->dir);
}

// Atualiza a altura de um nó com base na altura dos seus filhos
void atualizarAltura(Node* n) {
    if (n != nullptr)
        n->altura = 1 + max(altura(n->esq), altura(n->dir));
}

// Rotação simples para a direita
Node* rotacaoDireita(Node* y) {
    cout << "Rotacao simples a direita no no " << y->valor << endl;
    Node* x = y->esq;
    Node* T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

// Rotacao simples para a esquerda
Node* rotacaoEsquerda(Node* x) {
    cout << "Rotacao simples a esquerda no no " << x->valor << endl;
    Node* y = x->dir; // y será a nova raiz da subárvore
    Node* T2 = y->esq; // guarda a subárvore esquerda de y
    y->esq = x; // x vira filho esquerdo de y
    x->dir = T2; // T2 vira filho direito de x
    atualizarAltura(x);
    atualizarAltura(y);
    return y; // retorna novo topo da subárvore
}

// Balanceamento do nó
Node* balancear(Node* n) {
    atualizarAltura(n);
    int fb = fatorBalanceamento(n);

    if (fb > 1 && fatorBalanceamento(n->esq) >= 0)
        return rotacaoDireita(n);

    if (fb < -1 && fatorBalanceamento(n->dir) <= 0)
        return rotacaoEsquerda(n);

    if (fb > 1 && fatorBalanceamento(n->esq) < 0) {
        n->esq = rotacaoEsquerda(n->esq);
        return rotacaoDireita(n);
    }

    if (fb < -1 && fatorBalanceamento(n->dir) > 0) {
        n->dir = rotacaoDireita(n->dir);
        return rotacaoEsquerda(n);
    }

    return n;
}

// Inserção na árvore AVL
Node* inserir(Node* raiz, int valor) {
    if (raiz == nullptr)
        return new Node{valor, nullptr, nullptr, 1};

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    else
        return raiz;

    return balancear(raiz);
}

// Retorna o menor valor da subárvore
Node* minValor(Node* no) {
    Node* atual = no;
    while (atual->esq != nullptr)
        atual = atual->esq;
    return atual;
}

// Remoção na árvore AVL
Node* remover(Node* raiz, int valor) {
    if (!raiz) return raiz;

    if (valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor);
    else {
        if (!raiz->esq || !raiz->dir) {
            Node* temp = raiz->esq ? raiz->esq : raiz->dir;
            if (!temp) {
                temp = raiz;
                raiz = nullptr;
            } else {
                *raiz = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValor(raiz->dir);
            raiz->valor = temp->valor;
            raiz->dir = remover(raiz->dir, temp->valor);
        }
    }

    if (!raiz) return nullptr;

    return balancear(raiz);
}

// Impressão em ordem
void imprimirInOrdem(Node* raiz) {
    if (raiz) {
        imprimirInOrdem(raiz->esq);
        cout << raiz->valor << " ";
        imprimirInOrdem(raiz->dir);
    }
}

// Impressão dos fatores de balanceamento
void imprimirFB(Node* raiz) {
    if (raiz) {
        imprimirFB(raiz->esq);
        cout << "No " << raiz->valor << ": FB = " << fatorBalanceamento(raiz) << endl;
        imprimirFB(raiz->dir);
    }
}

// Cálculo da altura da árvore
int calcularAltura(Node* raiz) {
    return altura(raiz);
}
