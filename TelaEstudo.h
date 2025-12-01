#ifndef TELA_ESTUDO_H
#define TELA_ESTUDO_H

#include "TelaBase.h"
#include "ControladorEstudo.h"

class telaEstudo : public TelaBase {
public:
    int exibir(Usuario* usuario) override;
    telaEstudo(ControladorEstudo& controlador);
};

#endif