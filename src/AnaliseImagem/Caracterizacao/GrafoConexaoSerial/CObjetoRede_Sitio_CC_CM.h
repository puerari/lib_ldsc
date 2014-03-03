#ifndef CObjetoRede_Sitio_CC_CM_h
#define CObjetoRede_Sitio_CC_CM_h

/**
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
            Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================
Desenvolvido por:
            Laboratorio de Desenvolvimento de Software Cientifico [LDSC].
@author     André Duarte Bueno
@file       CObjetoRede_Sitio_CC_CM.h
@begin      Sat Sep 16 2000
@copyright  (C) 2000 by André Duarte Bueno
@email      andreduartebueno@gmail.com
*/

/*
-------------------------------------------------------------------------
Bibliotecas ANSI C++
-------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------
Bibliotecas LIB_LDSC
-------------------------------------------------------------------------
*/
#ifndef _LIB_LDSC_CLASS_h
#include <Base/_LIB_LDSC_CLASS.h>
#endif

#ifndef CObjetoRede_Sitio_CC_h
#include <AnaliseImagem/Caracterizacao/GrafoConexaoSerial/CObjetoRede_Sitio_CC.h>
#endif

// ===============================================================================
// Documentacao Classe: CObjetoRede_Sitio_CC_CM
// ===============================================================================
/**
 * @brief  é um sítio, herdeiro de CObjetoRede_Sitio_CC, acrescenta as coordenadas cx,cy,cz.
 * @author 	André Duarte Bueno
 * @see		grafos
 * @ingroup  HCObjetoGrafo
 * @todo: implementar template para tipo de cx cy cz
*/
class CObjetoRede_Sitio_CC_CM : public CObjetoRede_Sitio_CC {
// --------------------------------------------------------------Atributos
public:
     float cx{0.0};  ///< Posição x do objeto na imagem tridimensional
     float cz{0.0};  ///< Posição y do objeto na imagem tridimensional
     float cy{0.0};  ///< Posição z do objeto na imagem tridimensional

// -------------------------------------------------------------/**Construtor*/
/// Destrutor
     CObjetoRede_Sitio_CC_CM () = default;

// --------------------------------------------------------------/**Destrutor*/
/// Construtor
     virtual ~ CObjetoRede_Sitio_CC_CM ()  = default;

     /// @brief Salva atributos do objeto em disco.
     virtual std::ostream &Write ( std::ostream &os ) const override ;
	 
// ----------------------------------------------------------------Métodos
// --------------------------------------------------------------------Get
// --------------------------------------------------------------------Set
// -----------------------------------------------------------------Friend
     /// Sobrecarga do operador <<.
     friend std::ostream &operator<< ( std::ostream &os, CObjetoRede_Sitio_CC_CM &obj );
     // friend istream& operator>> (istream& is, CObjetoRede_Sitio_CC_CM& obj);
};

// -----------------------------------------------------------------Friend
// Declaração de Funções Friend
inline std::ostream &operator<< ( std::ostream &os, CObjetoRede_Sitio_CC_CM &obj );
// istream& operator>> (istream& is, CObjetoRede_Sitio_CC_CM& obj);

// Cria o tipo CObjetoRede_Sitio_CC_CMCentro, que é igual a CObjetoRede_Sitio_CC_CM
using CObjetoRede_Sitio_CC_Centro = CObjetoRede_Sitio_CC_CM ;

#endif
