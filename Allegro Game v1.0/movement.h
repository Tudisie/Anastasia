#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED

#include <iostream>
#include "shop.h"

int state,prev_state;
float BM;

bool unpressed;
bool erased;
bool slidesound = false;

int flag = NULL;
float freeze; //i.e. if it's shooting, it will not move until he ends his shooting point.
bool jumpPressed = false; // if it's  held the button it will jump once

float vx,vy; //velocity Anastasia
float vx2; //velocity monsters
bool tryvx;
float Mx,My; //mouse

int prevdir;//for monsters

int affected = 0;
int attacked = 0; // if you attacked a monster you will wait to recharge your power a little.

int lastgravex,lastgravey; //if you die more than once it will appear your last death's grave
int prevelem_death;

bool JMP = true;

ALLEGRO_SAMPLE_ID id;
bool played = false;
int meleesound;


inline bool GetUp() // if the character is sliding and (i.e. freeze = 0 , jump button is pressed)
{
    Y1 = 60;
    for(int i = X1; i <= X2; i +=2) //Ox colision (X1,Y1) -> (X1 ->Y2)
        if(Map[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] > 0 &&
                Map[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] <= nblocks -ndarkblocks ||
                Map[int(Anastasia.y + (Y2+Y1)/2 + vy)/BLOCK_SIZE][int((Anastasia.x + i)/BLOCK_SIZE)] > 0 &&
                Map[int(Anastasia.y + (Y2+Y1)/2 + vy)/BLOCK_SIZE][int((Anastasia.x + i)/BLOCK_SIZE)] <= nblocks -ndarkblocks||
                Map[int(Anastasia.y + Y1 + 40 + vy)/BLOCK_SIZE][int((Anastasia.x + i)/BLOCK_SIZE)] > 0 &&
                Map[int(Anastasia.y + Y1 + 40 + vy)/BLOCK_SIZE][int((Anastasia.x + i)/BLOCK_SIZE)] <= nblocks -ndarkblocks)
            freeze = 10*increaseBM;
    return (freeze <= 0 ? 1 : 0);
}

void Die()
{
    int diesound = 10;
    if(godmode) return;
    bool gravedraw = false;
    done = true;
    affected = 0;
    Anastasia.hp = 0;
    for(BM = dead; vx != 0 || JMP || BM < 20; BM = Min(20, BM + increaseBM))
    {
        if(diesound == 0)
            al_play_sample(deads,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        --diesound;
        al_wait_for_event(event_queue,&events);
        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            Drawing();
            al_flip_display();
            al_clear_to_color(LevelColor);

            if(JMP)
                vy += gravity;

            collision();
            Anastasia.hp = 0;

            if(!JMP)
            {
                if(gravedraw == false)
                {
                    lastgravey = int((Anastasia.y - 20)/BLOCK_SIZE) + 3;
                    lastgravex = int((Anastasia.x + 20)/BLOCK_SIZE) + 1;

                    prevelem_death = BackMap2[lastgravey][lastgravex];
                    BackMap2[lastgravey][lastgravex] = 7; //grave
                    gravedraw = true;
                }
                vy = 0;
                if(vx != 0) //friction
                    vx -= 0.04 * (vx/abs(vx));
                if(-0.04 < vx  && vx < 0.04) vx = 0; //bug
            }

            Anastasia.x += vx;
            Anastasia.y += vy;

            CameraUpdate();
            al_identity_transform(&camera);
            al_translate_transform(&camera,-cameraPositionX,-cameraPositionY);
            al_use_transform(&camera);
        }
    }
    al_rest(1.5);

    BackMap2[lastgravey][lastgravex] = prevelem_death;
}

#include "interact.h"
#include "edit.h"

inline void Bullet()
{
    erased = false;
    std::vector<BULLET>::iterator it;

    for(it = Anastasia.q.begin(); it!= Anastasia.q.end() && !erased; ++it)
    {
        ++(it->time);
        it->x += (it->dir)*bulletSpeed;
        if(it->time >= bulletTime ||
            Map[int((it->y)/BLOCK_SIZE)][int((it->x + 10)/BLOCK_SIZE)] > 0 &&
            Map[int((it->y)/BLOCK_SIZE)][int((it->x + 10)/BLOCK_SIZE)] <= nblocks -ndarkblocks)
        {
            Anastasia.q.erase(it);
            break;
        }
    }
    BulletInteract();
}

