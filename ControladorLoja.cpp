#include "ControladorLoja.h"
#include "ItemAudio.h"
#include <iostream>
#include <limits>

ControladorLoja::ControladorLoja(Usuario* usuario, RepositorioInventario* repoInv, RepositorioGamificacao* repo) 
    : repo(repo), repoInv(repoInv), usuario(usuario)
{
    // --- ADICIONANDO AS 10 MÚSICAS ---
    musicas.push_back(Musica("Study Calm Lo-Fi", "lofi-study-calm-peaceful-chill-hop-112191.mp3", 300));
    musicas.push_back(Musica("Sad Lo-Fi", "lofi-lofi-song-2-432220.mp3", 700));
    musicas.push_back(Musica("Chill Night Lo-Fi", "good-night-lofi-cozy-chill-music-160166.mp3", 1200));
    musicas.push_back(Musica("Morning Coffee", "morning-coffee.mp3", 150));
    musicas.push_back(Musica("Rainy Day", "rainy-day.mp3", 200));
    musicas.push_back(Musica("Focus Beats", "focus-beats.mp3", 250));
    musicas.push_back(Musica("Piano Study", "piano-study.mp3", 350));
    musicas.push_back(Musica("Synthwave Chill", "synthwave.mp3", 400));
    musicas.push_back(Musica("Library Ambience", "library.mp3", 100));
    musicas.push_back(Musica("Deep Focus", "deep-focus.mp3", 500));
}

std::vector<Musica>& ControladorLoja::getMusicas() {
    return musicas;
}

void ControladorLoja::salvarMusicaNoInventario(const Musica& musica) {
    // Formato: "Nome,Tipo,Valor,Arquivo"
    // Exemplo: "Study Calm Lo-Fi,Audio,300,lofi-study-calm-peaceful-chill-hop-112191.mp3"
    std::string dados = musica.nome + ",Audio," + std::to_string(musica.valor) + "," + musica.arquivo;
    
    // Salva no repositório do inventário
    repoInv->adicionarItem(dados);
    
    std::cout << "Musica adicionada ao seu inventario!" << std::endl;
}

bool ControladorLoja::comprarMusica(int indice) {
    // 1. Verifica se o numero digitado é valido
    if (indice < 0 || indice >= musicas.size()) {
        std::cout << "Erro: Musica nao encontrada.\n";
        return false;
    }

    // 2. Verifica se já comprou
    if (musicas[indice].comprada == true) {
        std::cout << "Voce ja possui a musica " << musicas[indice].nome << "!\n";
        return false;
    }

    // 3. Verifica se tem moedas suficientes
    int moedasAtuais = repo->getMoedas();
    int precoMusica = musicas[indice].valor;
    
    if (moedasAtuais >= precoMusica) {
        // Desconta moedas no repositório
        repo->setMoedas(moedasAtuais - precoMusica);
        
        // Marca como comprada
        musicas[indice].comprada = true;
        
        // SALVA NO INVENTÁRIO
        salvarMusicaNoInventario(musicas[indice]);
        
        // Atualiza o usuário (se o método existir)
        // Se não existir setMoedas(), use adicionarMoedas() ou crie o método
        if (usuario) {
            // Tentar diferentes métodos possíveis
            try {
                usuario->setMoedas(repo->getMoedas());
            } catch(...) {
                // Se setMoedas não existir, tenta outro método
                // Ou simplesmente não atualiza o usuário aqui
                // O repositório já guarda o estado
            }
        }
        
        std::cout << "SUCESSO! Voce comprou: " << musicas[indice].nome << "\n";
        std::cout << "Saldo restante: " << repo->getMoedas() << " moedas\n";
        return true;
    } else {
        std::cout << "Saldo insuficiente. Voce precisa de " << precoMusica << " moedas.\n";
        std::cout << "Voce tem: " << moedasAtuais << " moedas.\n";
        return false;
    }
}

void ControladorLoja::executar(){
    bool rodando = true;

    while (rodando) {
        tela.limparTela();
        std::cout << "========================================" << std::endl;
        std::cout << "           LOJA DE MUSICAS              " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "SEU SALDO: " << repo->getMoedas() << " moedas" << std::endl;  // Usando repo ao invés de usuario
        std::cout << "----------------------------------------" << std::endl;

        // Lista as músicas manualmente
        if (musicas.empty()) {
            std::cout << "(Nenhuma musica disponivel)" << std::endl;
        } else {
            for (size_t i = 0; i < musicas.size(); i++) {
                std::cout << "[" << (i + 1) << "] " << musicas[i].nome 
                          << " (" << musicas[i].valor << "$)";
                
                if (musicas[i].comprada) {
                    std::cout << " [COMPRADO]";
                }
                std::cout << std::endl;
            }
        }

        std::cout << "\nDigite o numero da musica para COMPRAR" << std::endl;
        std::cout << "Ou 0 para Voltar" << std::endl;
        std::cout << ">> Escolha: ";

        int opcao;
        std::cin >> opcao;

        // Tratamento básico de erro de entrada
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcao = -1;
        }

        if (opcao == 0) {
            rodando = false; // Sai do loop e volta pro menu principal
        }
        else if (opcao > 0 && (size_t)opcao <= musicas.size()) {
            // Tenta comprar (o índice do vetor é opcao - 1)
            bool sucesso = comprarMusica(opcao - 1);
            
            if (!sucesso) {
                // Se falhou (saldo insuficiente ou já tem), pausa para ler o erro
                tela.esperarEnter();
            } else {
                // Se funcionou, mostra mensagem e espera
                tela.esperarEnter();
            }
        }
        else {
            tela.mostrarErro("Opcao invalida!");
        }
    }
}