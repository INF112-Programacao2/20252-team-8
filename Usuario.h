#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Inventario.h" 
#include "HistoricoEstudos.h" 

class Usuario {
private:
    std::string nomeDeUsuario;
    int moedas;
    int pontos;
    int nivel;

    //Composicao 
    HistoricoEstudos historico;
    Inventario inventario;

public:
    Usuario();

    int getMoedas() const; 

    std::string getNome() const;

    void setNome(const std::string& novoNome);

    Inventario& getInventario();

    HistoricoEstudos& getHistorico();
};
#endif

