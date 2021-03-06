/**
===============================================================================
PROJETO:          Biblioteca LIB_LDSC
                  Ramo: AnaliseImagem/Caracterizacao/GrafoConexaoSerial
===============================================================================

Desenvolvido por:
			Laboratorio de Desenvolvimento de Software Cientifico [LDSC].
@author:    André Duarte Bueno
@file:      CGrafoConexaoSerial_M2.cpp
@begin:     Sat Sep 16 2000
@copyright: (C) 2000 by André Duarte Bueno
@email:     andreduartebueno@gmail.com
*/

// -----------------------------------------------------------------------
// Bibliotecas C/C++
// -----------------------------------------------------------------------
#include <cassert>

// -----------------------------------------------------------------------
// Bibliotecas LIB_LDSC
// -----------------------------------------------------------------------
#ifndef CGrafoConexaoSerial_M2_h
#include <AnaliseImagem/Caracterizacao/GrafoConexaoSerial/CGrafoConexaoSerial_M2.h>
#endif

using namespace std;

//-------------------------------------------------------------------------
//Função:  	Go
//-------------------------------------------------------------------------
/** @short  :  Cria um objeto de rotulagem intermediaria e chama Go da classe pai.
 * Go() da classe pai vai chamar DeterminarConexoesObjetos que foi reescrita nesta classe
 * (e usa o rotulador intermediário).
 * A imagem é lida plano a plano, diretamente do disco.
 * @author :	André Duarte Bueno
 *  
 * @param  : Recebe o nome do arquivo de disco com a imagem e  o número do maior rótulo já utilizado
 * @return : void
 *  OBS:
 * Observe que dois objetos conexos, podem gerar mais de uma ligação valida.
 * No esboço abaixo, o obj45 esta conectado ao plano 7, duas vezes.
 * Para entender, você precisa lembrar que é criado um plano de rotulagem adicional
 * entre os planos 7 e 8, e que o obj45 vai ser dividido em dois, tendo 2 ligações válidas.
 * ------------------------------obj 34 no plano 7
 * ------obj 45 plano 8    ------obj 45 plano 8
 * ------------------------------obj 60 no plano 9
*/
CRede* CGrafoConexaoSerial_M2::Go ( string nomeArquivo, unsigned long int funcao )
{
   // Vai ler o cabecalho do arquivo de disco
   // precisa da informação das dimensoes NX e Ny da imagem,
   // para criar o rotulador intermediario.
   ifstream fin ( nomeArquivo.c_str () );

   if ( fin.bad () ) {		// novo
         cerr << "Nao conseguiu abrir o arquivo de disco " << nomeArquivo;
         return 0;
      }

   // Leitura do cabecalho da imagem do disco
   char d3[55];
   unsigned int NNX, NNY, NNZ, numeroCores;
   fin >> d3 >> NNX >> NNY >> NNZ >> numeroCores;
   fin.close ();

   // Cria objeto de rotulagem para plano intermediario
   if ( rotInt != nullptr )
      delete rotInt;

   rotInt = new CRotulador2DCm ( NNX, NNY );

   if ( rotInt == nullptr )
      cerr << "Erro alocação rotInt";

   assert ( rotInt ); // variavel DEBUG

   // Chama Função Go da classe base
   CGrafoConexaoSerial::Go ( nomeArquivo, funcao );

   // Deleta o rotulador intermediario
   delete rotInt;
   rotInt = nullptr;
   return this;
}

// -------------------------------------------------------------------------
// Função:  	Go
// -------------------------------------------------------------------------
/** @short  :  Cria um objeto de rotulagem intermediaria e chama Go da classe pai.
 * Go() da classe pai vai chamar DeterminarConexoesObjetos que foi reescrita nesta classe
 * (e usa o rotulador intermediário).
 * Recebe a imagem 3D que já foi lida.
 * @author : André Duarte Bueno
 *  
 * @param  : Recebe o número do maior rótulo já utilizado
 * @return : void
*/
CRede* CGrafoConexaoSerial_M2::Go ( TCMatriz3D<int>* _img3D, unsigned long int _tamanhoMascara )
{
   // Cria o rotulador intermediário
   if ( rotInt != nullptr )
      delete rotInt;

   rotInt = new CRotulador2DCm ( _img3D->NX (), _img3D->NY () );

   if ( rotInt == nullptr )
      cerr << "Erro alocação rotInt";

   assert ( rotInt );

   // Chama Função da classe base
   CGrafoConexaoSerial::Go ( _img3D, _tamanhoMascara );

   // Deleta o rotulador intermediario
   delete rotInt;
   rotInt = nullptr;
   // CGrafo*
   return this;
}

