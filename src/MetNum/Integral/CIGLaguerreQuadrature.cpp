// #include <iostream.h>#include <cmath>#include <CIntegral/CIGLaguerreQuadrature.h>// ------------------------------------------------------------------------------// calcula area dos subintervalos, se numeroSubIntervalos=1 é o resultado final//      virtual double Go(double x=1,double y=0);       // calcula a funcao em si y=f(x)double  CIGLaguerreQuadrature::Go(double x,double y){//    limiteInferior=y;//    limiteSuperior=x;//    Dx();       resultado =      0.45896467 * funcao->Go(0.22284660)                                                   + 0.41700083 * funcao->Go(1.18893210)                                                   + 0.11337333 * funcao->Go(2.99273663)                                                   + 0.01039920 * funcao->Go(5.77514357)                                                   + 0.00026102 * funcao->Go(9.83746742)                                                   + 0.00000090 * funcao->Go(15.98287398);   return resultado;}