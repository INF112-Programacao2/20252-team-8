#include "RepositorioGamificacao.h"
#include "RepositorioBase.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

RepositorioGamificacao::RepositorioGamificacao(const std::string& nomeUsuario) :
    RepositorioBase(nomeUsuario) {
    
    // Verifica se usuário é novo
    bool usuarioNovo = true;
    std::string linhaAtual;
    std::ifstream checkArquivo(this->caminhoArquivo);
    
    if (checkArquivo.is_open()) {
        while (std::getline(checkArquivo, linhaAtual)) {
            // Verifica se a linha contem a chave "Moedas:"
            if (linhaAtual.find("Moedas:") != std::string::npos) {
                usuarioNovo = false;
                break; // Não precisa ler o resto.
            }
        }
        checkArquivo.close();
    }

    // Escreve informações se o usuário for novo
    if (usuarioNovo) {
        std::cout << "Criando perfil de gamificação padrão...\n";

        // Inicialização de vetor com informações do repositório
        std::vector<std::string> linhasParaAdicionar = {
            "Moedas: 0",
            "Pontos: 0",
            "Nivel: 0",
            "Badges: NULL"
        };

        this->escreverLinhasNoArquivo(linhasParaAdicionar);
    } 
    else {
        std::cout << "Perfil de gamificação carregado.\n";
    }
}


bool RepositorioGamificacao::getBadge(int badge_idx) {
    // MAPEAMENTO: Traduz o ID (1,2,3,4) para o Texto esperado
    std::string badgeEsperada;
    
    switch (badge_idx) {
        case 1: badgeEsperada = "Calouro"; break;
        case 2: badgeEsperada = "Estudante"; break;
        case 3: badgeEsperada = "Veterano"; break;
        case 4: badgeEsperada = "Formando"; break;
        default: 
            // Se passar um número inválido (ex: 5), retorna false 
            return false; 
    }
    std::ifstream repositorio (this->caminhoArquivo);

    std::string linhaAtual;
    std::string badgeNoArquivo = "NULL"; // Valor padrão caso não ache nada

    // LEITURA DO ARQUIVO
    if (repositorio.is_open()) {
        while (std::getline(repositorio, linhaAtual)) {
            // Verifica se a linha contem a chave "Badges: "
            if (linhaAtual.find("Badges: ") != std::string::npos) {
                badgeNoArquivo = linhaAtual.substr(8);  // Le até o fim da linha
                break;
            }
        }
        repositorio.close();
    }
    // COMPARAÇÃO E RETORNO
    // Se o que está no arquivo for igual ao que o ID pede, retorna true.
    if (badgeNoArquivo == badgeEsperada) {
        return true;
    } else {
        return false;
    }

}


void RepositorioGamificacao::setBadge(int badge_idx) {
    std::string novaBadge;
    switch (badge_idx) {
        case 1: novaBadge = "Calouro"; break;
        case 2: novaBadge = "Estudante"; break;
        case 3: novaBadge = "Veterano"; break;
        case 4: novaBadge = "Formando"; break;
        default:
            std::cerr << "Erro: Indice de badge invalido (use 1-4)." << std::endl;
            return; 
    }

    // LER TODO O ARQUIVO PARA A MEMÓRIA
    std::vector<std::string> linhasDoArquivo;
    std::string linhaAtual;
    std::ifstream leitura(this->caminhoArquivo);

    if (leitura.is_open()) {
        while (std::getline(leitura, linhaAtual)) {
            // Se encontramos a linha de Badges, substituímos ela pela nova versão
            if (linhaAtual.find("Badges: ") != std::string::npos) {
                linhasDoArquivo.push_back("Badges: " + novaBadge);
            } 
            else {
                // Se não for a linha de badges, copiamos a linha original
                linhasDoArquivo.push_back(linhaAtual);
            }
        }
        leitura.close();
    } else {
        std::cerr << "Erro: Nao foi possivel ler o repositorio." << std::endl;
        return;
    }

    // REESCREVER O ARQUIVO
    // ofstream APAGA tudo o que tinha antes (truncate) e começa do zero
    std::ofstream escrita(this->caminhoArquivo);

    if (escrita.is_open()) {
        for (const std::string& linha : linhasDoArquivo) {
            escrita << linha << std::endl;
        }
        escrita.close();
        std::cout << "Badge atualizada com sucesso para: " << novaBadge << std::endl;
    } else {
        std::cerr << "Erro crítico: Nao foi possivel salvar a nova badge." << std::endl;
    }
}

int RepositorioGamificacao::getNivel() {

}

void RepositorioGamificacao::setNivel (int nivel_atual) {

}

int RepositorioGamificacao::getMoedas() {

}

void RepositorioGamificacao::setMoedas (int qtd_moedas) {

}

int RepositorioGamificacao::getPontos() {

}

void RepositorioGamificacao::setPontos (int qtd_pontos) {

}
