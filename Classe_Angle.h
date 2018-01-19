/******************************************************************************\
fichier : Classe_Angle.h
\******************************************************************************/

#ifndef CLASSE_ANGLE_H
#define CLASSE_ANGLE_H

/* Inclusion des bibliotheques standard du C */
#include <stdint.h>

typedef uint16_t Classe_Angle;



/******************************************************************************/
/* ANG_Calculer_Cosinus_Sinus

Description :
   angle   : rad | resol = 2^-13 | min = 0      ;  0 | max = 51471 ; 2pi–(2^-13)
   cosinus :  -  | resol = 2^-14 | min = –16384 ; -1 | max = 16384 ; 1
   sinus   :  -  | resol = 2^-14 | min = –16384 ; -1 | max = 16384 ; 1

Parametres :


Retour :
    aucun
*/
void ANG_Calculer_Cosinus_Sinus( const Classe_Angle angle,
                                 int16_t* const cosinus,
                                 int16_t* const sinus );


#endif
