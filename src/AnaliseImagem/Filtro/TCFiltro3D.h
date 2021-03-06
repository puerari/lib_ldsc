// ítens conferidos: 1[] 2[] 3[] 4[] 5[] 6[] 7[] 8[] 9[] 10[]
#ifndef TCFiltro3D_h
#define TCFiltro3D_h

// ponteiro para matriz
#include <MetNum/Matriz/TCMatriz3D.h>

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
Nome deste arquivo:	TCFiltro3D.h
Nome da classe:      TCFiltro3D
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
*/

/**
 * @brief Realiza o processamento da filtragem de imagens 3D.
 * 
 * Representa a superclasse para os filtros que podem atuar sobre
 * o espaço discreto da imagem 
 * (filtros espaciais) ou filtros que atuam
 * sobre o espaço de cor das imagens (filtros de amplitude).
 * Tem um atributo básico que é um ponteiro para a imagem (matriz imagem)
 * a ser tratada.
 * Ou seja um filtro tem um ponteiro para a imagem podendo atuar sobre éla.
 * Cardinalidade:    1:1    ,de uma maneira geral usa-se um filtro para atuar
 * sobre uma imagem
 * 
 * Tarefas de um filtro:
 * -Funcao CanGo () informa se a operacao pode ser realizada
 * -Funcao Go realiza a filtragem da imagem,
*/
template <typename T>
class TCFiltro3D
{
protected:
	TCMatriz3D<T> * pm;	///< é um ponteiro para a imagem a ser filtrada

public:
/// Construtor, recebe o endereço da matriz a ser processada
	TCFiltro3D (TCMatriz3D<T> * &matriz) {
    pm = matriz;
  }

/// Destrutor
	~TCFiltro3D () {
  }

  
  /**
   * @brief Realiza o processamento da filtragem
   * @param matriz ponteiro para imagem 3D a ser processada
   * @param _tamanhoMascara  dimensão da mascara a ser utilizada
   * @return ponteiro para imagem processada
   */ 
	virtual TCMatriz3D<T> *Go (TCMatriz3D<T> * &matriz, unsigned int _tamanhoMascara = 0) = 0;
};

#include <AnaliseImagem/Filtro/TCFiltro3D.cpp>

#endif //   TCFiltro3D_h
