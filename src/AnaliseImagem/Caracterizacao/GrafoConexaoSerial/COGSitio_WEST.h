#ifndef COGSitio_WEST_h
#define COGSitio_WEST_h

/**
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
            Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================
Desenvolvido por:	
            Laboratorio de Desenvolvimento de Software Cientifico 	
            [LDSC].
@author     André Duarte Bueno
@file       COGSitio_WEST.h
@begin      Sat Sep 16 2000
@copyright  (C) 2000 by André Duarte Bueno
@email      andreduartebueno@gmail.com
*/

// -----------------------------------------------------------------------
// Bibliotecas C/C++
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// Bibliotecas LIB_LDSC
// -----------------------------------------------------------------------
#ifndef _LIB_LDSC_CLASS_h
#include <Base/_LIB_LDSC_CLASS.h>
#endif

#include <AnaliseImagem/Caracterizacao/GrafoConexaoSerial/COGSitio.h>

// ===============================================================================
// Documentacao Classe: COGSitio_WEST
// ===============================================================================
/** 
 * @brief Representa um sítio conectado a face esquerda do grafo.
 * Assunto:        CGrafo
 * Superclasse:    CParametroSolver->CObjetoGrafo->COGSitio->COGSitio_WEST
 * 
 * O valor de contorno é usado no calculo dos fluxo da malha como  um todo.
 * Ou seja, um algoritimo externo percorre toda a malha, e se o contorno for igual ao 
 * solicitado calcula alguma propriedade neste contorno.
 * @author  André Duarte Bueno		
 * @see     CGrafo
*/
class COGSitio_WEST : public COGSitio
{
// --------------------------------------------------------------Atributos
public:
// -------------------------------------------------------------Construtor
/// Construtor.
 COGSitio_WEST () = default;

// --------------------------------------------------------------Destrutor
/// Destrutor.
  virtual ~ COGSitio_WEST () =  default;

// ----------------------------------------------------------------Métodos
  /// Retorna o tipo de contorno a que pertence
  virtual CContorno::ETipoContorno Contorno () const override  {
     return CContorno::ETipoContorno::WEST;
  }

  /**
  * @brief Função herdada da classe CParametroSolver,
  * usada para calcular o valor de x retorna a pressão na fronteira direita
  */
  virtual long double Go (long double d = 0) override  {
    return x;
  }

// --------------------------------------------------------------------Get
// --------------------------------------------------------------------Set
// -----------------------------------------------------------------Friend
//       friend ostream& operator<< (ostream& os, COGSitio_WEST& obj);
//       friend istream& operator>> (istream& is, COGSitio_WEST& obj);
};

// -----------------------------------------------------------------Friend
// Declaração de Funções Friend
// ostream& operator<< (ostream& os, COGSitio_WEST& obj);
// istream& operator>> (istream& is, COGSitio_WEST& obj);
#endif
