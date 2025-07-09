#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Cliente {
    int codigo;
    char nome[50];
};

int gravarCliente(const Cliente &c) {
    ofstream arq("clientes.dat", ios::binary | ios::app);
    if (!arq) {
        cout << "Erro ao abrir clientes.dat\n";
        return -1;
    }
    arq.seekp(0, ios::end);
    int pos = arq.tellp();
    arq.write((char*)&c, sizeof(Cliente));
    arq.close();
    return pos / sizeof(Cliente); // RRN do cliente
}

void imprimirCliente(int rrn) {
    ifstream arq("clientes.dat", ios::binary);
    if (!arq) {
        cout << "Erro ao abrir clientes.dat\n";
        return;
    }
    arq.seekg(rrn * sizeof(Cliente));
    Cliente c;
    arq.read((char*)&c, sizeof(Cliente));
    cout << "Cliente Código: " << c.codigo << ", Nome: " << c.nome << "\n";
    arq.close();
}


#endif
