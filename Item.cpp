#include "Item.h"

Item::Item(std::string nome, std::string tipo, int valor) 
    : nome(nome), tipo(tipo), valor(valor) {}

std::string Item::getNome() const { return nome; }
std::string Item::getTipo() const { return tipo; }
int Item::getValor() const { return valor; }

void Item::usar() {
    // Comportamento padrão: apenas avisa que usou
    std::cout << ">> Voce utilizou o item: " << nome << std::endl;
}