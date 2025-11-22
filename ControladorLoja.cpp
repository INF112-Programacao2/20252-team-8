#include "ControladorLoja.h"
#include <iostream>

// Chama o construtor do pai com ':', o resto é feito dentro das chaves
ControladorLoja::ControladorLoja(int tempo_inicial) : ControladorGamificacao(tempo_inicial) {
    
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

    // 3. Verifica se tem pontos
    if (pontos >= musicas[indice].valor) {
        pontos = pontos - musicas[indice].valor; // Desconta pontos
        musicas[indice].comprada = true;         // Marca como comprada
        std::cout << "SUCESSO! Voce comprou: " << musicas[indice].nome << "\n";
        return true;
    } else {
        std::cout << "Saldo insuficiente. Voce precisa de " << musicas[indice].valor << " pontos.\n";
        return false;
    }
}