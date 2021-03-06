/*
  ===============================================================================
  PROJETO:    Biblioteca LIB_LDSC
  Assunto/Ramo: Programa de teste da LIB_LDSC
  ===============================================================================

  Desenvolvido por:
  Laboratorio de Desenvolvimento de Software Cientifico
  [LDSC].
  @author     Andre Duarte Bueno
  @file       main.cpp
  @begin      Sat Sep 16 2000
  @copyright  (C) 2000 by Andre Duarte Bueno
  @email      andre@lmpt.ufsc.br
*/

// ----------------------------------------------------------------------
// Bibliotecas C/C++
// ----------------------------------------------------------------------
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>       // EXIT_SUCCESS;
using namespace std;

// ----------------------------------------------------------------------
// Bibliotecas
// ----------------------------------------------------------------------
#include <AnaliseImagem/Simulacao/ConfiguracaoEquilibrio/CConfiguracoesEquilibrio2D.h>
#include <MetNum/Matriz/TCMatriz2D.h>

/**
 * Função main() inclui teste da biblioteca
 * Cria imagem 2D a partir do argumento passado para o programa na linha de comando,
 * ou solicitando o nome do arquivo de disco
 * A seguir cria objeto para determinação das configurações de equilíbrio
 * e chama o método Go().
 * @param argc
 * @param argv[]
 * @return
 */
int main(int argc, char *argv[])
{
    cout  << "\n================================================================================"
          << "\n====================== Programa de teste da LIB_LDSC ==========================="
          << "\n================================================================================" << endl;

    cout  << "\n================================================================================"
          << "\nUSO:"
          << "\n./confeq2D nomeImagem"
          << "\nou"
          << "\n./confeq2D"
          << "\n================================================================================" << endl;

    TCMatriz2D<int>* img2D { nullptr }; // ponteiro para imagem

    if (argc==2)
    {
        // Cria imagem 2D
        img2D = new TCMatriz2D<int>(argv[1]);
        if (img2D == NULL)
        {
            cerr << "\nFalha abertura arquivo: " << argv[1] << endl;
            return 0;
        }
    }
    else
    {
        string nomeArquivo;
        cout << "\nEntre com o nome da imagem 2D (ex: imagem.pbm ):";
        getline(cin,nomeArquivo);
        // Cria imagem 2D
        img2D = new TCMatriz2D<int>(nomeArquivo);
        if (img2D == NULL)
        {
            cerr << "\nFalha abertura arquivo: " << argv[1] << endl;
            return 0;
        }
    }
    
	// Cria arquivo de saída
    ofstream fout("confeq2D.out");
    // Cria objeto para determinação das configurações de equilíbrio
    CConfiguracoesEquilibrio2D *confeq { nullptr };
    confeq = new CConfiguracoesEquilibrio2D ( fout );
    if (confeq == NULL)
    {
        cerr << "\nFalha criação confeq: saindo \n";
        return 0;
    }

    cout << "Deseja modificar atributos da simulação e dos fluidos (s)(n)? ";
    char resp;
    bool disco = 0;
    cin >> resp;
    cin.get();
    if (resp == 's' || resp == 'S')
    {
        cout << "\n\nSalvarResultadosParciaisDisco (gera diversos arquivos com as camaras)? (0) não, (1) sim.";
        cin >> disco;
        cin.get();
        confeq->SalvarResultadosParciaisDisco(disco);

        int fluidoAcompressibilidade;
        cout << "\n\nEntre com a compressibilidade do fluidoA: (0) não compressível (1) compressível? ";
        cout << "\ndefault=" << confeq->fluidoA->Compressibilidade() << endl;
        cin >> fluidoAcompressibilidade;
        cin.get();
        confeq->fluidoA->Compressibilidade(fluidoAcompressibilidade);
        cout << "Entrou com o valor fluidoAcompressibilidade: " << fluidoAcompressibilidade << endl;

        int fluidoBmolhabilidade;
        cout << "\n\nEntre com a molhabilidade do fluidoB: (0) não molhante (1) molhante? ";
        cout << "\ndefault=" << confeq->fluidoB->Molhabilidade() << endl;
        cin >> fluidoBmolhabilidade;
        cin.get();
        confeq->fluidoB->Molhabilidade(fluidoBmolhabilidade);
        cout << "Entrou com o valor fluidoBmolhabilidade: " <<  fluidoBmolhabilidade << endl;
    }

    cout << "Propriedades: "  << endl;
    cout << "confeq->fluidoA->Compressibilidade(): " << confeq->fluidoA->Compressibilidade() << endl;
    cout << "confeq->fluidoB->Molhabilidade() : " << confeq->fluidoB->Molhabilidade() << endl;
    cout << "confeq->SalvarResultadosParciaisDisco()=" << confeq->SalvarResultadosParciaisDisco() << endl;

    // Executa determinação das configurações de equilíbrio
    cout << "\n================> Processando dados (pode demorar)." << endl;
    confeq->Go( img2D );

    // Destróe objetos criados
    delete img2D;
    delete confeq;
    return EXIT_SUCCESS;
}

