//Copyright and Disclaimer:
//This code is copyright Vienna University of Technology, 2004.
/*
a few simple mathematical routines; not the most efficient ones, but easy to understand.
*/

#pragma once

#define DOUBLE_MAX DBL_MAX

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>

// no cpp source for this

#ifndef M_PI
#define M_PI (double)3.14159265358979323846
#endif


#define PI M_PI
#define PI_2 M_PI/2
#define PI_180 M_PI/180

#ifndef max
//fixed parenthesis on max function
#define max( a, b) (((a) > (b))? (a) : (b))
#endif

#define maximum max

inline void clamp(double* value, const double min, const double max)
{
   *value = ( *value > max ) ? max : ( ( *value < min ) ? min : *value );
}

//absolut value of double
inline double absDouble(const double dA )
{
	return ( ( dA < 0.0)? (-dA):(dA) );
   //signum of double
};

inline double signDouble(const double a)
{
	return ( (a < 0.0)? (-1.0f): ( (a == 0.0)? (0.0f):(1.0f) ) );
}

inline double coTan(const double vIn)
{
	return (double)-tan(vIn+PI_2);
}

inline double relativeEpsilon(const double a, const double epsilon)
{
	return max(absDouble(a*epsilon),epsilon);
}

//	| a1 a2 |
//	| b1 b2 | calculate the determinent of a 2x2 matrix
inline double det2x2( const double a1, const double a2,
                      const double b1, const double b2)
{
	return a1*b2 - b1*a2;
}


//
//	| a1 a2 a3 |
//	| b1 b2 b3 |
//	| c1 c2 c3 | calculate the determinent of a 3x3 matrix
inline double det3x3(const double a1, const double a2, const double a3,
   			  const double b1, const double b2, const double b3,
  	   		  const double c1, const double c2, const double c3)
{
	return a1*det2x2(b2,b3,c2,c3)
        - b1*det2x2(a2,a3,c2,c3)
        + c1*det2x2(a2,a3,b2,b3);
}

// rand, sign, and range functions by Parkitect
#pragma once
short ShortRand(void);
short RandSign(void);
template<class InRangeType>
	bool InRange(InRangeType a,InRangeType l,InRangeType h){	return(l>h?InRange(a,h,l):a>=l&&a<=h);	}

float frand();
float frandCenter(float c,float distFrom);
float SignedFloatRand();
float ScaledRand(float scale);
float SignedScaledRand(float span);
float nzsign(float n);

template<class T>
T Max(T a,T b){		return(a>b?a:b);	}
template<class T>
T Min(T a,T b){		return(a<b?a:b);	}
template<class T>
T Avg(T a,T b){		return((a+b)/2);	}

// ! rand, sign, and range functions by Parkitect

//	logarithmic function by Parkitect

float ln(float v);
float logb(float v,float base);


//	!	logarithmic function by Parkitect
