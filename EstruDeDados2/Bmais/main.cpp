#include "cliente.hpp"
#include "bmais.hpp"

int rrnRaiz = -1;

void imprimirArvore(int rrn, int nivel = 0) {
    if (rrn == -1) return;
    NoBMais no = lerNo(rrn);

    cout << string(nivel * 4, ' ') << (no.folha ? "[Folha] " : "[Interno] ");
    for (int i = 0; i < no.numChaves; i++) {
        cout << no.chaves[i] << " ";
    }
    cout << "\n";

    if (!no.folha) {
        for (int i = 0; i <= no.numChaves; i++) {
            imprimirArvore(no.filhos[i], nivel + 1);
        }
    }
}

void dividirFolha(int rrnAntigo, NoBMais &folhaAntiga, int novaChave, int rrnCliente) {
    NoBMais novaFolha; // nova folha criada

    int todasChaves[ORDEM];
    int todosRRNs[ORDEM];

    for (int i = 0; i < ORDEM - 1; i++) {
        todasChaves[i] = folhaAntiga.chaves[i];
        todosRRNs[i] = folhaAntiga.rrnsClientes[i];
    }

    int i = ORDEM - 2;
    while (i >= 0 && novaChave < todasChaves[i]) {
        todasChaves[i + 1] = todasChaves[i];
        todosRRNs[i + 1] = todosRRNs[i];
        i--;
    }
    todasChaves[i + 1] = novaChave;
    todosRRNs[i + 1] = rrnCliente;

    folhaAntiga.numChaves = ORDEM / 2;
    novaFolha.numChaves = ORDEM - (ORDEM / 2);

    for (int j = 0; j < folhaAntiga.numChaves; j++) {
        folhaAntiga.chaves[j] = todasChaves[j];
        folhaAntiga.rrnsClientes[j] = todosRRNs[j];
    }

    for (int j = 0; j < novaFolha.numChaves; j++) {
        novaFolha.chaves[j] = todasChaves[j + folhaAntiga.numChaves];
        novaFolha.rrnsClientes[j] = todosRRNs[j + folhaAntiga.numChaves];
    }

    novaFolha.proximaFolha = folhaAntiga.proximaFolha;
    int rrnNova = gravarNo(novaFolha);
    folhaAntiga.proximaFolha = rrnNova;
    atualizarNo(rrnAntigo, folhaAntiga);

    cout << "\nFolha dividida!\n";
    cout << " - Chaves folha antiga: ";
    for (int i = 0; i < folhaAntiga.numChaves; i++) cout << folhaAntiga.chaves[i] << " ";
    cout << "\n - Chaves nova folha: ";
    for (int i = 0; i < novaFolha.numChaves; i++) cout << novaFolha.chaves[i] << " ";
    cout << "\n - Chave promovida: " << novaFolha.chaves[0] << "\n";
}

void cadastrarCliente() {
    Cliente c;
    cout << "Digite o código do cliente: ";
    cin >> c.codigo;
    cin.ignore();
    cout << "Digite o nome do cliente: ";
    cin.getline(c.nome, 50);

    int rrnCliente = gravarCliente(c);

    if (rrnRaiz == -1) {
        NoBMais folha;
        folha.numChaves = 1;
        folha.chaves[0] = c.codigo;
        folha.rrnsClientes[0] = rrnCliente;
        rrnRaiz = gravarNo(folha);
        cout << "Cliente inserido em nova folha. RRN raiz: " << rrnRaiz << "\n";
        imprimirArvore(rrnRaiz);
        return;
    }

    NoBMais folha = lerNo(rrnRaiz);

    if (folha.numChaves < ORDEM - 1) {
        int i = folha.numChaves - 1;
        while (i >= 0 && c.codigo < folha.chaves[i]) {
            folha.chaves[i + 1] = folha.chaves[i];
            folha.rrnsClientes[i + 1] = folha.rrnsClientes[i];
            i--;
        }
        folha.chaves[i + 1] = c.codigo;
        folha.rrnsClientes[i + 1] = rrnCliente;
        folha.numChaves++;
        atualizarNo(rrnRaiz, folha);
        cout << "Cliente inserido na folha existente.\n";
    } else {
        dividirFolha(rrnRaiz, folha, c.codigo, rrnCliente);
    }

    cout << "\nEstado atual da árvore B+:\n";
    imprimirArvore(rrnRaiz);
}

int buscar(int rrn, int chave) {
    if (rrn == -1) return -1;
    NoBMais no = lerNo(rrn);

    cout << "\nBuscando chave " << chave << " no nó com chaves: ";
    for (int i = 0; i < no.numChaves; i++) cout << no.chaves[i] << " ";
    cout << "\n";

    int i = 0;
    while (i < no.numChaves && chave > no.chaves[i]) i++;
    if (no.folha) {
        if (i < no.numChaves && no.chaves[i] == chave)
            return no.rrnsClientes[i];
        return -1;
    }
    return buscar(no.filhos[i], chave);
}

void listarClientesOrdenado() {
    if (rrnRaiz == -1) return;
    int rrn = rrnRaiz;
    NoBMais no = lerNo(rrn);
    while (!no.folha) {
        rrn = no.filhos[0];
        no = lerNo(rrn);
    }
    while (rrn != -1) {
        no = lerNo(rrn);
        for (int i = 0; i < no.numChaves; i++) {
            imprimirCliente(no.rrnsClientes[i]);
        }
        rrn = no.proximaFolha;
    }
}

int main() {
    int opcao;
    do {
        cout << "\n===== Sistema de Clientes com Árvore B+ =====\n";
        cout << "1 - Cadastrar Cliente\n";
        cout << "2 - Listar Clientes\n";
        cout << "3 - Buscar Cliente Por Codigo\n";
        cout << "4 - Listar Clientes Ordenados\n";
        cout << "5 - Mostrar Árvore B+\n";
        cout << "0 - Sair\n";
        cout << "Opção: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientesOrdenado(); break;
            case 3: {
                int codigo;
                cout << "Digite o código do cliente a buscar: ";
                cin >> codigo;
                int rrn = buscar(rrnRaiz, codigo);
                if (rrn != -1) {
                    imprimirCliente(rrn);
                } else {
                    cout << "Cliente não encontrado.\n";
                }
                break;
            }
            case 4: listarClientesOrdenado(); break;
            case 5: imprimirArvore(rrnRaiz); break;
            case 0: cout << "Encerrando...\n"; break;
            default: cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
    return 0;
}
