#include "usuario.h"

//Implementação do Construtor
Usuario::Usuario(int id, const std::string& usuario, const std::string& email, const std::string& senhaInicial) {
    this->idUnico = id;
    this->nomeDeUsuario = usuario;
    this->email = email;
    this->senha = senhaInicial;

    //Valores padrão
    this->privacidade = false;
    this->pontos = 0;

    //Alocação de memória inicial
    this->capacidadeAmigos = 10; // Começa com espaço para 10 amigos
    this->totalAmigos = 0;
    this->idsAmigos = new int[this->capacidadeAmigos]; // Aloca memória para 10 inteiros

    this->capacidadeLogsEstudo = 10; // Começa com espaço para 10 logs
    this->totalLogsEstudo = 0;
    this->historicoEstudos = new std::string[this->capacidadeLogsEstudo]; // Aloca memória para 10 strings
}

//Implementação do Destrutor
Usuario::~Usuario() {
    delete[] this->idsAmigos;
    delete[] this->historicoEstudos;
}

//Implementação do método para validar o login
bool Usuario::validarLogin(const std::string& usuario, const std::string& senhaFornecida) {
    if (this->nomeDeUsuario == usuario && this->senha == senhaFornecida) {
        std::cout << "Login validado com sucesso!\n";
        return true;
    }
    std::cout << "Usuário ou senha incorretos.\n";
    return false;
}

//Implementação do método para trocar a senha
bool Usuario::trocarSenha(const std::string& senhaAntiga, const std::string& novaSenha) {
    if (this->senha == senhaAntiga) {
        this->senha = novaSenha;
        std::cout << "Senha alterada com sucesso!\n";
        return true;
    }
    std::cout << "Senha antiga incorreta.\n";
    return false;
}