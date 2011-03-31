// ítens conferidos: 1[ ] 2[ ] 3[ ] 4[ ] 5[ ] 6[ ] 7[ ] 8[ ] 9[ ] 10[ ]

/*
----------------------------------------------------------------------------
PROJETO:		Anaimp.
			Analise de Imagens de Meios Porosos.
----------------------------------------------------------------------------

Desenvolvido por:	Laboratorio de Desenvolvimento de Software Cientifico   dos Materiais.
Programadores:   	Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani, Liang Zirong, Paulo C. Philippi, ...
Copyright @1997:  	Todos os direitos reservados.
Nome deste arquivo:	CFEPassaBaixa.cpp
Nome da classe:      CFEPassaBaixa
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
*/

/*
----------------------------------------------------------------------------
			BIBLIOTECAS
----------------------------------------------------------------------------
*/
#include "Filtro/FEspacial/CFEPassaBaixa.h"
#include "Mascara/CMPassaBaixa.h"

/*
==================================================================================
Documentacao      CriaMascara
==================================================================================
Descrição:	Se a mascara ja existe deve ser eliminada
	        O construtor da mascara chama a funcao de preenchimento da
		mascara e de calculo do peso da mascara
Programador:    Andre Duarte Bueno
*/

void
CFEPassaBaixa::CriaMascara (unsigned int _tamanhoMascara)
{
  tamanhoMascara = _tamanhoMascara;
  if (mask)
    delete mask;
  mask = new CMPassaBaixa (_tamanhoMascara);
}

