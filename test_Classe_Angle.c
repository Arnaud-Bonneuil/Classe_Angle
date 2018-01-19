#include <stdio.h> /* printf, getchar */
#include <stdlib.h> /* EXIT_SUCCESS */

#include "Classe_Angle.h"

#include <math.h>

void Tester_Calcul( double angle_d );
#define PI 3.14159265358979323846

int main ( int argc, char *argv[] )
{
    double i;
    Tester_Calcul( 0 );
    for( i = 1 ; i<=4 ; i++ )
    {
        Tester_Calcul( i*PI/11 );
        Tester_Calcul( i*PI/10 );
        Tester_Calcul( i*PI/9 );
        Tester_Calcul( i*PI/8 );
        Tester_Calcul( i*PI/7 );
        Tester_Calcul( i*PI/6 );
        Tester_Calcul( i*PI/5 );
        Tester_Calcul( i*PI/4 );
        Tester_Calcul( i*PI/3 );
        Tester_Calcul( i*PI/2 );
    }

    /*getchar();*/
    return EXIT_SUCCESS;
}

void Tester_Calcul( double angle_d )
{
    Classe_Angle angle = 0;
    int16_t cosinus = 0;
    int16_t sinus = 0;
    double angle_aff = 0;
    double cosinus_aff = 0;
    double sinus_aff = 0;
    double err_angle = 0;
    double err_cosinus = 0;
    double err_sinus = 0;

    double cosinus_d = 0;
    double sinus_d = 0;



    angle = (uint16_t)(angle_d*8192);
    angle_d = ((double)angle)/8192;

    cosinus_d = cos( angle_d );
    sinus_d = sin( angle_d );

    ANG_Calculer_Cosinus_Sinus( angle, &cosinus, &sinus );
    angle_aff = ((double)angle)/8192;
    cosinus_aff = ((double)cosinus)/16384;
    sinus_aff = ((double)sinus)/16384;
    err_angle = fabs( angle_d - angle_aff ),
    err_cosinus = fabs( cosinus_d - cosinus_aff );
    err_sinus = fabs( sinus_d - sinus_aff );

    printf( "%.5f %.5f %.5f\n", angle_d, cosinus_d, sinus_d );
    printf( "%.5f %.5f %.5f\n", angle_aff, cosinus_aff, sinus_aff );
    printf( "%.5f %.5f %.5f\n", err_angle, err_cosinus, err_sinus );
    printf( "%u %d %d\n\n", angle, cosinus, sinus );

}
