#ifndef LOJA_H
#define LOJA_H

#include <vector>
#include "Item.h"
class Loja {
private:
    std::vector<Item*> vitrine;        // Lista de itens que se pode comprar

public:
    // Construtor: Aqui se preenche a 'vitrine' com os itens disponíveis para compra
    Loja();

    // Destrutor: Importante para limpar a memória dos itens da vitrine ao fechar o programa
    ~Loja();

    // Método usado pelo ControladorLoja para pegar a lista e mostrar na Tela
    std::vector<Item*> getItensParaVenda() const;

    static Item* buscarItemPorId(int id); // Fábrica estática
};
#endif