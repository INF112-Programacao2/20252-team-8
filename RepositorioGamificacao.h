#ifndef REPOSITORIO_GAMIFICACAO_H
#define REPOSITORIO_GAMIFICACAO_H

#include <string>
#include <vector>
#include "RepositorioBase.h"

class RepositorioGamificacao : public RepositorioBase {
    public:
        RepositorioGamificacao(const std::string& nomeUsuario);

        bool getBadge(int badge_idx);
        void setBadge (int badge_idx, bool obtido);

        int getNivel();
        void setNivel (int nivel_atual);

        int getMoedas();
        void setMoedas (int qtd_moedas);

        int getPontos();
        void setPontos (int qtd_pontos);

};

#endif