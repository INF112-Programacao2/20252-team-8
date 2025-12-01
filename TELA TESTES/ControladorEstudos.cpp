#include "ControladorEstudo.h"
#include <iostream>

// ==========================================================
// CONSTRUTOR
// ==========================================================
ControladorEstudo::ControladorEstudo(Usuario* usuario, 
                                     RepositorioEstudos* repoEstudos, 
                                     RepositorioGamificacao* repoGami)
    : usuario(usuario), 
      repoEstudos(repoEstudos), 
      repoGamificacao(repoGami) {
    // A tela é inicializada automaticamente pela composição
    // A sessaoAtual é inicializada pelo construtor padrão dela
}

// ==========================================================
// LOOP PRINCIPAL (MENU DE ESTUDOS)
// ==========================================================
void ControladorEstudo::executar() {
    while (true) {
        // 1. Mostra o menu e pega a opção
        int opcao = tela.mostrarMenuEstudos();

        // 2. Decide para onde ir
        switch (opcao) {
            case 1: 
                iniciarNovaSessao(); 
                break;
            case 2: 
                exibirHistorico(); 
                break;
            case 0: 
                return; // Volta para o Menu Principal
            default:
                tela.mostrarErro("Opcao invalida!");
        }
    }
}

// ==========================================================
// LÓGICA DE NOVA SESSÃO
// ==========================================================
void ControladorEstudo::iniciarNovaSessao() {
    // 1. Coleta dados iniciais (Disciplina e Descrição)
    // Aqui poderiamos ter um método na tela, mas vamos fazer simples usando TelaBase
    tela.limparTela();
    tela.mostrarCabecalho("NOVA SESSAO DE ESTUDO");
    
    std::string disciplina, descricao;
    
    std::cout << "Digite a Disciplina (ex: Matematica): ";
    // Limpeza de buffer básica antes de getline se necessário
    if (std::cin.peek() == '\n') std::cin.ignore(); 
    std::getline(std::