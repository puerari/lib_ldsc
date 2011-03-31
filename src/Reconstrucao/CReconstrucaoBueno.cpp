// ------------------------------------------------------------------------------// Includes:
// -----------------------------------------------------------------------------
#include  <cmath>
#include  <cstdlib>
#include  <ctime>
#include  <fstream>
#include  <iostream>
#include  <iomanip>
using namespace std;

// ------------------------------------------------------------------------------
// Includes do LDSC
// ------------------------------------------------------------------------------
// declaracao da classe
// #include  <Reconstrucao/CReconstrucaoZhirong.h>
#include  <Reconstrucao/CReconstrucaoBueno.h>

// objeto CFNaoLinearRzRy                

#include  <Funcao/CFNaoLinearRzRy.h>

//#include  <Estatistica/CEstatisticaBasica.h>
#include  <Estatistica/CEstatistica.h>

#include  <Estatistica/CENormal.h>


// ----------------------------------------
// calculo de Ry
// ----------------------------------------
// Obs: Cria objeto externo TFuncaoNaoLinearRzRy equivale a antiga função ry=Rzry(yc,porosidade,rz);
// Determina todos os valores de Ry e salva o resultado em disco
// Obs: Embora utilize o fator de amplificação para definir quais os valores de Ry
// que serao utilizados na reconstrução, todos os valores sao determinados e salvos em disco
// isto se justifica se Ry for utilizado posteriormente em outros processos
void CReconstrucaoBueno::Calculo_Ry1D ()
{
  // Cria objeto filtro nao linear   que assume numeroPontos=35
  // cout<<"\nCriando objeto  filtroNaoLinearRzRy...";
  CFNaoLinearRzRy *funcaoNaoLinearRzRy =    new CFNaoLinearRzRy (yc, porosidade, 35, gt); 
  if (funcaoNaoLinearRzRy == NULL)
    {				
      // cout<<" ...erro alocação memória objeto filtroNaoLinearRzRy, encerra.";
      exit (1);
    }
  
  double porosidadeAoQuadrado = porosidade * porosidade;	// acelerador
  
  double porMenospor2 = porosidade - porosidadeAoQuadrado;	// acelerador
  
  int i = 0;
  
  double rz;
  
  nomeArquivoRy= "saidaRzRy.rzy";	// Abre arquivo disco para armazenar resultados
  
  // cout<<"\nVai tentar abrir o arquivo fout (escrita) com nome ="<<nomeArquivoRy;
  ofstream fout (nomeArquivoRy.c_str());	
  if (fout == NULL)
    {
      // cout<<"\nNao abriu arquivo disco "<<nomeArquivoRy<<", verifique o nome do arquivo\n";
      exit (1);
    }
  
     //  cout<<" abriu arquivo corretamente";
  fout.precision (5);		// precisao de 5 digitos na saída para disco

  // diferente:liang calcula rz para todo o cz e salva cz e rz em disco
  for (int i = 0; i < numeroPontosLidosArquivoCz; i++)
    {				// calculo de Ry em funcao de Rz
      rz = (Cz[i] - porosidadeAoQuadrado) / (porMenospor2);	// Cz normalizada
      
      Ry[i] = funcaoNaoLinearRzRy->Go (rz);	// calcula Ry de rz

      // cout<<"\nRz["<<i<<"]="<<rz<<"\tRy["<<i<<"]="<<Ry[i];             // mostra na tela
      fout << setw (4) << i << " " << setw (10) << rz << " " << setw (10) << Ry[i] << "\n";	// salva em disco
    }
    
  delete funcaoNaoLinearRzRy;	// elimina objeto criado
  
  // Aqui considera o fator de redução
  fout << "\nValores utilizados de i e Ry considerando fatorReducaoNumeroPontos";
  
  fout << "\ni\tRy";

  // obs: abaixo ao usar <=, esta usando numeroPontosCz+1 pontos e nao numeroPontosCz
  for (i = 0; i <= numeroPontosCz; i++)
    {
      Ry[i] = Ry[i * fatorAmplificacaoNumeroPontos];	// usa fator de redução para
    }

// novo: o calculo do Ry esta todo correto. Fornece exatamente os mesmos resultados do liang
  for (i = 0; i <= numeroPontosCz * fatorAmplificacaoNumeroPontos; i++)
    fout << "\n" << i << "\t" << Ry[i];	// determinar pontos a serem utilizados
  fout.close ();		// fecha ponteiro para arquivo

}

void CReconstrucaoBueno::SalvarImagemEmDisco (string arqimg)
{
	if ( fileName == arqimg ) {
		if (gt == 1) {
			fileName = "gt1-" + fileName;
			arqimg = fileName;
		} else {
			fileName = "gt2-" + fileName;
			arqimg = fileName;
		}
	}
	ofstream fimg (arqimg.c_str());	// abre arquivo disco
  	if (fimg == NULL) {
      	
	// cout<<"\nNao conseguiu abrir arquivo de disco "<<arqimag;
      	
	exit (1);
    	}
    	fimg << setw (0) << "D1\n" << NX << " " << NY << " " << NZ << "\n";
	fimg << setw (0) << "# fatorAmplificacao: " << fatorAmplificacaoNumeroPontos << "\n";
	fimg << setw (0) << "# sizePixel: " 	    << sizePixel << "\n";
	fimg << setw (0) << "# numeroPixelsBorda: " << 0 << "\n";	

  	for (k = 0; k < NZ; k++)
    		for (j = 0; j < (NY); j++) {
			for (i = 0; i < (NX); i++)	// salva arquivo de saida
				fimg << (int) Real_E1 (i, j, k) << " ";	// imagem reconstruida 3D
			fimg << "\n";
     	}
  	fimg.close ();		// fecha ponteiro para arquivo disco
}
