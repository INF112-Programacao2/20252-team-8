#include "ControladorLoja.h"
#include <iostream>
#include <limits>

// Chama o construtor do pai com ':', o resto é feito dentro das chaves
ControladorLoja::ControladorLoja(Usuario* usuario, RepositorioInventario* repoInv, RepositorioGamificacao* repo) 
    : repo(repo), repoInv(repoInv), usuario(usuario)
    {
    
    // --- ADICIONANDO AS 10 MÚSICAS ---
        musicas.push_back(Musica("Background Vibe I", "lofi-background-music-326931 (1).mp3", 180));
        musicas.push_back(Musica("Pure Lofi Flow", "lofi-lofi-music-412319.mp3", 200));
        musicas.push_back(Musica("Background Vibe II", "lofi-background-music-314199.mp3", 190));
        musicas.push_back(Musica("Study Calm Peaceful", "lofi-study-calm-peaceful-chill-hop-112191 (1).mp3", 210));
        musicas.push_back(Musica("Rainy City", "rainy-lofi-city-lofi-music-332746.mp3", 240));
        musicas.push_back(Musica("Background Vibe III", "lofi-background-music-336230.mp3", 220));
        musicas.push_back(Musica("Good Night Cozy", "good-night-lofi-cozy-chill-music-160166 (1).mp3", 300));
        musicas.push_back(Musica("Lofi Girl Ambient", "lofi-girl-lofi-ambient-music-365952.mp3", 205));
        musicas.push_back(Musica("Deep Ambient Lofi", "ambient-lofi-lofi-music-344112.mp3", 200));
        musicas.push_back(Musica("Chill Lofi Girl", "lofi-lofi-chill-lofi-girl-438671.mp3", 195));
}

std::vector<Musica>& ControladorLoja::getMusicas() {
    return musicas;
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

    // 3. Verifica se tem moedas suficientes (usando getMoedas() herdado)
    int moedasAtuais = repo->getMoedas();
    int precoMusica = musicas[indice].valor;
    
    if (moedasAtuais >= precoMusica) {
        // Desconta moedas usando o método herdado (passa valor negativo)
        repo->setMoedas(moedasAtuais - precoMusica);
        
        // Marca como comprada
        musicas[indice].comprada = true;
        
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
        std::cout << "SEU SALDO: " << usuario->getMoedas() << " moedas" << std::endl;
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