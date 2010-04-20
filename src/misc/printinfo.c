 /*
 ** KF-Ray, raytracer parallele
 **  printinfo.h
 **
 ** Copyright 2009 Karin Ait-Si-Amer & Florian Dang
 ** <aitsiame@polytech.upmc.fr>
 ** <tdang@polytech.upmc.fr>
 **
 ** Reportez-vous a COPYING pour les infos sur le Copyright
 */

#include <stdio.h>
#include <string.h>
#include "../objects/scene.h"
#include "printinfo.h"

void	InfoRaytracer(t_scene scn, char *img_name)
{
	char txt_aliasing[10];
	char txt_texture[10];

	if (scn.options.model_texture == 0)
		strcpy(txt_texture, txt_unactive);
	else
		strcpy(txt_texture, txt_active);

	if (scn.options.opt_aliasing == 0)
		strcpy(txt_aliasing, txt_unactive);
	else
		strcpy(txt_aliasing, txt_active);

	printf(">> Scene loading	:	[OK]\n");

	printf(">> Image output		:	[%s]\n", img_name);

	printf(">> BRDF/Texture/AA 	:\
	[%d/%s/%s]\n", scn.options.model_brdf, txt_texture, txt_aliasing);

	printf(">> Viewport dimension	:	[%dx%d]\n", scn.viewport[0], scn.viewport[1]);

	printf(">> Plane/Sphere/Light	:\
	[%d/%d/%d]\n", scn.n_plane, scn.n_sph, scn.n_light);
}

void	InfoMaster(char *img_name, int w, int h, int n_proc, int n_lines)
{
	printf(">> Scene loading	 :	[OK]\n");
	printf(">> Image output		 :	[%s]\n", img_name);
	printf(">> Viewport dimension	:	[%dx%d]\n", w, h);
	printf(">> Parallel computing MPI :	[OK]\n");
	printf(">> Processus/lines :		[%d/%d]\n", n_proc, n_lines);
}
