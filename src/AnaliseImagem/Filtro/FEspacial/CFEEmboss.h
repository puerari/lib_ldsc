// ítens conferidos: 1[ ] 2[ ] 3[ ] 4[ ] 5[ ] 6[ ] 7[ ] 8[ ] 9[ ] 10[ ]
#ifndef CFEEmboss_h
#define CFEEmboss_h

// inclue a biblioteca de filtros
#ifndef CFEspacial_h
#include <AnaliseImagem/Filtro/FEspacial/TCFEspacial.h>
#endif

/*
----------------------------------------------------------------------------
PROJETO:		Bibliotecas LDSC
			Biblioteca para manipulacao de mascaras
----------------------------------------------------------------------------

Desenvolvido por:	Laboratorio de Desenvolvimento de Software Cientifico e Propriedades 
Termofisicas  dos Materiais.
Programadores:   	Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani, 
Liang Zirong,
			Paulo C. Philippi, Cunha Neto J.A.B.,Nathan Mendes,...
Copyright @1997:  	Todos os direitos reservados.
Nome deste arquivo:	CFEEmboss.h
Nome da classe:      CFEEmboss
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
*/

/**
 * @brief Implementa o filtro Embooss, CFEEmboss.
 * Herdeiro de CFEspacial.
 */

class CFEEmboss : public TCFEspacial<int>
{
	public:
		/// Construtor
		CFEEmboss (TCMatriz2D< int > * &matriz, unsigned int _tamanhoMascara)
			:TCFEspacial<int> (matriz, _tamanhoMascara)
		{
		}

		/// Destrutor
		~CFEEmboss ()
		{
		}

		/// Cria a mascara adequada
		virtual void CriaMascara (unsigned int _tamanhoMascara);
};
#endif // CFEEmboss_h