// -------------------------------------------------------------------------
// Função:   DeterminarConexoesObjetos
// -------------------------------------------------------------------------
/** @short : Função DeterminarConexoesObjetos(ra,rp,maiorRotuloUtilizado) override;
  * Lembre-se no modelo M1, para cada pixel com intersecção uma conexão, neste modelo
  * M2 usamos um plano intermediário para evitar que cada intersecção entre píxeis
  * corresponda a uma conexão.
  * 
  * Neste modelo M2 a função DeterminarConexoesObjetos funciona da seguinte forma:
  * Os planos i e i+1 são rotulados, gerando-se a seguir os sítios.
  * Depois gera-se um objeto de rotulagem com o plano intermediário rotint (da conexão dos planos i com i+1)
  * e um vetor de link's válidos.
  * Percorre as imagens i e i+1 e estabelece as conexões nos dois sentidos, só que
  * para evitar a repetição da conexão a cada píxel com intersecção válida, 
  * após estabelecer a conexão entre os objetos seta o vetor de link para aquele rótulo
  * do plano intermediário como inválido (já conectado).
  * Desta forma as conexões são corretamente estabelecidas, e eliminan-se as conexões redundantes.
  * ex:
  * -------*****************----------************--------------------------- plano i
  * -----------------********************-------***************-------------- plano i+1
  * 
  * -------*****************----------************--------------------------- plano i
  * -----------------#######----------###-------##--------------------------- plano intermediário (interseções)
  * -----------------********************-------***************-------------- plano i+1
  * 
  * Conexões marcadas com | (note que não gera conexões extras).
  * -------*****************----------************--------------------------- plano i
  * -----------------|######----------|##-------|#--------------------------- plano intermediário (interseções)
  * -----------------********************-------***************-------------- plano i+1
  * OBS:
  * Observe acima que dois objetos conexos, podem gerar mais de uma conexão válida.
  * Ou seja, o plano intermediario pode ter mais de um objeto, com intersecção entre os planos ra e rp.
  *
  * @author : André Duarte Bueno
  *  
  * @param  : Recebe o número do maior rótulo já utilizado
  * @return : void
*/
void
CGrafoConexaoSerial_M2::DeterminarConexoesObjetos ( unsigned long int maiorRotuloUtilizado )
{
  // Variáveis auxiliares 
  unsigned long int rpa; // rótulo do píxel[i,j] no plano ra
  unsigned long int rpp; // rótulo do píxel[i,j] no plano rp

   // rotuladorIntermediario_NumeroObjetos
   unsigned long int rotuladorIntermediario_NumeroObjetos;

   // Copia dados da conexão das duas imagens para a img2D
   // ou seja gera imagem da intersecção entre os dois planos de rotulagem
   for ( int ii = 0; ii < img2D->NX (); ii++ )
      for ( int jj = 0; jj < img2D->NY (); jj++ )
         if ( ra->data2D[ii][jj] && rp->data2D[ii][jj] )
            img2D->data2D[ii][jj] = 1;
         else
            img2D->data2D[ii][jj] = 0;

   // Rotula a imagem intermediária (img2D) usando rotInt
   rotInt->Go ( img2D );

   // Determina o numero total de links (objetos do plano intermediario).
   // Ao criar +1 objeto, esta considerando o fundo, de forma que o indice i aponta parar o objeto i
   // indice=0 objeto fundo 0
   // indice=1 objeto com rotulo 1....e assim sucessivamente
   rotuladorIntermediario_NumeroObjetos = rotInt->RotuloFinal () + 1;

   // Cria vetor dos links válidos, incializa com valor 1
   // Se ==1 conexão é válida (ainda não foi estabelecida)
   // Se ==0 conexão inválida (já foi usada)
   vector<unsigned int> links_validos (rotuladorIntermediario_NumeroObjetos , 1);

   // Percorre imagem rotulada intermediária,
   // se conectada, seta o link como válido, e conecta os sítios
   for ( int ii = 0; ii < rotInt->NX (); ii++ )
      for ( int jj = 0; jj < rotInt->NY (); jj++ )

         // se não for o fundo, entra
         if ( rotInt->data2D[ii][jj] != 0 ) {
               // se for uma conexão válida, ainda não foi estabelecida, entra
               if ( links_validos[ rotInt->data2D[ii][jj] ] == 1 ) {
                     // Abaixo, seta a conexão como inválido (o que impede repetição da mesma conexão)
                     links_validos[ rotInt->data2D[ii][jj] ] = 0;

                     // Obtem os rótulos
                     rpa = ra->data2D[ii][jj];
                     rpp = rp->data2D[ii][jj];

                     // Acrescenta o deslocamento do maiorRotuloUtilizado
                     rpa += maiorRotuloUtilizado;

                     // Soma o maiorRotuloUtilizado + ra->RotuloFinal()
                     rpp += maiorRotuloUtilizado + ra->RotuloFinal ();

                     // Adiciona o objeto a lista de links
                     // rpa-1 esta conectado a rpp-1
                     objeto[rpa - 1]->Conectar ( objeto[rpp - 1] );
                     // rpp-1 esta conectado a rpa-1
                     objeto[rpp - 1]->Conectar ( objeto[rpa - 1] );
                  }
            }
}

