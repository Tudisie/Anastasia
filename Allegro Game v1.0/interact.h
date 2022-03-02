#ifndef INTERACT_H_INCLUDED
#define INTERACT_H_INCLUDED

inline void DamagedY()
{
    vy = -10;

    //if(moveSpeed == shiftedMoveSpeed) vy *= 2;
    affected = 150;
    JMP = true;
}

inline void DamagedX()
{
    if(vx > 0) vx = -8;
    else vx = 8;

    //if(moveSpeed == shiftedMoveSpeed) vx *= 2;
    affected = 150;
}

inline void BulletInteract()
{
    std::vector<BULLET>::iterator it;
    std::vector<posbm>::iterator it2;

    for(it = Anastasia.q.begin(); it!= Anastasia.q.end() && !erased; ++it)
    {
        for(it2 = mike.q.begin(); it2!= mike.q.end() && !erased; ++it2)
                if(it->x > it2->x && it->x < it2->x + mike.w &&
                   it->y > it2->y && it->y < it2->y + mike.h)
                    {
                            al_play_sample(mikes,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                            it2->hp -= gun; //mike loses health
                            it2->dir *= -1;
                            it2->affected = 120;
                            if(it2->hp  <= 0){
                                    mike.q.erase(it2);
                            }
                            Anastasia.q.erase(it);
                            erased = true;
                    }
            //rabbit isn't damaged by bullets
    }

    for(it = Anastasia.q.begin(); it!= Anastasia.q.end() && !erased; ++it)
    {
        for(it2 = laica.q.begin(); it2!= laica.q.end() && !erased; ++it2)
                if(it->x > it2->x && it->x < it2->x + laica.w &&
                   it->y > it2->y && it->y < it2->y + laica.h)
                    {
                            it2->hp -= gun;
                            it2->dir *= -1;
                            it2->affected = 120;
                            if(it2->hp  <= 0){
                                    laica.q.erase(it2);
                            }
                            Anastasia.q.erase(it);
                            erased = true;
                    }
    }

    for(it = Anastasia.q.begin(); it!= Anastasia.q.end() && !erased; ++it)
    {
        for(it2 = ork.q.begin(); it2!= ork.q.end() && !erased; ++it2)
                if(it->x > it2->x && it->x < it2->x + ork.w &&
                   it->y > it2->y && it->y < it2->y + ork.h)
                    {
                            al_play_sample(mikes,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                            it2->hp -= gun;
                            it2->dir *= -1;
                            it2->affected = 120;
                            if(it2->hp  <= 0){
                                    ork.q.erase(it2);
                            }
                            Anastasia.q.erase(it);
                            erased = true;
                    }
    }

    for(it = Anastasia.q.begin(); it!= Anastasia.q.end() && !erased; ++it)
    {
        for(it2 = flydragon.q.begin(); it2!= flydragon.q.end() && !erased; ++it2)
                if(it->x > it2->x && it->x < it2->x + flydragon.w &&
                   it->y > it2->y && it->y < it2->y + flydragon.h)
                    {
                            al_play_sample(bird,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                            it2->hp -= gun;
                            it2->dir *= -1;
                            it2->affected = 120;
                            if(it2->hp  <= 0){
                                    flydragon.q.erase(it2);
                            }
                            Anastasia.q.erase(it);
                            erased = true;
                    }
    }

    //Monster
    for(it = Anastasia.q.begin(); it!= Anastasia.q.end() && !erased; ++it)
    {
        for(it2 = monster.q.begin(); it2!= monster.q.end() && !erased; ++it2)
                if(it->x > it2->x && it->x < it2->x + monster.w &&
                   it->y > it2->y && it->y < it2->y + monster.h)
                    {
                            al_play_sample(monsters,Veffects*1./75,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                            it2->hp -= gun;
                            it2->affected = 120;
                            if(it2->hp  <= 0){
                                    monster.q.erase(it2);
                                    if(Level == 18)
                                        Map[18][51] = Map[19][51] = Map[16][51] = Map[17][51]  = 0;
                            }
                            Anastasia.q.erase(it);
                            erased = true;
                    }
            //rabbit isn't damaged by bullets
    }
}

inline void collision() //Anastasia
{
    if(!(Anastasia.y + Y1 > endy + Spell.h/2))
    if(!(Anastasia.y + Y2 < endy - Spell.h/2))
    if(!(Anastasia.x + X1 > endx + Spell.w/2))
    if(!(Anastasia.x + X2 < endx - Spell.w/2))
    {
        ++Level;
        done = true;
    }
    JMP = true;

    float prev_vy = vy;

    //Horizontal axis Ox vy

    if(prev_state == slide || done == true) Y1 = Y2 - BLOCK_SIZE + 5;
    else Y1 = 60;

    if(Anastasia.y + Y2/2 + vy > MapHeight - 10)
    {
        al_play_sample(pain1,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        JMP = false;

        if(!done)
        {
            vx = 0;
            DamagedY();
            Die();
        }
    }

    std::vector<posbm>::iterator it2;
    for(it2 = mike.q.begin(); it2!= mike.q.end(); ++it2)
        {
            //box collision
            if(Anastasia.y +Y1 > it2->y + mike.h || Anastasia.y +Y2 < it2->y ||
                Anastasia.x +X1 > it2->x + mike.w || Anastasia.x +X2 < it2->x ) continue;

                if(prev_state == melee && ((flag == NULL && Anastasia.x + X2 <= it2->x + 10) ||
                                           (flag == ALLEGRO_FLIP_HORIZONTAL && Anastasia.x + X1 >= it2->x - 10)))
                {
                    if(it2->affected <= 0)
                    {
                        it2->hp -= knife; //mike loses health
                        al_play_sample(mikes,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                        al_play_sample(knifes,Veffects*1./150,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                        it2->dir *= -1;
                        it2->affected = 120;
                        if(it2->hp  < 0){
                                //MonsterMap[it2->mapy][it2->mapx] = 0;
                                mike.q.erase(it2);
                                break;
                        }
                    }
                    else --it2->affected;
                }
                else if(!affected)
                {
                    al_play_sample(pain3,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 20;
                    if(Anastasia.hp > 0) DamagedY();
                }
        }

    for(it2 = laica.q.begin(); it2!= laica.q.end(); ++it2)
        {
            //box collision
            if(Anastasia.y +Y1 > it2->y + laica.h || Anastasia.y +Y2 < it2->y ||
                Anastasia.x +X1 > it2->x + laica.w || Anastasia.x +X2 < it2->x ) continue;

                if(prev_state == melee && ((flag == NULL && Anastasia.x + X2 <= it2->x + 10) ||
                                           (flag == ALLEGRO_FLIP_HORIZONTAL && Anastasia.x + X1 >= it2->x - 10)))
                {
                    if(it2->affected <= 0)
                    {
                        al_play_sample(dog,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                        it2->hp -= knife;
                        al_play_sample(knifes,Veffects*1./150,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

                        it2->dir *= -1;
                        it2->affected = 120;
                        if(it2->hp  < 0){
                                laica.q.erase(it2);
                                break;
                        }
                    }
                    else --it2->affected;
                }
                else if(!affected)
                {
                    al_play_sample(pain3,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 10;
                    if(Anastasia.hp > 0) DamagedY();
                }
        }

    for(it2 = rabbit.q.begin(); it2!= rabbit.q.end(); ++it2)
        {
            //box collision
            if(Anastasia.y +Y1 > it2->y + rabbit.h || Anastasia.y +Y2 < it2->y ||
                Anastasia.x +X1 > it2->x + rabbit.w || Anastasia.x +X2 < it2->x ) continue;
            if(!affected)
            {
                al_play_sample(pain3,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                Anastasia.hp -= 3;
                if(Anastasia.hp > 0) DamagedY();
            }
        }

    for(it2 = ork.q.begin(); it2!= ork.q.end(); ++it2)
        {
            //box collision
            if(Anastasia.y +Y1 > it2->y + ork.h || Anastasia.y +Y2 < it2->y ||
                Anastasia.x +X1 > it2->x + ork.w || Anastasia.x +X2 < it2->x) continue;

                if(prev_state == melee && ((flag == NULL && Anastasia.x + X2 <= it2->x + 10) ||
                                           (flag == ALLEGRO_FLIP_HORIZONTAL && Anastasia.x + X1 >= it2->x - 10)))
                {
                    if(it2->affected <= knife)
                    {
                        it2->hp -= knife;
                        al_play_sample(mikes,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                        al_play_sample(knifes,Veffects*1./150,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                        it2->dir *= -1;
                        it2->affected = 120;
                        if(it2->hp  < 0){
                                ork.q.erase(it2);
                                break;
                        }
                    }
                    else --it2->affected;
                }
                else if(!affected)
                {
                    al_play_sample(pain3,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 18;
                    if(Anastasia.hp > 0) DamagedY();
                }
        }

    for(it2 = flydragon.q.begin(); it2!= flydragon.q.end(); ++it2)
        {
            //box collision
            if(Anastasia.y +Y1 > it2->y + flydragon.h || Anastasia.y +Y2 < it2->y ||
                Anastasia.x +X1 > it2->x + flydragon.w || Anastasia.x +X2 < it2->x) continue;

                if(prev_state == melee && ((flag == NULL && Anastasia.x + X2 <= it2->x + 10) ||
                                           (flag == ALLEGRO_FLIP_HORIZONTAL && Anastasia.x + X1 >= it2->x - 10))
                   && Anastasia.y + Y1 + 30 <=it2->y + flydragon.h)
                {
                    if(it2->affected <= 0)
                    {
                        al_play_sample(bird,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                        it2->hp -= knife;
                        al_play_sample(knifes,Veffects*1./150,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                        it2->dir *= -1;
                        it2->affected = 120;
                        if(it2->hp  < 0){
                                flydragon.q.erase(it2);
                                break;
                        }
                    }
                    else --it2->affected;
                }
                else if(!affected)
                {
                    al_play_sample(pain3,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 8;
                    if(Anastasia.hp > 0) DamagedY();
                }
        }

    for(it2 = monster.q.begin(); it2!= monster.q.end(); ++it2)
        {
            //box collision
            if(Anastasia.y +Y1 > it2->y + monster.h || Anastasia.y +Y2 < it2->y ||
                Anastasia.x +X1 + 85 > it2->x + monster.w || Anastasia.x +X2 - 10 < it2->x ) continue;

            if(!affected)
            {
                al_play_sample(pain3,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                Anastasia.hp -= 20;
                if(Anastasia.hp > 0) DamagedY();
            }
        }

    if(vy != 0)
    for(int i = X1; i <= X2; i +=2)
    {
        /*al_draw_circle(Anastasia.x + i, Anastasia.y + Y1 + vy,2,al_map_rgb(255,0,0),2);
        al_draw_circle(Anastasia.x + i, Anastasia.y + Y2 + vy,2,al_map_rgb(255,0,0),2);*/
        if(vy < 0)
        {
            if(Anastasia.y + Y1 < 0) continue;
            if(Map[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] > 0 &&
                    Map[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] <= nblocks -ndarkblocks) vy = 1.5;
            if(!affected)
                if(BackMap2[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] == 1 ||
                        BackMap2[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] == 2 && !affected)
                {
                    al_play_sample(pain2,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 8;
                    if(Anastasia.hp > 0) DamagedY();
                }
            if(BackMap2[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] == 3)
                BackMap2[int((Anastasia.y + Y1 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] = 0,
                addcoin[++cn].x = int((Anastasia.x + i)/BLOCK_SIZE),
                addcoin[cn].y = int((Anastasia.y + Y1 + vy)/BLOCK_SIZE),
                ++Anastasia.coins, al_play_sample(coins,Veffects*1./80,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        }
        if(vy > 0)
        {
            if(Map[int((Anastasia.y + Y2 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] > 0 &&
                    Map[int((Anastasia.y + Y2 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] <= nblocks -ndarkblocks) JMP = false;
            if(!affected)
                if(BackMap2[int((Anastasia.y + Y2 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] == 1 ||
                        BackMap2[int((Anastasia.y + Y2 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] == 2 && !affected)
                {
                    al_play_sample(pain2,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 8;
                    if(Anastasia.hp > 0) DamagedY();
                }
            if(BackMap2[int((Anastasia.y + Y2 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] == 3)
                BackMap2[int((Anastasia.y + Y2 + vy)/BLOCK_SIZE)][int((Anastasia.x + i)/BLOCK_SIZE)] = 0,
                addcoin[++cn].x = int((Anastasia.x + i)/BLOCK_SIZE),
                addcoin[cn].y = int((Anastasia.y + Y2 + vy)/BLOCK_SIZE),
                ++Anastasia.coins,al_play_sample(coins,Veffects*1./80,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        }

    }

    //Vertical axis Oy, vx

    if(vx != 0)
    for(int i = Y1; i < Y2; i += 5)
    {
        /*al_draw_circle(Anastasia.x + X1 + vx, Anastasia.y + i,2,al_map_rgb(255,0,0),2);
        al_draw_circle(Anastasia.x + X2 + vx, Anastasia.y + i,2,al_map_rgb(255,0,0),2);*/

        if(Anastasia.y + i <= 0) continue;

        if(vx < 0)
        {
            if(Map[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X1 + vx)/BLOCK_SIZE) ] > 0
                    && Map[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X1 + vx)/BLOCK_SIZE) ] <= nblocks -ndarkblocks) vx = 0;
            if(BackMap2[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X1 + vx)/BLOCK_SIZE) ] == 1 or
                    BackMap2[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X1 + vx)/BLOCK_SIZE) ] == 2)
            {
                if(Anastasia.hp > 0 && !affected)
                {
                    al_play_sample(pain2,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 8;
                    DamagedX();
                    DamagedY();
                }
            }
            if(BackMap2[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X1 + vx - 10)/BLOCK_SIZE) ] == 3)
                BackMap2[int((Anastasia.y + i)/BLOCK_SIZE)][int((Anastasia.x + X1 + vx - 10)/BLOCK_SIZE)] = 0,
                addcoin[++cn].x = int((Anastasia.x + X1 + vx - 10)/BLOCK_SIZE),
                addcoin[cn].y = int((Anastasia.y + i)/BLOCK_SIZE),
                ++Anastasia.coins,al_play_sample(coins,Veffects*1./80,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        }
        if(vx > 0)
        {
            if(Map[int((Anastasia.y + i)/BLOCK_SIZE)][int((Anastasia.x + X2 + vx)/BLOCK_SIZE)] > 0 &&
                    Map[int((Anastasia.y + i)/BLOCK_SIZE)][int((Anastasia.x + X2 + vx)/BLOCK_SIZE)] <= nblocks -ndarkblocks) vx = 0;
            if(BackMap2[int((Anastasia.y + i)/BLOCK_SIZE)][int((Anastasia.x + X2 + vx)/BLOCK_SIZE)] == 1 or
                    BackMap2[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X2 + vx)/BLOCK_SIZE) ] == 2)
            {
                if(Anastasia.hp > 0 && !affected)
                {
                    al_play_sample(pain2,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                    Anastasia.hp -= 8;
                    DamagedX();
                    DamagedY();
                }
            }
            if(BackMap2[int((Anastasia.y + i)/BLOCK_SIZE) ][ int((Anastasia.x + X2 + vx + 10)/BLOCK_SIZE) ] == 3)
                BackMap2[int((Anastasia.y + i)/BLOCK_SIZE)][int((Anastasia.x + X2 + vx + 10)/BLOCK_SIZE)] = 0,
                addcoin[++cn].x = int((Anastasia.x + X2 + vx + 10)/BLOCK_SIZE),
                addcoin[cn].y = int((Anastasia.y + i)/BLOCK_SIZE),
                ++Anastasia.coins,al_play_sample(coins,Veffects*1./80,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
        }
    }

    if(JMP) state = jump;
    else vy = 0;

    if(!JMP && freeze > 0 && prev_state != slide) vx = 0; //i.e. if it's on the ground and it's shooting,it can't move (left or right)

    if(prev_vy != vy)
        if(prev_vy > 15 && !affected)
        {
            al_play_sample(pain1,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
            Anastasia.hp -= (prev_vy - 14) * (prev_vy - 14) * 2, affected = 150;
        }

    affected = Max(0,affected - 1);
    if(Anastasia.hp <= 0 & !done) Die();
}

inline void collision2(posbm &A,const int &W,const int &H) //rabbit,mike,laica
{
    if(vx2 != 0)
    {
        if(vx2 < 0)
            if(Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2 + 25)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2+ 25)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2+ 25)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2+ 25)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2+ 25)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2+ 25)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               (Map[int((A.y + H)/BLOCK_SIZE) ][ int((A.x + vx2+ 25)/BLOCK_SIZE) ] == 0
                    || Map[int((A.y + H)/BLOCK_SIZE) ][ int((A.x + vx2+ 25)/BLOCK_SIZE) ] > nblocks -ndarkblocks)
               ||
               A.x + vx2 <= 0)
                    vx2 = 0,A.dir *= -1;
        if(vx2 > 0)
            if(Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2 + W- 40)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2 + W- 40)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2 + W- 40)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2 + W- 40)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2 + W- 40)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 40)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
                ||
               (Map[int((A.y + H)/BLOCK_SIZE) ][ int((A.x + vx2 + W- 40)/BLOCK_SIZE) ] == 0
                    || Map[int((A.y + H)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 40)/BLOCK_SIZE) ] > nblocks -ndarkblocks))
                    vx2 = 0,A.dir *= -1;
            /*al_draw_filled_circle(A.x + vx2 + W - 40,A.y + H,3,RED);
            al_draw_filled_circle(A.x + vx2 +25,A.y + H,3,RED);*/
    }
}

inline void collision3(posbm &A,const int &W,const int &H) //flydragon
{
    if(vx2 != 0)
    {
        if(vx2 < 0)
            if(Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2 + 15)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2 + 15)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2 + 15)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2 + 15)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2 + 15)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2 + 15)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               A.x + vx2 <= 0)
                    vx2 = 0,A.dir *= -1;
        if(vx2 > 0)
            if(Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 15)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 15)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 15)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/2)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 15)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               ||
               Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 15)/BLOCK_SIZE) ] > 0
                    && Map[int((A.y + H/4*3)/BLOCK_SIZE) ][ int((A.x + vx2 + W - 15)/BLOCK_SIZE) ] <= nblocks -ndarkblocks
               || A.x + vx2 + W >= MapWidth
                )
                    vx2 = 0,A.dir *= -1;
    }
}

#endif // INTERACT_H_INCLUDED
