ma/*
=========================================================================
PROJETO:          Biblioteca LIB_LMPT
                  Ramo: TPadrao_ramo
=========================================================================

Desenvolvido por:	Laboratorio de Meios Porosos
		e Propriedades Termofisicas	[LMPT].
@author:          Andr� Duarte Bueno
File:             CSMDTDMA.cpp
begin:            Sat Sep 16 2000
copyright:        (C) 2000 by Andr� Duarte Bueno
email:            andre@lmpt.ufsc.br
*/

// -----------------------------------------------------------------------
// Bibliotecas C/C++
// -----------------------------------------------------------------------
// #include <fstream>

// -----------------------------------------------------------------------
// Bibliotecas LIB_LMPT
// -----------------------------------------------------------------------
#include <SMatriz/SMDiagonal/CSMDTDMA.h>

#include <Base/COperacao.h>

// #include "TNo\TNo-novo.h" bug?????????

// ---------------------------------------------------------------------------
// Construtor
// ---------------------------------------------------------------------------
CSMDTDMA::CSMDTDMA ():CSMDiagonalDominante ()
{
  int    numeroObjetos = 10;
  p = new double[numeroObjetos];
  q = new double[numeroObjetos];
  COperacao::TestaAlocacao (q, "CSMDTDMA coeficientes p,q");
}

// ---------------------------------------------------------------------------
// Destrutor
// ---------------------------------------------------------------------------
CSMDTDMA::~CSMDTDMA ()
{
  if (p)
    delete[]p;
  if (q)
    delete[]q;
}

/*
// ---------------------------------------------------------------------------
// Atualiza o valor de X
// ---------------------------------------------------------------------------
Possivel formato generico para o TDMA
1- Para poder acessar atributos do objeto n� avan�ado, precisa de um cast dinamico
  // obj � um ponteiro para a classe pai
	 CSMParametroSolverAvancado* no=dynamic_cast<CSMParametroSolverAvancado*>(obj);

2- Antes de calcular P e Q, os parametros Ai do objeto n� devem ser atualizados
	 obja->AtualizaParametrosAi();
    	// se for no de contorno deve considerar o contorno
3- Deve ent�o calcular os valores de P e Q
     Calcula PQ
4- Atualiza todos os valores de X
5- Faz k=numeroObjetos encerrando o for k do solver,
	e eventualmente iteracoes=limiteIteracoes encerrando o do..while() do solver.
*/
void
CSMDTDMA::AtualizaX ()
{
  // -------------------------------------------------------------------------
  // cast dinamico para acesso a atributos extras
  TNo *no = dynamic_cast < TNo * > (obj);
	// obs obj � um ponteiro de ponteiro, por isso usei *obj

  // -------------------------------------------------------------------------
  // Atualiza os valores dos coeficientes Ai do no
  no->AtualizaCoeficientesAi ();

  // -------------------------------------------------------------------------
  // Fun��o CalculaPQ(); // Com base nos coeficientes Ai calcula P e Q
  p[0] = no[0].ae / no[0].ap;
  q[0] = no[0].b / no[0].ap;
  for (int i = 1; i < numeroObjetos - 1; i++)
    {
      p[i] = no[i].ae / (no[i].ap - no[i].aw * p[i - 1]);
      q[i] =
	(no[i].aw * q[i - 1] + no[i].b) / (no[i].ap - no[i].aw * p[i - 1]);
    }
  p[numeroObjetos - 1] = 0.0;	// porque b=Ae=0
  q[numeroObjetos - 1] =
    (no[numeroObjetos - 1].aw * q[numeroObjetos - 1 - 1] +
     no[numeroObjetos - 1].b) / (no[numeroObjetos - 1].ap - no[numeroObjetos -
							       1].aw *
				 p[numeroObjetos - 1 - 1]);

  // -------------------------------------------------------------------------

  // Atualiza��o de todos os valores de X
  X[numeroObjetos - 1] = q[numeroObjetos - 1];	// calcula X[N]=q[N];
  for (int i = numeroObjetos - 1; i > 0; i--)
    X[i - 1] = p[i - 1] * X[i] + q[i - 1];	// calcula os demais X
}


/*
Obs:
 Segundo a hierarquia, a fun��o AtualizaX deveria atualizar o valor de X.
 Mas o TDMA usa um procedimento de calcular todos os p e q,
 e posteriormente atualizar todos os valores de X.
 A solu��o �:
 1- Tirar o TDMA desta hierarquia (inicialmente desconsiderada)
 Optei por:
 2- A fun��o atualiza X faria o seguinte:
   -Atualizaria os valores dos coeficientes Ai
 	-Chamaria CalculaPQ (que calcularia todos os valores de p e q)
   -Atualizaria todos os valores de X
   -Faria k=numeroObjetosPassados (encerrando o loop).
*/

// ---------------------------------------------------------------------------
// Funcao calcula PQ antiga      (Auxiliar)
// ---------------------------------------------------------------------------
/*void CSMDTDMA::CalculaPQ()
{
  p[0]=ae[0]/ap[0];
  q[0]=b[0]/ap[0];
  for(int i=1;i<numeroEquacoes-1;i++)
	{
	p[i]=ae[i]/(ap[i]-aw[i]*p[i-1]);
	q[i]=(aw[i]*q[i-1]+b[i])/(ap[i]-aw[i]*p[i-1]);
	}
  p[numeroEquacoes-1]=0.0;// porque b=Ae=0
  q[numeroEquacoes-1]=(aw[numeroEquacoes-1]*q[numeroEquacoes-1-1]+b[numeroEquacoes-1])
/(ap[numeroEquacoes-1]-aw[numeroEquacoes-1]*p[numeroEquacoes-1-1]);
}*/
