#ifndef TELA_LOJA_H
#define TELA_LOJA_H

#include "TelaBase.h"
#include "Item.h"
#include "Usuario.h"
#include <vector>

class TelaLoja : public TelaBase {
public:
    // Retorna o índice do item escolhido ou 0 para voltar
    int mostrarVitrine(const std::vector<Item*>& itens, const Usuario& usuario);
};

#endif