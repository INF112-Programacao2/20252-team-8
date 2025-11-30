#include "item.h" 

Item::Item() 
: id(""),
  nome(""), 
  descricao(""), 
  valor(0) 
{}

Item::Item(const std::string& id, const std::string& nome, const std::string& descricao, int valor)
    : id(id), 
    nome(nome), 
    descricao(descricao), 
    valor(valor) 
    {}

std::string Item::getId() const {
    return this->id;
}

std::string Item::getNome() const {
    return this->nome;
}

std::string Item::getDescricao() const {
    return this->descricao;
}

int Item::getValor() const {
    return this->valor;
}