#include "RepositorioGamificacao.h"
#include "RepositorioBase.h"
#include "Usuario.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Construtor
RepositorioGamificacao::RepositorioGamificacao(const std::string& nomeUsuario) :
    RepositorioBase(nomeUsuario) {
    
    this->_nomeUsuario = nomeUsuario;   // Salva o nome para uso posterior

    // Verifica se usuário é novo
    bool usuarioNovo = true;
    std::string linhaAtual;
    std::ifstream checkArquivo(this->caminhoArquivo);
    
    // Tenta achar "Moedas:" para verificar se o usuário é novo
    if (checkArquivo.is_open()) {
        while (std::getline(checkArquivo, linhaAtual)) {
            if (linhaAtual.find("Moedas:") != std::string::npos) {
                usuarioNovo = false;
                break; 
            }
        }
        checkArquivo.close();
    }

    // Escreve informações se o usuário for novo
    if (usuarioNovo) {
        std::cout << "Criando perfil de gamificação padrão...\n";

        // ORDEM PADRÃO DE DADOS:
        std::vector<std::string> linhasParaAdicionar = {
            "Moedas: 5000",
            "Pontos: 0",
            "Nivel: 0",
            "Badges: NULL"
        };

        this->escreverLinhasNoArquivo(linhasParaAdicionar, true);
    } 
    else {
        std::cout << "Perfil de gamificação carregado.\n";
    }
}


// Le infomações contidas no repositorio e retorna ponteiro Usuario
Usuario* RepositorioGamificacao::carregarUsuario(){
    std::vector<std::string> linhas = LerLinhasDoArquivo();

    // Valores padrão caso falhe a leitura
    int moedas = 0;
    int xp = 0;
    int nivel = 0;
    std::string badge = "NULL";

    for (const std::string& linha : linhas) {
        try {
            if (linha.find("Moedas: ") != std::string::npos) {
                moedas = std::stoi(linha.substr(8)); // Pula "Moedas: "
            }
            else if (linha.find("Pontos: ") != std::string::npos) {
                xp = std::stoi(linha.substr(8));    // Pula "Pontos: "
            }
            else if (linha.find("Nivel: ") != std::string::npos) {
                nivel = std::stoi(linha.substr(7)); // Pula "Nivel: "
            }
            else if (linha.find("Badges: ") != std::string::npos) {
                badge = linha.substr(8);
                // Tratamento extra: Remover quebras de linha (CR/LF) que podem vir do arquivo
                // Isso evita bugs visuais na hora de imprimir
                if (!badge.empty() && badge.back() == '\r') {
                    badge.pop_back();
                }
            }
        } catch (std::exception& e) {
            std::cerr << "Erro ao ler valor do arquivo: " << e.what() << std::endl;
        }
    }

    // Retorna o objeto Usuario montado
    return new Usuario(this->_nomeUsuario, nivel, xp, moedas, badge);
}


// Recebe ponteiro Usuario e atualiza repositorio
void RepositorioGamificacao::salvarUsuario(Usuario* usuario) {
    if (!usuario) return;      // Para o caso de ponteiro nulo

    // 1. Ler badge atual do arquivo
    std::string badgeSalva = "NULL";
    std::vector<std::string> linhasAtuais = LerLinhasDoArquivo();
    for(const auto& linha : linhasAtuais) {
        if(linha.find("Badges: ") != std::string::npos) {
            badgeSalva = linha.substr(8);
            break;
        }
    }

    //2. Montar novo conteúdo no mesmo padrão
    std::vector<std::string> novosDados;
    novosDados.push_back("Moedas: " + std::to_string(usuario->getMoedas()));
    novosDados.push_back("Pontos: " + std::to_string(usuario->getXp()));
    novosDados.push_back("Nivel: " + std::to_string(usuario->getNivel()));
    novosDados.push_back("Badges: " + badgeSalva); // Mantém a badge antiga

    // 3. Sobrescrever arquivo (false = truncate/sobrescrever)
    this->escreverLinhasNoArquivo(novosDados, false);
}


// Le repositorio e retorna badge salva
std::string RepositorioGamificacao::getBadge() {

    std::vector<std::string> linhas = LerLinhasDoArquivo();
    for (const auto& linha : linhas) {
        if (linha.find("Badges: ") != std::string::npos) {
            std::string badgeNoArquivo = linha.substr(8);
            return badgeNoArquivo;
        }
    }
    return "NULL";
}


