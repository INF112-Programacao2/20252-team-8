#ifndef TELA_GAMIFICACAO_H
#define TELA_GAMIFICACAO_H

#include "TelaBase.h"
#include "Usuario.h"
#include <string>

class TelaGamificacao : public TelaBase {
public:
    // Exibe o perfil completo (Menu principal da gamificação)
    void mostrarPerfil(Usuario* usuario);

    // Avisos rápidos (Pop-ups de texto)
    void mostrarGanhoRecursos(int xp, int moedas);
    void mostrarLevelUp(int novoNivel, int moedasGanhas, const std::string& novaBadge);
};

#endif