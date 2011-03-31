#ifndef CFEConectividade3D_h
#define CFEConectividade3D_h
/*
----------------------------------------------------------------------------
PROJETO:	LIB_LDSC
		Bibliotecas de Objetos
----------------------------------------------------------------------------
Desenvolvido por:Laboratorio de Desenvolvimento de Software Cientifico e Propriedades 
Termofisicas  dos Materiais.
Programadores:   Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani,
 Liang Zirong, Paulo C. Philippi,
							Marcos Damiani,...
Copyright @1997:    Todos os direitos reservados.
Nome deste arquivo: CFEConectividade3D.h
Nome da classe:     CFEConectividade3D
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
----------------------------------------------------------------------------
*/

#ifndef __IOSTREAM_H
#include <iostream>
#endif
/*
#ifndef _LIB_LDSC_CLASS_h
#include <Base/_LIB_LDSC_CLASS.h>
#endif
*/
#include <Rotulador/CRotulador3D.h>
#include <Matriz/CImagem3D.h>
#include <Matriz/CMatriz3D.h>
#include <set>

/**
 * @brief Declara a classe CFEConectividade3D.
 * 
 * A classe CFEConectividade3D representa conceitos geométricos.
 * 
 * A classe  CFEConectividade3D é filha da classe CRotulador3D. 
 * De forma que recebe uma imagem  no construtor e processa a 
 * rotulagem através da função Go (da mesma forma que na classe pai).
 * 
 * Acrecenta entretanto a função GetImagemConectada, que retorna os objetos da
 * imagem que tiverem conectividade entre a primeira e última camada.
 * 
*/

using namespace std;

class CFEConectividade3D : public CRotulador3D
{
// Atributos
protected:
  int INDICE;

public:
  /// Construtor (recebe CImagem3D)
  CFEConectividade3D ( CImagem3D * imagem, int indice = 1, int fundo = 0 ) : CRotulador3D ( dynamic_cast<CMatriz3D *>(imagem) ), INDICE(indice) { FUNDO = fundo; }
  
  /// Construtor (recebe CMatriz3D)
  CFEConectividade3D ( CMatriz3D * imagem, int indice = 1, int fundo = 0 ) : CRotulador3D ( imagem ), INDICE(indice) { FUNDO = fundo; }
  
  /// Destrutor
  virtual ~ CFEConectividade3D () { }
  
// Métodos  
  /// Retorna a lista de objetos conectados.
  set<int> GetObjetosConectados ( CImagem3D * pmOrig);
  
  /// Retorna a lista de objetos conectados.
  set<int> GetObjetosConectados ( CMatriz3D * pmOrig);
  
  /// Verifica se a imagem possui conectividade no eixo Y.
  bool isConnected ( CImagem3D * pmOrig);
  
  /// Verifica se a matriz possui conectividade no eixo Y.
  bool isConnected ( CMatriz3D * pmOrig);

  /// Retorna uma nova imagem conectada de acordo com o indice e com o valor de fundo informados.
  CImagem3D * GetImagemConectada ( CImagem3D * pmOrig);

  /// Retorna uma nova matriz conectada de acordo com o indice e com o valor de fundo informados.
  CMatriz3D * GetMatrizConectada ( CMatriz3D * pmOrig);

  /// Altera Imagem 3D retornando Imagem 3D conectada.
  bool Go (CImagem3D * pmCon);
  
  /// Altera Matriz 3D retornando matriz 3D conectada.
  bool Go (CMatriz3D * pmCon);
  
  /// Seta valores de INDICE E FUNDO
  void IndiceFundo (int _indice, int _fundo) {
  	INDICE = _indice;
  	FUNDO = _fundo;
  }
  /// Retorna valor de INDICE
  int Indice ( ) {
  	return INDICE;
  }

  /// Retorna valor de FUNDO
  int Fundo ( ) {
  	return FUNDO;
  }

};

#endif
