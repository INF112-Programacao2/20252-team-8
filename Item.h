#ifndef ITEM_H
#define ITEM_H
#include <string> 

class Item {
private:
    std::string id;
    std::string nome;
    std::string descricao;
    int valor;  //Custo do item 

public:
    //Necessario para o vector para criar "slots" vazios quando o vetor eh pre-alocado
    Item(); 

    Item(const std::string& id, const std::string& nome, const std::string& descricao, int valor);

    std::string getId() const;
    std::string getNome() const;
    std::string getDescricao() const;
    int getValor() const;
};
#endif