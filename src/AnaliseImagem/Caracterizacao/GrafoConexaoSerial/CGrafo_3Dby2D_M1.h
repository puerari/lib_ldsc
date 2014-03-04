#ifndef CGrafo_3Dby2D_M1_h
#define CGrafo_3Dby2D_M1_h

/**
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
            Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================
Desenvolvido por:
            Laboratorio de Desenvolvimento de Software Cientifico
            [LDSC].
@author     André Duarte Bueno
@file       CGrafo_3Dby2D_M1.h
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

#ifndef CGrafo_3Dby2D_h
#include <AnaliseImagem/Caracterizacao/GrafoConexaoSerial/CGrafo_3Dby2D.h>
#endif

/**
 * @brief Determina o grafo de uma imagem 3D usando o modelo 1 (+simples),
 * para cada pixel uma ligação.
 *
 * Função Go()
 *
 * Neste modelo a função Go funciona da seguinte forma:
 * Os planos i e i+1 são rotulados, gerando-se a seguir os sítios.
 * Depois estabelece-se as conexões entre os planos consecutivos.
 * Observe que duas regiões que se interceptam vão gerar um número
 * grande de conexões (com conexões redundantes).
 * Ou seja, existe uma repetição no número de ligações entre duas regiões,
 * pois para cada conexão entre píxeis,
 * estabelece uma conexão.
 *
 * @author 	André Duarte Bueno
 * @see	      	Grafo
 * @ingroup  HCGrafo
*/
class CGrafo_3Dby2D_M1 : public CGrafo_3Dby2D {
// --------------------------------------------------------------Atributos
public:

// -------------------------------------------------------------Construtor
     /// Construtor
     CGrafo_3Dby2D_M1 ( std::string _nomeArquivo ) :CGrafo_3Dby2D ( _nomeArquivo )  {
          tipoGrafo  =  ETipoGrafo::grafo3DBy2D_M1 ;
     }

// --------------------------------------------------------------Destrutor
     /// Destrutor
     virtual ~ CGrafo_3Dby2D_M1 () = default;

// ----------------------------------------------------------------Métodos
     /** @brief Calcula as condutâncias.
      * */
     void CalcularCondutancias ( long double _viscosidade,
                                 long double _dimensaoPixel,
                                 unsigned long int fatorAmplificacao ) override;

protected:
     /// Conecta planos,  Versão com Links duplicados.
     virtual void DeterminarConeccoesObjetos ( unsigned long int maiorRotuloUtilizado ) override;

     // Função Go
     // virtual CGrafo* Go( TCMatriz3D<int> * _img3D,unsigned int _tamanhoMascara = 1);

// --------------------------------------------------------------------Get
// --------------------------------------------------------------------Set
// -----------------------------------------------------------------Friend
//       friend ostream& operator<< (ostream& os, CGrafo_3Dby2D_M1& obj);
//       friend istream& operator>> (istream& is, CGrafo_3Dby2D_M1& obj);
};

// -----------------------------------------------------------------Friend
// Declaração de Funções Friend
// ostream& operator<< (ostream& os, CGrafo_3Dby2D_M1& obj);
// istream& operator>> (istream& is, CGrafo_3Dby2D_M1& obj);

#endif