// -------------------------------------------------------------------------
// Função:   CalcularCondutancias
// -------------------------------------------------------------------------
/** Função:   CalcularCondutancias (ex: converte raio hidraulico em condutância).
    @short:   Todo objeto do grafo tem uma propriedade que é armazenada.
    A função CalcularCondutancias é uma função criada para alteração
    desta propriedade levando em conta os fenômenos que se deseja estudar.

    Específico:
    No caso específico do cálculo da permeabilidade de representações tridimensionais,
    transforma a propriedade raioHidraulico dos "sítios" em condutância.
    Esta condutância é usada pelo objeto "sítio" para calcular a sua pressão (x).

    Ou seja:
    Quando se determina o grafo a propriedade armazenada nos objetos é o raio hidraulico.
    Quando se deseja determinar a permeabilidade a propriedade armazenada é a condutancia.

    Note que a função esta calculando a condutancia segundo a lei de Poiselle -> para ligações
    (eq 5.16 da tese Liang).
    condutancia=       ( CMath::PI * dH * dH * dH * dH )
                                       /
                (128.0 * _viscosidade * _dimensaoPixel * _fatorAmplificacao );

    Abaixo a equacao da condutancia para sitios segundo Koplik (1983), eq 5.17 da tese do Liang
    Calcula a condutancia do sitio usando a equação ri^3/(3*viscosidade) [corrigir equação pois tem erro!]
    condutancia=(raio_hidraulico*raio_hidraulico*raio_hidraulico)/(3.0*_viscosidade);

    Na classe CGrafoConexaoSerial_M2::CalcularCondutancias considera o raio hidraulico de this para
    calcular a condutancia.
    @author : André Duarte Bueno
      CPermabilidade
    @param  : viscosidade, dimensão do pixel e fator de amplificação do pixel.
    @return : void
*/
void CGrafoConexaoSerial_M2::CalcularCondutancias ( long double _viscosidade, long double _dimensaoPixel,
      unsigned long int _fatorAmplificacao )
{
   // Variáveis auxiliares
   // Raio hidrâulico
   long double raio_hidraulico {0.0};
   // Diâmetro hidrâulico
   long double dH {0.0};
   long double dimensaoPixelXfatorAmplificacao = _dimensaoPixel * _fatorAmplificacao;
   long double variavelAuxiliar = ( CMath::PI ) / ( 128.0 * _viscosidade * dimensaoPixelXfatorAmplificacao );

   // Percorre  todos os objetos do grafo
   for ( unsigned long int k = 0; k < objeto.size (); k++ ) {
         // Pega o raio hidraulico do objeto k e já converte para metros
         raio_hidraulico = objeto[k]->propriedade * dimensaoPixelXfatorAmplificacao;
         dH = raio_hidraulico + raio_hidraulico + raio_hidraulico + raio_hidraulico;
         // Calcula condutancia a partir do diâmetro hidraulico.
         objeto[k]->propriedade = ( variavelAuxiliar * dH * dH * dH * dH );
      }
   return;
}
