#define MINIAUDIO_IMPLEMENTATION // <--- CORRETO! Deve estar aqui.
#include "tocarmusica.h"
#include <iostream>
#include <string>

// --- Construtor e Destrutor ---

TocarMusicas::TocarMusicas(int tempo_de_estudo_inicial)
    : Loja(tempo_de_estudo_inicial), 
      musicaEstaCarregada(false)    
{
    // Inicializa a engine de áudio
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cerr << "Falha ao inicializar a engine de audio!" << std::endl;
    }
}

TocarMusicas::~TocarMusicas() {
    descarregarMusica(); // MUDANÇA: Chama a função com nome novo
    ma_engine_uninit(&engine); 
}

// --- Métodos de Controle ---

// Esta é a sua antiga função 'parar()', agora com um nome mais claro
void TocarMusicas::descarregarMusica() {
    if (musicaEstaCarregada) {
        ma_sound_stop(&musicaAtual);
        ma_sound_uninit(&musicaAtual);
        musicaEstaCarregada = false;
    }
}

// NOVA FUNÇÃO: Apenas pausa o som
void TocarMusicas::pausarMusica() {
    if (musicaEstaCarregada && ma_sound_is_playing(&musicaAtual)) {
        ma_sound_stop(&musicaAtual);
        std::cout << "Musica pausada." << std::endl;
    } else if (musicaEstaCarregada) {
        std::cout << "A musica ja esta pausada." << std::endl;
    } else {
        std::cout << "Nenhuma musica tocando para pausar." << std::endl;
    }
}

// NOVA FUNÇÃO: Apenas resume o som
void TocarMusicas::resumirMusica() {
    if (musicaEstaCarregada) {
        if (ma_sound_is_playing(&musicaAtual) == MA_FALSE) { // MA_FALSE significa "não está tocando"
            ma_sound_start(&musicaAtual);
            std::cout << "Resumindo musica..." << std::endl;
        } else {
            std::cout << "A musica ja esta tocando." << std::endl;
        }
    } else {
        std::cout << "Nenhuma musica carregada para resumir." << std::endl;
        std::cout << "Escolha uma musica para tocar primeiro (1, 2 ou 3)." << std::endl;
    }
}

// ATUALIZADO: 'tocar' agora chama 'descarregarMusica()'
void TocarMusicas::tocar(const std::string& caminhoMusica) {
    // 1. Para e descarrega qualquer música que já esteja tocando
    descarregarMusica(); // MUDANÇA: Chama a função com nome novo

    // 2. Tenta carregar o novo arquivo de música
    ma_result result = ma_sound_init_from_file(&engine, caminhoMusica.c_str(), 0, NULL, NULL, &musicaAtual);
    if (result != MA_SUCCESS) {
        std::cerr << "Falha ao carregar o arquivo: " << caminhoMusica << std::endl;
        std::cerr << "Verifique se o arquivo esta na pasta correta!" << std::endl;
        return;
    }

    // 3. Toca o som
    ma_sound_start(&musicaAtual);
    musicaEstaCarregada = true;
    std::cout << "Tocando: " << caminhoMusica << "..." << std::endl;
}

// --- O Método Principal de Interação (MENU ATUALIZADO) ---

void TocarMusicas::mostrarMenuMusicas() {
    int escolha = 0;

    const std::string ARQUIVO_MUSICA_1 = "lofi-study-calm-peaceful-chill-hop-112191.mp3"; 
    const std::string ARQUIVO_MUSICA_2 = "lofi-lofi-song-2-432220.mp3";
    const std::string ARQUIVO_MUSICA_3 = "good-night-lofi-cozy-chill-music-160166.mp3";

    while (true) {
        std::cout << "\n--- MEU PLAYER DE MUSICAS ---" << std::endl;
        std::cout << "Musicas disponiveis (compradas na loja):" << std::endl;
        
        int opcoesDisponiveis = 0;
        if (musica1_comprada) {
            std::cout << "  1. " << nomemusica1 << std::endl;
            opcoesDisponiveis++;
        }
        if (musica2_comprada) {
            std::cout << "  2. " << nomemusica2 << std::endl;
            opcoesDisponiveis++;
        }
        if (musica3_comprada) {
            std::cout << "  3. " << nomemusica3 << std::endl;
            opcoesDisponiveis++;
        }

        if (opcoesDisponiveis == 0) {
            std::cout << "\nVoce ainda nao comprou nenhuma musica!" << std::endl;
            std::cout << "Visite a loja para comprar." << std::endl;
            return; 
        }

        std::cout << "---------------------------------" << std::endl;
        std::cout << "  4. Pausar musica" << std::endl;      // MUDANÇA
        std::cout << "  5. Resumir (Play)" << std::endl;     // NOVO
        std::cout << "  6. Parar (Descarregar)" << std::endl; // NOVO (Antigo 'parar')
        std::cout << "  7. Sair do Player" << std::endl;     // MUDANÇA
        std::cout << "Escolha uma opcao: ";

        // Bloco de validação de entrada (igual ao do main)
        if (!(std::cin >> escolha)) {
            std::cout << "Entrada invalida. Tente novamente." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue; 
        }

        if (escolha == 1) {
            if (musica1_comprada) tocar(ARQUIVO_MUSICA_1);
            else std::cout << "Musica nao comprada!" << std::endl;
        } 
        else if (escolha == 2) {
            if (musica2_comprada) tocar(ARQUIVO_MUSICA_2);
            else std::cout << "Musica nao comprada!" << std::endl;
        } 
        else if (escolha == 3) {
            if (musica3_comprada) tocar(ARQUIVO_MUSICA_3);
            else std::cout << "Musica nao comprada!" << std::endl;
        } 
        else if (escolha == 4) {
            pausarMusica(); // MUDANÇA
        } 
        else if (escolha == 5) {
            resumirMusica(); // NOVO
        }
        else if (escolha == 6) {
            descarregarMusica(); // NOVO (Antigo 'parar')
            std::cout << "Musica parada e descarregada." << std::endl;
        }
        else if (escolha == 7) {
            descarregarMusica(); // Garante que a musica pare ao sair
            return;  
        } 
        else {
            std::cout << "Opcao invalida." << std::endl;
        }
    }
}