// Atualiza a badge no repositorio
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

    // Ler tudo
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    
    // Modificar na memória
    for (auto& linha : linhas) {
        if (linha.find("Badges: ") != std::string::npos) {
            linha = "Badges: " + novaBadge;
            break; // Achou e trocou
        }
    }

    // Atualizar repositorio
    this->escreverLinhasNoArquivo(linhas, false);
}


// Le repositorio e retorna nivel salvo (padrão = 0)
int RepositorioGamificacao::getNivel() {
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    for (const auto& linha : linhas) {
        if (linha.find("Nivel: ") != std::string::npos) {
            try {
                return std::stoi(linha.substr(7));
            }
            catch (...) {
                return 0;   // Valor padrão, caso repositório esteja corrompido
            }
        }
    }
    return 0;   // Valor padrão, caso repositório não tenha "Nivel: "
}


// Atualiza nivel no repositorio
void RepositorioGamificacao::setNivel (int nivel_atual) {
    // Ler tudo
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    bool achou = false;  // Flag auxiliar

    // Modificar na memória
    for (auto& linha : linhas) {
        if (linha.find("Nivel: ") != std::string::npos) {
            linha = "Nivel: " + std::to_string(nivel_atual);
            achou = true;
            break; // Achou e trocou
        }
    }

    // Se não achou a linha "Nivel:", adiciona ela no final para não perder o dado
    if (!achou) {
        linhas.push_back("Nivel: " + std::to_string(nivel_atual));
    }

    // Atualizar repositorio (false = sobrescrever/truncate)
    this->escreverLinhasNoArquivo(linhas, false);
}


// Le repositorio e retorna quantidade de moedas
int RepositorioGamificacao::getMoedas() {
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    for (const auto& linha : linhas) {
        if (linha.find("Moedas: ") != std::string::npos) {
            try {
                return std::stoi(linha.substr(8));
            }
            catch (...) {
                return 0;   // Valor padrão, caso repositório esteja corrompido
            }
        }
    }
    return 0;   // Valor padrão, caso repositório não tenha "Moedas: "
}


// Atualiza moedas no repositorio
void RepositorioGamificacao::setMoedas (int qtd_moedas) {
    // Ler tudo
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    bool achou = false;  // Flag auxiliar

    // Modificar na memória
    for (auto& linha : linhas) {
        if (linha.find("Moedas: ") != std::string::npos) {
            linha = "Moedas: " + std::to_string(qtd_moedas);
            achou = true;
            break; // Achou e trocou
        }
    }

    // Se não achou a linha "Moedas:", adiciona ela no final para não perder o dado
    if (!achou) {
        linhas.push_back("Moedas: " + std::to_string(qtd_moedas));
    }

    // Atualizar repositorio (false = sobrescrever/truncate)
    this->escreverLinhasNoArquivo(linhas, false);
}


// Le repositorio e retorna quantidade de pontos
int RepositorioGamificacao::getPontos() {
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    for (const auto& linha : linhas) {
        if (linha.find("Pontos: ") != std::string::npos) {
            try {
                return std::stoi(linha.substr(8));
            }
            catch (...) {
                return 0;   // Valor padrão, caso repositório esteja corrompido
            }
        }
    }
    return 0;   // Valor padrão, caso repositório não tenha "Pontos: "
}


// Atualiza pontos (xp) no repositorio 
void RepositorioGamificacao::setPontos (int qtd_pontos) {
    // Ler tudo
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    bool achou = false;  // Flag auxiliar

    // Modificar na memória
    for (auto& linha : linhas) {
        if (linha.find("Pontos: ") != std::string::npos) {
            linha = "Pontos: " + std::to_string(qtd_pontos);
            achou = true;
            break; // Achou e trocou
        }
    }

    // Se não achou a linha "Pontos:", adiciona ela no final para não perder o dado
    if (!achou) {
        linhas.push_back("Pontos: " + std::to_string(qtd_pontos));
    }

    // Atualizar repositorio (false = sobrescrever/truncate)
    this->escreverLinhasNoArquivo(linhas, false);
}
