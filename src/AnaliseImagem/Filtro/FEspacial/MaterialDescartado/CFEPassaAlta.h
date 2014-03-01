// �tens conferidos: 1[ ] 2[ ] 3[ ] 4[ ] 5[ ] 6[ ] 7[ ] 8[ ] 9[ ] 10[ ]
#ifndef CFEPassaAlta_h
#define CFEPassaAlta_h

// inclue a biblioteca de filtros
#ifndef CFEspacial_h
#include <Filtro/FEspacial/CFEspacial.h>
#endif

/*
----------------------------------------------------------------------------
PROJETO:		Bibliotecas LMPT
			Biblioteca para manipulacao de mascaras
----------------------------------------------------------------------------

Desenvolvido por:	Laboratorio de Meios Porosos e Propriedades Termofisicas  dos Materiais.
Programadores:   	Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani, Liang Zirong,
			Paulo C. Philippi, Cunha Neto J.A.B.,Nathan Mendes,...
Copyright @1997:  	Todos os direitos reservados.
Nome deste arquivo:	CFEPassaAlta.h
Nome da classe:      CFEPassaAlta
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
*/

/*
============================================================================
Documentacao Classe:    CFEPassaAlta
============================================================================
Assunto:             Filtros espaciais (atuam sobre o espa�o geom�trico da imagem).
Superclasse:         CFiltro-> CFEspacial
Descri��o:           Cria e utiliza uma m�scara passa alta para atuar sobre a imagem.
                     O resultado geral � o aumento dos contornos. A identifica��o dos contornos.
Acesso:           import
Cardinalidade:    1:1    ,de uma maneira geral usa-se um filtro para atuar sobre uma imagem
Abstrata/Concreta:  concreta
Arquivo de documentacao auxiliar:
*/

class CFEPassaAlta : public CFEspacial
{
public:
  CFEPassaAlta (CMatriz2D * &matriz, unsigned int _tamanhoMascara)	// construtor
  : CFEspacial (matriz, _tamanhoMascara)
  {
  }

  virtual void CriaMascara (unsigned int _tamanhoMascara);	// Cria a mascara adequada

};
#endif //  CFEPassaAlta_h
