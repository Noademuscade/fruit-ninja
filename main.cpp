#include <iostream>
#include <Grapic.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace grapic;

const int DIMW=500;
const float FRICTION =0.6f;
const int MAX =150;
const int NFP = 6;

/*Mon mini-projet est de réaliser le jeu Fruit-Ninja
Fruit Ninja est un jeu ou des fruits sont lancés et ou le joueur doit les couper pour augmenter son score
Si un fruit tombe mais n'est pas coupé, le joueur perd une vie
Au bout de 3 vies il a perdu.

COMPTE-RENDU 12/04
J'ai implanté quasiment toutes les fonctions principales nécessaires au fonctionnement du jeu
Le jeu s'affiche , a un menu et on peux jouer (quelques détails à paufiner sur les trajectoires des fruits et leur vitesse)
La semaine prochaine, je compte finaliser toutes les fonctions principales et entamer l'ajout de mécanique en plus comme une difficulté crescendo et de nouveaux fruits spéciaux etc
Je vous mets ci-joint un lien Github pour accéder au zip avec les images nécessaires (je n'utilise pas souvent github mais j'ai essayé pour prendre l'habitude)
https://github.com/Noademuscade/fruit-ninja*/
char fruits_possibles[NFP]={'p','b','c','f','a','x'};

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
bool operator==(Vec2 a,Vec2 b)
{
    if((a.x==b.x)&&(a.y==b.y))
    {
        return true;
    }
    return false;
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
    int etat;//0 fruit entier 1 fruit coupé gauche 2 fruit coupé droit 3 fruit supprimé / plus traité #### si fruit = bombe : 0 entier 1 explosé
};
void fruitInit(Fruit &f)
{
    f.p.x=frand(100,DIMW-100);
    f.p.y=frand(-50,0);
    f.v.x=frand(-20.F,20.F);
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
    float dt=0.2;
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
        else if (f.etat == 2)
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
        else if (f.etat == 2)
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
        else if (f.etat == 2)
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
        else if (f.etat == 2)
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
        else if (f.etat == 2)
        {
            im = image("data/fruitninja/ananas3.png");
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id =='x')
    {
        if (f.etat==0)
        {
            im=image("data/fruitninja/bomb1.png");
        }
        else
        {
            im=image("data/fruitninja/bomb2.png");
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
void cutFruitInWorld(World &w,Fruit &fg)
{
    if (fg.etat==0 && fg.id != 'x')
    {
        Fruit fd=copyFruit(fg);
        fg.etat=1;
        fd.etat=2;
        fg.v.x=-10;
        fg.v.y=10;
        fd.p.x=fg.p.x+50;
        fd.v.x=10;
        fd.v.y=10;
        fg.m=1.5;
        fd.m=1.5;
        Vec2 chg = make_vec(-50,30);
        Vec2 chd = make_vec(50,30);
        fruitAddForce(fg,chg);
        fruitAddForce(fd,chd);
        addFruitToWorld(w,fd);
    }
}
bool fruitWaveDone(World w)
{
    for (int i =0;i<w.nb_fruits;i++)
    {
        if (w.liste_fruits[i].etat !=3)
        {
            return false;
        }
    }
    return true;
}
void createFruitWave(World &w)
{
    int waveSize=(rand()%6)-1;
    for(int i = 0;i<waveSize;i++)
    {
        Fruit f;
        fruitInit(f);
        addFruitToWorld(w,f);
    }
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
        if (w.liste_fruits[i].etat!=3)
        {
            drawFruit(w.liste_fruits[i]);
        }
    }
}
void updateWorld(World &w)
{
    if (w.vies >0)
    {
        int mx,my;
        for (int i=0;i<w.nb_fruits;i++)
        {
            if (w.liste_fruits[i].etat != 3)
            {
                mousePos(mx,my);
                fruitUpdatePV(w.liste_fruits[i]);
                if ((w.liste_fruits[i].p.x>=mx-60) && (w.liste_fruits[i].p.x<=mx+60) &&(w.liste_fruits[i].p.y>=my-60)&&(w.liste_fruits[i].p.y<=my+60) && (w.liste_fruits[i].etat==0))
                {
                    if (w.liste_fruits[i].id!='x')
                    {
                        cutFruitInWorld(w,w.liste_fruits[i]);
                        w.score++;
                    }
                    else
                    {
                        w.liste_fruits[i].etat=1;
                        drawWorld(w);
                        w.vies =0;
                    }

                }
                if(w.liste_fruits[i].etat==0 && w.liste_fruits[i].p.y<-50 && w.liste_fruits[i].id !='x')
                {
                    w.liste_fruits[i].etat=3;
                    w.vies--;
                }
                if((w.liste_fruits[i].etat!=0 || w.liste_fruits[i].id == 'x') && w.liste_fruits[i].p.y<-50)
                {
                    w.liste_fruits[i].etat=3;
                }
            }
        }
    }

    //doit supprimer un fruit si celui-ci sort de la fenêtre
    //Si il est coupé le score augmente sinon il perd une vie
}
void endWorld(World &w)
{
    fontSize(60);
    color(255,0,0);
    print(150,300,"PERDU");
    rectangleFill(150,150,350,100);
    color(255,211,0);
    rectangleFill(150,250,350,200);
    color(0,0,0);
    fontSize(24);
    print(200,212,"REJOUER");
    print(200,112,"QUITTER");
    int mx,my;
    mousePos(mx,my);
    if (isMousePressed(SDL_BUTTON_LEFT) && mx<=350 && mx>=150 && my<=150 && my>=100 )
    {
        winQuit();
    }
    if (isMousePressed(SDL_BUTTON_LEFT) && mx<=350 && mx>=150 && my<=250 && my>=200 )
    {
        initWorld(w);
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
		if(fruitWaveDone(w)&& w.vies > 0)
        {
            createFruitWave(w);
        }
        if(w.vies <= 0)
        {
            endWorld(w);
        }

		stop = winDisplay();
	}
	winQuit();
	return 0;
}
