#ifndef CRede_h
#define CRede_h

/**
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
            Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================
Desenvolvido por:
            Laboratorio de Desenvolvimento de Software Cientifico [LDSC].
@author     André Duarte Bueno
@file       CRede.h
@begin      Sat Sep 16 2000
@copyright  (C) 2000 by André Duarte Bueno
@email      andreduartebueno@gmail.com
*/

// -----------------------------------------------------------------------
// Bibliotecas C/C++
// -----------------------------------------------------------------------
#include <fstream>
#include <vector>
#include <cassert>

// ----------------------------------------------------------------------------
// Bibliotecas LIB_LDSC
// ----------------------------------------------------------------------------
#ifndef _LIB_LDSC_CLASS_h
#include <Base/_LIB_LDSC_CLASS.h>
#endif

#ifndef CBaseGrafoRedeEsqueleto_h
#include <EstruturaDados/CBaseGrafoRedeEsqueleto.h>
#endif

#ifndef CObjetoRede_h
#include <EstruturaDados/ObjetoRede/CObjetoRede.h>
#endif

#ifndef CObjetoRede_Ligacao_h
#include <EstruturaDados/ObjetoRede/CObjetoRede_Ligacao.h>
#endif

#ifndef CObjetoRede_Ligacao_EST_h
#include <EstruturaDados/ObjetoRede/CObjetoRede_Ligacao_EST.h>
#endif

#ifndef CObjetoRede_Ligacao_WEST_h
#include <EstruturaDados/ObjetoRede/CObjetoRede_Ligacao_WEST.h>
#endif

#ifndef CObjetoRede_Sitio_h
#include <EstruturaDados/ObjetoRede/CObjetoRede_Sitio.h>
#endif

#ifndef CObjetoRede_Sitio_EST_h
#include <EstruturaDados/ObjetoRede/CObjetoRede_Sitio_EST.h>
#endif

#ifndef CObjetoRede_Sitio_WEST_h
#include <EstruturaDados/ObjetoRede/CObjetoRede_Sitio_WEST.h>
#endif

#ifndef CObjetoRede_Tipo_h
#include <EstruturaDados/ObjetoRede/CObjetoRede_Tipo.h>
#endif

/// Agrega o conjunto de classes que estão diretamente relacionadas a hierarquia HCGrafo.
/// @defgroup HCGrafo

// ===============================================================================
// Documentacao Classe: CRede
// ===============================================================================
/**
 * @brief Um CRede é uma representação para uma estrutura de dados.
 * Um CRede é composto de uma lista de objetos do tipo CObjetoGrafo.
 * A forma como os objetos se relacionam é definida, normalmente, pelo próprio CObjetoGrafo.
 * Assim, existe uma hierarquia de grafos cujo pai é CRede e
 * uma hierarquia de objetos de grafo cujo pai é CObjetoGrafo.
 *
 * @author André Duarte Bueno
 * @see    grafos
 * @ingroup  HCGrafo
*/
class  CRede : public CBaseGrafoRedeEsqueleto {
   // --------------------------------------------------------------Atributos
public:
   /// Usa-se objeto[i] para obter ponteiro para o objeto i do grafo
   /// @todo: trocar por unique_ptr shared_ptr
   std::vector <CObjetoRede *> objeto;

   // -------------------------------------------------------------Construtor
   /// Construtor default.
   CRede( )  = default;

   // -------------------------------------------------------------Construtor
   /// Constroi o grafo, recebe um nome de arquivo de disco que tem as informações do grafo.
   CRede( std::string _na ) : CBaseGrafoRedeEsqueleto( _na ) { }

   // --------------------------------------------------------------Destrutor
   /// Destroi o objeto, como o grafo é o proprietário dos objetos deve eliminá-los.
   virtual ~CRede()  {
      for( auto objeto_i :  objeto )
         delete objeto_i;
   }

   // ----------------------------------------------------------------Métodos
protected:
   /**
    * @brief  Função usada para criar os objetos do grafo.
    * @param  Recebe um ETipoObjetoGrafo, que informa o tipo de objeto a ser criado.
    * @return Retorna um objeto herdeiro de CObjetoGrafo, de acordo com o ETipoGrafo.
   */
   /*virtual */
   CObjetoGrafo * CriarObjetoGrafo( ETipoObjetoGrafo tipo ) {
      CObjetoGrafo * data;

      switch( tipo ) {
         case ETipoObjetoGrafo::ObjetoRede :
            data = new CObjetoRede();
            break;

         case ETipoObjetoGrafo::ObjetoRede_Ligacao :
            data = new CObjetoRede_Ligacao();
            break;

         case ETipoObjetoGrafo::ObjetoRede_Ligacao_EST :
            data = new CObjetoRede_Ligacao_EST();
            break;

         case ETipoObjetoGrafo::ObjetoRede_Ligacao_WEST :
            data = new CObjetoRede_Ligacao_WEST();
            break;

         case ETipoObjetoGrafo::ObjetoRede_Sitio :
            data = new CObjetoRede_Sitio();
            break;

         case ETipoObjetoGrafo::ObjetoRede_Sitio_EST :
            data = new CObjetoRede_Sitio_EST();
            break;

         case ETipoObjetoGrafo::ObjetoRede_Sitio_WEST :
            data = new CObjetoRede_Sitio_WEST();
            break;

	 case  ETipoObjetoGrafo::CObjetoRede_Tipo :
	 default : 
            data = new CObjetoRede_Tipo( tipo );
            break;
         }

      assert( data );
      return data;
   }

   /// Deleta um objeto do grafo, considerando a posição no vetor.
   virtual bool DeletarObjeto( int i ) override {
      delete objeto[i];
      objeto.erase( objeto.begin() + i );
   }

   /// Deleta considerando o endereço do objeto.
   /// @todo: testar
   virtual bool DeletarObjeto( CObjetoRede * objeto_i ) /*override*/ {
      delete objeto_i;
      // Para calcular valor i, preciso diminuir o ponteiro para objeto_i 
      // do ponteiro para início do vetor, que é dado por objeto.data();
      int posicao_i = objeto_i - (*objeto.data());
      objeto.erase( objeto.begin() + posicao_i );
   }

public:
   /**
    * @brief Função que monta o grafo, genérica.
   */
//    virtual CRede * Go( long double, long double ) = 0;

   /**
    * @brief Fun que salva o grafo e seus objetos em disco, recebe a ofstream.
    */
   virtual void Write( std::ostream & out );

   // --------------------------------------------------------------------Get
   // --------------------------------------------------------------------Set
   // -----------------------------------------------------------------Friend
   /// Escreve em "os" os dados do objeto grafo e seus agregados
   friend std::ostream & operator<< ( std::ostream & os, const CRede & obj );

   // friend istream& operator>> (istream& is, CRede& obj);
};

std::ostream & operator<< ( std::ostream & os, const CRede & obj );
// istream& operator>> (istream& is, CRede& obj);
#endif
