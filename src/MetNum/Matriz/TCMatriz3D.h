#ifndef TCMatriz3D_h
#define TCMatriz3D_h

/*
===============================================================================
PROJETO:    Biblioteca LIB_LDSC
						Assunto/Ramo: TCMatriz3D...
===============================================================================
Desenvolvido por:	
						Laboratorio de Desenvolvimento de Software Cientifico
						[LDSC].
@author     André Duarte Bueno
@file       TCMatriz3D.h
@begin      Sat Sep 16 2000
@copyright  (C) 2000 by André Duarte Bueno
@email      andreduartebueno@gmail.com
*/

// -----------------------------------------------------------------------
// Bibliotecas C/C++
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// Bibliotecas LIB_LDSC
// -----------------------------------------------------------------------
#ifndef _LIB_LDSC_CLASS_h
#include <Base/_LIB_LDSC_CLASS.h>
#endif

#ifndef CBaseMatriz_h
#include <MetNum/Matriz/CBaseMatriz.h>
#endif

#include <MetNum/Matriz/TCMatriz2D.h>
#include <vector>

/**
 * @brief Representa uma matriz 3D.
 *
 * Permite criar e usar uma matriz .
 * A alocacao e feita dinamicamente
 * Tem tres construtores,
 * Para criar uma matriz toda nova use
 * Tmatriz3D(NX,NY,NZ),cria matriz, aloca data, zera valores
 *
 * Para criar uma copia no programa use
 * Tmatriz3D(Tmatriz3D), cria uma copia
 * Tmatriz3D=Tmatriz3D;
 *
 * Para abrir uma matriz do disco use
 * Tmatriz3D("nomearquivo")    	// Cria matriz nova a partir de arquivo de disco
 * Tmatriz3D.Read("nomearquivo")
 *
 * Para salvar a matriz em disco use
 * Tmatriz3D.Write(std::string nomeArquivo)
 *
 * Para acessar o conteudo da matriz use data3D
 * Tmatriz3D.data3D[i][j][k]=33;
 * int x=Tmatriz3D.data3D[i][j][k];
 * Posteriormente se for de interesse, acrescentar
 * soma,diminuicao, multiplicacao,..,inversao,..,transposta
 * @author 	André Duarte Bueno
 * @see		Matriz
*/

//#define Matriz3D(tipo) vector<tipo>**

/// Enumera os eixos de uma imagem 3D
enum E_eixo { EIXO_X, EIXO_Y, EIXO_Z };

template< typename T >
class TCMatriz3D : public CBaseMatriz
{
		// --------------------------------------------------------------Atributos
		// Atributos e metodos estaticos
	protected:

		int nx;///< Dimensão nx
		int ny;///< Dimensão ny
		int nz;///< Dimensão nz

	public:
		/// Ponteiro para matriz 3D
		vector<T>** data3D;

		/// Alocal matriz 3D e retorna ponteiro int***
		bool AlocaMatriz3D (int _nx, int _ny, int _nz);

		/// Desaloca matriz 3D
		static void DesalocaMatriz3D (vector<T>** &dat, int nx, int ny, int nz);

		// -------------------------------------------------------------Construtor
		// Metodos construtores
		/// Construtor
		TCMatriz3D ();

		/// Construtor le TCMatriz3D do disco
		TCMatriz3D (std::string nomeArquivo);

		/// Construtor le arquivo RAW do disco. Recebe nome do arquivo, largura, altura, profundidade e tipo (D4_X_Y_Z_BINARY (default), D5_X_Y_Z_GRAY_BINARY ou D6_X_Y_Z_COLOR_BINARY) da imagem.
		TCMatriz3D (std::string fileRAW, int _nx, int _ny, int _nz, EImageType tipo=D4_X_Y_Z_BINARY );

		/// Construtor cria copia TCMatriz3D
		TCMatriz3D (TCMatriz3D &);

		/// Construtor cria nova TCMatriz3D
		TCMatriz3D (int, int, int);

		// --------------------------------------------------------------Destrutor
		/// Destrutor
		virtual ~ TCMatriz3D () {
			TCMatriz3D::DesalocaMatriz3D (data3D, nx, ny, nz);
		}

		// ----------------------------------------------------------------Métodos
	protected:
		/// Le os dados separados por " "
		void LeDados (std::ifstream & fin);

		/// Le os dados, colados 010111001
		void LeDadosColados (std::ifstream & fin);

		/// Le os dados gravados em formato binario
		void LeDadosBinarios (std::ifstream & fin);

		// Alocacao, Desalocacao
		/// Aloca a matriz
		virtual bool Aloca () {
			return TCMatriz3D::AlocaMatriz3D (nx, ny, nz);
		}

		/// Desaloca a matriz
		virtual bool Desaloca () {
			TCMatriz3D::DesalocaMatriz3D (data3D, nx, ny, nz);
			return true;
		}

	public:
		/// Redimensiona  a matriz
		virtual bool Redimensiona (int NX, int NY = 0, int NZ = 0);

