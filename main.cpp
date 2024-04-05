#include <iostream>
#include <Grapic.h>

using namespace std;
using namespace grapic;

const int DIMW=500;
const float FRICTION =0.6f;
const int MAX =50;

/*Mon mini-projet est de réaliser le jeu Fruit-Ninja
Fruit Ninja est un jeu ou des fruits sont lancés et ou le joueur doit les couper pour augmenter son score
Si un fruit tombe mais n'est pas coupé, le joueur perd une vie
Au bout de 3 vies il a perdu.*/


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
    //printVec(A);
    A.x+=B.x;
    A.y+=B.y;
    //printVec(A);
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
    Image im;
};
void fruitInit(Fruit &f)
{
    f.p.x=frand(100,DIMW-100);
    f.p.y=frand(0,100);
    f.v.x=frand(-30.F,10.F);
    f.v.y=frand(50.F,100.F);
    f.m=1.0;
    f.im=image("data/fruitninja/pomme.png");
}
void fruitAddForce(Fruit &f,Vec2 force)
{
    f.f+=force;
}
void fruitUpdatePV(Fruit &f)
{
    float dt=0.001;
    f.f.x=0;
    f.f.y=0;
    Vec2 g=make_vec(0,-9.81*f.m);
    fruitAddForce(f,g);
    f.v+=dt*(1/f.m)*f.f;
    f.p+=dt*f.v;
}
void drawFruit(Fruit f)
{
    image_draw(f.im,f.p.x,f.p.y,-1,-1);
}
Fruit copyFruit(Fruit f)
{
    Fruit r;
    r.p=f.p;
    r.v=f.v;
    r.f=f.f;
    r.m=f.m;
    r.im=f.im;

}
//World

struct World
{
    Fruit liste_fruits[MAX];
    int score;
    int vies;
    int nb_fruits;
};
void worldInit(World &w)
{

    w.score=0;
    w.vies=3;
    w.nb_fruits=1;
    Image imf1 = image("data/fruitninja/pomme.png");
    Image tab_image[w.nb_fruits] = {imf1};
    for (int i=0;i<w.nb_fruits;i++)
    {
        cout<<"oui"<<endl;
        Fruit f;
        fruitInit(f);
        f.im=tab_image[i];
        w.liste_fruits[i]=f;
    }
}
void drawWorld(World w)
{
    fontSize(24);
    color(255,255,100);
    print(50,450,w.score);
    color(255,0,0);
    print(450,450,w.vies);
}
int main(int , char**)
{
    Image imf1 = image("data/fruitninja/pomme.png");
    Image tab_image[w.nb_fruits] = {imf1};
	winInit("vide",DIMW,DIMW);
	backgroundColor(95,42,4);
	World w;
	worldInit(w);
	Fruit f;
	fruitInit(f);
	Vec2 force = make_vec(0,5);
	fruitAddForce(f,force);
	bool stop = false;
	while( !stop )
	{
		winClear();
		drawWorld(w);
		drawFruit(f);
		fruitUpdatePV(f);
		stop = winDisplay();
	}
	winQuit();
	return 0;
}
