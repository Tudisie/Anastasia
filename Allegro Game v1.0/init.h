#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>
#include "color.h"

#define Max(a,b) (a > b ? a : b)
#define Min(a,b) (a < b ? a : b)
#define ScreenWidth 1280
#define ScreenHeight 720
#define FPS 60

#include "images.h"
#include "map.h"

ALLEGRO_FONT *fontB26,*font1,*font2,*font1B,*fontB36,*fontdead;

ALLEGRO_SAMPLE *coins,*emptys,*jumps,*jumps2,*knifes,*mikes,*runs,*runs2,*shoots,*shops,*slides,*bird;
ALLEGRO_SAMPLE *deads,*pain1,*pain2,*pain3,*dog,*turn,*rains,*monsters;
ALLEGRO_SAMPLE *beginsong,*closer,*music,*fights;

bool fightsound = false;

bool fullscreen = false;
bool cheatgodmode = false;

const int LEVELS = 18;

ALLEGRO_SAMPLE_ID idbegin,idfight;

bool jumpsound = 0; // 0 - jumps, 1 - jumps2

struct coord{
    float x,y;
}level_end[100],anastasia_begin[100],creative_begin[4],last_death[4];

coord addcoin[30];
int cn; //if you get the coins on a level, they will not disappear forever!

float knife,gun; //atack
short RGB_A[100],RGB_B[100],RGB_C[100];
short sky[100];
bool rainyy[100];

bool language = 0; // 0- English, 1 - Romanian
bool creative = false; //creative mode. It would work only if it's activated everytime you are entering the game.
int Vmusic = 100,Veffects = 100;
int Difficulty = 2; // 1 - Easy, 2 - Medium, 3 - Hard, 4 - Insane
bool godmode = false; // full hp  whatever happens

int Level = 1;
ALLEGRO_COLOR LevelColor;

ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_DISPLAY *display;

enum states{idle = 1,run = 21,jump = 29,melee = 39,shoot = 46,slide = 49,dead = 11};

const float jumpSpeed = 10;
float gravity = 0.25;

float shiftedMoveSpeed = 4.5,nonshiftedMoveSpeed = 2.5;
float shiftedIncreaseBM = 0.2,nonshiftedIncreaseBM = 0.13;
float moveSpeed;
float increaseBM;

const float bulletSpeed = 5;
const float bulletTime = 100;

int X1,Y1,X2,Y2; // we have a box collision with 2 situations : the image is normal and flipped.

int HB;

inline float abs(float x)
{
    return (x > 0 ? x : -x);
}

inline void swap(int &A,int &B)
{
    int aux = A;
    A = B;
    B = aux;
}

void Loading_Screen()
{
    al_clear_to_color(BLACK);
    ALLEGRO_FONT *font = al_load_font("fonts\\Incognitype.ttf",42,NULL);
    al_draw_text(font,RED,ScreenWidth/2,ScreenHeight/2,ALLEGRO_ALIGN_CENTRE,"Loading...");

    al_flip_display();
    al_destroy_font(font);
}

void info()
{
    std::ifstream fin("positions.txt");

    for(int i=0; i<=100; ++i)
        fin>>anastasia_begin[i].x>>anastasia_begin[i].y>>level_end[i].x>>level_end[i].y,
        fin>>sky[i]>>rainyy[i]>>RGB_A[i]>>RGB_B[i]>>RGB_C[i];
    fin.close();
}

void init()
{
    al_init();
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(ScreenWidth,ScreenHeight);
    al_set_window_title(display,"Anastasia");

    al_install_audio();
    al_init_acodec_addon();

    al_init_font_addon();
    al_init_ttf_addon();

    Loading_Screen();

    al_init_image_addon();
    al_init_primitives_addon();

    load_images();

    al_set_display_icon(display,icon);

    event_queue = al_create_event_queue();

    al_install_mouse();
    al_register_event_source(event_queue,al_get_mouse_event_source());

    al_hide_mouse_cursor(display);

    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    fontB26 = al_load_font("fonts/Bohemian.ttf",26,NULL);
    fontB36 = al_load_font("fonts/Bohemian.ttf",36,NULL);
    font1 = al_load_font("fonts\\Bohemian.ttf",64,NULL);
    font2 = al_load_font("fonts\\Incognitype.ttf",128,NULL);
    font1B = al_load_font("fonts\\Bohemian.ttf",66,NULL); //for "outline"
    fontdead = al_load_font("fonts//Incognitype.ttf",98,NULL);

    HB = al_get_font_line_height(fontB26);

    coins = al_load_sample("Audio//coin.wav");
    emptys = al_load_sample("Audio//empty.wav");
    jumps = al_load_sample("Audio//jump.wav");
    jumps2 = al_load_sample("Audio//jump2.wav");
    knifes = al_load_sample("Audio//knife.wav");
    mikes = al_load_sample("Audio//mike.wav");
    runs = al_load_sample("Audio//run.wav");
    shoots = al_load_sample("Audio//shoot.wav");
    shops = al_load_sample("Audio//shop.wav");
    slides = al_load_sample("Audio//slide.wav");
    bird = al_load_sample("Audio//bird.wav");
    deads = al_load_sample("Audio//dead.wav");
    pain1 = al_load_sample("Audio//pain1.wav");
    pain2 = al_load_sample("Audio//pain2.wav");
    pain3 = al_load_sample("Audio//pain3.wav");
    dog = al_load_sample("Audio//dog.wav");
    turn = al_load_sample("Audio//turn.wav");
    rains = al_load_sample("Audio//rain.ogg");
    monsters = al_load_sample("Audio//monster.ogg");

    beginsong = al_load_sample("Audio//begin.ogg");
    closer = al_load_sample("Audio//Closer.ogg");
    music = al_load_sample("Audio//Music.ogg");

    al_reserve_samples(12);

    X1 = 85;
    Y1 = 60;
    X2 = Anastasia.w - 85;
    Y2 = Anastasia.h - 1;

    godmode = false;
    gravity = 0.25;
    info();
}

#endif // INIT_H_INCLUDED
