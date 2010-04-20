 /*
 ** KF-Ray, raytracer parallèle
 **  postprocessing.c
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
#include <time.h>

#include "../misc/misc.h"
#include "../objects/scene.h"
#include "../raytracer.h"
#include "../raycaster/raycaster.h"
#include "postprocessing.h"

#define MONTE_CARLO 50		// Pourcentage de reussite pour un rayon d etre lance

float *AntiAliasing(t_scene scn, float *RGB, int x, int y)
{
		int	k;
		float	x_delta, y_delta;
		int 	level;
		float 	coeff_reflection;
		float	coeff_refraction;

		int	n_samples = 9;	// doit être un carré supersampling
		float	delta = 1.0f / sqrtf(n_samples);
		int	n_cases = 0;

		float	*RGB_samples;
		RGB_samples = (float *) malloc(3 * sizeof (float));

		for ( x_delta = (float) x ; x_delta < (float) x + 1.0f; x_delta += delta )
			for ( y_delta = (float) y ; y_delta < (float) y + 1.0f; y_delta += delta )
			{
				if (rand() % 100 < MONTE_CARLO)	// Monte Carlo
				{
					for ( k = 0 ; k < 3; k ++ )
						RGB_samples[k] = 0.0f;

					level = 0;
					coeff_reflection = 1.0f;
					coeff_refraction = 1.0f;

					t_ray	ray_cast = CameraRay(scn, x_delta, y_delta);

					t_castray struct_cast = CreateCastray	(&ray_cast, &level,
										&coeff_reflection,
										&coeff_refraction);

					RGB_samples = CastRay(scn, struct_cast, RGB_samples);

					for ( k = 0 ; k < 3; k ++ )
						RGB[k] += RGB_samples[k];

					n_cases ++;
				}
			}

		if (n_cases == 0)	// Rare mais peut arriver
		{
			coeff_reflection = 1.0f;
			coeff_refraction = 1.0f;
			level = 0;

			t_ray ray_cast = CameraRay(scn, (float) x, (float) y);
			t_castray struct_cast = CreateCastray	(&ray_cast, &level,
								&coeff_reflection, &coeff_refraction);

			RGB = CastRay(scn, struct_cast, RGB);
		}
		else
		{
			for (k = 0 ; k < 3; k++)
				RGB[k] = MIN(RGB[k]/n_cases, MAX_COLOR);
		}

		free(RGB_samples);

		return RGB;
}


float *GammaCorrection(float *RGB)
{
	float invgamma = 1.0/2.2f;
/*
	RGB[0] = MIN(powf(RGB[0] * MAX_COLOR, invgamma), MAX_COLOR);
	RGB[1] = MIN(powf(RGB[1] * MAX_COLOR, invgamma), MAX_COLOR);
	RGB[2] = MIN(powf(RGB[2] * MAX_COLOR, invgamma), MAX_COLOR);
*/
	RGB[0] = MIN(powf(RGB[0] * 255.0f, invgamma), 255.0f);
	RGB[1] = MIN(powf(RGB[1] * 255.0f, invgamma), 255.0f);
	RGB[2] = MIN(powf(RGB[2] * 255.0f, invgamma), 255.0f);

	return RGB;
}


float	*Filter(float coeff_r, float coeff_g, float coeff_b, float *RGB)
{
	RGB[0] *= coeff_r;
	RGB[1] *= coeff_g;
	RGB[2] *= coeff_b;

	return RGB;
}
