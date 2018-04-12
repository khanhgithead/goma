/************************************************************************ *
* Goma - Multiphysics finite element software                             *
* Sandia National Laboratories                                            *
*                                                                         *
* Copyright (c) 2014 Sandia Corporation.                                  *
*                                                                         *
* Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,  *
* the U.S. Government retains certain rights in this software.            *
*                                                                         *
* This software is distributed under the GNU General Public License.      *
\************************************************************************/


/*
 *$Id: mm_fill_species.h,v 5.5 2008-11-06 15:53:44 hkmoffa Exp $
 */

#ifndef MM_FILL_POPULATION_H
#define MM_FILL_POPULATION_H

#ifdef EXTERN
#undef EXTERN
#endif

#ifdef _MM_FILL_POPULATION_C
#define EXTERN /* do nothing */
#endif

#ifndef _MM_FILL_POPULATION_C
#define EXTERN extern
#endif

#include "std.h"
#include "mm_as_structs.h"

EXTERN void wheeler_algorithm(int N, double *moments, double *weights, double *nodes);

EXTERN int get_foam_pbe_indices(int *index_W, int *index_OH, int *index_BA_l,
				 int *index_BA_g, int *index_CO2_l, int *index_CO2_g);
EXTERN double
foam_pbe_heat_source(HEAT_SOURCE_DEPENDENCE_STRUCT *d_h,
		     double tt,	/* parameter to vary time integration from
				 * explicit (tt = 1) to implicit (tt = 0) */
		     double dt);	/* current time step size */

EXTERN double
foam_pbe_conductivity( CONDUCTIVITY_DEPENDENCE_STRUCT *d_k,
		       dbl time );

struct moment_source_dependence
{
  double T[MAX_MOMENTS][MDE];           /* temperature dependence. */
  double C[MAX_MOMENTS][MAX_CONC][MDE]; /* conc dependence. */
};
typedef struct moment_source_dependence MOMENT_SOURCE_DEPENDENCE_STRUCT;

struct moment_growth_rate {
  double G[MAX_CONC][MAX_MOMENTS];
  double d_G_dC[MAX_CONC][MAX_MOMENTS][MDE];
  double d_G_dT[MAX_CONC][MAX_MOMENTS][MDE];
};

EXTERN int
moment_source(double *msource, MOMENT_SOURCE_DEPENDENCE_STRUCT *d_msource);

EXTERN int
assemble_moments(double time,	/* present time value */
		 double tt,	/* parameter to vary time integration from explicit (tt = 1) to implicit (tt = 0) */
		 double dt,	/* current time step size */
		 const PG_DATA *pg_data );

EXTERN double PBEVolumeSource (double time,
			       double dt,
			       double tt,
			       double dFVS_dv[DIM][MDE],
			       double dFVS_dT[MDE],
			       double dFVS_dx[DIM][MDE],
			       double dFVS_dC[MAX_CONC][MDE],
			       double dFVS_dMOM[MAX_MOMENTS][MDE]);

EXTERN int get_moment_growth_rate_term(struct moment_growth_rate *MGR);

EXTERN void foam_pbe_conversion_water(struct Species_Conservation_Terms *st,
				      double time,
				      double tt,
				      double dt);

EXTERN void foam_pbe_conversion_OH(struct Species_Conservation_Terms *st,
				   double time,
				   double tt,
				   double dt);

EXTERN void foam_pbe_ba_gas_source(struct Species_Conservation_Terms *st,
				   double time,
				   double tt,
				   double dt);

EXTERN void foam_pbe_ba_liquid_source(struct Species_Conservation_Terms *st,
				      double time,
				      double tt,
				      double dt);

EXTERN void foam_pbe_co2_gas_source(struct Species_Conservation_Terms *st,
				    double time,
				    double tt,
				    double dt);

EXTERN void foam_pbe_co2_liquid_source(struct Species_Conservation_Terms *st,
				       double time,
				       double tt,
				       double dt);

EXTERN int
assemble_density();

EXTERN double PBEVolumeSource_rhoeqn(double time,
				     double dt,
				     double tt,
				     double dFVS_drho[MDE]);

#endif /* MM_FILL_POPULATION_H */
