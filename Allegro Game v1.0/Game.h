#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <cstring>

#include "cameraeffects.h"
#include "Story.h"

bool isdead = false;
bool done, draw;
float endx,endy;
float prevhp,prevbullets,prevcoins;

float timepassed = 0; //for music first song - the others
float timerspeed;
bool closersong = false;
bool beginmusic = false;

ALLEGRO_SAMPLE_ID idcloser,idmusic,rainsound;

bool rainy;

ALLEGRO_TRANSFORM camera;

ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_EVENT events;

ALLEGRO_BITMAP *celest; //Moon or Sun

coord randomcoins[20];
char random[100]; // for level 18
int pozrand;
int nrandom;

void collision();
void Die();
void Drawing();
bool ExitQ();

#include "movement.h"

inline void DrawingCreature(MOVING_GIF &g)
{
    std::vector<posbm>::iterator it2;
    int flag;
    for(it2 = g.q.begin(); it2!= g.q.end(); ++it2)
    {
        it2->affected = Max(0,it2->affected - 1);
        if(it2->x >= Max(Anastasia.x + ScreenWidth/2,ScreenWidth)  + 100|| it2->y >= Anastasia.y + ScreenHeight/2 + 100||
           it2->x <= Min(Anastasia.x - ScreenWidth/2,MapWidth - ScreenWidth) - 100|| it2->y <= Anastasia.y - ScreenHeight/2 - 100) continue;
        if(it2->affected %20 <= 14)
        {
            if(it2->dir == 1) flag = NULL;
                else flag = ALLEGRO_FLIP_HORIZONTAL;
            al_draw_bitmap(g.bm[g.k],it2->x,it2->y - 3,flag);
        }
    }
}

