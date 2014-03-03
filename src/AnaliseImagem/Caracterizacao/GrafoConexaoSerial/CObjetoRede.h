#ifndef CObjetoRede_h
#define CObjetoRede_h

/**
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
            Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================
Desenvolvido por:
            Laboratorio de Desenvolvimento de Software Cientifico [LDSC].
@author     André Duarte Bueno
@file       CObjetoRede.h
@begin      Sat Sep 16 2000
@copyright  (C) 2000 by André Duarte Bueno
@email      andreduartebueno@gmail.com
*/

// -----------------------------------------------------------------------
// Bibliotecas C/C++
// -----------------------------------------------------------------------
// Interface disco
#include <fstream>

// Classe container para vetores
#include <vector>

// -----------------------------------------------------------------------
// Bibliotecas LIB_LDSC
// -----------------------------------------------------------------------
#ifndef _LIB_LDSC_CLASS_h
#include <Base/_LIB_LDSC_CLASS.h>
#endif

#ifndef CObjetoGrafo_h
#include <AnaliseImagem/Caracterizacao/GrafoConexaoSerial/CObjetoGrafo.h>
#endif

// Definição de CSMParametroSolver, classe base
#ifndef CSMParametroSolver_h
#include <MetNum/Solver/SistemaEquacoes/CSMParametroSolver.h>
#endif


// ===============================================================================
// Documentacao Classe: CObjetoRede
// ===============================================================================
/**
 * @brief  Representa um objeto de uma rede é herdeiro de CObjetoGrafo e CSMParametroSolver.
 * Tem uma propriedade x (herdada de CParametroSolver)
 * um rótulo (herdado de CObjetoGrafo).
 * Acrescenta um long double propriedade.
 *
 * @author:  André Duarte Bueno
 * @see:     grafos
 * @todo:    implementar operadores >>.
 * @ingroup  HCObjetoGrafo
*/
class CObjetoRede : /*virtual*/ public CObjetoGrafo, public CSMParametroSolver  {
// --------------------------------------------------------------Atributos
public:
     /// Todo CObjetoGrafo tem uma propriedade// Ex:raio hidraulico ou condutancia
     long double propriedade {0.0};                // assume default  = 0

// -------------------------------------------------------------Construtor
/// Construtor
     CObjetoRede () = default;

// --------------------------------------------------------------Destrutor
/// Destrutor
     virtual ~ CObjetoRede () = default;

// ----------------------------------------------------------------Métodos
     /// @brief Salva atributos do objeto em disco.
     virtual std::ostream &Write ( std::ostream &os ) const override;
	 
// --------------------------------------------------------------------Get
	      /// @brief Retorna a propriedade.
     long double Propriedade () const  {
          return propriedade;
     }

// --------------------------------------------------------------------Set
     /// @brief Seta a propriedade.
     void Propriedade ( long double _p ) {
          propriedade = _p;
     };

	 // -----------------------------------------------------------------Friend
     friend std::ostream &operator<< ( std::ostream &os, CObjetoRede &obj );
//       friend istream& operator>> (istream& is, CObjetoRede& obj);

};

// -----------------------------------------------------------------Friend
// Declaração de Funções Friend
std::ostream &operator<< ( std::ostream &os, CObjetoRede &obj );
// istream& operator>> (istream& is, CObjetoRede& obj);


// Cria o tipo CObjetoRede_CENTER, que é igual a CObjetoRede
// typedef CObjetoRede CObjetoRede_CENTER;
using CObjetoRede_CENTER = CObjetoRede;

#endif
