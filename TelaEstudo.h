#ifndef TELA_ESTUDO_H
#define TELA_ESTUDO_H

#include "TelaBase.h"
#include "SessaoEstudo.h"
#include <vector>

class TelaEstudo : public TelaBase {
public:
    // Menu inicial: "1. Novo Estudo", "2. Ver Histórico", "0. Voltar"
    int mostrarMenuEstudos();

    // Loop do Cronômetro: Mostra o tempo passando e opções de controle
    // Retorna a ação (1. Pausar, 2. Finalizar)
    int mostrarSessaoAtiva(const SessaoEstudo& sessao);

    // Lista o histórico passado pelo Repositório
    void mostrarHistorico(const std::vector<SessaoEstudo>& historico);

    int exibir(Usuario* usuario) override;

};

#endif