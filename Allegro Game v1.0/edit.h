#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED

int prevelem,elem,activategod;
int pressed;

void GOD_EDIT()
{
    if(prevelem)
    if(activategod == true)
    {
        activategod = false;
        //elem = 0;
        for(int i=0; i<My; ++i)
            for(int j=0; j<Mx; ++j)
                if(Map[i][j] == prevelem)
                    Map[i][j] = elem;
    }
}

inline void edit()
{
    /*  ~ delete
        (CTRL / ALT / NONE) + 1234567890- Map (Blocks)
        QWERTYUIOP ASDFGHJKL FrontMap
        QWERTYUIOP ASDFGHJKL + CTRL BackMap
        QWERTYUIOP ASDFGHJKL + ALT Back2Map

        TAB + Q - Mike

        RCTRL - +HP.
        F1+F2+F3  changes all the elements with the same texture The cursor indicates to the texture you put last time
        if you press 1 and than F1 +F2 +F3 when the cursor is on a 3 block, it will be changed al the 3 blocks to 1.
    */

    pressed = false;
    prevelem = Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)];

    if(al_key_down(&keyState,ALLEGRO_KEY_F1))
        if(al_key_down(&keyState,ALLEGRO_KEY_F2))
            if(al_key_down(&keyState,ALLEGRO_KEY_F3))
                 activategod = true;

    if(al_key_down(&keyState,ALLEGRO_KEY_TILDE))
        Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] =
            BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] =
                BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] =
                    FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 0;

    if(al_key_down(&keyState,ALLEGRO_KEY_1)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 1, elem = 1,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_2)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 2, elem = 2,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_3)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 33, elem = 33,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_4)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 4, elem = 4,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_5)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 5, elem = 5,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_6)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 6, elem = 6,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_7)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 7, elem = 7,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_8)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 8, elem = 8,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_9)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 9, elem = 9,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_0)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 10, elem = 10,pressed = true;
    if(al_key_down(&keyState,ALLEGRO_KEY_MINUS)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 11, elem = 11,pressed = true;


    if(al_key_down(&keyState,ALLEGRO_KEY_LCTRL))
    {
        if(al_key_down(&keyState,ALLEGRO_KEY_1)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 12, elem = 12,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_2)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 13, elem = 13,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_3)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 14, elem = 14,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_4)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 15, elem = 15,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_5)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 16, elem = 16,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_6)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 17, elem = 17,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_7)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 18, elem = 18,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_8)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 19, elem = 19,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_9)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 20, elem = 20,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_0)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 21, elem = 21,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_MINUS)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 22, elem = 22,pressed = true;
    }
    if(al_key_down(&keyState,ALLEGRO_KEY_ALT))
    {
        if(al_key_down(&keyState,ALLEGRO_KEY_1)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 23, elem = 23,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_2)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 24, elem = 24,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_3)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 25, elem = 25,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_4)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 26, elem = 26,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_5)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 27, elem = 27,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_6)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 28, elem = 28,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_7)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 29, elem = 29,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_8)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 30, elem = 30,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_9)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 31, elem = 31,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_0)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 32, elem = 32,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_MINUS)) Map[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 3, elem = 3,pressed = true;
    }

    if(!al_key_down(&keyState,ALLEGRO_KEY_LCTRL) && !al_key_down(&keyState,ALLEGRO_KEY_ALT) &&
       !al_key_down(&keyState,ALLEGRO_KEY_TAB))//FrontMap
    {
        if(al_key_down(&keyState,ALLEGRO_KEY_Q)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 1,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_W)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 2,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_E)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 3,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_R)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 4,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_T)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 5,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_Y)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 6,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_U)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 7,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_I)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 8,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_O)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 9,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_P)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 10,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_A)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 11,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_S)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 12,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_D)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 13,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_F)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 14,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_G)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 15,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_H)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 16,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_J)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 17,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_K)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 18,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_L)) FrontMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 19,pressed = true;

    }
    if(al_key_down(&keyState,ALLEGRO_KEY_LCTRL)) // BackMap
    {
        if(al_key_down(&keyState,ALLEGRO_KEY_Q)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 1,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_W)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 2,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_E)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 3,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_R)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 4,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_T)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 5,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_Y)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 6,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_U)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 7,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_I)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 8,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_O)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 9,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_P)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 10,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_A)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 11,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_S)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 12,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_D)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 13,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_F)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 14,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_G)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 15,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_H)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 16,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_J)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 17,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_K)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 18,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_L)) BackMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 19,pressed = true;
    }

    if(al_key_down(&keyState,ALLEGRO_KEY_ALT)) //BackMap2
    {
        if(al_key_down(&keyState,ALLEGRO_KEY_Q)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 1,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_W)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 2,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_E)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 3,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_R)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 4,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_T)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 5,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_Y)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 6,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_U)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 7,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_I)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 8,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_O)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 9,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_P)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 10,pressed = true;
            if(al_key_down(&keyState,ALLEGRO_KEY_A)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 11,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_S)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 12,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_D)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 13,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_F)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 14,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_G)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 15,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_H)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 16,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_J)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 17,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_K)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 18,pressed = true;
        if(al_key_down(&keyState,ALLEGRO_KEY_L)) BackMap2[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 19,pressed = true;
    }

    if(!al_key_down(&keyState,ALLEGRO_KEY_TAB) && !al_key_down(&keyState,ALLEGRO_KEY_RCTRL)) unpressed = true;

    if(al_key_down(&keyState,ALLEGRO_KEY_TAB)) //Monsters
    {
        if(al_key_down(&keyState,ALLEGRO_KEY_Q) && unpressed)
        {
            pressed = true;
            MonsterMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 1;
            mike.q.push_back({CameraX(Mx) - mike.w/2 + 20,(CameraY(My))/BLOCK_SIZE*BLOCK_SIZE - mike.h + 90, 1,200,CameraX(Mx),CameraY(My),0}),
            unpressed = false;
        }
        if(al_key_down(&keyState,ALLEGRO_KEY_W) && unpressed)
        {
            pressed = true;
            MonsterMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 2;
            laica.q.push_back({CameraX(Mx) - laica.w/2 + 20,(CameraY(My))/BLOCK_SIZE*BLOCK_SIZE - laica.h + 90, 1,100,CameraX(Mx),CameraY(My),0}),
            unpressed = false;
        }
        if(al_key_down(&keyState,ALLEGRO_KEY_E) && unpressed)
        {
            pressed = true;
            MonsterMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 3;
            rabbit.q.push_back({CameraX(Mx) - rabbit.w/2 + 20,(CameraY(My))/BLOCK_SIZE*BLOCK_SIZE - rabbit.h + 95, 1,100,CameraX(Mx),CameraY(My),0}),
            unpressed = false;
        }
        if(al_key_down(&keyState,ALLEGRO_KEY_R) && unpressed)
        {
            pressed = true;
            MonsterMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 4;
            ork.q.push_back({CameraX(Mx) - ork.w/2 + 20,(CameraY(My))/BLOCK_SIZE*BLOCK_SIZE - ork.h + 95, 1,150,CameraX(Mx),CameraY(My),0}),
            unpressed = false;
        }
        if(al_key_down(&keyState,ALLEGRO_KEY_T) && unpressed)
        {
            pressed = true;
            MonsterMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 5;
            flydragon.q.push_back({CameraX(Mx) - flydragon.w/2 + 20,(CameraY(My))/BLOCK_SIZE*BLOCK_SIZE - flydragon.h + 85, 1,60,CameraX(Mx),CameraY(My),0}),
            unpressed = false;
        }
        if(al_key_down(&keyState,ALLEGRO_KEY_Y) && unpressed)
        {
            pressed = true;
            MonsterMap[int(CameraY(My)/BLOCK_SIZE)][int(CameraX(Mx)/BLOCK_SIZE)] = 6;
            monster.q.push_back({CameraX(Mx) - monster.w/2 + 20,((CameraY(My))/BLOCK_SIZE+1)*BLOCK_SIZE - monster.h + 65, 1,1000,CameraX(Mx),CameraY(My),0}),
            unpressed = false;
        }
    }

    if(pressed)
    {
        int I = int(CameraY(My)/BLOCK_SIZE);
        int J = int(CameraX(Mx)/BLOCK_SIZE);

        Last[I] = Max(Last[I],J);
        LastF[I] = Max(LastF[I],J);
        LastB[I] = Max(LastB[I],J);
        LastBB[I] = Max(LastBB[I],J);
        LastM[I] = Max(LastM[I],J);
    }

    if(al_key_down(&keyState,ALLEGRO_KEY_RCTRL) && unpressed)
        Anastasia.hp = Min(100,Anastasia.hp + 5),
        ++Anastasia.coins,Anastasia.bullets = Min(99,Anastasia.bullets + 1),unpressed = false;

    GOD_EDIT();
}

#endif // EDIT_H_INCLUDED
