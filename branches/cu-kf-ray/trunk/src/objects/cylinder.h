 /*
 ** KF-Ray, raytracer parallele
 **  cylinder.h
 **
 ** Copyright 2009 Karin Ait-Si-Amer & Florian Dang
 ** <aitsiame@polytech.upmc.fr>
 ** <tdang@polytech.upmc.fr>
 **
 ** Reportez-vous a COPYING pour les infos sur le Copyright
 */

#ifndef CYLINDER_H_
#define CYLINDER_H_

/**
 * \file	cylinder.h
 * \brief	Gestion de l'objet cylindre
 * \author	Karin Ait-Si-Amer et Florian Dang
 * \version	1.0.1
 * \date	Fevrier-Mai 2009
 *
 * Déclare la structure du cylinder et les prototypes de fonctions liées à cet objet.
 *
 */

#include "vector.h"
#include "../misc/misc.h"

/**
 * \struct	s_cylinder
 * \brief	Objet Cylindre
 *
 * Définit un cylindre par :
 * - sa distance par rapport au point d'origine
 * (distance du projeté orthogonal de l'origine par rapport à la normale du cylinder),
 * - un vecteur normal,
 * - son matériau
 */
typedef struct 	s_cylinder
{

	t_vector	point;		/*!< Centre du cylindre */
	t_vector	dir;		/*!< Un vecteur directeur du cylindre */
	float		height;		/*!< Hauteur du cylindre */
	t_material	*material;	/*!< Matériau du cylindre */

}		t_cylinder;


/**
 * \fn 		t_cylinder CreateCylinder(float dist0, t_vector normal0, t_material *mat0);
 * \brief 	Fonction de création d'un objet cylindre
 *
 * \param 	dist0	Distance du projeté orthogonal de l'origine du raytracer par rapport à la normale
 * \param 	normal0	Un vecteur normal au cylindre
 * \param	mat0	Matériau de la sphère
 *
 * \bug		Mineur : Si l'utilisateur met une normale opposée à la source lumineuse
 *		on n'a pas de réflexion (réglage en cours).
 *
 * \return 	Objet cylindre
 */
t_cylinder 	CreateCylinder(t_vector point0, t_vector dir0, float height0, t_material *mat0);


/**
 * \fn 		t_cylinder 	*Copycylindere(t_cylinder *cylinder0);
 * \brief 	Fonction de copie d'un matériel
 *
 * \param 	cylinder0	une adresse d'un cylinder
 *
 * \return 	un pointeur sur le nouveau cylinder copié
 */
t_cylinder 	*CopyCylinder(t_cylinder *cylinder0);


/**
 * \fn 		void    	Printcylinder(t_cylinder cylinder);
 * \brief 	Fonction d'affichage de cylinder
 *
 * \param 	cylinder un cylinder
 *
 * \return 	néant
 */
void    	PrintCylinder(t_cylinder cylinder);

#endif	/* CYLINDER_H_ */
