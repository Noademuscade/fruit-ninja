#include <iostream>
#include <Grapic.h>

using namespace std;
using namespace grapic;

const int DIMW=500;
const float FRICTION =0.6f;
const int MAX =150;
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
    Image im;
    if (f.id == 'p')
    {
        if (f.etat==0)
        {
            im = image("data/fruitninja/pomme1.png");
        }
        else if (f.etat == 1)
        {
            im = image("data/fruitninja/pomme2.png");
        }
        else
        {
            im = image("data/fruitninja/pomme3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'b')
    {
        if (f.etat==0)
        {
            im = image("data/fruitninja/banane1.png");
        }
        else if (f.etat == 1)
        {
            im = image("data/fruitninja/banane2.png");
        }
        else
        {
            im = image("data/fruitninja/banane3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'f')
    {
        if (f.etat==0)
        {
            im = image("data/fruitninja/fraise1.png");
        }
        else if (f.etat == 1)
        {
            im = image("data/fruitninja/fraise2.png");
        }
        else
        {
            im = image("data/fruitninja/fraise3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'c')
    {
        if (f.etat==0)
        {
            im = image("data/fruitninja/coco1.png");
        }
        else if (f.etat == 1)
        {
            im = image("data/fruitninja/coco2.png");
        }
        else
        {
            im = image("data/fruitninja/coco3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'a')
    {
        if (f.etat==0)
        {
            im = image("data/fruitninja/ananas1.png");
        }
        else if (f.etat == 1)
        {
            im = image("data/fruitninja/ananas2.png");
        }
        else
        {
            im = image("data/fruitninja/ananas3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
}
Fruit copyFruit(Fruit f)
{
    Fruit r;
    r.p.x=f.p.x;
    r.p.y=f.p.y;
    r.v.x=f.v.x;
    r.v.y=f.v.y;
    r.m=f.m;
    r.id=f.id;
    r.etat=f.etat;
    return r;
}

void cutFruit(Fruit &fg)
{
    Fruit fd=copyFruit(fg);
    fg.etat=1;
    fd.etat=2;
    fg.v.x=-10;
    fg.v.y=5;
    fd.v.x=-10;
    fd.v.y=5;
    Vec2 chute = make_vec(-50,10);
    fruitAddForce(fg,chute);
    fruitAddForce(fd,chute);
    // a compléter apr world fini
}
//Jeu

struct World
{
    Fruit liste_fruits[MAX];
    int score;
    int vies;
    int nb_fruits;
};
void addFruitToWorld(World &w,Fruit f)
{
    w.liste_fruits[w.nb_fruits]=f;
    w.nb_fruits++;
}
void initWorld(World &w)
{
    w.score=0;
    w.vies=3;
    w.nb_fruits=(rand()%5)+1;
    for (int i=0;i<w.nb_fruits;i++)
    {
        Fruit f;
        fruitInit(f);
        w.liste_fruits[i]=f;
    }
}
void updateWorld(World &w)
{
    for (int i=0;i<w.nb_fruits;i++)
    {
        fruitUpdatePV(w.liste_fruits[i]);
    }
    //doit supprimer un fruit si celui-ci sort de la fenêtre
    //Si il est coupé le score augmente sinon il perd une vie
}

void drawWorld(World w)
{
    int mx,my;
    mousePos(mx,my);
    color(255,255,255);
    circleFill(mx,my,5);
    fontSize(24);
    color(255,211,0);
    print(DIMW-30,DIMW-30,w.score);
    color(255,0,0);
    print(20,DIMW-30,w.vies);
    for (int i =0 ;i<w.nb_fruits;i++)
    {
        drawFruit(w.liste_fruits[i]);
    }
}
int main(int , char**)
{
	winInit("vide",DIMW,DIMW);
	backgroundColor(95,42,4);
	World w;
	initWorld(w);
	bool stop = false;
	while( !stop )
	{
		winClear();
		drawWorld(w);
		updateWorld(w);
		stop = winDisplay();
	}
	winQuit();
	return 0;
}
