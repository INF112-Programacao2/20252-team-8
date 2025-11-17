#ifndef MUSICA_H
#define MUSICA_H

#include <string>

struct Musica {
    std::string nome;
    std::string arquivo; // Caminho para o .mp3
    int valor;
    bool comprada;

    // Construtor para facilitar a criação
    Musica(std::string n, std::string a, int v)
        : nome(n), arquivo(a), valor(v), comprada(false) {}
};

#endif // MUSICA_H