#ifndef CONTROLADORINVENTARIO_H
#define CONTROLADORINVENTARIO_H

#include "ControladorLoja.h"
#include "miniaudio.h" 

class ControladorInventario : public ControladorLoja {
private:
    ma_engine engine;
    ma_sound som;
    bool estaTocando;

public:
    ControladorInventario(int tempo_inicial);
    ~ControladorInventario();

    void tocarMusica(std::string nomeArquivo);
    void pararMusica();
};
#endif