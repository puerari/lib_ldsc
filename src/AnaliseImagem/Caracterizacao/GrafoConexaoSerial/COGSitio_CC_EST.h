#ifndef COGSitio_CC_EST_h
#define COGSitio_CC_EST_h

/*
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
            Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================
Desenvolvido por:
            Laboratorio de Desenvolvimento de Software Cientifico [LDSC].
@author     André Duarte Bueno
@file       COGSitio_CC_EST.h
@begin      Sat Sep 16 2000
@copyright  (C) 2000 by André Duarte Bueno
@email      andreduartebueno@gmail.com
*/

// -----------------------------------------------------------------------
// Bibliotecas LIB_LDSC
// -----------------------------------------------------------------------
#include <AnaliseImagem/Caracterizacao/GrafoConexaoSerial/COGSitio_CC.h>

// ===============================================================================
// Documentacao Classe: COGSitio_CC_EST
// ===============================================================================
/** 
 * @brief Representa um sítio que armazena a informação associada a conexão.
 * Assume valor de contorno = 2.
 * O valor de contorno é usado no calculo dos fluxo da malha como
 * um todo.Ou seja, um algoritimo externo percorre toda
 * a malha, e se o contorno for igual ao solicitado
 * calcula alguma propriedade neste contorno.
 * @author 	André Duarte Bueno	
 * @see			grafos
 * @Superclasse:    CParametroSolver->CObjetoGrafo->COGSitio->COGSitio_CC->COGSitio_CC_EST
 * @todo renomear COGSitio_CC_EST -> COGSitio_CCDir
 */
class COGSitio_CC_EST : public COGSitio_CC
{
// --------------------------------------------------------------Atributos
public:

// --------------------------------------------------------------Construtor
/// Construtor
 COGSitio_CC_EST () = default;
// ---------------------------------------------------------------Destrutor 
/// Destrutor
   virtual ~ COGSitio_CC_EST ()= default;

// -----------------------------------------------------------------Métodos
// Redefinição de funções herdadas

   /// Retorna o tipo de contorno
  virtual CContorno::ETipoContorno Contorno () const override  {
     return CContorno::ETipoContorno::EST;
  }

   /**
    * @brief Função herdada da classe CParametroSolver usada para 
    * calcular o valor de x retorna a pressão na fronteira direita
    * Observe que retorna direto o valor de x, ou seja,
    * um objeto da fronteira nao recalcula seu fluxo
   */
  virtual long double Go (long double d = 0) override   {
    return x;
  }

// --------------------------------------------------------------------Get
// --------------------------------------------------------------------Set
// -----------------------------------------------------------------Friend
  // friend ostream& operator<< (ostream& os, COGSitio_CC_EST& obj);
  // friend istream& operator>> (istream& is, COGSitio_CC_EST& obj);
};

// -----------------------------------------------------------------Friend
// Declaração de Funções Friend
// ostream& operator<< (ostream& os, COGSitio_CC_EST& obj);
// istream& operator>> (istream& is, COGSitio_CC_EST& obj);
#endif
