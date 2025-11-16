#ifndef TELA_LOJA_H
#define TELA_LOJA_H

#include <iostream>
#include "TelaBase.h"

class telaLoja : public telaBase {
    private:
        int mostrarSaldoMoedas();
        void mostrarItensDisponiveis();
    public:
        telaLoja();
        void exibirTela() override;
};

#endif