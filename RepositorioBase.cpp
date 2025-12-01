#include "RepositorioBase.h"
#include <fstream>  
#include <iostream> 

// Construtor (cria 'usuário_repositorio.txt')
RepositorioBase::RepositorioBase(const std::string& nomeUsuario) {
    this->caminhoArquivo = nomeUsuario + "_repositorio.txt";

    // Verifica se o repositório já existe, abrindo-o no modo escrita
    std::ifstream arquivo (caminhoArquivo);
    if (arquivo.good()){
        std::cout << "\nBem vindo novamente, " << nomeUsuario << " !\n";
        arquivo.close();
    }
    else {
        // Cria arquivo em modo escrita e padroniza formato
        std::ofstream arquivo (caminhoArquivo);
        
        if (!arquivo.is_open()){
            throw std::runtime_error("ERRO: Não foi possível criar o arquivo.");
        }
        else {
            std::cout << "\nRepositório criado com sucesso!\n";
        }
    
        arquivo << "REPOSITÓRIO USUÁRIO: " << nomeUsuario << std::endl;
        arquivo.close();
    }
}


// Construtor (recebe nome do arquivo para gerar txt)
RepositorioBase::RepositorioBase(const std::string& nomeRepo, bool isCaminho) {
    this->caminhoArquivo = nomeRepo;

    // Apenas garante que o arquivo exista (append mode cria se não existir)
    std::ofstream arquivo(this->caminhoArquivo, std::ios::app);
    
    if (!arquivo.is_open()) {
        throw std::runtime_error("ERRO: Nao foi possivel criar/abrir o arquivo: " + nomeRepo);
    }

    arquivo.close();

}


// Lê todo o conteúdo do arquivo e retorna um vetor de strings, onde cada elemento é uma linha.
std::vector<std::string> RepositorioBase::LerLinhasDoArquivo() {
    std::vector<std::string> linhas;
    std::ifstream ifs(this->caminhoArquivo);

    if (!ifs.is_open()) {
        std::cerr << "Erro: Nao foi possivel ler o arquivo (verifique permissoes): " 
                  << this->caminhoArquivo << std::endl;
        
        throw std::runtime_error("ERRO: Não foi possível ler o arquivo.");
    }

    std::string linha;
    while (std::getline(ifs, linha)) {
        linhas.push_back(linha);
    }

    ifs.close();
    return linhas;
}


// Escreve um vetor de strings no arquivo.
// Usa bool para decidir entre modo append (adicionar escrita no final do arquivo) ou truncate (reescrita total)
// Padrão é truncate
void RepositorioBase::escreverLinhasNoArquivo(const std::vector<std::string>& linhasParaEscrever, bool modoAppend) {
    
    // Define o modo de abertura com base no booleano
    std::ios_base::openmode modo = modoAppend ? std::ios::app : std::ios::trunc;

    std::ofstream ofs(this->caminhoArquivo, modo); 

    if (!ofs.is_open()) {
        std::cerr << "Erro: Nao foi possivel escrever no arquivo (verifique permissoes): " 
                  << this->caminhoArquivo << std::endl;
        return; // Sai da função se não conseguir escrever
    }

    for (const std::string& linha : linhasParaEscrever) {
        ofs << linha << "\n";
    }
    
}