 /*
 ** KF-Ray, raytracer parallèle
 **  raytracer.c
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
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "raytracer.h"
#include "raycaster/raycaster.h"
#include "objects/scene.h"
#include "misc/misc.h"
#include "misc/printinfo.h"
#include "misc/image.h"
#include "models/postprocessing.h"
#include "misc/image.c"

#ifdef _OPENMP
# include <omp.h>
#endif

//#define MY_ANAGLYPH

void	Raytracer(t_scene scn, char *img_name)
{
	InfoRaytracer(scn, img_name);

	int		x;
	int		y;

	unsigned char	*image;
	image  = 	(unsigned char*) \
			malloc(scn.viewport[0] * scn.viewport[1] * 3 * sizeof (unsigned char));

	//printf(">> Balayage :				[En cours...]\n");
	printf(">> Ray tracing...\n");

	if (scn.options.opt_aliasing != 0)
		srand((unsigned)time(NULL));

	#ifdef _OPENMP
	// On regarde combien il y a de cores
	if(omp_get_num_procs() > 0)
                omp_set_num_threads(omp_get_num_procs());
	#endif

	#pragma omp parallel
	{
	// A voir c'est pas convaincant ce dynamic
	#pragma omp for schedule(dynamic, 2) private(x, y)
	for (y = 0; y < scn.viewport[1]; y ++)
		for (x = 0; x < scn.viewport[0]; x ++)
			ComputePixel(scn, image, x, y);

	}
	SaveImage(image, img_name, scn.viewport[0], scn.viewport[1]);
	FreeScene(scn);
	//free(image); WTF Segmentation fault sur shell mais pas sur codeblocks ?!
}


void	ComputePixel(t_scene scn, unsigned char *image, int x, int y)
{
	float 	coeff_reflection = 1.0f;
	float	coeff_refraction = 1.0f;
	int 	level = 0;

	float	*RGB;
	RGB = (float*) malloc(3 * sizeof (float));

	RGB[0] = 0.0f;
	RGB[1] = 0.0f;
	RGB[2] = 0.0f;

	if (scn.options.opt_aliasing == 0)
	{
		t_ray ray_cast = CameraRay(scn, (float) x, (float) y);
		t_castray struct_cast = CreateCastray	(&ray_cast, &level,
							&coeff_reflection, &coeff_refraction);

		RGB = CastRay(scn, struct_cast, RGB);
	}
	else
		RGB = AntiAliasing(scn, RGB, x, y);

	/* Anaglyph Test */

#ifdef MY_ANAGLYPH

	RGB = Filter(1.0f, 1.0f, 0.2f, RGB);

	float	*RGB_3D;
	RGB_3D = (float*) malloc(3 * sizeof (float));

	// On initialise RGB à [0,0,0]

		RGB_3D[0] = 0.0f;
		RGB_3D[1] = 0.0f;
		RGB_3D[2] = 0.0f;

	if (scn.options.opt_aliasing == 0)
	{
		t_ray ray_cast = CameraRay(scn, (float) x + 10.0f, (float) y);
		t_castray struct_cast = CreateCastray	(&ray_cast, &level,
							&coeff_reflection, &coeff_refraction);

		RGB_3D = CastRay(scn, struct_cast, RGB_3D);
	}
	else
		RGB_3D = AntiAliasing(scn, RGB_3D, x, y);

	RGB_3D = Filter(0.2f, 0.2f, 1.0f, RGB_3D);

	RGB[0] = MIN(MAX_COLOR, (RGB[0] + RGB_3D[0]));
	RGB[1] = MIN(MAX_COLOR, (RGB[1] + RGB_3D[1]));
	RGB[2] = MIN(MAX_COLOR, (RGB[2] + RGB_3D[2]));
#endif

	// Remise à l'échelle
	
//	for (k = 0 ; k < 3; k++)
//		RGB[k] = RGB[k] * 255.0f / MAX_COLOR;

	// Déroulage boucle pour perfs
	RGB[0] = RGB[0] * 255.0f / MAX_COLOR;
	RGB[1] = RGB[1] * 255.0f / MAX_COLOR;
	RGB[2] = RGB[2] * 255.0f / MAX_COLOR;

//	RGB = GammaCorrection(RGB);

	SetPixel(image, scn.viewport[0], x, y,
		(int) RGB[0], (int) RGB[1], (int) RGB[2]);

	// Désallocation mémoire
	free(RGB);
}


t_ray	CameraRay(t_scene scn, float x, float y)
{
	t_vector point_spectator = CreateVector	(x  + scn.camera.point.x,
						scn.viewport[1] - (y + scn.camera.point.y),
						scn.camera.point.z);

	t_vector vect_view = CreateVector	( point_spectator.x - scn.viewport[0]/2,
						point_spectator.y - scn.viewport[1]/2 ,
						scn.camera.dist_view - point_spectator.z);

	vect_view = Normalize(vect_view);

	t_ray	ray_cast = CreateRay(point_spectator, vect_view);

	return	ray_cast;
}



/* Caméra libre pour les versions prochaines il faut bouger le plan de vision etc...*/

#if 0

t_ray	CameraRayFree(t_scene scn, int x, int y)
{
	t_vector vect_view = CreateVector	( -scn.camera.point.x,
						-scn.camera.point.y,
						-scn.camera.point.z );

	vect_view = Normalize(vect_view);


	t_vector point_view = Prod(scn.camera.center_view.z, vect_view);

	/* Truc compliqué prise de tête qui marche pas normal faut rotationner le plan de vue -_- */
	/*
	t_vector vect_i = Normalize(CreateVector(1.0f, -(point_view.x / point_view.y), 0.0f));
	t_vector vect_j = Normalize(CreateVector(1.0f, 0.0f, -(point_view.x / point_view.z)));

	t_vector point_spectator = CreateVector	(x * vect_i.x + scn.camera.point.x,
						scn.viewport[1] - (y * vect_j.y + scn.camera.point.y),
						scn.camera.point.z + x * vect_i.z + y * vect_j.z );
	*/

	t_vector point_spectator = CreateVector	(x  + scn.camera.point.x,
						scn.viewport[1] - (y + scn.camera.point.y),
						scn.camera.point.z);

	t_vector vect_vision =	CreateVector	(point_spectator.x - point_view.x - scn.camera.center_view.x,
						point_spectator.y - point_view.y - scn.camera.center_view.y,
						point_view.z - point_spectator.z );

	vect_vision = Normalize(vect_vision);

	t_ray	ray_cast = CreateRay(point_spectator, vect_vision);

	return ray_cast;
}

#endif
