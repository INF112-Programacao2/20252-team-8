#include "ControladorEstudo.h"
#include <iostream>
#include <string>

// ==========================================================
// CONSTRUTOR
// ==========================================================
// Inicializa os ponteiros recebidos da main na lista de inicialização.
ControladorEstudo::ControladorEstudo(Usuario* usuario, 
                                     RepositorioEstudos* repoEstudos, 
                                     RepositorioGamificacao* repoGamificacao)
    : usuario(usuario), 
      repoEstudos(repoEstudos), 
      repoGamificacao(repoGamificacao) {
    // A 'tela' e a 'sessaoAtual' são instanciadas automaticamente 
    // pelos seus construtores padrão.
}

// ==========================================================
// MÉTODO PRINCIPAL (LOOP DO MENU)
// ==========================================================
void ControladorEstudo::executar() {
    bool rodando = true;

    while (rodando) {
        // 1. Mostra o menu de opções (Novo Estudo, Histórico, Voltar)
        int opcao = tela.mostrarMenuEstudos();

        // 2. Redireciona para a lógica correta
        switch (opcao) {
            case 1: 
                iniciarNovaSessao(); 
                break;
            case 2: 
                exibirHistorico(); 
                break;
            case 0: 
                rodando = false; // Sai do loop e retorna ao Menu Principal
                break;
            default:
                tela.mostrarErro("Opcao invalida! Tente novamente.");
        }
    }
}

// ==========================================================
// LÓGICA DE INÍCIO DE SESSÃO
// ==========================================================
void ControladorEstudo::iniciarNovaSessao() {
    // 1. Prepara a tela
    tela.limparTela();
    tela.mostrarCabecalho("NOVA SESSAO DE ESTUDO");
    
    // 2. Coleta dados do usuário
    std::string disciplina, descricao;
    
    std::cout << "Digite a Disciplina (ex: Calculo I): ";
    // Limpa buffer se necessário para evitar pular o getline
    if (std::cin.peek() == '\n') std::cin.ignore(); 
    std::getline(std::cin, disciplina);

    std::cout << "Digite uma Descricao (ex: Lista de Integrais): ";
    std::getline(std::cin, descricao);

    // Validação simples
    if (disciplina.empty()) {
        tela.mostrarErro("A disciplina nao pode ser vazia!");
        return;
    }

    // 3. Configura o objeto Sessao na memória
    sessaoAtual.resetar(); // Garante estado limpo
    sessaoAtual.setDisciplina(disciplina);
    sessaoAtual.setDescricao(descricao);

    // 4. Tenta iniciar e entra no loop do cronômetro
    try {
        sessaoAtual.iniciar(); // Marca hora inicial e muda estado para RODANDO
        gerenciarSessaoEmAndamento();
    } 
    catch (std::exception& e) {
        tela.mostrarErro(e.what());
    }
}

// ==========================================================
// LOOP DO CRONÔMETRO (Sessão Ativa)
// ==========================================================
void ControladorEstudo::gerenciarSessaoEmAndamento() {
    bool sessaoAtiva = true;

    while (sessaoAtiva) {
        // 1. A tela mostra o tempo correndo e retorna a ação do usuário
        // (1 = Pausar/Continuar, 2 = Finalizar)
        int acao = tela.mostrarSessaoAtiva(sessaoAtual);

        switch (acao) {
            case 1: // Alternar Pausa
                try {
                    // Se rodando -> Pausa
                    if (sessaoAtual.getEstado() == "rodando") {
                        sessaoAtual.pausar();
                    } 
                    // Se pausado -> Continua
                    else if (sessaoAtual.getEstado() == "pausado") {
                        sessaoAtual.continuar();
                    }
                } catch (std::exception& e) {
                    tela.mostrarErro(e.what());
                }
                break;

            case 2: // Finalizar
                finalizarSessao();
                sessaoAtiva = false; // Quebra este loop e volta para o menu de estudos
                break;

            default:
                // Se digitou algo errado, apenas ignora e atualiza a tela
                break; 
        }
    }
}

// ==========================================================
// FINALIZAÇÃO E RECOMPENSA (Coração do Sistema)
// ==========================================================
void ControladorEstudo::finalizarSessao() {
    // 1. Encerra a contagem de tempo na Entidade
    sessaoAtual.finalizar();

    // 2. Persistência: Salva os dados no arquivo de histórico
    // O RepositorioEstudos vai ler os dados da sessaoAtual e gravar no .txt
    repoEstudos->adicionarSessao(sessaoAtual);

    // 3. Lógica de Recompensa (Gamificação)
    // Regra simples: 1 segundo = 1 XP (para testes)
    // Regra moeda: 1 moeda a cada 10 segundos
    long long tempoTotal = sessaoAtual.getSegundos();
    
    int xpGanho = static_cast<int>(tempoTotal); 
    int moedasGanhas = static_cast<int>(tempoTotal / 10); 

    // 4. Atualiza o Usuário (Na Memória RAM)
    usuario->adicionarXp(xpGanho);
    usuario->adicionarMoedas(moedasGanhas);

    // 5. Persistência: Salva o progresso do usuário no arquivo dele
    // CRUCIAL: Se não salvar aqui, o XP é perdido ao fechar o jogo
    repoGamificacao->salvarUsuario(usuario);

    // 6. Feedback Visual
    tela.limparTela();
    tela.mostrarMensagem("SESSAO FINALIZADA COM SUCESSO!");
    std::cout << "Tempo Total: " << tempoTotal << " segundos." << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Recompensas:" << std::endl;
    std::cout << "[+] " << xpGanho << " XP" << std::endl;
    std::cout << "[+] " << moedasGanhas << " Moedas" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    tela.esperarEnter();
}

// ==========================================================
// EXIBIÇÃO DE HISTÓRICO
// ==========================================================
void ControladorEstudo::exibirHistorico() {
    // 1. Busca os dados no disco
    std::vector<SessaoEstudo> historico = repoEstudos->obterHistorico();

    // 2. Passa os dados para a tela formatar
    tela.mostrarHistorico(historico);
}