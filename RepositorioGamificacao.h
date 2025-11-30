#ifndef REPOSITORIO_GAMIFICACAO_H
#define REPOSITORIO_GAMIFICACAO_H

#include <string>
#include <vector>
#include "RepositorioBase.h"
#include "Usuario.h"

class RepositorioGamificacao : public RepositorioBase {
    private:
        std::string _nomeUsuario;   // Será usado no carregarUsuario()
    public:
        RepositorioGamificacao(const std::string& nomeUsuario);

        // Método para carregar estado atual do usuário
        Usuario* carregarUsuario();

        // Método para salvar o estado atual
        void salvarUsuario(Usuario* usuario);

        // Métodos específicos para manipulação direta do arquivo
        std::string getBadge();
        void setBadge (int badge_idx);

        int getNivel();
        void setNivel (int nivel_atual);

        int getMoedas();
        void setMoedas (int qtd_moedas);

        int getPontos();
        void setPontos (int qtd_pontos);

};

#endif