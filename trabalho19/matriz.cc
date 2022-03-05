#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/timeb.h>

using namespace std;

const int TAM = 1000; 

double a[TAM][1];
double b[1][TAM];
double c[TAM][TAM];
double t1[TAM][TAM];
double t2[1][TAM];
double res[TAM][TAM];

template <int L, int C>
void inicializa( double (&m)[L][C] ) {
  for( int i = 0; i < L; i++ )
    for( int j = 0; j < C; j++ )
      m[i][j] = rand() / (double) RAND_MAX;
}

template <int L, int CL, int C>
void mult( double (&res)[L][C], const double (&a)[L][CL], const double (&b)[CL][C] ) {
  for( int i = 0; i < L; i++ )
    for( int j = 0; j < C; j++ )
      res[i][j] = 0;
  
  for( int i = 0; i < L; i++ )
    for( int j = 0; j < C; j++ )
      for( int k = 0; k < CL; k++ )
	res[i][j] += a[i][k] * b[k][j];
}



int main() {
  int opcao = 0;
  
  inicializa( a );
  inicializa( b );
  inicializa( c );

  cin >> opcao;
  
  if( opcao == 0 ) {
    cout << "multiplicacao a * b * c" << endl;
    mult( t1, a, b );
    mult( res, t1, c );
  }
  else {
    cout << "multiplicacao a * (b * c)" << endl;
    mult( t2, b, c );
    mult( res, a, t2 );
  }
    
  return 0;
}
