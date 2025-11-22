#ifndef TELA_LOJA_H
#define TELA_LOJA_H

#include "TelaBase.h"

class telaLoja : public TelaBase {
public:
    int exibir(Usuario* usuario) override;
};

#endif