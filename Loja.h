#ifndef LOJA_H
#define LOJA_H

#include <vector>
#include "Item.h"
class Loja {
private:
    std::vector<Item> itens;        // Lista de itens
    int capacidadeMaxima;           // Capacidade máxima da loja

public:
    // Construtor com capacidade inicial = 100
    Loja(int capacidadeMaxima = 100);

    // Adiciona item se não ultrapassar a capacidade
    void adicionarItem(const Item& item);

    // Remove item por ID
    bool removerItem(const std::string& id);

    // Busca item por ID
    Item* buscarItem(const std::string& id);

    // Getters
    const std::vector<Item>& getItens() const;
    int getQuantidadeAtual() const;  
    int getCapacidadeMaxima() const;

    // Verifica se está cheia
    bool estaCheia() const;

    // Salvar em arquivo
    bool salvarLoja(const std::string& nomeArquivo) const;

    // Carregar do arquivo
    bool carregarLoja(const std::string& nomeArquivo);

    static Item* buscarItemPorId(int id); // Fábrica estática
};
#endif