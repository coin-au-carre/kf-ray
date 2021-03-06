 /*
 ** KF-Ray, raytracer parallèle
 **  effects.c
 **
 ** Copyright 2009 Karin Ait-Si-Amer & Florian Dang
 ** <aitsiame@polytech.upmc.fr>
 ** <tdang@polytech.upmc.fr>
 **
 */

 /*************************************************************************
 *   This file is part of KF-Ray.
 *
 *   KF-Ray is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   KF-Ray is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KF-Ray.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "effects.h"
#include "../textures/perlin.h"


t_vector BumpMapping(t_vector vect_normal, t_vector point_intersect, float bump)
{
		float coeff_noise = 0.1f;

		float noise_x = Pnoise(coeff_noise *
				point_intersect.x, coeff_noise * point_intersect.y,coeff_noise * point_intersect.z);
		float noise_y = Pnoise(coeff_noise *
				point_intersect.y, coeff_noise * point_intersect.z,coeff_noise * point_intersect.x);
		float noise_z = Pnoise(coeff_noise *
				point_intersect.z, coeff_noise * point_intersect.x,coeff_noise * point_intersect.y);

		bump *= 0.8; // On atténue le bump ca fait des trucs zarbs sur les bords

		vect_normal.x = (1.0f - bump) * vect_normal.x + bump * noise_x;
		vect_normal.y = (1.0f - bump) * vect_normal.y + bump * noise_y;
		vect_normal.z = (1.0f - bump) * vect_normal.z + bump * noise_z;

		float temp = DotProd(vect_normal, vect_normal);

		vect_normal = Prod(1.0f/sqrtf(temp), vect_normal);

		return Normalize(vect_normal);
}


float	*Mist(t_scene scn, t_vector point_intersect, float *RGB)
{
	e_mist	TYPE_MIST = scn.options.opt_mist;
	int	k;

	float RGB_mist[] = { MAX_COLOR - 10000.0f, MAX_COLOR - 10000.0f, MAX_COLOR - 10000.0f };
	float dist_mist = 2800.0f;

	float dist_object = sqrtf(DotProd(point_intersect, point_intersect));
	float rapport_dist = dist_object/dist_mist;

//	if (rapport_dist < 0.0f)
//		fprintf(stderr, "!Warning : Rapport distance mist negatif\n");

	switch(TYPE_MIST)
	{
		case MIST_LINEAR:
			for (k=0; k<3; k++)
				// FUN 23 !!!
				//RGB[k] = RGB_mist[k] * rapport_dist + RGB[k] * (1.0f - MAX(rapport_dist, 1.0f));
				RGB[k] = RGB_mist[k] * rapport_dist + RGB[k] * (1.0f - MIN(rapport_dist, 1.0f));
			break;

		case MIST_EXP:
			for (k=0; k<3; k++)
				RGB[k] = RGB_mist[k] * (1.0f - expf(-rapport_dist)) +
					 RGB[k] * expf(-rapport_dist);
			break;

		case MIST_EXP_SQUARE:
			for (k=0; k<3; k++)
				RGB[k] = RGB_mist[k] * (1.0f - expf(-rapport_dist*rapport_dist)) +
					 RGB[k] * expf(-rapport_dist * rapport_dist);
			break;

		default:
			break;
	}

	return RGB;
}

