/*
===============================================================================
PROJETO:          Biblioteca LIB_LDSC
                  Ramo: TPadrao_ramo
===============================================================================

Desenvolvido por:	Laboratorio de Desenvolvimento de Software Cientifico
			[LDSC].
@author:          André Duarte Bueno
File:             CImagem3D.cpp
begin:            Sat Sep 16 2000
copyright:        (C) 2000 by André Duarte Bueno
email:            andre@lmpt.ufsc.br
*/

// -----------------------------------------------------------------------
// Bibliotecas C/C++
// -----------------------------------------------------------------------
// #include <fstream>
#include <algorithm>

// -----------------------------------------------------------------------
// Bibliotecas LIB_LDSC
// -----------------------------------------------------------------------
#include <Matriz/CImagem3D.h>

/*
----------------------------------------------------------------------------
Atributos estticos da classe
----------------------------------------------------------------------------
*/
//  int CImagem3D::PRETO=0;
//  int CImagem3D::BRANCO=255;

/*
-------------------------------------------------------------------------
Função:
-------------------------------------------------------------------------
@short  :Verifica se a imagem contem o ponto passado
@author :André Duarte Bueno
@see    :
@param  :
@return :
*/
bool CImagem3D::Contem (int i, int j, int k) const
{
    if (i < nx && j < ny && k < nz)	// acusa ser sempre verdadeira?
        return 1;
    else
        return 0;
};

void CImagem3D::SalvaInformacoesRecontrucao (ofstream & fout) const
{
    if (fout) {
        fout << setw (0) << "\n# fatorAmplificacao: " << fatorAmplificacao << "\n";
        fout << setw (0) << "# sizePixel: " 	    << sizePixel 	     << "\n";
				fout << setw (0) << "# numeroPixelsBorda: " << numeroPixelsBorda;
    }
}

bool CImagem3D::LeInformacoesRecontrucao (ifstream & fin)
{
    if (fin.good()) {
        int posInicial = fin.tellg();		//guarda a posição de leitura no arquivo.
        char linha[256];
        string aux;
        fin.seekg(0, ios::beg);			//posiciona o ponteiro de leitura no começo do arquivo
        do {
            fin >> aux;
        } while ( ( aux != "#" ) and ( fin.tellg() < 128 ) ); //
        bool encontrou = false;
        if (aux == "#") {
            do {
                fin >> aux;
                if (aux == "fatorAmplificacao:") {
                    fin >> fatorAmplificacao;
                    //cerr << "\nfatorAmplificacao=" << fatorAmplificacao << endl;
                    encontrou = true;
                } else if (aux == "sizePixel:") {
                    fin >> sizePixel;
                    encontrou = true;
                    //cerr << "\nsizePixel=" << sizePixel << endl;
                } else if (aux == "numeroPixelsBorda:") {
                    fin >> numeroPixelsBorda;
                    //cerr << "\nnumeroPixelsBorda=" << numeroPixelsBorda << endl;
                    encontrou = true;
                }
                if ( encontrou ) {
                    fin >> aux;
                } else {
                    fin.getline(linha, 256);
                    fin >> aux;
                }
            } while ( aux == "#" );
        }
        fin.seekg(posInicial, ios::beg);	//reposiciona o ponteiro de leitura para a posição inicial;
        return encontrou;
    }
    return false;
}

bool CImagem3D::LeInformacoesRecontrucao (string fileName)
{
    ifstream fin;									// Ponteiro para arquivo de disco
    CBaseMatriz::AbreArquivo (fin, fileName);			// Abre o arquivo de disco no formato correto
    if (fin.good ()) {								// Se o arquivo foi corretamente aberto
        return LeInformacoesRecontrucao (fin);
    }
    return false;
}

/*
-------------------------------------------------------------------------
Funcao:
-------------------------------------------------------------------------
@short  : Salva dados do cabecalho
@author : Andre Duarte Bueno, modificada por: Leandro Puerari
@see    :
@param  :
@return :
*/
void CImagem3D::SalvaCabecalho (ofstream & fout) const {
	CMatriz3D::SalvaCabecalho (fout);
	SalvaInformacoesRecontrucao(fout);
}

