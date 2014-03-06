#ifndef CObjetoRede_Sitio_WEST_h
#define CObjetoRede_Sitio_WEST_h

/**
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
            Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================
Desenvolvido por:
            Laboratorio de Desenvolvimento de Software Cientifico [LDSC].
@author     André Duarte Bueno
@file       CObjetoRede_Sitio_WEST.h
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

#include <AnaliseImagem/Caracterizacao/GrafoConexaoSerial/CObjetoRede_Sitio.h>

// ===============================================================================
// Documentacao Classe: CObjetoRede_Sitio_WEST
// ===============================================================================
/**
 * @brief Representa um sítio conectado a face esquerda do grafo.
 * Assunto:        CGrafo
 * Superclasse:    CParametroSolver->CObjetoGrafo->CObjetoRede_Sitio->CObjetoRede_Sitio_WEST
 *
 * O valor de contorno é usado no calculo dos fluxo da malha como  um todo.
 * Ou seja, um algoritimo externo percorre toda a malha, e se o contorno for igual ao
 * solicitado calcula alguma propriedade neste contorno.
 * @author  André Duarte Bueno
 * @see     CGrafo
 * @ingroup  HCObjetoGrafo
*/
class CObjetoRede_Sitio_WEST : public CObjetoRede_Sitio {
// --------------------------------------------------------------Atributos
public:
// -------------------------------------------------------------Construtor
/// Construtor.
     CObjetoRede_Sitio_WEST () = default;

// --------------------------------------------------------------Destrutor
/// Destrutor.
     virtual ~ CObjetoRede_Sitio_WEST () =  default;

// ----------------------------------------------------------------Métodos
     /// Retorna o tipo de objeto do grafo.
     virtual ETipoObjetoGrafo Tipo () const  override { return ETipoObjetoGrafo::ObjetoRede_Sitio_WEST;  }

     /// Retorna o tipo de contorno a que pertence
     inline virtual CContorno::ETipoContorno Contorno () const override  {
          return CContorno::ETipoContorno::WEST;
     }

     /**
     * @brief Função herdada da classe CParametroSolver,
     * usada para calcular o valor de x retorna a pressão na fronteira direita
     */
     inline virtual long double Go ( long double d = 0 ) override  {
          return x;
     }

// --------------------------------------------------------------------Get
// --------------------------------------------------------------------Set
// -----------------------------------------------------------------Friend
//       friend ostream& operator<< (ostream& os, CObjetoRede_Sitio_WEST& obj);
//       friend istream& operator>> (istream& is, CObjetoRede_Sitio_WEST& obj);
};

// -----------------------------------------------------------------Friend
// Declaração de Funções Friend
// ostream& operator<< (ostream& os, CObjetoRede_Sitio_WEST& obj);
// istream& operator>> (istream& is, CObjetoRede_Sitio_WEST& obj);
#endif
