#ifndef TELA_BASE_H
#define TELA_BASE_H

#include "Usuario.h"
#include <string>
#include <iostream>

class TelaBase {
public:
    // Destrutor Virtual: Essencial quando usamos herança!
    // Garante que o destrutor das filhas seja chamado corretamente.
    virtual ~TelaBase() {}

    // Limpa o console (funciona em Windows e Linux/Mac)
    void limparTela();

    // Mostra um título formatado com linhas divisórias
    void mostrarCabecalho(std::string titulo);

    // Mostra uma mensagem simples (com formatação padrão)
    void mostrarMensagem(std::string mensagem);

    // Mostra uma mensagem de erro em vermelho (ou stderr)
    void mostrarErro(std::string erro);

    // Pausa a execução até o usuário apertar ENTER
    void esperarEnter();

    // Lê um número inteiro do teclado com tratamento de erro
    // (Impede loop infinito se o usuário digitar letras)
    int lerOpcao();

    virtual int exibir(Usuario* usuario) = 0;
};

#endif