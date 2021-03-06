//  ítens conferidos: 1[ ] 2[ ] 3[ ] 4[ ] 5[ ] 6[ ] 7[ ] 8[ ] 9[ ] 10[ ]

/*
----------------------------------------------------------------------------
PROJETO:	Anaimp
	Analise de Imagens de Meios Porosos
----------------------------------------------------------------------------

Desenvolvido por:	Laboratorio de Desenvolvimento de Software Cientifico   dos Materiais.
Programadores:   	Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani, Liang Zirong, Paulo C. Philippi, ...
Copyright @1997:  	Todos os direitos reservados.
Nome deste arquivo:	TCFEMMIDFdi.cpp
Nome da classe:      TCFEMMIDFdi
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
Descricao:	 Implementa a função CriaMascara da classe TCFEMMIDFdi.
*/

//  ----------------------------------------------------------------------------
//  Bibliotecas
//  ----------------------------------------------------------------------------
// using namespace std;
#ifndef TCFEMMIDFdi_h
#include "AnaliseImagem/Filtro/FEspacial/FEMorfologiaMatematica/TCFEMMIDFdi.h"	//  Classe base
#endif
#include "AnaliseImagem/Geometria/Bola/BCDiscreta/CBCdi.h"


/*
==================================================================================
Documentacao 		CriaMascara
==================================================================================
Descrição:        Funcao que cria a mascara de chanfro adequada.
Pré-condições:
Excessões:        tipos de excessoes
Concorrência:
Tempo processamento(s):
Tamanho(bits):
Comentarios:
Programador:      Andre Duarte Bueno
*/
template<typename T>
void TCFEMMIDFdi<T>::CriaMascara (unsigned int _tamanhoMascara) {
	if (this->mask) {			//  se existe uma mascara
		if (this->mask->NX () == _tamanhoMascara) {	//  e é do mesmo  tamanho
			return;			//  sai
		}
		delete this->mask;		//  se  não é do mesmo tamanho apaga objeto mask
	}				//  e abaixo cria uma nova
	this->mask = new CBCdi (_tamanhoMascara, mi, raioBase);	//  se não existe a mascara, cria uma nova
}

//  Mascara de chanfro d4
//      1
//   1  p  1
//      1
//  TCMatriz2D< int > * TCFEMMIDFdi::Go( TCMatriz2D< int > *& matriz)
//  Obs
template<typename T>
TCMatriz2D<T> * TCFEMMIDFdi<T>::Go (TCMatriz2D<T> * &matriz, unsigned int /*_tamanhoMascara */ ) {
	this->ExecutadaPorGo (matriz); //  verifica a matriz e copia dados para data2D
	//  IDFNosPlanosDeContorno(mi); //  verifica planos de contorno
	//  ida    MinimoIda
	//  IDFNosPlanosDeContornoIDA(mi); //  verifica planos de contorno
	int x, y; //  Indices para percorrer a matriz
	for (y = 1; y < this->ny - 1; y++)	{//  NY() é igual a this->ny, this->ny da matriz idf
		//  y_1=y-1;
		for (x = 1; x < this->nx - 1; x++)
			if (this->data2D[x][y] != 0)	//  Testa a imagem, se nao for solido entra
			{			//
				this->minimo = this->raioMaximo;	//  64000 aqui 65536
				//  -----------------------------------------------------------
				this->min (this->data2D[x - 1][y] + mi);	/*ponto[x][y] */
				this->min (this->data2D[x][y - 1] + mi);
				//  -----------------------------------------------------------
				this->data2D[x][y] = this->minimo;
			}
	}
	//  volta  MinimoVolta
	//       IDFNosPlanosDeContornoVOLTA(mi);
	//  int ym1;                              //  otimizacao
	for (y = this->ny - 2; y > 0; y--)	//  -2 pois começa do zero e a mascara tem tamanho 1
	{				//  ym1=y+1;
		for (x = this->nx - 2; x > 0; x--)
			if (this->data2D[x][y] != 0)	//  Se nao for solido, entra
			{
				this->minimo = this->data2D[x][y];	//  armazena valor minimo ida
				//  -----------------------------------------------------------

				this->min (this->data2D[x][y + 1] + mi);
				this->min (this->data2D[x + 1][y] + mi);

				//  -----------------------------------------------------------
				this->data2D[x][y] = this->minimo;
			}
	}
	return this->pm;
}