		/// Salva dados do cabecalho
		virtual void SalvaCabecalho (std::ofstream & fout) const;

		/// Salva dados em formato binario
		virtual void SalvaDadosBinarios (std::ofstream & fout) const;

		/// Salva dados "colados" sem espaço
		virtual void SalvaDadosColados (std::ofstream & fout) const;

		/// Salva dados com um espaco " "
		virtual void SalvaDados (std::ofstream & fout) const;

		/// Checa indice de acesso, retorna true/false
		bool ChecaIndice (int NX, int NY, int NZ) const {
			return (NX >= 0 && NX < (int) nx && NY >= 0 && NY < (int) ny && NZ >= 0 && NZ < (int) nz) ? 1 : 0;
		}

		/// Lê matriz 3D de uma arquivo.
		bool Read (std::string nomeArquivo, int separado = 1); //Como é chamada pelo construtor nao pode ser virtual

		/// Lê arquivo binário do tipo RAW. Recebe o nome do arquivo e o tipo (D4_X_Y_Z_BINARY (default), D5_X_Y_Z_GRAY_BINARY ou D6_X_Y_Z_COLOR_BINARY).
		bool ReadRAW (std::string nomeArquivo, int _nx, int _ny, int _nz, EImageType tipo = D4_X_Y_Z_BINARY); // Como é chamada pelo construtor nao pode ser virtual

		/// lê o plano z da matriz 3D e retona a matriz 2D correspondente ao plano lido.
		TCMatriz2D<T>* LePlano (unsigned int planoZ, E_eixo direcao = EIXO_Z);

		/// lê a matriz 3D na direção e plano informados e seta na matriz 2D passada como parametro. As direções podem ser: x, y, z ou X, Y, Z ou i, j, k ou I, J, K.
		bool LePlano (TCMatriz2D<T> * pm2D, int plano, E_eixo direcao = EIXO_Z);

		/// rotaciona a imagem 3D, 90 graus a direita no eixo informado
		bool Rotacionar90 (E_eixo axis = EIXO_Z);

		/// Cria e retorna uma nova matriz 3D que será um recorte da matriz (this).
		TCMatriz3D<T>* Crop (int startX, int endX, int startY, int endY, int startZ, int endZ);

		/// Preenche com valor constante
		virtual void Constante (T cte);

		/// Inverte valores (0)-->(1)  (>0) -->0
		virtual void Inverter ();

		/// Retorna o maior valor da matriz
		int MaiorValor () const;

		/// Retorna o menor valor da matriz
		int MenorValor () const;

		/// Retorna o menor valor da matriz (diferente de zero). Se a matriz só tiver zeros, irá retornar 9999999999
		int MenorValorNzero () const;

		/// Retorna o um par correspondente ao maior e ao menor valor da matriz (diferente de zero). Se a matriz só tiver zeros, irá retornar 0 e 9999999999
		pair<T,T> MaiorMenorValorNzero () const;

		/// Calcula e retorna a média
		virtual double Media () const;

		/// Troca todos os valores i por j no vetor
		int Replace (T i, T j);

		// -------------------------------------------------------------Sobrecarga
		/// Sobrecarga operator+
		TCMatriz3D<T> & operator+ (TCMatriz3D<T> & pm3);

		/// Sobrecarga operator-
		TCMatriz3D<T> & operator- (TCMatriz3D<T> & pm3);

		/// Sobrecarga operator+=
		TCMatriz3D<T> & operator= (TCMatriz3D<T> & pm3);

		/// Sobrecarga operator==
		bool operator== (TCMatriz3D<T> & pm3);

		/// Sobrecarga operator!=
		bool operator!= (TCMatriz3D<T> & pm3);

		/// Sobrecarga operator()
		inline T &operator  () (int x, int y, int z) const {
			return data3D[x][y][z];
		}

		/// Sobrecarga operator[]
		inline T &operator[] (int x) const {
			return data3D[x][0][0];
		}

		// --------------------------------------------------------------------Get
	public:
		/// Retorna nx
		inline int NX () const {
			return nx;
		}

		/// Retorna ny
		inline int NY () const {
			return ny;
		}

		/// Retorna nz
		inline int NZ () const {
			return nz;
		}

		/// Retorna data3D
		inline vector<T>** & Data3D () {
			return data3D;
		}

		/// Retorna DimensaoMatriz
		virtual int DimensaoMatriz () const {
			return 3;
		}

		// --------------------------------------------------------------------Set
	public:
		/// Seta nx
		inline void NX (int NX) {
			nx = NX;
		}

		/// Seta ny
		inline void NY (int NY) {
			ny = NY;
		}

		/// Seta nz
		inline void NZ (int NZ) {
			nz = NZ;
		}

		/// Define formato do arquivo
		void SetFormato(EImageType _formato);

		// -----------------------------------------------------------------Friend
		//       friend ostream& operator<< (ostream& os, TCMatriz3D& obj);
		//       friend istream& operator>> (istream& is, TCMatriz3D& obj);

};

#include <MetNum/Matriz/TCMatriz3D.cpp>

#endif

