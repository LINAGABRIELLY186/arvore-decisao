#ifndef BMAIS_HPP
#define BMAIS_HPP

#include <iostream>
#include <fstream>
using namespace std;

#define ORDEM 4

struct NoBMais {
    int folha;
    int numChaves;
    int chaves[ORDEM - 1];
    int filhos[ORDEM];
    int rrnsClientes[ORDEM - 1];
    int proximaFolha;

    NoBMais(int ehFolha = 1) {
        folha = ehFolha;
        numChaves = 0;
        proximaFolha = -1;
        for (int i = 0; i < ORDEM - 1; i++) {
            chaves[i] = -1;
            rrnsClientes[i] = -1;
        }
        for (int i = 0; i < ORDEM; i++) {
            filhos[i] = -1;
        }
    }
};

int gravarNo(NoBMais &no) {
    ofstream arq("indice.dat", ios::binary | ios::app);
    if (!arq) {
        cerr << "Erro ao abrir indice.dat\n";
        exit(1);
    }

    arq.seekp(0, ios::end);
    int rrn = arq.tellp() / sizeof(NoBMais);
    arq.write(reinterpret_cast<char*>(&no), sizeof(NoBMais));
    arq.close();
    return rrn;
}

NoBMais lerNo(int rrn) {
    ifstream arq("indice.dat", ios::binary);
    if (!arq) {
        cerr << "Erro ao abrir indice.dat\n";
        exit(1);
    }

    arq.seekg(rrn * sizeof(NoBMais), ios::beg);
    NoBMais no;
    arq.read(reinterpret_cast<char*>(&no), sizeof(NoBMais));
    arq.close();
    return no;
}

void atualizarNo(int rrn, const NoBMais &no) {
    fstream arq("indice.dat", ios::binary | ios::in | ios::out);
    if (!arq) {
        cerr << "Erro ao abrir indice.dat para atualizar\n";
        exit(1);
    }

    arq.seekp(rrn * sizeof(NoBMais), ios::beg);
    arq.write(reinterpret_cast<const char*>(&no), sizeof(NoBMais));
    arq.close();
}


#endif
