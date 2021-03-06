 /*
 ** KF-Ray, raytracer parallèle
 **  main.c
 **
 ** Copyright 2009 Karin AIT-SI-AMER & Florian DANG
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "loader/loader.h"
#include "misc/printinfo.h"
#include "main.h"

#ifdef MY_MPI
#include <mpi.h>
#include "parallel/master.h"
#include "parallel/slave.h"
#endif


int		main(int argc, char **argv)
{
	int	model_brdf = 3;			// Blinn-Phong par défaut
	int	model_texture = 1;		// Texture activé par défaut
	int	opt_aliasing = 0;		// Anti-aliasing désactivé par défaut
	int	n_lines = 10;			// Nombres lignes calculés par chaque processus slave
	int	opt_display = 0;		// Lancement du display désactivé à la fin
	float	cam_move = 0.0f;		// Distance du point de fuite supplémentaire (animation)
	int	opt_mist = 0;			// Type de brouillard
	char	scn_name[MAX_FILE_LENGTH];	// Nom du fichier de scène
	char	img_name[MAX_FILE_LENGTH];	// Nom de l'image final
	strcpy(scn_name, "");			// Nom de fichier par défaut
	strcpy(img_name, "kfray.ppm");		// Nom d'image par défaut
	int	rank = 0;			// Rang du processus
	int	n_proc = 1;			// Nombre de processus

#ifdef MY_MPI
	/* Initialisation MPI */
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
#endif

	t_arguments arg_main = CreateArg(scn_name, img_name, &model_brdf, &model_texture,
					&n_lines, &opt_display, &opt_aliasing, &cam_move, &opt_mist);

	if (!LookArguments(argc, argv, arg_main))
		return 0;

	t_scene	scn = Loader(	scn_name, model_brdf, model_texture,
				opt_aliasing, cam_move, opt_mist );

	return	CallRaytracer(scn, opt_display, img_name, n_proc, rank, n_lines);
}


int		CallRaytracer	(t_scene scn, int opt_display,
				char *img_name, int n_proc, int rank, int n_lines)
{
	// Debut du chronometrage
	double	debut = my_gettimeofday();

#ifndef MY_MPI
	if (!opt_display)
		Raytracer(scn, img_name);
	else
		ForkRaytracer(scn, img_name);

	double fin = my_gettimeofday();
	fprintf( stdout, "\n>> Processed in 	: 	[%g s]\n\n", fin - debut);
#else
	MPI_Status status;

	if (n_proc <= 1)
	{
		printf("%s", splash);
		if (!opt_display)
			Raytracer(scn, img_name);
		else
			ForkRaytracer(scn, img_name);
	}
	else
	{
		if (rank == 0)
			Master	(n_proc, scn.viewport[1], scn.viewport[0],
				n_lines, img_name, opt_display);
		else
			Slave	(scn, scn.viewport[1], scn.viewport[0],
				n_lines, rank);
	}

	// Chronométrage pour chaque processus
	double	fin = my_gettimeofday();
	fprintf( stdout, "# Process %d finished in : %g s\n", rank, fin - debut);

	MPI_Finalize();

#endif

	return	0;
}


int		ForkRaytracer(t_scene scn, char *img_name)
{
	pid_t	pid = fork();
	int	pid_status;

	if (pid == -1)
	{
		perror( "(EE) Error ! Fork problem !\n");
		return EXIT_FAILURE;
	}
	else if (pid == 0)		// Fils
	{
		Raytracer(scn, img_name);
		/*
		** On ne sait jamais si on a à rajouter du code ici
		*/
	}
	else				// Pere
	{
		waitpid(pid, &pid_status, WUNTRACED);	// On attend que le raytracer finisse

		if (ShowImage(img_name))
			perror("Exec error !");

		return EXIT_FAILURE;
	}

	return	0;
}

