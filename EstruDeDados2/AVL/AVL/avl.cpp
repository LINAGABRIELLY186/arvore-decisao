#include "avl.h"


int main() {
    Node* raiz = nullptr;

    cout << "\n--- CASO 1: Insercao com rotacao simples a esquerda ---\n";
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30); // rotação simples

    imprimirInOrdem(raiz);
    cout << "\nFatores:\n"; imprimirFB(raiz);
    cout << "Altura: " << calcularAltura(raiz) << "\n";

    cout << "\n--- CASO 2: Insercao com rotacao dupla a direita ---\n";
    Node* raiz2 = nullptr;
    raiz2 = inserir(raiz2, 30);
    raiz2 = inserir(raiz2, 10);
    raiz2 = inserir(raiz2, 20); // rotação dupla

    imprimirInOrdem(raiz2);
    cout << "\nFatores:\n"; imprimirFB(raiz2);
    cout << "Altura: " << calcularAltura(raiz2) << "\n";

    cout << "\n--- CASO 3: Remocao com rotacao simples a direita ---\n";
    raiz = remover(raiz, 30);

    imprimirInOrdem(raiz);
    cout << "\nFatores:\n"; imprimirFB(raiz);
    cout << "Altura: " << calcularAltura(raiz) << "\n";

    cout << "\n--- CASO 4: Remocao com rotacao dupla a   esquerda ---\n";
    raiz2 = remover(raiz2, 10);

    imprimirInOrdem(raiz2);
    cout << "\nFatores:\n"; imprimirFB(raiz2);
    cout << "Altura: " << calcularAltura(raiz2) << "\n";

    return 0;
}
