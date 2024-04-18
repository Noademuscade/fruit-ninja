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
const int NFP = 8;


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


// idée fruit bonus/malus : un fruit qui quand on le coupe se transforme en 5 fruits qui "explose" / un fruit qui change la gravité (gravité lunaire)

char fruits_possibles[NFP]={'p','b','c','f','a','x','g','l'};

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
const Vec2 G = make_vec(0,-9.81);
float norm(Vec2 a)
{
    return sqrt(a.x*a.x+a.y*a.y);
}

void importImages(Image tab[MAX])
{
    Image p1;
    p1 = image("data/fruitninja/pomme1.png");
    Image p2;
    p2 = image("data/fruitninja/pomme2.png");
    Image p3;
    p3 = image("data/fruitninja/pomme3.png");
    Image b1;
    b1 = image("data/fruitninja/banane1.png");
    Image b2;
    b2 = image("data/fruitninja/banane2.png");
    Image b3;
    b3 = image("data/fruitninja/banane3.png");
    Image f1;
    f1 = image("data/fruitninja/fraise1.png");
    Image f2;
    f2 = image("data/fruitninja/fraise2.png");
    Image f3;
    f3 = image("data/fruitninja/fraise3.png");
    Image c1;
    c1 = image("data/fruitninja/coco1.png");
    Image c2;
    c2 = image("data/fruitninja/coco2.png");
    Image c3;
    c3 = image("data/fruitninja/coco3.png");
    Image a1;
    a1 = image("data/fruitninja/ananas1.png");
    Image a2;
    a2 = image("data/fruitninja/ananas2.png");
    Image a3;
    a3 = image("data/fruitninja/ananas3.png");
    Image x1;
    x1 = image("data/fruitninja/bomb1.png");
    Image x2;
    x2 = image("data/fruitninja/bomb2.png");
    Image g1;
    g1 = image("data/fruitninja/grenade1.png");
    Image g2;
    g2 = image("data/fruitninja/grenade2.png");
    Image g3;
    g3 = image("data/fruitninja/grenade3.png");
    Image l1;
    l1 = image("data/fruitninja/fruitlune1.png");
    Image l2;
    l2 = image("data/fruitninja/fruitlune2.png");
    Image l3;
    l3 = image("data/fruitninja/fruitlune3.png");
    tab[0] = p1;
    tab[1] = p2;
    tab[2] = p3;
    tab[3] = b1;
    tab[4] = b2;
    tab[5] = b3;
    tab[6] = f1;
    tab[7] = f2;
    tab[8] = f3;
    tab[9] = c1;
    tab[10] = c2;
    tab[11] = c3;
    tab[12] = a1;
    tab[13] = a2;
    tab[14] = a3;
    tab[15] = x1;
    tab[16] = x2;
    tab[17] = g1;
    tab[18] = g2;
    tab[19] = g3;
    tab[20] = l1;
    tab[21] = l2;
    tab[22] = l3;
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
    f.v.y=frand(70.F,80.F);
    f.m=1.0;
    f.id=fruits_possibles[rand()%NFP];
    f.etat=0;
}
void fruitInitEx(Fruit &f,Fruit g)
{
    f.p.x=g.p.x;
    f.p.y=g.p.y;
    f.v.x=frand(-50.F,50.F);
    f.v.y=frand(20.F,30.F);
    f.m=1.0;
    f.id=fruits_possibles[rand()%(NFP-3)];
    f.etat=0;
}
void fruitAddForce(Fruit &f,Vec2 force)
{
    f.f+=force;
}
void fruitUpdatePV(Fruit &f,Vec2 g)
{
    float dt=0.01;
    f.f.x=0;
    f.f.y=0;
    fruitAddForce(f,g);
    f.v+=dt*(1/f.m)*f.f;
    f.p+=dt*f.v;
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
    Image tab_images[MAX];
    int score;
    int vies;
    int nb_fruits;
    bool inGame;
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
        fd.p.x=fg.p.x+60;
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
void drawFruitInWorld(World w,Fruit f)
{
    Image im;
    if (f.id == 'p')
    {
        if (f.etat==0)
        {
            im = w.tab_images[0];
        }
        else if (f.etat == 1)
        {
            im = w.tab_images[1];
        }
        else if (f.etat == 2)
        {
            im = w.tab_images[2];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'b')
    {
        if (f.etat==0)
        {
            im = w.tab_images[3];
        }
        else if (f.etat == 1)
        {
            im = w.tab_images[4];
        }
        else if (f.etat == 2)
        {
            im = w.tab_images[5];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'f')
    {
        if (f.etat==0)
        {
            im = w.tab_images[6];
        }
        else if (f.etat == 1)
        {
            im = w.tab_images[7];
        }
        else if (f.etat == 2)
        {
            im = w.tab_images[8];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'c')
    {
        if (f.etat==0)
        {
            im = w.tab_images[9];
        }
        else if (f.etat == 1)
        {
            im = w.tab_images[10];
        }
        else if (f.etat == 2)
        {
            im = w.tab_images[11];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'a')
    {
        if (f.etat==0)
        {
            im = w.tab_images[12];
        }
        else if (f.etat == 1)
        {
            im = w.tab_images[13];
        }
        else if (f.etat == 2)
        {
            im = w.tab_images[14];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id =='x')
    {
        if (f.etat==0)
        {
            im=w.tab_images[15];
        }
        else
        {
            im=w.tab_images[16];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'g')
    {
        if (f.etat==0)
        {
            im = w.tab_images[17];
        }
        else if (f.etat == 1)
        {
            im = w.tab_images[18];
        }
        else if (f.etat == 2)
        {
            im = w.tab_images[19];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
    }
    else if (f.id == 'l')
    {
        if (f.etat==0)
        {
            im = w.tab_images[20];
        }
        else if (f.etat == 1)
        {
            im = w.tab_images[21];
        }
        else if (f.etat == 2)
        {
            im = w.tab_images[22];
        }
        image_draw(im,f.p.x,f.p.y,-1,-1);
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
void explodeGrenadeInWorld(Fruit g,World &w)
{
    for(int i = 0;i<5;i++)
    {
        Fruit f;
        fruitInitEx(f,g);
        addFruitToWorld(w,f);
    }
}
void initWorld(World &w)
{
    importImages(w.tab_images);
    w.score=0;
    w.vies=3;
    w.nb_fruits=(rand()%5)+1;
    for (int i=0;i<w.nb_fruits;i++)
    {
        Fruit f;
        fruitInit(f);
        w.liste_fruits[i]=f;
    }
    w.inGame=false;
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
            drawFruitInWorld(w,w.liste_fruits[i]);
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
                fruitUpdatePV(w.liste_fruits[i],G);
                if ((w.liste_fruits[i].p.x>=mx-60) && (w.liste_fruits[i].p.x<=mx+60) &&(w.liste_fruits[i].p.y>=my-60)&&(w.liste_fruits[i].p.y<=my+60) && (w.liste_fruits[i].etat==0))
                {
                    /*if(w.liste_fruits[i].id=='g')
                    {
                        explodeGrenadeInWorld(w.liste_fruits[i],w);
                    }*/
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
                    if (w.liste_fruits[i].p.x>=0 && w.liste_fruits[i].p.x<=DIMW)
                    {
                        w.liste_fruits[i].etat=3;
                        w.vies--;
                    }
                    else
                    {
                        w.liste_fruits[i].etat=3;
                    }

                }
                if((w.liste_fruits[i].etat!=0 || w.liste_fruits[i].id == 'x') && w.liste_fruits[i].p.y<-50)
                {
                    w.liste_fruits[i].etat=3;
                }
            }
        }
    }
}
void startingMenu(World &w)
{
    fontSize(60);
    color(255,210,0);
    print(73,300,"FRUIT NINJA");
    fontSize(30);
    print(130,200,"Cliquez pour jouez");
    if (isMousePressed(SDL_BUTTON_LEFT))
    {
        w.inGame=true;
    }
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
        w.inGame=true;
    }
}
int main(int , char**)
{
	winInit("vide",DIMW,DIMW);
	backgroundColor(162,42,42);
	//Image background = image("data/fruitninja/bg.jpg");
	//image_draw(background,0,0,DIMW,DIMW);
	World w;
	initWorld(w);
	bool stop = false;
	while( !stop )
	{
	    winClear();
	    if(w.inGame)
        {

            drawWorld(w);
            updateWorld(w);
            if(fruitWaveDone(w)&& w.vies > 0)
            {
                createFruitWave(w);
            }
            if(w.vies <= 0)
            {
                winClear();
                endWorld(w);
            }
        }
        else
        {
            startingMenu(w);
        }
        stop = winDisplay();
	}
	winQuit();
	return 0;
}
