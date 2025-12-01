#ifndef CONTROLADOR_ESTUDO_H
#define CONTROLADOR_ESTUDO_H

// --- Dependências de Associação (Ponteiros recebidos da Main) ---
#include "Usuario.h"
#include "RepositorioEstudos.h"
#include "RepositorioGamificacao.h"

// --- Dependência de Composição (A Tela pertence ao Controlador) ---
#include "TelaEstudo.h"

// --- Dependência de Uso (O objeto que vamos manipular) ---
#include "SessaoEstudo.h"

class ControladorEstudo {
private:
    // Poteiros para os objetos principais do sistema (Injeção de Dependência)
    // O Controlador USA estes objetos, mas não é dono deles (não dá delete)
    Usuario* usuario;
    RepositorioEstudos* repoEstudos;
    RepositorioGamificacao* repoGamificacao; 

    // Instância da Tela (Composição)
    // Criada automaticamente quando o controlador nasce
    TelaEstudo tela;

    // Objeto que representa a sessão que está acontecendo agora
    // Mantemos na memória para controlar o cronômetro
    SessaoEstudo sessaoAtual;

public:
    // Construtor
    // Recebe os ponteiros fundamentais inicializados na main
    ControladorEstudo(Usuario* usuario, 
                      RepositorioEstudos* repoEstudos, 
                      RepositorioGamificacao* repoGamificacao);

    // Método Principal
    // Inicia o loop do menu de estudos (Chamado pelo ControladorPrincipal)
    void executar();

private:
    // --- Métodos Auxiliares (Lógica Interna) ---

    // 1. Pede disciplina/descrição e prepara o objeto sessaoAtual
    void iniciarNovaSessao();

    // 2. Loop do cronômetro (Pausar, Continuar, Finalizar)
    // Fica travado aqui enquanto o usuário estuda
    void gerenciarSessaoEmAndamento();

    // 3. Chamado ao encerrar: Salva no repo e dá XP/Moedas ao usuário
    void finalizarSessao();

    // 4. Busca dados no repoEstudos e manda a tela exibir
    void exibirHistorico();
};

#endif

