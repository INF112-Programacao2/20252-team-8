#ifndef CONTROLADORINVENTARIO_H
#define CONTROLADORINVENTARIO_H

#include "Loja.h"
#include "RepositorioInventario.h"
#include "miniaudio.h" 

class ControladorInventario {
private:
    ma_engine engine;
    ma_sound som;
    bool estaTocando;

public:
    ControladorInventario(int tempo_inicial);
    ~ControladorInventario();

    void tocarMusica(std::string nomeArquivo);
    void pararMusica();
    void executar();
};
#endif