#include <iostream>
#include <Grapic.h>

using namespace std;
using namespace grapic;

const int DIMW=500;
const float FRICTION =0.6f;
const int MAX =50;
const int NFP = 5;

/*Mon mini-projet est de réaliser le jeu Fruit-Ninja
Fruit Ninja est un jeu ou des fruits sont lancés et ou le joueur doit les couper pour augmenter son score
Si un fruit tombe mais n'est pas coupé, le joueur perd une vie
Au bout de 3 vies il a perdu.*/
char fruits_possibles[NFP]={'p','b','c','f','a'};

//Vecteur
struct Vec2
{
    float x,y;
};
void printVec(Vec2 v)
{
 cout << " X " << v.x << " Y " << v.y << endl;
}
Vec2 operator+(Vec2 A,Vec2 B)
{
    Vec2 r;
    r.x=A.x+B.x;
    r.y=A.y+B.y;
    return r;
}
Vec2 operator+=(Vec2& A,Vec2 B)
{
    A.x+=B.x;
    A.y+=B.y;
    return A;
}
Vec2 operator*(float a,Vec2 B)
{
    Vec2 r;
    r.x=a*B.x;
    r.y=a*B.y;
    return r;
}
Vec2 make_vec(float x,float y)
{
    Vec2 r;
    r.x=x;
    r.y=y;
    return r;
}

float norm(Vec2 a)
{
    return sqrt(a.x*a.x+a.y*a.y);
}
//Fruit
struct Fruit
{
    Vec2 p;
    Vec2 v;
    Vec2 f;
    float m;
    char id;
    int etat;//0 fruit entier 1 fruit coupé gauche 2 fruit coupé droit
};
void fruitInit(Fruit &f)
{
    f.p.x=frand(100,DIMW-100);
    f.p.y=frand(-50,0);
    f.v.x=frand(-30.F,30.F);
    f.v.y=frand(50.F,100.F);
    f.m=1.0;
    f.id=fruits_possibles[rand()%NFP];
    f.etat=0;
}
void fruitAddForce(Fruit &f,Vec2 force)
{
    f.f+=force;
}
void fruitUpdatePV(Fruit &f)
{
    float dt=0.1;
    f.f.x=0;
    f.f.y=0;
    Vec2 g=make_vec(0,-9.81*f.m);
    fruitAddForce(f,g);
    f.v+=dt*(1/f.m)*f.f;
    f.p+=dt*f.v;
}
void drawFruit(Fruit f)
{
    if (f.id == 'p')
    {
        if (f.etat==0)
        {
            Image im = image("data/fruitninja/pomme1.png");
        }
        else if (f.etat == 1)
        {
            Image im = image("data/fruitninja/pomme2.png");
        }
        else
        {
            Image im = image("data/fruitninja/pomme3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'b')
    {
        if (f.etat==0)
        {
            Image im = image("data/fruitninja/banane1.png");
        }
        else if (f.etat == 1)
        {
            Image im = image("data/fruitninja/banane2.png");
        }
        else
        {
            Image im = image("data/fruitninja/banane3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'f')
    {
        if (f.etat==0)
        {
            Image im = image("data/fruitninja/fraise1.png");
        }
        else if (f.etat == 1)
        {
            Image im = image("data/fruitninja/fraise2.png");
        }
        else
        {
            Image im = image("data/fruitninja/fraise3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'c')
    {
        if (f.etat==0)
        {
            Image im = image("data/fruitninja/coco1.png");
        }
        else if (f.etat == 1)
        {
            Image im = image("data/fruitninja/coco2.png");
        }
        else
        {
            Image im = image("data/fruitninja/coco3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'a')
    {
        if (f.etat==0)
        {
            Image im = image("data/fruitninja/ananas1.png");
        }
        else if (f.etat == 1)
        {
            Image im = image("data/fruitninja/ananas2.png");
        }
        else
        {
            Image im = image("data/fruitninja/ananas3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
}
//World

struct Jeu
{
    Fruit liste_fruits[MAX];
    int score;
    int vies;
    int nb_fruits;
};

int main(int , char**)
{
	winInit("vide",DIMW,DIMW);
	backgroundColor(95,42,4);
	Fruit f;
	fruitInit(f);
	Vec2 force = make_vec(0,5);
	fruitAddForce(f,force);
	bool stop = false;
	while( !stop )
	{
		winClear();
		drawFruit(f);
		fruitUpdatePV(f);
		stop = winDisplay();
	}
	winQuit();
	return 0;
}
