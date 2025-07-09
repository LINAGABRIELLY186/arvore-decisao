//heaps

#include <iostream>
using namespace std;

// Definição da estrutura do nó
struct Node {
    int prioridade;
    string tarefa;
    Node* esquerda;
    Node* direita;

    Node(int p, string t) : prioridade(p), tarefa(t), esquerda(nullptr), direita(nullptr) {}
};

// Função para inserir elementos na árvore binária
Node* inserir(Node* raiz, int prioridade, string tarefa) {
    if (!raiz) return new Node(prioridade, tarefa);

    if (prioridade < raiz->prioridade)
        raiz->esquerda = inserir(raiz->esquerda, prioridade, tarefa);
    else
        raiz->direita = inserir(raiz->direita, prioridade, tarefa);

    return raiz;
}

// Função para encontrar a tarefa com maior prioridade (nó mais à direita)
Node* encontrarMax(Node* raiz) {
    while (raiz && raiz->direita)
        raiz = raiz->direita;
    return raiz;
}

// Função para remover a tarefa de maior prioridade
Node* removerMax(Node* raiz) {
    if (!raiz) return raiz;
    if (!raiz->direita) {
        Node* temp = raiz->esquerda;
        delete raiz;
        return temp;
    }
    raiz->direita = removerMax(raiz->direita);
    return raiz;
}

// Função para exibir a árvore em ordem crescente de prioridade
void imprimirEmOrdem(Node* raiz) {
    if (!raiz) return;
    imprimirEmOrdem(raiz->esquerda);
    cout << "Tarefa: " << raiz->tarefa << " (Prioridade " << raiz->prioridade << ")\n";
    imprimirEmOrdem(raiz->direita);
}

int main() {
    Node* raiz = nullptr;

    // Adicionando tarefas
    raiz = inserir(raiz, 3, "Enviar relatório");
    raiz = inserir(raiz, 5, "Atender emergência médica");
    raiz = inserir(raiz, 1, "Atualizar software");
    raiz = inserir(raiz, 4, "Realizar backup");

    cout << "Tarefas ordenadas por prioridade:\n";
    imprimirEmOrdem(raiz);

    // Removendo a tarefa de maior prioridade
    cout << "\nRemovendo a tarefa de maior prioridade...\n";
    raiz = removerMax(raiz);
    imprimirEmOrdem(raiz);

    return 0;
}