inline void Drawing() //with flipping display
{
    timepassed += timerspeed;
    draw = false;

    if(Level <= LEVELS)
        al_draw_tinted_bitmap(Mountain.bm, al_map_rgba_f(1, 1, 1, 0.5),CameraX(0),CameraY(ScreenHeight - Mountain.h),NULL);

    if(celest != NULL)
        al_draw_bitmap(celest, CameraX(20), CameraY(20), NULL);

    if(rainy)
        gif(rain,CameraX(0),CameraY(0));

    DrawMap(Map);
    al_draw_bitmap(Spell.bm,endx - Spell.w/2,endy - Spell.h/2,NULL);
    DrawMap(BackMap);
    DrawMap(BackMap2);

    al_draw_textf(fontB26,DARKRED,CameraX(20),CameraY(20),ALLEGRO_ALIGN_CENTER,"%d",Level);

    if(Level == 0) //text for tutorial
    {
        al_draw_text(fontB26,DARKRED,438,715,ALLEGRO_ALIGN_CENTER,"Hold LEFT and RIGHT buttons to move");
        al_draw_text(fontB26,DARKRED,1109,825,ALLEGRO_ALIGN_CENTER,"Press UP or SPACE button to jump");
        al_draw_text(fontB26,DARKRED,2800,812,ALLEGRO_ALIGN_CENTER," Be careful of the spikes");
        al_draw_text(fontB26,DARKRED,3800,803,ALLEGRO_ALIGN_CENTER,"hold SHIFT to run, increasing your speed");
        al_draw_text(fontB26,DARKRED,5689,717,ALLEGRO_ALIGN_CENTER,"hold DOWN button to slide");
        al_draw_text(fontB26,DARKRED,6453,733,ALLEGRO_ALIGN_CENTER,"and more..");
        al_draw_text(fontB26,DARKRED,8746,769,ALLEGRO_ALIGN_CENTER,"Be careful at animals and monsters. They will hurt you");
        al_draw_text(fontB26,DARKRED,10922,988,ALLEGRO_ALIGN_CENTER,"You can buy bullets and HP from shop");
        al_draw_text(fontB26,DARKRED,10922,1020,ALLEGRO_ALIGN_CENTER,"pressing B button");
        al_draw_text(fontB26,DARKRED,11747,927,ALLEGRO_ALIGN_CENTER,"Hold X button to attack the monsters");
        al_draw_text(fontB26,DARKRED,12539,935,ALLEGRO_ALIGN_CENTER,"Press C to shoot");
    }

    //Anastasia
    int X = Anastasia.x,Y = Anastasia.y + 5;
    if((state == dead || state == shoot) && flag == ALLEGRO_FLIP_HORIZONTAL)
        X -= 38;
    if(affected % 20 <= 10)
        al_draw_bitmap(Anastasia.bm[int(BM)], X,Y, flag);

    DrawingCreature(mike);
    DrawingCreature(laica);
    DrawingCreature(ork);
    DrawingCreature(rabbit);
    DrawingCreature(flydragon);
    DrawingCreature(monster);

    std::vector<BULLET>::iterator it;
    for(it = Anastasia.q.begin(); it != Anastasia.q.end(); ++it)
    {
        int x = it->x;
        int y = it->y;
        int flag;
        if(it->dir == 1) flag = NULL;
            else flag = ALLEGRO_FLIP_HORIZONTAL;
        al_draw_bitmap(Anastasia.bul,x,y,flag);
    }

    DrawMap(FrontMap);


    //information box
    /*al_draw_filled_rectangle(CameraX(15), CameraY(ScreenHeight - 5*HB - 5),CameraX(205), CameraY(ScreenHeight - 5),BLACK);
    al_draw_filled_rectangle(CameraX(20), CameraY(ScreenHeight - 5*HB),CameraX(200), CameraY(ScreenHeight - 10),GREY);
    al_draw_filled_rectangle(CameraX(22), CameraY(ScreenHeight - 5*HB + 2),CameraX(198), CameraY(ScreenHeight - 12),BLACK);*/

    al_draw_bitmap(BoardR.bm, CameraX(8), CameraY(ScreenHeight - BoardR.h - 10), NULL);

    al_draw_textf(fontB26,DARKRED,CameraX(30),CameraY(ScreenHeight - 4*HB),ALLEGRO_ALIGN_LEFT,"HP : %.2f",Anastasia.hp);
    al_draw_textf(fontB26,DARKRED,CameraX(30),CameraY(ScreenHeight - 3*HB),ALLEGRO_ALIGN_LEFT,"Bullets : %d",Anastasia.bullets);
    al_draw_textf(fontB26,DARKRED,CameraX(30),CameraY(ScreenHeight - 2*HB),ALLEGRO_ALIGN_LEFT,"Coins : %d",Anastasia.coins);

    if(Anastasia.hp <= 20)
        al_draw_bitmap(Blood.bm,CameraX(135),CameraY(ScreenHeight - 160),NULL);

    if(Anastasia.hp <= 0) //if the game is done and you are still drawing, it's Game Over
        al_draw_text(fontdead,YELLOW,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2-50),ALLEGRO_ALIGN_CENTRE,"GAME OVER");

    if(creative)
        al_draw_bitmap(Cursor,CameraX(Mx),CameraY(My),NULL);
}

bool ExitQ()
{
    //Are you sure.You want to exit the game?
    al_stop_sample(&id);
    int pivot = 0,entertime = 0;
    int X1,X2,Y1,Y2,W,H;

    H = 200; W = 400;
    X1 = ScreenWidth/2- W/2 + 50;
    X2 = ScreenWidth/2+ W/2 - 50;
    Y1 = Y2 = ScreenHeight/2 + H/2 -50; // for NO and YES

    do
    {
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            Drawing();

            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 12), CameraY(ScreenHeight/2 - H/2 - 12),
                                    CameraX(ScreenWidth/2 + W/2 + 12), CameraY(ScreenHeight/2 + H/2 + 12),GREY);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 10), CameraY(ScreenHeight/2 - H/2 - 10),
                                    CameraX(ScreenWidth/2 + W/2 + 10), CameraY(ScreenHeight/2 + H/2 + 10),BLACK);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2), CameraY(ScreenHeight/2 - H/2),
                                    CameraX(ScreenWidth/2 + W/2), CameraY(ScreenHeight/2 + H/2),GREY);

            al_draw_text(fontB26,RED,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2 - 90),ALLEGRO_ALIGN_CENTRE,"Are you sure");
            al_draw_text(fontB26,RED,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2 - 50),ALLEGRO_ALIGN_CENTRE,"you want to exit the game?");

            al_draw_text(fontB26,RED,CameraX(X1),CameraY(Y1),ALLEGRO_ALIGN_CENTRE,"NO");
            al_draw_text(fontB26,RED,CameraX(X2),CameraY(Y2),ALLEGRO_ALIGN_CENTRE,"YES");

            if(pivot == 0)
                al_draw_text(fontB26,CYAN,CameraX(X1),CameraY(Y1),ALLEGRO_ALIGN_CENTRE,"NO");
            else
                al_draw_text(fontB26,CYAN,CameraX(X2),CameraY(Y2),ALLEGRO_ALIGN_CENTRE,"YES");

            al_flip_display();
            al_clear_to_color(LevelColor);
        }
        else if(events.keyboard.keycode == ALLEGRO_KEY_RIGHT) pivot = 1;
        else if(events.keyboard.keycode == ALLEGRO_KEY_LEFT) pivot = 0;
        ++entertime;
    } while(events.keyboard.keycode != ALLEGRO_KEY_ENTER || entertime <= 20);

    return pivot;
}

