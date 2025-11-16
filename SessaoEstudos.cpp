#include "SessaoEstudo.h"
#include <iostream>
#include <ctime>

// construtor default
SessaoEstudo::SessaoEstudo()
    : segundos(0), estadoSessao(0), tempoInicial(0),
      disciplina(""), etiqueta(""), descricao("") {}

// construtor parametrizado
SessaoEstudo::SessaoEstudo(long long int segundos, int estadoSessao, std::string disciplina, std::string etiqueta, std::string descricao)
    :segundos(segundos), estadoSessao(estadoSessao), disciplina(disciplina), etiqueta(etiqueta), descricao(descricao), tempoInicial(0) {}

// métodos privados para gerenciar estados
void SessaoEstudo::sessaoiniciada() {
    std::cout << "Sessão iniciada para: " << disciplina << std::endl;
}

void SessaoEstudo::sessaopausada() {
    std::cout << "Sessão pausada" << std::endl;
}

void SessaoEstudo::sessaofinalizada() {
    std::cout << "Sessão finalizada. Tempo total: " << segundos << " segundos" << std::endl;
}

// Ggrenciar estado
void SessaoEstudo::gerenciar() {
    switch(estadoSessao) {
        case 0:
            std::cout << "Sessão parada" << std::endl;
            break;
        case 1:
            std::cout << "Sessão em andamento..." << std::endl;
            break;
        case 2:
            std::cout << "Sessão pausada" << std::endl;
            break;
        default:
            std::cout << "Estado inválido" << std::endl;
    }
}

// iniciar cronômetro
void SessaoEstudo::iniciar() {
    if (estadoSessao == 0) {
        tempoInicial = time(nullptr);
        estadoSessao = 1;
        sessaoiniciada();
    }
}

// pausar cronômetro
void SessaoEstudo::pausar() {
    if (estadoSessao == 1) {
        long long int tempoAtual = time(nullptr);
        segundos += (tempoAtual - tempoInicial);
        estadoSessao = 2;
        sessaopausada();
    }
}

// resetar cronômetro
void SessaoEstudo::resetar() {
    segundos = 0;
    tempoInicial = 0;
    estadoSessao = 0;
    std::cout << "Sessão resetada" << std::endl;
}

// continuar sessão pausada
void SessaoEstudo::continuar() {
    if (estadoSessao == 2) {
        tempoInicial = time(nullptr);
        estadoSessao = 1;
        std::cout << "Sessão retomada" << std::endl;
    }
}

// armazenar metadados
void SessaoEstudo::armazenar() {
    if (estadoSessao == 1) {
        pausar();
    }
    sessaofinalizada();
    estadoSessao = 0;
}

// getters
long long int SessaoEstudo::getSegundos() {
    // Se está rodando, adiciona o tempo decorrido
    if (estadoSessao == 1) {
        long long int tempoAtual = time(nullptr);
        return segundos + (tempoAtual - tempoInicial);
    }
    return segundos;
}

std::string SessaoEstudo::getDisciplina() {
    return disciplina;
}

std::string SessaoEstudo::getEtiqueta() {
    return etiqueta;
}

std::string SessaoEstudo::getDescricao() {
    return descricao;
}