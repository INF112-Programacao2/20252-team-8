#include "Usuario.h"
#include <iostream>

Usuario::Usuario()
    : nomeDeUsuario("Jogador"),
      moedas(0),
      pontos(0),
      nivel(1),
    {}


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


