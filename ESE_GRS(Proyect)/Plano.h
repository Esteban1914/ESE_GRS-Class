#pragma once
#include "CRD.h"
#include <math.h>
#include "Sistema_Cartesiano.h"
class Plano:public Sistema_Cartesiano
{
public:
	char*name;
	CRD*Punto1;
	CRD*PuntosCrearPlano;
	double A,B,C,D;//Secuencia Ax+By+Cz+D=0
	bool RestringirAlPlano,pintarPlano;
	Plano(char*name){
		pintarPlano=true;
	 this->name=new char[strlen(name)+1];
		this->name[strlen(name)]=0;
		for(unsigned i=0;i<strlen(name);i++)
			this->name[i]=name[i];
	  Punto1=new CRD;
	  PuntosCrearPlano=new CRD[4];
	  RestringirAlPlano=false;
	};
	Plano(char*name,CRD Punt1,CRD Punt2,CRD Punt3,bool restring=false){
		pintarPlano=true;
		PuntosCrearPlano=new CRD[4];
		CRD vectorA,vectorB,vectorProyect,vectorC,vectorD;
		CRD pnt4,puntofinal;
		vectorD=Punt2-Punt1;
		//PuntosCrearPlano[0]=Punt1;
		PuntosCrearPlano[1]=Punt2+vectorD;
		vectorD=Punt3-Punt2;
		PuntosCrearPlano[2]=Punt3+vectorD;
		vectorA=Punt3-Punt1;
        vectorB=Punt2-Punt1;
		double a_punt_b=vectorA.x*vectorB.x+vectorA.y*vectorB.y+vectorA.z*vectorB.z;
		double long_a=sqrt(pow(vectorA.x,2)+pow(vectorA.y,2)+pow(vectorA.z,2));
		vectorProyect=vectorA*(a_punt_b/pow(long_a,2));
		pnt4=Punt1+vectorProyect;
		vectorC=pnt4-Punt2;
		vectorC=vectorC*2;
		puntofinal=Punt2+vectorC;
		vectorD=puntofinal-Punt3;
		PuntosCrearPlano[3]=puntofinal+vectorD;
		vectorD= Punt1-puntofinal;
		PuntosCrearPlano[0]=Punt1+vectorD;
		
		
		this->name=new char[strlen(name)+1];
		this->name[strlen(name)]=0;
		for(unsigned i=0;i<strlen(name);i++)
			this->name[i]=name[i];
		RestringirAlPlano=restring;
	Punto1=new CRD(Punt1);
	CRD v1,v2;
	double d1,d2,d3,d4,d5,d6;
	v1.x=Punt1.x-Punt2.x;
	v1.y=Punt1.y-Punt2.y;
	v1.z=Punt1.z-Punt2.z;
	v2.x=Punt1.x-Punt3.x;
	v2.y=Punt1.y-Punt3.y;
	v2.z=Punt1.z-Punt3.z;
	d1=v1.y*v2.z;
	d2=v1.z*v2.y;
	d3=v1.x*v2.z;
	d4=v1.z*v2.x;
	d5=v1.x*v2.y;
	d6=v1.y*v2.x;
	this->A=d1-d2;
	this->B=-(d3-d4);
	this->C=d5-d6;
	this->D=-(A*Punto1->x+B*Punto1->y+C*Punto1->z);
	if(A<0)
	{
	A*=-1;
	B*=-1;
	C*=-1;
	D*=-1;
	}
};
	~Plano(void){
		delete Punto1;
	};
	static CRD Distncia(CRD punt,Plano*p){
	CRD puntPlano,V;
	double A=p->A,B=p->B,C=p->C,D=p->D;
	double t=(-D-A*punt.x-B*punt.y-C*punt.z)/(A*A+B*B+C*C);//calculo el parametro t como la inteseccion de la recta creada por le punot y la normal del plano y el plano
	puntPlano.x=punt.x+A*t;//calculo la coordenada x el punto de interseccion entre la recta y el plano
	puntPlano.y=punt.y+B*t;//calculo la coordenada y el punto de interseccion entre la recta y el plano
	puntPlano.z=punt.z+C*t;//calculo la coordenada z el punto de interseccion entre la recta y el plano
	//hallo el vector 
	V.x=puntPlano.x-punt.x;
	V.y=puntPlano.y-punt.y;
	V.z=puntPlano.z-punt.z;
	//calculo la norma	
	double norma=sqrt(V.x*V.x+V.y*V.y+V.z*V.z);
	return V;

};
	static double DistnciaReal(CRD punt,Plano*p){
    double denomin=sqrt((p->A*p->A)+(p->B*p->B)+(p->C*p->C));
	double real=(p->A*punt.x+p->B*punt.y+p->C*punt.z+p->D)/denomin;
	return real;
};
	static CRD CoordRestringida(CRD coord,Plano*p)
	{
		CRD a(coord),b(Distncia(coord,p));
		a.x+=b.x;
		a.y+=b.y;
		a.z+=b.z;
		return a;
	}
	static void add(CRD vertex,Plano*p){
		if(p->RestringirAlPlano)
			Sistema_Cartesiano::add(CoordRestringida(vertex,p),p);
		else
		   Sistema_Cartesiano::add(vertex,p);
	};
	static void Draw(CRD*cooRd,Plano*p,bool pintarPlano=false,bool proyectpunt=false){
		if(p->RestringirAlPlano&&pintarPlano&&p->pintarPlano)
		{

		glColor3f((GLfloat)0.5,(GLfloat)0.5,(GLfloat)0.5);
		glBegin(GL_POLYGON);
		for(unsigned i=0;i<4;i++)
		  glVertex3f((GLfloat)p->PuntosCrearPlano[i].x,(GLfloat)p->PuntosCrearPlano[i].y,(GLfloat)p->PuntosCrearPlano[i].z);
		//glVertex3f((GLfloat)p->PuntosCrearPlano[0].x,(GLfloat)p->PuntosCrearPlano[0].y,(GLfloat)p->PuntosCrearPlano[0].z);
		glVertex3f((GLfloat)p->PuntosCrearPlano[1].x,(GLfloat)p->PuntosCrearPlano[1].y,(GLfloat)p->PuntosCrearPlano[1].z);
		//glVertex3f((GLfloat)p->PuntosCrearPlano[2].x,(GLfloat)p->PuntosCrearPlano[2].y,(GLfloat)p->PuntosCrearPlano[2].z);
		glEnd();
		}
		Sistema_Cartesiano::Draw(cooRd,p,p->RestringirAlPlano,p->RestringirAlPlano?&Plano::CoordRestringida(*cooRd,p):new CRD(0,0,0),proyectpunt);
	}
	static char*EcucaionPlano(Plano*p){
		string s;
		char*a;
		s=to_string(p->A)+"A"+(p->B>0?"+":"")+to_string(p->B)+"B"+(p->C>0?"+":"")+to_string(p->C)+"D";
		a=new char[s.length()+1];
		a[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			a[i]=s[i];
		return a;
	};
};

