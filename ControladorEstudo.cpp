#include "ControladorEstudo.h"
#include <iostream>
#include <string>
#include "ItemAudio.h"
#include <vector>
#include "Item.h"
#include <sstream>

// ==========================================================
// CONSTRUTOR
// ==========================================================
// Inicializa os ponteiros recebidos da main na lista de inicialização.
ControladorEstudo::ControladorEstudo(Usuario* usuario, 
                                    RepositorioEstudos* repoEstudos, 
                                    RepositorioGamificacao* repoGamificacao,
                                    RepositorioInventario* repoInventario)
    : usuario(usuario), 
      repoEstudos(repoEstudos), 
      repoGamificacao(repoGamificacao),
      repoInventario(repoInventario),
      audioInicializado(false) {
    // A 'tela' e a 'sessaoAtual' são instanciadas automaticamente pelos seus construtores padrão.
    if (ma_engine_init(NULL, &engine) == MA_SUCCESS) {
        audioInicializado = true;
    } else {
        std::cout << "AVISO: Sistema de audio nao pode ser iniciado.\n";
    }
}

// --- Destrutor ---
ControladorEstudo::~ControladorEstudo() {
    if (audioInicializado) {
        ma_engine_uninit(&engine);
    }
}

void ControladorEstudo::selecionarMusica() {
    caminhoMusicaEscolhida = ""; // Reseta escolha anterior

    // 1. Carrega itens do repositório
    std::vector<std::string> itens = repoInventario->carregarItens();
    std::vector<std::pair<std::string, std::string>> musicasDisponiveis;

    // 2. Filtra apenas itens do tipo "Audio"
    for (const auto& linha : itens) {
        std::stringstream ss(linha);
        std::string nome, tipo, valor, arquivo;
        
        std::getline(ss, nome, ',');
        std::getline(ss, tipo, ',');
        std::getline(ss, valor, ',');
        std::getline(ss, arquivo, ',');

        // Remove espaços extras (trim)
        if(!tipo.empty() && tipo.front() == ' ') tipo.erase(0, 1);
        if(!nome.empty() && nome.front() == ' ') nome.erase(0, 1);
        if(!arquivo.empty() && arquivo.front() == ' ') arquivo.erase(0, 1);

        if (tipo == "Audio") {
            // Garante que o caminho esteja correto (adiciona assets/ se faltar)
            if (arquivo.find("assets/") == std::string::npos) {
                arquivo = "assets/" + arquivo;
            }
            musicasDisponiveis.push_back({nome, arquivo});
        }
    }

    // 3. Se não tiver músicas, avisa e volta
    if (musicasDisponiveis.empty()) {
        return; // Usuário estuda em silêncio
    }

    // 4. Menu de escolha
    tela.limparTela();
    std::cout << "=== TRILHA SONORA ===\n";
    std::cout << "[0] Silencio\n";
    for (size_t i = 0; i < musicasDisponiveis.size(); i++) {
        std::cout << "[" << (i+1) << "] " << musicasDisponiveis[i].first << "\n";
    }
    
    std::cout << ">> Escolha uma musica: ";
    int op;
    std::cin >> op;
    std::cin.ignore(); // Limpa buffer

    if (op > 0 && op <= (int)musicasDisponiveis.size()) {
        caminhoMusicaEscolhida = musicasDisponiveis[op-1].second;
        std::cout << "Musica selecionada: " << musicasDisponiveis[op-1].first << "\n";
    }
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

    selecionarMusica();

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
    bool tocandoAgora = false;

    if (audioInicializado && !caminhoMusicaEscolhida.empty()) {
        ma_result result = ma_sound_init_from_file(&engine, caminhoMusicaEscolhida.c_str(), 0, NULL, NULL, &musicaFundo);
        
        if (result == MA_SUCCESS) {
            ma_sound_set_looping(&musicaFundo, MA_TRUE); // Loop infinito
            ma_sound_start(&musicaFundo); // O som começa em outra thread!
            tocandoAgora = true;
        } else {
            tela.mostrarErro("Nao foi possivel carregar o arquivo: " + caminhoMusicaEscolhida);
        }
    }

    while (sessaoAtiva) {
        // 1. A tela mostra o tempo correndo e retorna a ação do usuário
        // (1 = Pausar/Continuar, 2 = Finalizar, 3 = Trocar Musica)
        int acao = tela.mostrarSessaoAtiva(sessaoAtual);

        switch (acao) {
            case 1: // Alternar Pausa
                try {
                    // Se rodando -> Pausa
                    if (sessaoAtual.getEstado() == SessaoEstudo::rodando) {
                        sessaoAtual.pausar();
                        if (!caminhoMusicaEscolhida.empty() && tocandoAgora) {
                            ma_sound_stop(&musicaFundo);
                            tocandoAgora = false; 
                        }
                    } 
                    // Se pausado -> Continua
                    else if (sessaoAtual.getEstado() == SessaoEstudo::pausado) {
                        sessaoAtual.continuar();

                        // Só tenta dar play se o usuário escolheu uma música
                        if (!caminhoMusicaEscolhida.empty() && !tocandoAgora) {
                            ma_sound_start(&musicaFundo);
                            tocandoAgora = true;
                        }
                    }
                } catch (std::exception& e) {
                    tela.mostrarErro(e.what());
                }
                break;

            case 2: // Finalizar
                finalizarSessao();
                sessaoAtiva = false; // Quebra este loop e volta para o menu de estudos
                break;

            case 3: // Trocar Musica
                // Pausa o timer para o aluno escolher com calma
                if (sessaoAtual.getEstado() == SessaoEstudo::rodando) {
                    sessaoAtual.pausar();
                }

                // Para e Limpa a música atual
                if (tocandoAgora) {
                    ma_sound_stop(&musicaFundo);
                    ma_sound_uninit(&musicaFundo);
                    tocandoAgora = false;
                }

                // Abre o menu de seleção novamente
                selecionarMusica();

                // Se escolheu algo novo, carrega e toca
                if (!caminhoMusicaEscolhida.empty()) {
                    ma_result res = ma_sound_init_from_file(&engine, caminhoMusicaEscolhida.c_str(), 0, NULL, NULL, &musicaFundo);
                    if (res == MA_SUCCESS) {
                        ma_sound_set_looping(&musicaFundo, MA_TRUE);
                        ma_sound_start(&musicaFundo);
                        tocandoAgora = true;
                    } else {
                        tela.mostrarErro("Erro ao carregar nova musica.");
                    }
                }

                // Retoma o estudo automaticamente
                sessaoAtual.continuar();
                break;
            default:
                // Se digitou algo errado, apenas ignora e atualiza a tela
                break; 
        }
    }
    
    if (tocandoAgora) {
        ma_sound_stop(&musicaFundo);
        ma_sound_uninit(&musicaFundo); // Libera memória específica desse som
    }
}

