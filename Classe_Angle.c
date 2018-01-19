/******************************************************************************\
fichier : Classe_Angle.c
\******************************************************************************/

#include "Classe_Angle.h"

/* Inclusion des bibliotheques standard du C */


/******************************************************************************/
/* Constantes privees */
/******************************************************************************/
/* table des angles de rotation */
static const int32_t table_rotations[10] = { 248918915, 131521918, 66762579,
                                             33510843, 16771758, 8387925,
                                             4194219, 2097141, 1048575,
                                             524288 };


/******************************************************************************/
/* Definition des methodes publiques */
/******************************************************************************/
void ANG_Calculer_Cosinus_Sinus( const Classe_Angle angle,
                                 int16_t* const cosinus,
                                 int16_t* const sinus )
{
    int32_t somme_rotations = 421657428L; /* = pi/4 * 2^29 */

    int32_t copie_cosinus_32bits; /* resol 2^-30 */
    int32_t cosinus_32bits = 652032874L; /*  cos(pi/4) * K'(29) / resol */
      /* =0.7071*0.858785336480428*2^30, facteur K applique a l'avance (n=29) */
    int32_t sinus_32bits = 652032874L; /*  sin(pi/4) * K'(29) / resol */
      /*= 0.7071*0.858785336480428*2^30, facteur K applique a l'avance (n=29) */

    /* Selection du premier angle de rotation */
    int32_t rotation = table_rotations[0];

    uint8_t ind_rot; /* indice de rotation */
    int32_t angle_32bits;

    /* Reduction au domaine [0, pi/2] */
    if( angle > 38604U ) /* si angle > 3pi/2 */
    {
        ANG_Calculer_Cosinus_Sinus( 51472U - angle , cosinus, sinus );
        *cosinus = *cosinus;
        *sinus = -*sinus;
    }
    else if( angle > 25736U ) /* si angle > pi */
    {
        ANG_Calculer_Cosinus_Sinus( angle - 25736U, cosinus, sinus );
        *cosinus = -*cosinus;
        *sinus = -*sinus;
    }
    else if( angle > 12868U ) /* si angle > pi/2 */
    {
        ANG_Calculer_Cosinus_Sinus( 25736U - angle, cosinus, sinus );
        *cosinus = -*cosinus;
        *sinus = *sinus;
    }
    /* Algorithme CORDIC */
    else
    {
        /* passage sur 32 bits */
        angle_32bits = angle<<16;

        /* 29 rotations pour faire converger somme_rotations
        vers angle_32bits */
        for ( ind_rot=1 ; ind_rot<=29 ; ind_rot++ )
        {
            copie_cosinus_32bits = cosinus_32bits;
            if( angle_32bits > somme_rotations )
            {
                cosinus_32bits = cosinus_32bits - (sinus_32bits>>ind_rot);
                sinus_32bits = (copie_cosinus_32bits>>ind_rot) + sinus_32bits;
                somme_rotations = somme_rotations + rotation;
            }
            else
            {
                cosinus_32bits = cosinus_32bits + (sinus_32bits>>ind_rot);
                sinus_32bits = -(copie_cosinus_32bits>>ind_rot) + sinus_32bits;
                somme_rotations = somme_rotations - rotation;
            }

            /* Selection de l'angle de rotation suivant */
            if ( ind_rot < 10 )
            {
                rotation = table_rotations[ind_rot];
            }
            else
            {
                rotation = rotation/2;
            }
        }
        /* Retour sur 16 bits */
        *cosinus = cosinus_32bits>>16;
        *sinus = sinus_32bits>>16;
    }
}
/******************************************************************************/