/*The maps are named MapX.txt,MapFX.txt,MapBX.txt, MapBBX.txt, where X is the level you are pointed to, in folder Maps//
X = 997,998,999 if it's the creative mode.
*/

inline void read_begin()
{
    std::ifstream fin("positionscreative.txt");
    fin>>creative_begin[1].x>>creative_begin[1].y>>last_death[1].x>>last_death[1].y;
    fin>>creative_begin[2].x>>creative_begin[2].y>>last_death[2].x>>last_death[2].y;
    fin>>creative_begin[3].x>>creative_begin[3].y>>last_death[3].x>>last_death[3].y;
    fin.close();
}

void DIF()
{
    if(Difficulty == 1)
    {
        knife = 25;
        gun = 100;
    }
    else if(Difficulty == 2)
    {
        knife = 10;
        gun = 40;
    }
    else if(Difficulty == 3)
    {
        knife = 6;
        gun = 20;
    }
    else
    {
        knife = 2;
        gun = 10;
    }
}

bool blocked1,blocked2;

inline void initTraps()
{
    blocked1 = false;
    blocked2 = false;
}

inline void endingTraps();

inline void Traps()
{
    if(Level == 18)
    {
        if(blocked2 == false)
        {
            blocked2 = true;
            Map[18][51] = Map[19][51] = Map[16][51] = Map[17][51] = 10;
        }

        if(Anastasia.x > 900 && blocked1 == false)
        {
            blocked1 = true;
            Map[18][14] = Map[17][14] = Map[16][14] = Map[15][14] = 10;
        }

        if(BackMap2[int(randomcoins[random[pozrand] - '0'].y)][int(randomcoins[random[pozrand] - '0'].x)] == 0)
        {
            ++pozrand;
            if(pozrand >= nrandom) pozrand = 0;
            BackMap2[int(randomcoins[random[pozrand] - '0'].y)][int(randomcoins[random[pozrand] - '0'].x)] = 3;
        }
    }
}

