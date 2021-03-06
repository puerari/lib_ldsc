// ítens conferidos: 1[ ] 2[ ] 3[ ] 4[ ] 5[ ] 6[ ] 7[ ] 8[ ] 9[ ] 10[ ]
#ifndef  CFABIterativoThrussel_cpp
#define  CFABIterativoThrussel_cpp

/*
----------------------------------------------------------------------------
PROJETO:		Bibliotecas LDSC.
			Analise de Imagens de Meios Porosos (mascaras e filtros)
----------------------------------------------------------------------------

Desenvolvido por:	Laboratorio de Desenvolvimento de Software Cientifico   dos Materiais.
Programadores:   	Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani, Liang Zirong, Paulo C. Philippi, ...
Copyright @1997:  Todos os direitos reservados.
Nome deste arquivo:	CFABIterativoThrussel.cpp   (thris)
Nome da classe:      CFABIterativoThrussel
Arquivos de documentacao do projeto em: path\documentacao\*.doc, path\Help
Descricao:      	Implementa o filtro binario usando nível de corte médio
*/
/*
----------------------------------------------------------------------------
Bibliotecas
----------------------------------------------------------------------------
*/

#include "AnaliseImagem/Filtro/FAmplitude/CFABIterativoThrussel.h"
#include "MetNum/Matriz/CHistograma.h"
#include "MetNum/Matriz/TCMatriz2D.h"

/*
==================================================================================
Documentacao       Go
==================================================================================
Descrição:        Calcula o valor médio do nível de corte
						e depois processa binarização
Programador:      Andre Duarte Bueno
*/
template<typename T>
TCMatriz2D<T> * CFABIterativoThrussel<T>::Go (TCMatriz2D<T> * &matriz, unsigned int _tamanhoMascara) {
	this->pm = matriz;
	long i;			// , j;                           // Contadores
	long nivelAnterior;		// nivel de corte anterior
	long a, b, c, d;		// variáveis auxiliares

	CHistograma histograma (256);	// Cria histograma
	histograma.Go (this->pm);		//  e já calcula
	CFABinario<T>::nivel = this->pm->Media ();		// Calcula o valor médio da imagem
	// que é a semente inicial para o processo iterativo
	// poderia ser o valor do histograma com 50% dos píxel's

	do {				// inicia processo iterativo
		nivelAnterior = CFABinario<T>::nivel;	// armazena nivel de corte anterior
		a = 0;
		b = 0;
		for (i = 0; i <= nivelAnterior; i++) {	// calcula valores a e b do histograma inferior
			a += i * histograma.data1D[i];
			b += histograma.data1D[i];
		}
		b += b;

		c = 0;
		d = 0;
		for (i = nivelAnterior + 1; i < 256; i++)	{// calcula valores c e d do histograma superior
			c += i * histograma.data1D[i];
			d += histograma.data1D[i];
		}
		d += d;

		if (b == 0)
			b = 1;
		if (d == 0)
			d = 1;
		CFABinario<T>::nivel = a / b + c / d;	// calcula o nível como uma relação entre a,b,c e d
	}
	while (CFABinario<T>::nivel != nivelAnterior);	// se foi alterado continua iteração
	// se for o mesmo sai

	return CFABinario<T>::Go (this->pm);	// Executa função Go da classe base
	// que processa a binarização
	// o valor de corte é nivel
}
#endif
