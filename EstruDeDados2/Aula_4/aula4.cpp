
// int main(){
//    cout << "ola,mundo!" << endl;
//    return 0;
// }
//Aula 25/04/2025
/*Arvore bineraria cheia = completa. joga-se todos os elementos a 
o mais possivel Tarefa de casa: exemplo de aplicação para utilizar 
heaps binarios. É usado para filas de prioridades.
-- HEAPS MAXIMO: O no pai é maior ou igual que seus nos filhos
-- HEAPS MINIMO : O no pai é menor que os pais filhos
-- Posso fazer de um voo com prioridades.*/

#include <iostream>
using namespace std;

struct Arv {
    char item;
    Arv* esq;
    Arv* dir;

    Arv(char i, Arv* e = nullptr, Arv* d = nullptr) : item(i), esq(e), dir(d) {}
};

Arv* arv(Arv* esq, char item, Arv* dir) {
    return new Arv(item, esq, dir);
}

// Encontrar o menor elemento (mais à esquerda)
Arv* encontrarMin(Arv* A) {
    if (A == nullptr) return nullptr;
    while (A->esq != nullptr)
        A = A->esq;
    return A;
}

// Encontrar o maior elemento (mais à direita)
Arv* encontrarMax(Arv* A) {
    if (A == nullptr) return nullptr;
    while (A->dir != nullptr)
        A = A->dir;
    return A;
}

Arv* removerMax(Arv* A) {
    if (A == nullptr) return nullptr;

    if (A->dir == nullptr) {
        Arv* temp = A->esq; // Salva o filho esquerdo
        delete A;           // Remove o nó máximo
        return temp;        // Retorna novo nó raiz ajustado
    }

    A->dir = removerMax(A->dir); // Continua a busca pelo maior
    return A;
}

int main() {
    Arv* A = arv(arv(arv(nullptr, '1', nullptr), '2', arv(nullptr, '3', nullptr)),
                 '4',
                 arv(arv(nullptr, '5', nullptr), '6', nullptr));

    Arv* B = arv(arv(arv(nullptr, '7', nullptr), '8', arv(nullptr, '9', nullptr)),
                 '2',
                 arv(arv(nullptr, '5', nullptr), '6', nullptr));

    Arv* R = A;

    int opcao;
    char valor;

    do {
        cout << "\n--- MENU ---\n";
        cout << "Arvore atual: " << ((R == A) ? "A" : "B") << endl;
        cout << "1. MAX\n";
        cout << "2. MIN\n";
        cout << "3. REMOVER MINIMO\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                cout << "Maximo: " << encontrarMax(R)->item << endl;
                break;
            case 2:
                cout << "Minimo: " << encontrarMin(R)->item << endl;
                break;
            case 3:
                cout << "Removendo maximo: " << removerMax(R)->item << endl;
                break;
            
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }

    } while(opcao != 0);

    return 0;
}
