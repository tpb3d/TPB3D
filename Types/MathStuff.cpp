//Copyright and Disclaimer:
//This code is copyright Vienna University of Technology, 2004.

//#include <math.h>
//#include <float.h>
#include "MathStuff.h"



//const double PI = M_PI;
//const double PI_2 = M_PI/2;
//const double PI_180 = M_PI/180;

/*double maximum(const double a, const double b)
{
	return ( (a > b)? a : b );
}*/

//void clamp(double* value, const double min, const double max)
//{
//   *value = ( *value > max ) ? max : ( ( *value < min ) ? min : *value );
//}

//double absDouble(const double a)
//{
//	return ( (a < 0.0)? (-a):(a) );
//}

//double signDouble(const double a)
//{
//	return ( (a < 0.0)? (-1.0f): ( (a == 0.0)? (0.0f):(1.0f) ) );
//}

//double coTan(const double vIn)
//{
//	return (double)-tan(vIn+PI_2);
//}

//double relativeEpsilon(const double a, const double epsilon)
//{
//	return max(absDouble(a*epsilon),epsilon);
//}

//int alike(const double a, const double b, const double epsilon)
//{
//	if(a == b)
//   {
//		return 1;
//	}
//	double relEps = relativeEpsilon(a,epsilon);
//	return (a-relEps <= b) && (b <= a+relEps);
//}



//int alikeVector3(const Vector3& a, const Vector3& b, const double epsilon)
//{
//	return ( alike(a[0],b[0],epsilon) &&
//		      alike(a[1],b[1],epsilon) &&
//		      alike(a[2],b[2],epsilon) );
//}
//
//void linCombVector3(Vector3& result, const Vector3& pos, const Vector3& dir, const double t)
//{
//	for(int i = 0; i < 3; i++)
//   {
//		result[i] = pos[i]+t*dir[i];
//	}
//}

//double squaredLength(const Vector3 vec) {
//	int i;
//	double tmp = 0.0;
//	for(i = 0; i < 3; i++) {
//		tmp += vec[i]*vec[i];
//	}
//	return tmp;
//}

//void normalize(Vector3 vec)
//{
//	int i;
//	const double len = (double)(1.0/sqrt(squaredLength(vec)));
//	for(i = 0; i < 3; i++) {
//		vec[i] *= len;
//	}
//}

//void copyVector3(Vector3& result, const Vector3& input)
//{
//	result[0] = input[0];
//	result[1] = input[1];
//	result[2] = input[2];
//}

//void copyNormalize(Vector3& vec, const Vector3& input)
//{
//	copyVector3(vec,input),
//	normalize(vec);
//}

/*	| a1 a2 |
	| b1 b2 | calculate the determinent of a 2x2 matrix*/
//double det2x2( const double a1, const double a2,
//			      const double b1, const double b2)
//{
//	return a1*b2 - b1*a2;
//}
//
//	| a1 a2 a3 |
//	| b1 b2 b3 |
//	| c1 c2 c3 | calculate the determinent of a 3x3 matrix
//double det3x3(const double a1, const double a2, const double a3,
//   			  const double b1, const double b2, const double b3,
//  	   		  const double c1, const double c2, const double c3)
//{
//	return a1*det2x2(b2,b3,c2,c3)
//        - b1*det2x2(a2,a3,c2,c3)
//        + c1*det2x2(a2,a3,b2,b3);
//}


short ShortRand(void){
	short r;		static short ncalls=0;		short callThreshold=100;
	if(ncalls>=callThreshold)	{	srand(time(NULL));ncalls=0;	}
	else						++ncalls;
	r=rand()%0x8000;
	//std::cout<<r<<" "<<inited<<"\r\n";
	return(r);
	}

short RandSign(void)	{	return((ShortRand()%2==0)?1:-1);	}

float frand(){
	float fr=(float)(ShortRand())/0x8000l;
	//std::cout<<fr<<"\r\n";
	return(fr);
	}
float frandCenter(float c,float distFrom)	{
	distFrom=abs(distFrom);
	return(frand()*distFrom*2+c-distFrom);
	}
float SignedFloatRand(){	return(RandSign()*frand());	}
float ScaledRand(float scale){			return(frand()*scale);		}
float SignedScaledRand(float span){			return(frand()*span-(span/2));		}
float nzsign(float n){	return(n>=0?1:-1);	}

// Gaussian Weight Function by Parkitect
// CalcGaussian Weight()
//		in: x offset from origin, y offset from origin, radius, standard deviation of dataset
float CalcGaussianWeight(float xo,float yo,float radius,float dev){
	float expNume=sqrt(pow(xo,2)+pow(yo,2));
	float expDenom=2*pow(dev,2);//
	float denom=sqrt(expDenom*PI);
	float gw=exp(-expNume/expDenom)/denom;
	return(gw);
	}
// ! Gaussian Weight Function by Parkitect


// ! rand, sign, and range functions by Parkitect

//	logarithmic function by Parkitect

float ln(float v){	return(log(v));	}
float logb(float base,float v){	return(log(v)/log(base));	}


//	!	logarithmic function by Parkitect
