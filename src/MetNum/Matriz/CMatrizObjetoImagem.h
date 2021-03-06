#ifndef CMatrizObjetoImagem_H
#define CMatrizObjetoImagem_H

#include <AnaliseImagem/Segmentacao/PorosGargantas/CObjetoImagem.h>
#include <map>

class CMatrizObjetoImagem
{		//atributos
	public:
		std::map<int, CObjetoImagem> matrizObjetos;

		// Construtores / Destrutor
	public:
		CMatrizObjetoImagem();

		~CMatrizObjetoImagem();

		// Métodos
	public:
		/// Grava em disco, com o nome informado, os objetos identificados.
		bool SalvarListaObjetos(std::string nomeArquivo, int nx, int ny, int nz);

};

#endif // CMatrizObjetoImagem_H
