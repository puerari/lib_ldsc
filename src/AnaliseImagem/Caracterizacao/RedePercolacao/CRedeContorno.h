#ifndef CRedeContorno_h
#define CRedeContorno_h

#include <AnaliseImagem/Caracterizacao/RedePercolacao/CRedeDePercolacao.h>

using namespace std;

/**
 * @short: A \class CRedeContorno representa uma rede de percolação sujeita a condições de contornos;
 * Herdeira da classe CRedeDePercolacao, a classe CRedeContorno acrescenta a idéia
 * de que uma rede pode estar submetida a determinadas condições de contorno.
 * Na prática acrescenta um vetor que armazena os objetos de contorno.
 * Note que existe uma hierarquia para objetos de contorno, este
 * vetor terá ponteiros para objetos da classe base da hierarquia de contornos.
 * @author 	Leandro Puerari <puerari@gmail.com>
 * @author 	André Duarte Bueno <andreduartebueno@gmail.com>
*/
class CRedeContorno : public CRedeDePercolacao
{
		// --------------------------------------------------------------Atributos
	public:
		/// Usa-se contorno[i] para obter ponteiro para contorno i.
		std::vector < CContorno * >contorno;

		// -------------------------------------------------------------Construtores
		/// Cria os objetos de contorno e incluí no vetor contorno (recebe imagem binária que será segmentada).
		CRedeContorno (TCImagem3D<bool> *&_pm, int _raioMaximo, int _raioDilatacao, int _fatorReducao, int _incrementoRaio, EModelo _modelo, int _indice=1, int _fundo=0, unsigned long int _numero_contornos=0);

		/// Cria os objetos de contorno e incluí no vetor contorno (recebe imagem em tons de cinza fundo=0; sitio=1, ligação=2).
		CRedeContorno (TCImagem3D<int> *&_pm, unsigned long int _numero_contornos = 0);

		// --------------------------------------------------------------Destrutor
		/// Delete os objetos de contorno do vetor contorno.
		~CRedeContorno ();

		// ----------------------------------------------------------------Métodos
		// virtual void Write(std::string fileName);

	public:

		// --------------------------------------------------------------------Get
		// --------------------------------------------------------------------Set
		// -----------------------------------------------------------------Friend
		friend std::ostream & operator<< (std::ostream & os, const CRedeContorno & obj);
		//friend istream& operator>> (istream& is, CRedeContorno& obj);
};

// -----------------------------------------------------------------Friend
// Declaração de Funções Friend
std::ostream & operator<< (std::ostream & os, const CRedeContorno & obj);
// istream& operator>> (istream& is, CRedeContorno& obj);

#endif