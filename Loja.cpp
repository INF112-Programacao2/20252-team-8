#include "Loja.h"

// É necessário incluir as classes filhas de Item para poder instanciá-las
#include "ItemConsumivel.h"
#include "ItemAudio.h"

// ==========================================================
// FÁBRICA DE ITENS (MÉTODO ESTÁTICO)
// ==========================================================
// Aqui definimos TODOS os itens que existem no jogo.
// Se você quiser criar um novo item, adicione um case aqui.
Item* Loja::buscarItemPorId(int id) {
    switch (id) {
        // --- COSMÉTICOS (IDs 100 a 199) ---
        case 100: 
            // id, nome, preço, tipo/local
            return new ItemConsumivel(100, "Bone Vermelho", 50, "cabeca");
        
        case 101: 
            return new ItemConsumivel(101, "Oculos Escuros", 75, "rosto");
        
        case 102:
            return new ItemConsumivel(102, "Camisa Dev C++", 120, "tronco");

        // --- ÁUDIO / MÚSICA (IDs 200 a 299) ---
        case 200: 
            // id, nome, preço, nome_arquivo
            return new ItemAudio(200, "Lofi Beats", 100, "lofi_study.mp3");
        
        case 201: 
            return new ItemAudio(201, "Rock Classico", 150, "rock_bg.mp3");

        case 202: 
            return new ItemAudio(202, "Piano Suave", 80, "piano.mp3");

        // --- CONSUMÍVEIS / OUTROS (Exemplo futuro) ---
        // case 300: return new ItemConsumivel(...);

        default: 
            return nullptr; // ID não existe
    }
}

// ==========================================================
// CONSTRUTOR
// ==========================================================
Loja::Loja() {
    // Aqui decidimos quais itens do catálogo vão aparecer na vitrine inicial.
    // Usamos o próprio método estático para criar os objetos.
    
    // Adicionando Cosméticos
    this->vitrine.push_back(buscarItemPorId(100));
    this->vitrine.push_back(buscarItemPorId(101));
    this->vitrine.push_back(buscarItemPorId(102));

    // Adicionando Músicas
    this->vitrine.push_back(buscarItemPorId(200));
    this->vitrine.push_back(buscarItemPorId(201));
    this->vitrine.push_back(buscarItemPorId(202));
}

// ==========================================================
// DESTRUTOR
// ==========================================================
Loja::~Loja() {
    // Como a vitrine guarda PONTEIROS criados com 'new',
    // precisamos deletar um por um para não vazar memória.
    for (Item* item : this->vitrine) {
        delete item;
    }
    this->vitrine.clear();
}

// ==========================================================
// GETTER
// ==========================================================
std::vector<Item*> Loja::getItensParaVenda() const {
    return this->vitrine;
}