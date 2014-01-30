#ifndef CRedeDePercolacao_H
#define CRedeDePercolacao_H

#include <Caracterizacao/Distribuicao/CDistribuicaoTamanhoPorosGargantas.h>
#include <Matriz/TCMatriz3D.h>

/**
 * @brief A classe CRedeDePercolacao representa meios porosos tridimensionais
 * de forma simplificada, através de redes de percolação 3D, irregulares e com
 * número de cordenação variável.
 *
 * Herdeira da classe CDistribuicaoTamanhoPorosGargantas, de forma que possibilita
 * calcular a distribuição de tamanho de poros e gargantas de imagens binárias ou
 * de imagens em tons de cinza segmentadas pela classe CAberturaDilatacao3D.
 *
 * Se a imagem recebída for uma imagem binária, esta será segmantada através
 * da classe CAberturaDilatacao3D.
 *
 * A classe CDistribuicaoTamanhoPorosGargantas, utiliza a classe CDistribuicao3D
 * para calcular as distribuições de tamanho de poros e gargantas.
 *
 * @author Leandro Puerari <puerari@gmail.com>
 * @author André Duarte Bueno <andreduartebueno@gmail.com>
*/
class CRedeDePercolacao : public CDistribuicaoTamanhoPorosGargantas
{		// Atributos
	private:
		///Par de ponteiros para a classe CDistribuicao, representado respectivamente a distribuição de tamanho de portos e a distribuição de tamanho de gargantas.
		std::pair< CDistribuicao3D *, CDistribuicao3D * > dtpg;
		TCMatriz3D<bool> *pm;

		// Construtores / Destrutor
	public:
		/// Construtor (recebe imagem binária que será segmentada)
		CRedeDePercolacao( TCImagem3D<bool> *&_pm, int & _raioMaximo, int & _raioDilatacao, int & _fatorReducao, int & _incrementoRaio, EModelo _modelo, int _indice=1, int _fundo=0 );

		/// Construtor (recebe imagem em tons de cinza fundo=0; sitio=1, ligação=2)
		CRedeDePercolacao( TCImagem3D<int> *&_pm );


		/// Destrutor
		~CRedeDePercolacao();

		// Métodos
	public:
		/// Executa o cálculo das distribuições e cria a rede de percolação.
		bool Go( int &nx, int &ny, int &nz, CDistribuicao3D::Metrica3D _metrica = CDistribuicao3D::d345 );
};

#endif // CRedeDePercolacao_H
