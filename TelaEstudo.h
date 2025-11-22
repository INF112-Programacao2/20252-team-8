#ifndef TELA_ESTUDO_H
#define TELA_ESTUDO_H

#include "TelaBase.h"

class telaEstudo : public TelaBase {
public:
    int exibir(Usuario* usuario) override;
};

#endif