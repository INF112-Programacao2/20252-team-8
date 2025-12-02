#ifndef LOJA_H
#define LOJA_H

#include "Item.h"
#include <vector>

class Loja {
private:
    // Voltamos para o nome que você usa: vitrine
    std::vector<Item> vitrine;

public:
    Loja();
    std::vector<Item> getItens();
    void adicionarItem(const Item& item);

    // Método estático (Fábrica)
    static Item* buscarItemPorId(int id);
};

#endif