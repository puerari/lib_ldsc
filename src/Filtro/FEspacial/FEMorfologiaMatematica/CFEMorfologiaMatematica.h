//  itens conferidos: 1[ ] 2[ ] 3[ ] 4[ ] 5[ ] 6[ ] 7[ ] 8[ ] 9[ ] 10[ ]
#ifndef CFEMorfologiaMatematica_h
#define CFEMorfologiaMatematica_h

//  inclue a biblioteca de filtros
#ifndef CFEspacial_h
#include <Filtro/FEspacial/CFEspacial.h>
#endif

/*
----------------------------------------------------------------------------
PROJETO:	Bibliotecas LDSC
		Biblioteca para manipulacao de mascaras
----------------------------------------------------------------------------
Desenvolvido por:	Laboratorio de Desenvolvimento de Software Cientifico e Propriedades Termofisicas  dos Materiais.
Programadores:   	Andre D.Bueno, Celso P.Fernandez, Fabio S.Magnani, Liang Zirong, Paulo C. Philippi, Cunha Neto J.A.B., Nathan Mendes,...
Copyright @1997:  	Todos os direitos reservados.
Nome deste arquivo:	CFEMorfologiaMatematica.h
Nome da classe:     CFEMorfologiaMatematica
*/

/**
 * @brief Classe básica para os filtros da morfologia matematica.
 *
 * Tem a função que  cria uma máscara, euclidiana (uma bola) que é utilizada como elemento
 * estruturante nas operacoes de filtragem.
 *
 * Obs: para funcionamento do afinamento e espessamento
 * foram acrescentados dois flags e duas funcoes CriaEEB1 e CriaEEB2,
 * posteriormente remodelar este funcionamento, que ficou um pouco confuso.
*/
class CFEMorfologiaMatematica : public CFEspacial {
        bool EEHitMiss1; 	///<  flags de controle de criacao da mascara
        bool EEHitMiss2;	///<  flags de controle de criacao da mascara
    public:
        int INDICE;
        int FUNDO;

    public:
        /// Construtor
        CFEMorfologiaMatematica ( TCMatriz2D< int > * &matriz, unsigned int _tamanhoMascara, int _indice=1, int _fundo=0 )
           : CFEspacial ( matriz, _tamanhoMascara ), EEHitMiss1 ( false ), EEHitMiss2 ( false ), INDICE ( _indice ), FUNDO ( _fundo ) { }

        /**
         *  Abaixo a funcao Go que é reescrita aqui, vazia, para inibir o
         * calculo da convolucao realizado na classe CFEspacial
         * As operacaes da morfologia matematica sao diferentes.
         * (Verificar necessidade de herança/).
         * @param matriz
         * @param _tamanhoMascara
         * @return
         */
        virtual TCMatriz2D< int > *Go ( TCMatriz2D< int > * &matriz, unsigned int _tamanhoMascara = 0 ) {
            _tamanhoMascara = 0; // evitar warning
            return matriz;
        }

        ///  Cria mascara recebe o tamanho da mascara. Cria a mascara adequada.
        virtual void CriaMascara ( unsigned int _tamanhoMascara );

        /// Processa  Abertura, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *Abertura ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        /// Processa  Erosao, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *Erosao ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        /// Processa  Dilatacao, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *Dilatacao ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        /// Processa  Fechamento, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *Fechamento ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        //  Corrigir arrumar, as funcoes abaixo
        /// Processa  DeteccaoContorno, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *DeteccaoContorno ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        /// Processa  HitMiss, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *HitMiss ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        /// Processa  Afinamento, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *Afinamento ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        /// Processa  Espessamento, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *Espessamento ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

        /// Processa  Esqueleto, as operacoes recebem o raio da bola
        virtual TCMatriz2D< int > *Esqueleto ( TCMatriz2D< int > * &matriz, unsigned int _RaioBola );

    protected:
        /// Cria mascara do tipo b1, usadas no afinamento e espessamento
        void CriaEEB1 ( unsigned int _tamanhoMascara );

        /// Cria mascara do tipo b2, usadas no afinamento e espessamento
        void CriaEEB2 ( unsigned int _tamanhoMascara );
};

typedef CFEMorfologiaMatematica CFEMMClassica;

#endif //  CFEMorfologiaMatematica_h