void Run(int Lmap)
{
    if(Level == 18)
    {
        randomcoins[1].x = 15;
        randomcoins[1].y = 13;
        randomcoins[2].x = 27;
        randomcoins[2].y = 3;
        randomcoins[3].x = 27;
        randomcoins[3].y = 7;
        randomcoins[4].x = 36;
        randomcoins[4].y = 5;
        randomcoins[5].x = 31;
        randomcoins[5].y = 3;
        randomcoins[6].x = 35;
        randomcoins[6].y = 14;
        randomcoins[7].x = 46;
        randomcoins[7].y = 14;
        randomcoins[8].x = 32;
        randomcoins[8].y = 21;
        randomcoins[9].x = 15;
        randomcoins[9].y = 21;
        strcpy(random,"9125734378625172643965824137653482132964385214826539462812637542861296");
        nrandom = strlen(random);
        pozrand = 0;
        BackMap2[int(randomcoins[1].y)][int(randomcoins[1].x)] = 3;
    }
    if(creativemode)
    {
        creative = true;
        al_stop_sample(&idbegin);
    }
    DIF();
    //reset the matrix
    for(int i=0; i<200; ++i)
        for(int j=0; j<600; ++j)
            Map[i][j] = FrontMap[i][j] = BackMap[i][j] = BackMap2[i][j] = MonsterMap[i][j] = 0;

    done = false;
    draw = true;
    cn = 0;

    Loading(Lmap);
    if(!creativemode)
    {
        LevelColor = al_map_rgb(RGB_A[Lmap],RGB_B[Lmap],RGB_C[Lmap]);

        if(sky[Level] == 1) celest = Sun.bm;
            else if(sky[Level] == 2) celest = Moon.bm;
                else celest = NULL;
        rainy = rainyy[Level];

        if(!cheatgodmode)
            godmode = false;
    }

    if(creativemode)
    {
        rainy  = false;
        celest = Sun.bm;
        godmode = true;
        read_begin();
        if(Lmap == 997)
            Anastasia.y = creative_begin[1].y, Anastasia.x = creative_begin[1].x,
            lastgravey = last_death[1].y,lastgravex = last_death[1].x;
        else if(Lmap == 998)
            Anastasia.y = creative_begin[2].y, Anastasia.x = creative_begin[2].x,
            lastgravey = last_death[2].y,lastgravex = last_death[2].x;
        else
            Anastasia.y = creative_begin[3].y, Anastasia.x = creative_begin[3].x,
            lastgravey = last_death[3].y, lastgravex = last_death[3].x;

        Anastasia.hp = 100;
        endx =  - 1000;
        endy = - 1000;
    }
    else
    {
        Anastasia.x = anastasia_begin[Lmap].x;
        Anastasia.y = anastasia_begin[Lmap].y;
        endx = level_end[Lmap].x;
        endy = level_end[Lmap].y;
    }

    if(Lmap == 0) //tutorial
    {
        rainy  = false;
        celest = Sun.bm;
        godmode = true;
        Anastasia.hp = 100;
        Anastasia.bullets = 3;
        Anastasia.coins = 20;

        Level = 0;
    }

    BM = 1;
    state = idle;

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    affected = 0;

    timerspeed = al_get_timer_speed(timer);

    if(rainy == true)
        al_play_sample(rains,Veffects*1./130,0,1.0,ALLEGRO_PLAYMODE_LOOP,&rainsound);

    if(Level == 1 && creativemode == false && closersong == false && Lmap != 0)
        al_play_sample(closer,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,&idcloser),timepassed = false,
        closersong = true;
    else if(closersong == false && beginmusic == false)
        al_play_sample(music,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idmusic),beginmusic = true;

    if(Level == 18)
    {
         if(fightsound == false)
            fightsound = true, fights = al_load_sample("Audio//Fight.ogg");
        al_stop_sample(&idmusic);
        al_stop_sample(&idcloser);
        al_play_sample(fights,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idfight),beginmusic = true;
    }

    initTraps();

    while(al_drop_next_event(event_queue));

    while(!done)
    {
        if(closersong == true)
            if(timepassed > 500 && beginmusic == false) // ending of the song
                al_play_sample(music,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idmusic),beginmusic = true;
        if(godmode)
            Anastasia.hp = 100;
        KEYBOARD();
        Traps(); // and random coins

        if(draw)
        {
            Anastasia.x += vx;
            Anastasia.y += vy;
            Drawing();
            al_flip_display();
            al_clear_to_color(LevelColor);

            gif_found(coin);
            gif_found(banana);
            gif_found(fly);
            gif_found(water);
            gif_found(spider);
            gif_found(spider2);
            gif_found(darkcloud);
            gif_found(darkcloud2);
            gif_found(fire);
            if(rainy)
                gif_found(rain);
        }

    }

    endingTraps();

    if(Anastasia.hp <= 0)
    {
        beginmusic = closersong = false;
        al_stop_sample(&idcloser);
        al_stop_sample(&idmusic);
        al_stop_sample(&idfight);
        timepassed = 550;
    }
    else if(Level > LEVELS)
    {
        al_stop_sample(&idfight);
        al_clear_to_color(BLACK);

        al_draw_text(font1,DARKRED,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2),ALLEGRO_ALIGN_CENTRE,"To be continued...");

        al_flip_display();


        int left = 0;

        al_rest(2);

        Level = 1;
        Anastasia.hp = 100;
        Anastasia.bullets = 3;
        Anastasia.coins = 0;
        isdead = true;
    }

    std::cout<<"MapHeight : "<<MapWidth<<" "<<MapHeight - Anastasia.h<<"\n";

    for(int i=1; i<=cn; ++i)
        BackMap2[int(addcoin[i].y)][int(addcoin[i].x)] = 3;
    //if(creativemode)
        Saving(Lmap);

    if(creativemode)
    {
        if(Lmap == 997)
            creative_begin[1].y = Anastasia.y, creative_begin[1].x = Anastasia.x,
            last_death[1].y = lastgravey, last_death[1].x = lastgravex;
        else if(Lmap == 998)
            creative_begin[2].y = Anastasia.y, creative_begin[2].x = Anastasia.x,
            last_death[2].y = lastgravey, last_death[2].x = lastgravex;
        else
            creative_begin[3].y = Anastasia.y, creative_begin[3].x = Anastasia.x,
            last_death[3].y = lastgravey, last_death[3].x = lastgravex;

        if(Anastasia.y + Anastasia.h > MapHeight - 10)
        {
            if(Lmap == 997)
                creative_begin[1].y = 2907, creative_begin[1].x = 200;
            else if(Lmap == 998)
                creative_begin[2].y = 2907, creative_begin[2].x = 200;
            else
                creative_begin[3].y = 2907, creative_begin[3].x = 200;
        }

        std::ofstream fout("positionscreative.txt");
        for(int i=1; i<=3; ++i)
            fout<<creative_begin[i].x<<" "<<creative_begin[i].y<<" "<<last_death[i].x<<" "<<last_death[i].y<<"\n";
        fout.close();
    }

    if(rainy)
        al_stop_sample(&rainsound);

    al_destroy_timer(timer);

    cameraPositionX = cameraPositionY = 0;
    al_identity_transform(&camera);
    al_translate_transform(&camera,0,0);
    al_use_transform(&camera);
    while(al_drop_next_event(event_queue));

    mike.q.erase(mike.q.begin(),mike.q.end());
    laica.q.erase(laica.q.begin(),laica.q.end());
    rabbit.q.erase(rabbit.q.begin(),rabbit.q.end());
    ork.q.erase(ork.q.begin(),ork.q.end());
    flydragon.q.erase(flydragon.q.begin(),flydragon.q.end());
    monster.q.erase(monster.q.begin(),monster.q.end());

    if(creativemode)
    {
        al_play_sample(beginsong,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idbegin);
        al_stop_sample(&idcloser);
        al_stop_sample(&idmusic);

        if(!cheatgodmode)
            godmode = false;
        creative = false;
    }
}

