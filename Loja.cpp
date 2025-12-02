#include "Loja.h"
#include "ItemAudio.h" // Necessário para os instrumentos

Loja::Loja() {
    // --- COSMÉTICOS / ITENS COMUNS ---
    // Adiciona na vitrine
    vitrine.push_back(Item("Cafe Expresso", "Consumivel", 10));
    vitrine.push_back(Item("Energetico", "Consumivel", 25));
    vitrine.push_back(Item("Bone Vermelho", "Cabeca", 50));

    // --- INSTRUMENTOS (ItemAudio) ---
    // Criamos como ItemAudio para definir o tipo "Audio"
    vitrine.push_back(ItemAudio("Violao", 500, "assets/Violao.mp3"));
    vitrine.push_back(ItemAudio("Guitarra", 1200, "assets/Guitarra.mp3"));
    vitrine.push_back(ItemAudio("Bateria", 1500, "assets/Bateria.mp3"));
}

std::vector<Item> Loja::getItens() {
    return vitrine; // Retorna a vitrine
}

void Loja::adicionarItem(const Item& item) {
    vitrine.push_back(item);
}

// =========================================================
// FÁBRICA DE ITENS (MÉTODO ESTÁTICO)
// =========================================================
Item* Loja::buscarItemPorId(int id) {
    switch (id) {
        // --- COSMÉTICOS (IDs 100 a 199) ---
        case 100: 
            return new Item("Bone Vermelho", "Cabeca", 50);
        case 101: 
            return new Item("Oculos Escuros", "Rosto", 75);
        case 102:
            return new Item("Camisa Dev C++", "Tronco", 120);

        // --- ÁUDIO / MÚSICA (IDs 200 a 299) ---
        case 200: 
            return new ItemAudio("Lofi Beats", 100, "assets/lofi_study.mp3"); 
        case 201: 
            return new ItemAudio("Rock Classico", 150, "assets/rock_bg.mp3");
        case 202: 
            return new ItemAudio("Piano Suave", 80, "assets/piano.mp3");

        default: 
            return nullptr; // ID não encontrado
    }
}