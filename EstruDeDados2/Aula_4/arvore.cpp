#include <stdio.h>
#include <stdlib.h>
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

void emordem(Arv* A) {
    if (A != nullptr) {
        emordem(A->esq);
        cout << A->item << " ";
        emordem(A->dir);
    }
}

void preordem(Arv* A){
    if (A == nullptr) return;
    cout << A->item << " ";
    preordem(A->esq);
    preordem(A->dir);   
}

void posordem(Arv* A){
    if (A == nullptr) return;
    posordem(A->esq);
    posordem(A->dir);
    cout << A->item << " ";
}

void destroi(Arv* A){
    if(A == nullptr) return;
    destroi(A->esq);
    destroi(A->dir);
    delete A;
}

//Crie a função nos (A), que devolve o total de nós na árvore binária A
//base de recursão: se A == NULL, devolve 0
//passo recursivo: devolve 1 + nos(A->esq) + nos(A->dir)
int nos(Arv* A){
    if (A == nullptr) return 0;
    return 1 + nos(A->esq) + nos(A->dir);  
}


// Crie a função folhas (A), que devolve o total de folhas na árvore binária A
// base de recursão: se A == NULL, devolve 0
// passo recursivo: se A->esq == NULL e A->dir == NULL, devolve 1
// caso contrário, devolve folhas(A->esq) + folhas(A->dir)
int folhas(Arv* A){
    if (A == nullptr) return 0;
    if (A->esq == nullptr && A->dir == nullptr) return 1;
    return folhas(A->esq) + folhas(A->dir);
}



int altura(Arv* A) {
    if (A == nullptr) return 0;
    int alturaEsq = altura(A->esq);
    int alturaDir = altura(A->dir);
    return 1 + max(alturaEsq, alturaDir);
}

bool tem(Arv* A, char x) {
    if (A == nullptr) return false;
    if (A->item == x) return true;
    return tem(A->esq, x) || tem(A->dir, x);
}

bool eb(Arv* A) {
    if (A == nullptr) return true; 
    if (A->esq == nullptr && A->dir == nullptr) return true; 
    if (A->esq != nullptr && A->dir != nullptr) return eb(A->esq) && eb(A->dir); 
    return false; 
}

bool igual(Arv* A, Arv* B) {
    if (A == nullptr && B == nullptr) return true; 
    if (A != nullptr && B != nullptr) {
        return (A->item == B->item) && igual(A->esq, B->esq) && igual(A->dir, B->dir);
    }
    return false; 
}

void exibe_dec(Arv* A) {
    if (A == nullptr) return;
    exibe_dec(A->dir);
    cout << A->item << " ";
    exibe_dec(A->esq);
}


int main() {
    Arv* A = arv(arv(arv(nullptr, '1', nullptr), '2', arv(nullptr, '3', nullptr)),
                 '4',
                 arv(arv(nullptr, '5', nullptr), '6', nullptr));
                 
    //Arv* A = arv(arv(arv(nullptr, '1', nullptr), '2', arv(nullptr, '3', nullptr)),
    //'4',
    //arv(arv(nullptr, '5', nullptr), '6', nullptr));


    Arv* B = arv(arv(arv(nullptr, '7', nullptr), '8', arv(nullptr, '9', nullptr)),
                 '2',
                 arv(arv(nullptr, '5', nullptr), '6', nullptr));

    Arv* R = A;

    int opcao;
    char valor;

    do {
        cout << "\n--- MENU ---\n";
        cout << "Arvore atual: " << ((R == A) ? "A" : "B") << endl;
        cout << "1. Trocar arvore\n";
        cout << "2. Em ordem\n";
        cout << "3. Pre ordem\n";
        cout << "4. Pos ordem\n";
        cout << "5. Total de nos\n";
        cout << "6. Total de folhas\n";
        cout << "7. Altura da arvore\n";
        cout << "8. Verificar se contem um item\n";
        cout << "9. Verificar se e estritamente binaria\n";
        cout << "10. Verificar se A e B sao iguais\n";
        cout << "11. Exibir decrescente\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                R = (R == A) ? B : A;
                break;
            case 2:
                cout << "Em ordem: ";
                emordem(R);
                cout << endl;
                break;
            case 3:
                cout << "Pre ordem: ";
                preordem(R);
                cout << endl;
                break;
            case 4:
                cout << "Pos ordem: ";
                posordem(R);
                cout << endl;
                break;
            case 5:
                cout << "Total de nos: " << nos(R) << endl;
                break;
            case 6:
                cout << "Total de folhas: " << folhas(R) << endl;
                break;
            case 7:
                cout << "Altura: " << altura(R) << endl;
                break;
            case 8:
                cout << "Digite o valor: ";
                cin >> valor;
                cout << "Tem " << valor << "? " << (tem(R, valor) ? "Sim" : "Nao") << endl;
                break;
            case 9:
                cout << "E estritamente binaria? " << (eb(R) ? "Sim" : "Nao") << endl;
                break;
            case 10:
                cout << "A e B sao iguais? " << (igual(A, B) ? "Sim" : "Nao") << endl;
                break;
            case 11:
                cout << "Exibindo em ordem decrescente: ";
                exibe_dec(R);
                cout << endl;
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }

    } while(opcao != 0);

    destroi(A);
    destroi(B);
    cout << "Arvores destruidas. Encerrando...\n";
    return 0;
}
