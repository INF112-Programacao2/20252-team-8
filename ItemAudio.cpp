#include "ItemAudio.h"
#include <iostream>
#include "miniaudio.h" 

ItemAudio::ItemAudio(std::string nome, int valor, std::string caminhoArquivo)
    : Item(nome, "Audio", valor), caminhoArquivo(caminhoArquivo) {
}

void ItemAudio::usar() {
    std::cout << ">> Tocando: " << this->nome << "..." << std::endl;

    ma_engine engine;
    ma_result result;

    // Inicializa o motor de áudio
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cout << "[ERRO] Falha ao iniciar motor de audio." << std::endl;
        return;
    }

    // Toca o arquivo
    result = ma_engine_play_sound(&engine, this->caminhoArquivo.c_str(), NULL);
    
    if (result != MA_SUCCESS) {
        std::cout << "[ERRO] Nao foi possivel tocar o arquivo: " << this->caminhoArquivo << std::endl;
    } else {
        std::cout << "(Pressione ENTER para parar a musica...)" << std::endl;
        // Pausa simples para ouvir o som
        if (std::cin.peek() == '\n') std::cin.ignore();
        std::cin.get();
    }

    // Desliga o motor de áudio
    ma_engine_uninit(&engine);
}