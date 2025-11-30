#include "ControladorEstudo.h"
#include <iostream>

ControladorEstudo::ControladorEstudo(ControladorGamificacao* controladorG) 
    : controladorGami(controladorG), sessaoAtiva(nullptr), estado("parado") {
}

ControladorEstudo::~ControladorEstudo() {
    if (sessaoAtiva != nullptr) {  //se houver uma sessão ativa, limpa
        delete sessaoAtiva;
        sessaoAtiva = nullptr;
    }
}

void ControladorEstudo::iniciarSessao(int duracao) {
    if (estado != "parado") {
        std::cout << "Erro: Já existe uma sessão em andamento!" << std::endl;
        return;
    }

    //solicita os dados da sessão
    std::string disciplina, etiqueta, descricao;
    std::cin.ignore();
    std::cout << "\nConfigurar Sessão de Estudo" << std::endl;
    std::cout << "Disciplina: ";
    std::getline(std::cin, disciplina);
    std::cout << "Descrição (opcional): ";
    std::getline(std::cin, descricao);

    //cria nova sessão
    sessaoAtiva = new SessaoEstudo(0, 0, disciplina, etiqueta, descricao);
    sessaoAtiva->iniciar();
    estado = "rodando";
    
    std::cout << "\nSessão iniciada! Bons estudos!!" << std::endl;
}

void ControladorEstudo::pausarSessao() {
    if (estado != "rodando") {
        std::cerr << "Erro: Não há sessão rodando para pausar." << std::endl;
        return;
    }

    if (sessaoAtiva != nullptr) {
        sessaoAtiva->pausar();
        estado = "pausado";
        std::cout << "Sessão pausada." << std::endl;
    }
}

void ControladorEstudo::finalizarSessao(Usuario* u) {
    if (sessaoAtiva == nullptr) {
        std::cerr << "Erro: Não há sessão ativa para finalizar." << std::endl;
        return;
    }

    //armazena os dados da sessão
    sessaoAtiva->armazenar();
    //para mostrar resumo
    long long int tempoEstudado = sessaoAtiva->getSegundos();
    int minutos = tempoEstudado / 60;
    int segundos = tempoEstudado % 60;
    std::cout << "\nSessão Finalizada, bom trabalho!" << std::endl;
    std::cout << "Disciplina: " << sessaoAtiva->getDisciplina() << std::endl;
    std::cout << "Tempo estudado: " << minutos << " minutos e " << segundos << " segundos" << std::endl;

    //limpa a sessão
    delete sessaoAtiva;
    sessaoAtiva = nullptr;
    estado = "parado";
}

void ControladorEstudo::salvarSessao(Usuario* u, SessaoEstudo& sessao) {
    sessao.armazenar();
    u->getRepositorio().adicionarSessao(sessao);
    
    //atualiza a gamificação
    if (controladorGami != nullptr) {
        controladorGami->atualizarStatus();
    }
}

SessaoEstudo* ControladorEstudo::getSessaoAtiva() {
    return sessaoAtiva;
}

std::string ControladorEstudo::getEstado() const {
    return estado;
}