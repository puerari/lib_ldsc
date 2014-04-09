#include <gtest/gtest.h>
#include <omp.h>
#include <string>
#include <AnaliseImagem/Simulacao/Permeabilidade/CSimPermeabilidadeIntrinseca.h>
#include <AnaliseImagem/Simulacao/Permeabilidade/CPermeabilidadeIntrinsecaByRede.h>
#include "../../../gtest_configure.h"

GtestConfigure gtc = GtestConfigure();

TEST(TestPermeabilidade, IntrinsecaByGrafo) {
	//carrega a imagem original
	TCImagem3D<int>* pm = new TCImagem3D<int>(gtc.original3D);

	//Cria objeto rede
	CSimPermeabilidadeIntrinseca objPerIn = CSimPermeabilidadeIntrinseca();
	objPerIn.limiteIteracoes = 100000;
	objPerIn.limiteErro = 1.0e-06;
	long double permeabilidade = objPerIn.Go ( pm );

	//cerr << "permeabilidade: " << permeabilidade << endl;

	//compara resultado com  valor esperado
	//ASSERT_DOUBLE_EQ(permeabilidade,0.14688171985462564);
	//EXPECT_DOUBLE_EQ(permeabilidade,0.16156298595496066);
	EXPECT_NEAR(permeabilidade,0.16156298595496066,0.015);

	//deleta ponteiros
	delete pm;
}

TEST(TestPermeabilidade, IntrinsecaByRede) {
	//carrega a imagem original
	TCImagem3D<bool>* pm = new TCImagem3D<bool>(gtc.original3D);

	//Cria objeto rede
	CPermeabilidadeIntrinsecaByRede objPerIn = CPermeabilidadeIntrinsecaByRede();
	objPerIn.limiteIteracoes = 100000;
	objPerIn.limiteErro = 1.0e-06;
	long double permeabilidade = objPerIn.Go ( pm,100,100,100,23,2,1,1,EModelo::ONZE,1,0 );

	//cerr << "permeabilidade: " << permeabilidade << endl;

	//compara resultado com  valor esperado
	//ASSERT_DOUBLE_EQ(permeabilidade,0.14688171985462564);
	EXPECT_NEAR(permeabilidade,0.16156298595496066,0.015);

	//deleta ponteiros
	delete pm;
}
