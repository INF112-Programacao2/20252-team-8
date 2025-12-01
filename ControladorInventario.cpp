// Esta linha abaixo faz a biblioteca de som funcionar. É obrigatoria aqui.
#define MINIAUDIO_IMPLEMENTATION
#include "ControladorInventario.h"
#include "Loja.h"
#include <vector>
#include <iostream>

ControladorInventario::ControladorInventario(int tempo_inicial) : ControladorLoja(tempo_inicial) {
    estaTocando = false;
    
    // Inicia o sistema de som do miniaudio
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cout << "ERRO CRITICO: Falha ao iniciar sistema de audio!\n";
    }
}

ControladorInventario::~ControladorInventario() {
    pararMusica();
    ma_engine_uninit(&engine);
}

void ControladorInventario::pararMusica() {
    if (estaTocando) {
        ma_sound_stop(&som);
        ma_sound_uninit(&som);
        estaTocando = false;
        std::cout << "Musica parada.\n";
    }
}

void ControladorInventario::tocarMusica(std::string nomeArquivo) {
    // Se já estiver tocando algo, para antes de começar a nova
    pararMusica(); 

    std::cout << "Tentando tocar: " << nomeArquivo << "...\n";

    // Carrega e toca o arquivo
    if (ma_sound_init_from_file(&engine, nomeArquivo.c_str(), 0, NULL, NULL, &som) == MA_SUCCESS) {
        ma_sound_start(&som);
        estaTocando = true;
        std::cout << "Reproduzindo agora!\n";
    } else {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo '" << nomeArquivo << "'.\n";
        std::cout << "Verifique se o arquivo .mp3 esta na mesma pasta do executavel.\n";
    }
}


void ControladorInventario::executar() {
    while(true) {
        // 1. Pega os IDs do arquivo
        std::vector<int> ids = repoInventario->carregarIds();
        
        // 2. Transforma IDs em Objetos para mostrar na tela
        std::vector<Item*> itensParaMostrar;
        
        for (int id : ids) {
            Item* item = Loja::buscarItemPorId(id);
            if (item != nullptr) {
                itensParaMostrar.push_back(item);
            }
        }

        // 3. Manda a tela exibir os objetos (nome, tipo, etc)
        // O método mostrarInventario agora recebe vector<Item*>
        int escolha = tela.mostrarInventario(itensParaMostrar);

        // ... lógica de equipar item ...

        // 4. LIMPEZA DE MEMÓRIA (Muito Importante!)
        // Como a Loja deu 'new', o Controlador tem que dar 'delete'
        // antes de recarregar ou sair, senão vaza memória.
        for (Item* i : itensParaMostrar) {
            delete i; 
        }
        
        if (escolha == 0) break;
    }
}