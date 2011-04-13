#ifndef CFEEsqueleto_h
#define CFEEsqueleto_h

/*
----------------------------------------------------------------------------
Bibliotecas e Defines
----------------------------------------------------------------------------
*/
// inclue a biblioteca de filtros
#ifndef CFEspacial_h
#include <Filtro/FEspacial/CFEspacial.h>
#endif

// inclue a biblioteca de filtros
#ifndef CMatriz2D_h
#include <Matriz/CMatriz2D.h>
#endif

/*
----------------------------------------------------------------------------
PROJETO:		Bibliotecas LDSC
		       	Biblioteca para manipulacao de imagens
----------------------------------------------------------------------------

Desenvolvido por:      	Laboratorio de Desenvolvimento de Software Cientifico
       			dos Materiais.
Programadores:         Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani,
    			Liang Zirong,
		     	Paulo C. Philippi, Cunha Neto J.A.B.,Nathan Mendes,...
Copyright @1997:  	Todos os direitos reservados.
Nome deste arquivo:	CFEEsqueleto.h
Nome da classe:      CFEEsqueleto
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
*/

/**
 * @brief Classe para determinação do esqueleto de imagem imagem.
 * Herdeira de CFEspacial.
*/

class CFEEsqueleto : public CFEspacial
{

// Atributos
protected:
  int valorEsqueleto;		///< Valor final dos pixel's que pertencem ao esqueleto
  int valorObjeto;		///< Valor final dos pixel's que não pertencem ao esqueleto
				///< mas fazem parte do objeto inicial (antes descascamento)

// Métodos
public:			/// Construtor
  CFEEsqueleto (CMatriz2D * &matriz, unsigned int _tamanhoMascara = 0)
	: CFEspacial (matriz, _tamanhoMascara), valorEsqueleto (1), valorObjeto (0)
  {
  }

  /// Destrutor
   ~CFEEsqueleto ()
  {
  }

  /// Seta valorEsqueleto
  void ValorEsqueleto (int ve)
  {
    valorEsqueleto = ve;
  }

  /// Obtêm valorEsqueleto
  int ValorEsqueleto () const
  {
    return valorEsqueleto;
  }

  /// Seta valorObjeto
  void ValorObjeto (int vo)
  {
    valorObjeto = vo;
  }

 /// Obtêm valorEsqueleto
  int ValorObjeto () const
  {
    return valorObjeto;
  }


  /// Método usado para eliminar pés de galinha (ramos mortos).
  virtual void EliminaPeGalinha (CMatriz2D * imagem);	//
};
#endif //  CFEEZhangSuen_h
