//  ítens conferidos: 1[ ] 2[ ] 3[ ] 4[ ] 5[ ] 6[ ] 7[ ] 8[ ] 9[ ] 10[ ]
#ifndef TCFEMMIDFdi_h
#define TCFEMMIDFdi_h

/*
----------------------------------------------------------------------------
PROJETO:	Anaimp
	Analise de Imagens de Meios Porosos
----------------------------------------------------------------------------

Desenvolvido por:	Laboratorio de Desenvolvimento de Software Cientifico   dos Materiais.
Programadores:   	Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani, Liang Zirong, Paulo C. Philippi, ...
Copyright @1997:  	Todos os direitos reservados.
Nome deste arquivo:	TCFEMMIDFdi.h
Nome da classe:      TCFEMMIDFdi
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
*/

//  ----------------------------------------------------------------------------
//  Bibliotecas
//  ----------------------------------------------------------------------------

#include <AnaliseImagem/Filtro/FEspacial/FEMorfologiaMatematica/TCFEMMIDF.h>
#include <AnaliseImagem/Filtro/Mascara/MCDiscreta/CMCdi.h>

//  ----------------------------------------------------------------------------
//  Classe:       TCFEMMIDFdi
//  ----------------------------------------------------------------------------
/**
 * @brief  Matriz IDF de uma imagem usando mascara de chanfro di.
 */
template<typename T>
class TCFEMMIDFdi : public TCFEMMIDF<T>, public CMCdi {
	protected:
		///  Redefinida, herdada de TCFEMMIDF
		virtual unsigned int Mi () {
			return mi;
		}

	public:
		/// Construtor.
		TCFEMMIDFdi (TCMatriz2D<T> * &matriz, unsigned int _mi, unsigned int _rb, int _indice=1, int _fundo=0)
			: TCFEMMIDF<T> (matriz, _rb, 32000, _indice, _fundo), CMCdi (_mi, _rb) {
		}

		///  Destrutor.
		virtual ~ TCFEMMIDFdi () {
		}

		/// Cria a mascara.
		virtual void CriaMascara (unsigned int _tamanhoMascara);

		/// Realiza processamento da imagem.
		virtual TCMatriz2D<T> *Go (TCMatriz2D<T> * &matriz, unsigned int _tamanhoMascara =	 0);

		///  Corrige o erro físico que ocorre (em configurações de equilíbrio) na rotulagem da imagem após a operação de abertura.
		virtual void CorrigeAbertura ( TCMatriz2D<T> * &matriz, int &regiao ) = 0;

};

#include "AnaliseImagem/Filtro/FEspacial/FEMorfologiaMatematica/TCFEMMIDFdi.cpp"

#endif //  TCFEMMIDFdi_h
