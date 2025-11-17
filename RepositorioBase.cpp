#include "RepositorioBase.h"
#include <fstream>  // Para std::ifstream (leitura) e std::ofstream (escrita)
#include <iostream> // Para std::cerr (relatar erros)

/**
 * Construtor 1:
 * Recebe um caminho de arquivo direto.
 */
RepositorioBase::RepositorioBase(const std::string& caminho) {
    this->caminhoArquivo = caminho;
    garantirArquivoExiste(); // Garante que o arquivo seja criado se não existir
}

/**
 * Construtor 2:
 * Gera um nome de arquivo (ex: "usuario_repositorio.txt")
 * O parâmetro 'gerarArquivo' é um truque para diferenciar as assinaturas
 * (C++ não permite sobrecarga apenas por lógica interna).
 */
RepositorioBase::RepositorioBase(const std::string& nomeUsuario, bool gerarArquivo) {
    if (gerarArquivo) {
        this->caminhoArquivo = nomeUsuario + "_repositorio.txt";
    } else {
        // Fallback para caso 'gerarArquivo' seja falso, embora o esperado seja true.
        this->caminhoArquivo = nomeUsuario;
    }
    garantirArquivoExiste(); // Garante que o arquivo seja criado
}

/**
 * Função auxiliar privada para garantir a existência do arquivo.
 * Tenta abrir o arquivo em modo 'append'. Se o arquivo não existir,
 * o std::ofstream o criará automaticamente.
 */
void RepositorioBase::garantirArquivoExiste() {
    // std::ios::app (append) abre para escrita no final.
    // Crucialmente, ele CRIA o arquivo se não existir, sem apagar o conteúdo.
    std::ofstream ofs(this->caminhoArquivo, std::ios::app); 

    if (!ofs.is_open()) {
        // Se mesmo assim não conseguir abrir (ex: permissão negada),
        // informa o erro.
        std::cerr << "Erro: Nao foi possivel criar ou abrir o arquivo em: " 
                  << this->caminhoArquivo << std::endl;
    }
    // O arquivo é fechado automaticamente quando 'ofs' sai do escopo.
}

/**
 * Lê todo o conteúdo do arquivo e retorna um vetor de strings,
 * onde cada elemento é uma linha.
 */
std::vector<std::string> RepositorioBase::LerLinhasDoArquivo() {
    std::vector<std::string> linhas;
    std::ifstream ifs(this->caminhoArquivo);

    // Conforme sua solicitação: o construtor garante que o arquivo existe,
    // mas esta função trata erros de leitura (ex: permissão).
    if (!ifs.is_open()) {
        std::cerr << "Erro: Nao foi possivel ler o arquivo (verifique permissoes): " 
                  << this->caminhoArquivo << std::endl;
        
        // Retorna um vetor vazio para sinalizar o erro
        return linhas; 
    }

    std::string linha;
    while (std::getline(ifs, linha)) {
        linhas.push_back(linha);
    }

    // ifs.close() é chamado automaticamente quando sai do escopo.
    return linhas;
}

/**
 * Escreve um vetor de strings no arquivo.
 * Conforme solicitado, ele adiciona (append) as novas linhas ao final.
 * * Este método é 'virtual', então RepositorioItens pode, por exemplo,
 * reimplementá-lo para ler tudo, modificar, e reescrever o arquivo (simulando
 * uma substituição de linha).
 */
void RepositorioBase::escreverLinhasNoArquivo(const std::vector<std::string>& linhasParaEscrever) {
    // Abre em modo 'append' (adicionar ao final)
    std::ofstream ofs(this->caminhoArquivo, std::ios::app); 

    if (!ofs.is_open()) {
        std::cerr << "Erro: Nao foi possivel escrever no arquivo (verifique permissoes): " 
                  << this->caminhoArquivo << std::endl;
        return; // Sai da função se não conseguir escrever
    }

    // Adiciona um separador ou nova linha se o arquivo já tiver conteúdo
    // (Opcional, mas útil para logs)
    // ofs << "\n"; 

    for (const std::string& linha : linhasParaEscrever) {
        ofs << linha << "\n";
    }
    
    // ofs.close() é chamado automaticamente.
}