// ==========================================================
// FINALIZAÇÃO E RECOMPENSA (Coração do Sistema)
// ==========================================================
void ControladorEstudo::finalizarSessao() {
    // Encerra a contagem de tempo na Entidade
    sessaoAtual.finalizar();

    // Persistência: Salva os dados no arquivo de histórico
    // O RepositorioEstudos vai ler os dados da sessaoAtual e gravar no .txt
    repoEstudos->adicionarSessao(sessaoAtual);

    // Lógica de Recompensa (Gamificação)
    // Regra simples: 1 segundo = 1 XP (para testes)
    // Regra moeda: 1 moeda a cada 10 segundos
    long long tempoTotal = sessaoAtual.getSegundos();
    
    int xpGanho = static_cast<int>(tempoTotal); 
    int moedasGanhas = static_cast<int>(tempoTotal / 10); 

    // Guarda o nível antes de ganhar os pontos
    int nivelAntes = usuario->getNivel();

    // Atualiza o Usuário (Na Memória RAM)
    usuario->adicionarXp(xpGanho);
    usuario->adicionarMoedas(moedasGanhas);

    // Persistência: Salva o progresso do usuário no arquivo dele
    // CRUCIAL: Se não salvar aqui, o XP é perdido ao fechar o jogo
    repoGamificacao->salvarUsuario(usuario);

    // Pega o nível depois
    int nivelDepois = usuario->getNivel();

    // Feedback Visual
    tela.limparTela();
    tela.mostrarMensagem("SESSAO FINALIZADA COM SUCESSO!");
    std::cout << "Tempo Total: " << tempoTotal << " segundos." << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Recompensas:" << std::endl;
    std::cout << "[+] " << xpGanho << " XP" << std::endl;
    std::cout << "[+] " << moedasGanhas << " Moedas" << std::endl;

    // Verifica se subiu de nivel
    if (nivelDepois > nivelAntes) {
        std::cout << "\n========================================\n";
        std::cout << "           PARABENS! LEVEL UP!          \n";
        std::cout << "========================================\n";
        std::cout << "Voce alcancou o Nivel " << nivelDepois << "!\n";
        std::cout << "Nova Badge: " << usuario->getBadge() << "\n"; // Mostra a patente atualizada
        std::cout << "========================================\n";
    }

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