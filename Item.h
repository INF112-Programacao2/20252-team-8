#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
protected:
    std::string nome;
    std::string tipo;
    int valor;

public:
    Item(std::string nome, std::string tipo, int valor);
    
    // Destrutor virtual obrigatório para herança
    virtual ~Item() {}

    std::string getNome() const;
    std::string getTipo() const;
    int getValor() const;

    // Método virtual: permite que as subclasses tenham comportamentos diferentes
    virtual void usar();
};

#endif