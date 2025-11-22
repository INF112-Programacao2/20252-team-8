#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include "Item.h"

class Inventario {
private:
    std::vector<Item> itens;   //Lista de itens
    
    int quantidadeAtual;    //Quantidade de itens 
public:
    //Construtor com capacidade inicial = 100
    Inventario(int capacidadeMaxima = 100);

    //Adiciona item se nao ultrapassar a capacidade
    void adicionarItem(const Item& item);

    const std::vector<Item>& getItens() const;

    int getQuantidadeAtual() const;

    int getCapacidadeMaxima() const;

    bool salvarInventario(const std::string& nomeArquivo) const;
};
#endif
