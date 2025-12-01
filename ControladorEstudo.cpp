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
    std::getline(std::cin, disciplina);

    std::cout << "Digite uma Descricao (ex: Lista de Exercicios): ";
    std::getline(std::cin, descricao);

    // 2. Configura a sessão na memória
    sessaoAtual.resetar(); // Garante que está zerada
    sessaoAtual.setDisciplina(disciplina);
    sessaoAtual.setDescricao(descricao);

    // 3. Inicia o cronômetro
    try {
        sessaoAtual.iniciar();
        // Entra no loop do cronômetro
        gerenciarSessaoEmAndamento();
    } 
    catch (std::exception& e) {
        tela.mostrarErro(e.what());
    }
}

// ==========================================================
// LOOP DO CRONÔMETRO (SESSÃO ATIVA)
// ==========================================================
void ControladorEstudo::gerenciarSessaoEmAndamento() {
    bool sessaoAtiva = true;

    while (sessaoAtiva) {
        // 1. Mostra o status atual (Tempo, Estado) e pede ação
        int acao = tela.mostrarSessaoAtiva(sessaoAtual);

        // 2. Processa a ação do usuário
        switch (acao) {
            case 1: // Pausar / Continuar
                try {
                    if (sessaoAtual.getEstado() == EstadoSessao::RODANDO) {
                        sessaoAtual.pausar();
                    } else if (sessaoAtual.getEstado() == EstadoSessao::PAUSADO) {
                        sessaoAtual.continuar();
                    }
                } catch (std::exception& e) {
                    tela.mostrarErro(e.what());
                }
                break;

            case 2: // Finalizar
                finalizarSessao();
                sessaoAtiva = false; // Quebra o loop
                break;

            default:
                tela.mostrarErro("Opcao invalida. Digite 1 ou 2.");
        }
    }
}

// ==========================================================
// FINALIZAÇÃO E RECOMPENSA
// ==========================================================
void ControladorEstudo::finalizarSessao() {
    // 1. Para o cronômetro definitivamente
    sessaoAtual.finalizar();

    // 2. Salva no Histórico (Arquivo de Estudos)
    repoEstudos->adicionarSessao(sessaoAtual);

    // 3. Lógica de Gamificação (Recompensa)
    // Exemplo: 1 XP a cada segundo + 1 moeda a cada 10 segundos
    long long tempo = sessaoAtual.getSegundos();
    int xpGanho = (int)tempo; 
    int moedasGanhas = (int)(tempo / 10); 

    // Atualiza o objeto Usuario na memória RAM
    usuario->adicionarXp(xpGanho);
    usuario->adicionarMoedas(moedasGanhas);

    // 4. Salva o progresso do usuário no disco (Arquivo Gamificação)
    // IMPORTANTE: Se não salvar aqui, o usuário perde o XP se fechar o jogo.
    repoGamificacao->salvarUsuario(usuario);

    // 5. Feedback para o usuário
    tela.limparTela();
    tela.mostrarMensagem("SESSAO FINALIZADA COM SUCESSO!");
    std::cout << "Voce estudou por " << tempo << " segundos." << std::endl;
    std::cout << "Recompensa: +" << xpGanho << " XP | +" << moedasGanhas << " Moedas" << std::endl;
    tela.esperarEnter();
}

// ==========================================================
// HISTÓRICO
// ==========================================================
void ControladorEstudo::exibirHistorico() {
    // Busca dados no disco e manda pra tela
    std::vector<SessaoEstudo> lista = repoEstudos->obterHistorico();
    tela.mostrarHistorico(lista);
}