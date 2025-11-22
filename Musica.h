#ifndef MUSICA_H
#define MUSICA_H
#include <string>

struct Musica {
    std::string nome;
    std::string arquivo;
    int valor;
    bool comprada;

    // Construtor simples
    Musica(std::string n, std::string a, int v) {
        nome = n;
        arquivo = a;
        valor = v;
        comprada = false; // Começa sempre como não comprada
    }
};
#endif