inline void KEYBOARD()
{
    al_wait_for_event(event_queue,&events);
    al_get_keyboard_state(&keyState);

    /*the order of operations is important now.
        So first, we can at any time to choose orientation (left or right)
        If we shoot one time, we can't move in this time.
        While we melee, we can't move or jump.
        Slide command is after running command because we can crawl and slip.
        Same thing is happening with the jump comand.
        */

    if(events.type == ALLEGRO_EVENT_TIMER)
    {
        draw = true;
        prev_state = state;

        state = idle; //inactive sprite

        tryvx = false;

        //left or right direction?
        if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT))
            flag = NULL,tryvx = true;
        else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT))
            flag = ALLEGRO_FLIP_HORIZONTAL,tryvx = true;


        if(al_key_down(&keyState,ALLEGRO_KEY_LSHIFT))
        {
            if(moveSpeed == nonshiftedMoveSpeed) //changing run sound x2
                al_stop_sample(&id),played = false;
            moveSpeed = shiftedMoveSpeed;
            increaseBM = shiftedIncreaseBM;
        }
        else
        {
            if(moveSpeed == shiftedMoveSpeed) //changing run sound x1
                al_stop_sample(&id),played = false;
            moveSpeed = nonshiftedMoveSpeed;
            increaseBM = nonshiftedIncreaseBM;
        }

        if(affected && abs(vx) > moveSpeed) vx -= 0.1 * (vx/abs(vx));
        else vx = 0;

        if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT))
        {
            if(!affected || abs(vx) < moveSpeed + 1)
                vx = moveSpeed;
            state = run;
        }
        else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT))
        {
            if(!affected || abs(vx) < moveSpeed + 1)
                vx = -moveSpeed;
            state  = run;
        }

        vy += gravity;

        collision();

        if(al_key_down(&keyState,ALLEGRO_KEY_X) && state != slide)
        {
            state = melee;
            if(!JMP) vx = 0;// if it's on the ground it can't move when meels

        }

        if(al_key_down(&keyState,ALLEGRO_KEY_DOWN))
        {
            if(tryvx != 0)
            {
                if(al_key_down(&keyState,ALLEGRO_KEY_LSHIFT))
                    freeze = 12;
                else freeze = 6;
                prev_state  = slide;
                BM = slide;
            }
        }

        if(!slidesound && !JMP && prev_state == slide)
            al_play_sample(slides,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0),slidesound = true;

        if(creative) //editing
            edit();

        CameraUpdate();
        al_identity_transform(&camera);
        al_translate_transform(&camera,-cameraPositionX,-cameraPositionY);
        al_use_transform(&camera);
    }
    if(events.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        draw = true;
        switch(events.keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:
            if(!JMP)
            {
                vy = -jumpSpeed;
                if(jumpsound == 0) al_play_sample(jumps,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    else al_play_sample(jumps2,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                jumpsound = 1 - jumpsound;
                JMP = true;
                jumpPressed = true;
            }
            break;
        case ALLEGRO_KEY_SPACE:
            if(!JMP)
            {
                vy = -jumpSpeed;
                if(jumpsound == 0) al_play_sample(jumps,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    else al_play_sample(jumps2,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                jumpsound = 1 - jumpsound;
                JMP = true;
                jumpPressed = true;
            }
            break;
        case ALLEGRO_KEY_ESCAPE:
            if(ExitQ() == true) godmode = false,Die(),godmode = true;
            break;
        case ALLEGRO_KEY_C:
            if(Anastasia.bullets > 0 && prev_state != slide)
            {
                --Anastasia.bullets;
                al_play_sample(shoots,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                BM = shoot;
                prev_state = shoot;
                freeze = 6; //3 bitmaps for one real shooting x2 shoots

                //for the bullet
                int bul_dir = (flag == NULL ? 1:-1);
                int bul_x = (flag == NULL ? Anastasia.x + Anastasia.w : Anastasia.x);
                int bul_y = Anastasia.y + Anastasia.h/2;

                Anastasia.q.push_back({bul_x,bul_y,0,bul_dir});
            }
            else
            {
                al_play_sample(emptys,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
            }
            break;
        case ALLEGRO_KEY_B:
            Shop();
            break;
        case ALLEGRO_KEY_M:
            if(Level < LEVELS && godmode)
            {
                ++Level;
                done = true;
            }
            break;
        }
    }
    if(creative)
    {
        if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
            Mx = events.mouse.x,
            My = events.mouse.y;
        else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1)
            {
                std::cout<<CameraX(Mx)<<" "<<CameraY(My)<<" and the MapXY: "<<int(CameraX(Mx)/BLOCK_SIZE)<<" "<<int(CameraY(My)/BLOCK_SIZE)<<"\n";
                Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 1;
            }
            else if(events.mouse.button & 2)
                BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 1;
        }
    }

    if(draw)
    {
        if(freeze <= 0 && prev_state) GetUp(); //if it was sliding it would try to stand up (but only if it's possible
        if(freeze > 0)
            freeze -= increaseBM, state =  prev_state;

        //bitmap changing - Anastasia

        if(prev_state == state)
        {
            if(!(state == slide && !vx))
                BM += increaseBM;

            if(state == run && BM >= 29) BM = state;
            if(state == idle && BM >= 11) BM = state;
            if(state == jump && BM >= 39) BM = 38;
            if(state == melee && BM >= 46) BM = state;
            if(state == shoot && BM >= 49) BM = state;
            if(state == slide && BM >= 54) BM = state;
            if(state == dead && BM >= 21) BM = state;
        }
        else BM = state;

        if(state != slide) slidesound = false;

        //bullet moving and collision
        Bullet();

        //bitmap changing - Mike

        std::vector<posbm>::iterator it2;

        for(it2 = mike.q.begin(); it2!= mike.q.end(); ++it2)
        {
            if(!mike.found)
            {
                mike.found = true;
                ++mike.time;
                if(mike.time >= mike.ntime)
                {
                    mike.time = 0;
                    ++mike.k;
                    if(mike.k >= mike.n) mike.k = 0;
                }
            }
            //if(mike.time == 0 && mike.k == 0) it2->dir *= -1;

            vx2 = (it2->dir)*nonshiftedMoveSpeed;
            collision2(*it2,mike.w,mike.h);
            it2->x += vx2;
        }
        mike.found = false;

        for(it2 = laica.q.begin(); it2!= laica.q.end(); ++it2)
        {
            if(!laica.found)
            {
                laica.found = true;
                ++laica.time;
                if(laica.time >= laica.ntime)
                {
                    laica.time = 0;
                    ++laica.k;
                    if(laica.k >= laica.n) laica.k = 0;
                }
            }
            vx2 = (it2->dir)*nonshiftedMoveSpeed;
            collision2(*it2,laica.w,laica.h);
            it2->x += vx2 * 2;
        }
        laica.found = false;

        for(it2 = rabbit.q.begin(); it2!= rabbit.q.end(); ++it2)
        {
            if(!rabbit.found)
            {
                rabbit.found = true;
                ++rabbit.time;
                if(rabbit.time >= rabbit.ntime)
                {
                    rabbit.time = 0;
                    ++rabbit.k;
                    if(rabbit.k >= rabbit.n) rabbit.k = 0;
                }
            }
            vx2 = (it2->dir)*nonshiftedMoveSpeed;
            collision2(*it2,rabbit.w,rabbit.h - 20);
            it2->x += vx2/3;
        }
        rabbit.found = false;

        for(it2 = ork.q.begin(); it2!= ork.q.end(); ++it2)
        {
            if(!ork.found)
            {
                ork.found = true;
                ++ork.time;
                if(ork.time >= ork.ntime)
                {
                    ork.time = 0;
                    ++ork.k;
                    if(ork.k >= ork.n) ork.k = 0;
                }
            }

            vx2 = (it2->dir)*nonshiftedMoveSpeed/2.2;
            collision2(*it2,ork.w,ork.h - 5);

            it2->x += vx2;
        }
        ork.found = false;

        for(it2 = flydragon.q.begin(); it2!= flydragon.q.end(); ++it2)
        {
            if(!flydragon.found)
            {
                flydragon.found = true;
                ++flydragon.time;
                if(flydragon.time >= flydragon.ntime)
                {
                    flydragon.time = 0;
                    ++flydragon.k;
                    if(flydragon.k >= flydragon.n) flydragon.k = 0;
                }
            }

            vx2 = (it2->dir)*(nonshiftedMoveSpeed*3./4);
            collision3(*it2,flydragon.w,flydragon.h - 20);

            it2->x += vx2;
        }
        flydragon.found = false;


        for(it2 = monster.q.begin(); it2!= monster.q.end(); ++it2)
        {
            if(!monster.found)
            {
                monster.found = true;
                ++monster.time;
                if(monster.time >= monster.ntime)
                {
                    monster.time = 0;
                    ++monster.k;
                    if(monster.k >= monster.n) monster.k = 0;
                }
            }
            prevdir = it2->dir;
            vx2 = (it2->dir)*2*nonshiftedMoveSpeed;
            collision2(*it2,monster.w - 50,monster.h - 10);
            if(prevdir != it2->dir)
                it2->x += prevdir * 50;
            it2->x += vx2;
        }
        monster.found = false;
    }

    //knife sound

    if(state == melee)
        if(meleesound <= 0)
    {
        bool found = false;

        for(int i = Y1 + 30; i <= Y2 - 10; i+= 8) //continua dupa
        if(Map[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X1 - 35)/BLOCK_SIZE) ] > 0
        && Map[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X1 - 35)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
        && flag == ALLEGRO_FLIP_HORIZONTAL
           ||
           Map[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X2 + 35)/BLOCK_SIZE) ] > 0
        && Map[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X2 + 35)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
        && flag == NULL)
            found = true;

        if(found)
            if(moveSpeed == nonshiftedMoveSpeed)
                al_play_sample(knifes,Veffects*1./150,0,1.0,ALLEGRO_PLAYMODE_ONCE,0),meleesound = 75;
            else
                al_play_sample(knifes,Veffects*1./150,0,1.8,ALLEGRO_PLAYMODE_ONCE,0),meleesound = 75/2;

    }

    //run

    meleesound = Max(0,meleesound - 1);

    if(!JMP && state == run)
    {
        if(!played)
            al_play_sample(runs,Veffects*1.3/100,0,moveSpeed/nonshiftedMoveSpeed,ALLEGRO_PLAYMODE_LOOP,&id) , played = true;

    }
    if((JMP || state != run) && played) al_stop_sample(&id), played = false;
}

#endif // MOVEMENT_H_INCLUDED
