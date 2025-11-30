#include "Usuario.h"
#include <iostream>
#include <string>

Usuario::Usuario(std::string nome)
    : moedas(0), pontos(0),
      nivel(1), badge("NULL") {
        this->nome = nome;
    }


Usuario::Usuario(std::string nome, int nivel, int pontos, int moedas, std::string badge) {
    this->nome = nome;
    this->nivel = nivel;
    this->pontos = pontos;
    this->moedas = moedas;
    this->badge = badge;
}


int Usuario::getMoedas() const {
    return this->moedas;
}

std::string Usuario::getNome() const {
    return this->nomeDeUsuario;
}

void Usuario::setNome(const std::string& novoNome) {
    if (!novoNome.empty()) {
        this->nomeDeUsuario = novoNome;
    }
}

Inventario& Usuario::getInventario() {
    return this->inventario;
}

HistoricoEstudos& Usuario::getHistorico() {
    return this->historico;
}


