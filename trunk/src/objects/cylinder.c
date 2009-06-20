 /*
 ** KF-Ray, raytracer parallèle
 **  plan.c
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
#include "scene.h"


t_cylinder 		CreateCylinder(t_vector point0, t_vector dir0, float height0, t_material *mat0)
{
	t_cylinder cylinder;

	cylinder.point = point0;
	cylinder.dir = dir0;
	cylinder.height = height0;
	cylinder.material = CopyMaterial(mat0);

	return	cylinder;
}

t_cylinder		*CopyCylinder(t_cylinder *cylinder0)
{
	t_cylinder	*cylinder;
	cylinder = (t_cylinder *) malloc(sizeof (t_cylinder));

	cylinder->point = cylinder0->point;
	cylinder->dir = cylinder0->dir;
	cylinder->height = cylinder0->height;
	cylinder->material = CopyMaterial(cylinder0->material);

	return	cylinder;
}

void			PrintCylinder(t_cylinder cylinder)
{
	fprintf(stdout, "[cylinder] Hauteur = %f - Point/Dir = ", cylinder.height);
	PrintVect(cylinder.point);
	PrintVect(cylinder.dir);
	PrintMaterial(cylinder.material);
	fprintf(stdout, "\n***\n");
}
