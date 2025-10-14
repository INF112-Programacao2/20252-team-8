#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>

class Usuario {
private:
    //Dados
    int idUnico;
    std::string nomeDeUsuario;
    std::string email;
    std::string senha;

    //Configurações e progresso
    bool privacidade;
    int pontos;

    //Ponteiros 
    int* idsAmigos;
    std::string* historicoEstudos;

    //Contadores para o número de elementos atuais
    int totalAmigos;
    int totalLogsEstudo;

    //Contadores para a capacidade máxima 
    int capacidadeAmigos;
    int capacidadeLogsEstudo;

public:
    //Construtor
    Usuario(int id, const std::string& usuario, const std::string& email, const std::string& senhaInicial);

    //Destrutor
    ~Usuario();

    //Desabilitar cópia para evitar problemas com ponteiros (Regra dos Três/Cinco)
    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;

    //Métodos públicos
    bool validarLogin(const std::string& usuario, const std::string& senhaFornecida);
    bool trocarSenha(const std::string& senhaAntiga, const std::string& novaSenha);
};

#endif // USUARIO_H