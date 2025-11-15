#include "inventario.h" 
#include <iostream> 

Inventario::Inventario(int capacidadeMaxima) 
    : itens(capacidadeMaxima),  //Pre-aloca o vetor com 'capacidadeMaxima' slots
      quantidadeAtual(0)       
    {}

void Inventario::adicionarItem(const Item& item) {
    //retorna a capacidade máxima 
    if (this->quantidadeAtual < this->itens.size()) {
        
        //Adiciona o item no proximo "slot" livre
        this->itens[this->quantidadeAtual] = item;

        //Incrementa o contador de itens
        this->quantidadeAtual++;

    } else {
        std::cerr << "Erro: Inventário está cheio! Capacidade máxima atingida." << std::endl;
    }
}

const std::vector<Item>& Inventario::getItens() const {
    return this->itens;
}

int Inventario::getQuantidadeAtual() const {
    return this->quantidadeAtual;
}

int Inventario::getCapacidadeMaxima() const {
    return this->itens.size();
}