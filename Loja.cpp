#include "Loja.h"
#include "ItemConsumivel.h"
#include "ItemAudio.h"
#include "ItemAlarme.h"

// A Fábrica Central - Define todos os itens do jogo AQUI
Item* Loja::buscarItemPorId(int id) {
    switch(id) {
        // Exemplos que serão implementados:
        // case 100: return new ItemAlarme(100, "padrão", 50, "ring.mp3");
        // case 200: return new ItemAudio(200, "Musica Lofi", 150, "lofi.mp3");
        // case 300: return new ItemConsumivel(300, "Dobro XP", 100, "boost");
        default: return nullptr;
    }
}


Loja::Loja() {
    // Preenche a vitrine usando a própria lógica da fábrica
    this->vitrine.push_back(buscarItemPorId(100));
    this->vitrine.push_back(buscarItemPorId(200));
}


Loja::~Loja() {
    for (Item* i : this->vitrine) {
        delete i; // Limpa a memória
    }
    this->vitrine.clear();
}


std::vector<Item*> Loja::getItensParaVenda() const {
    return this->vitrine;
}