inline void endingTraps()
{
    if((Level == 19 && Anastasia.hp > 0) || (Level == 18 && Anastasia.hp <= 0)) // 18 but next level
    {
        Map[18][14] = Map[17][14] = Map[16][14] = Map[15][14] = 0;
        BackMap2[int(randomcoins[random[pozrand] - '0'].y)][int(randomcoins[random[pozrand] - '0'].x)] = 0;
    }

}

void Loading_Save()
{
    std::ifstream fin("Info.txt");
    fin>>Level;
    fin>>Anastasia.hp>>Anastasia.bullets>>Anastasia.coins;
    fin.close();

    prevhp = Anastasia.hp;
    prevbullets = Anastasia.bullets;
    prevcoins = Anastasia.coins;
}

void Saving_Save()
{
    if(Anastasia.hp <= 0)
    {
        isdead = true;
        Anastasia.bullets = prevbullets;
        Anastasia.coins = prevcoins;
    }
    else isdead = false;
    std::ofstream fout("auxi.txt");
    fout<<Level<<"\n";
    fout<<"100 "<<Anastasia.bullets<<" "<<Anastasia.coins<<"\n";
    fout.close();

    remove("Info.txt");
    rename("auxi.txt","Info.txt");
}

inline void beg_level(const int &level)
{
    al_play_sample(turn,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
    al_clear_to_color(BLACK);
    al_draw_textf(font1,RED,ScreenWidth/2,ScreenHeight/2,ALLEGRO_ALIGN_CENTER,"Level %d",level);
    al_flip_display();
    al_rest(1);
}

void Game()
{
    do
    {
        al_stop_sample(&idbegin);
        Loading_Save();
        if(Level == 1)
            Story();
        beg_level(Level);
        Run(Level);
        vy = 0;
        Saving_Save();
        al_play_sample(beginsong,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idbegin);
    } while(!isdead);
    al_stop_sample(&idcloser);
}

#endif // GAME_H_INCLUDED
