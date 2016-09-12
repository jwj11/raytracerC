/*
 * deals with lights/shading functions
 *
 *	John Amanatides, Nov 2015
 */


#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "artInternal.h"

#define CHECKERBOARD	1
#define ZONE_PLATE	2

extern double	Normalize(Vector *);
extern Vector	ReflectRay(Vector, Vector);
extern int	IntersectScene(Ray *, double *, Vector *, Material *);
extern int	ShadowProbe(Ray *, double);

static Color	background;
static Material	currentMaterial;
static Color black= {0.0, 0.0, 0.0}, white= {1.0, 1.0, 1.0};



char *
art_Light(double x, double y, double z, double intensity, double radius)
{
	/* your code goes here */

	return NULL;
}


char *
art_Material(Material material)
{
	currentMaterial= material; /* should really check for mistakes */
	return NULL;
}


Material
GetCurrentMaterial(void)
{
	return currentMaterial;
}


char *
art_Background(Color color)
{
	background= color;	/* should really check for mistakes */
	return NULL;
}


static Color
Texture(Material *material, Point position)
{               
	int funnySum;
	double EPSILON= 0.0001;
	double contribution;
	Color result;

	switch(material->texture) {

	case CHECKERBOARD: 
		funnySum= floor(position.v[0]+EPSILON)
			+ floor(position.v[1]+EPSILON)
			+ floor(position.v[2]+EPSILON);
		if(funnySum % 2)
			return white;
		else    return material->col;
	case ZONE_PLATE:
		contribution= 0.5*cos(DOT(position, position))+0.5;
		TIMES(result, material->col, contribution);
		return result;  
	default:                
	return material->col;
	}       
}       


/*
 * a simple shader
 */
static Color
ComputeRadiance(Ray *ray, double t, Vector normal, Material material)
{
	(void) Normalize(&normal);

	/* your code goes here */

	return white;
}


Color
GetRadiance(Ray *ray)
{
	double t;
	Vector normal;
	Material material;

	if(IntersectScene(ray, &t, &normal, &material) == HIT)
		return ComputeRadiance(ray, t, normal, material);
	else	return background;
}


void InitShading()
{
	Material material;

	material.col= white;
	material.Ka= 0.2;
	material.Kd= 0.6;
	material.Ks= 0.7;
	material.n= 50.0;
	material.Kr= 0.0;
	material.Kt= 0.0;
	material.index= 1.0;
	material.texture= 0;
	(void) art_Material(material);
	(void) art_Background(black);

	/* your code goes here */
}


void FinishShading()
{
	/* your code goes here */
}
