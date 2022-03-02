#ifndef SHOP_H_INCLUDED
#define SHOP_H_INCLUDED

inline void Shop()
{
    al_play_sample(shops,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
    int greentimer = 0;
    int greenpivot;
    int H,W;
    H = 250; W = 350;
    bool exit_shop = false;
    int pivot = 0;
    do
    {
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            Drawing();
            /*al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 12), CameraY(ScreenHeight/2 - H/2 - 12),
                                    CameraX(ScreenWidth/2 + W/2 + 12), CameraY(ScreenHeight/2 + H/2 + 12),GREY);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 10), CameraY(ScreenHeight/2 - H/2 - 10),
                                    CameraX(ScreenWidth/2 + W/2 + 10), CameraY(ScreenHeight/2 + H/2 + 10),BLACK);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2), CameraY(ScreenHeight/2 - H/2),
                                    CameraX(ScreenWidth/2 + W/2), CameraY(ScreenHeight/2 + H/2),GREY);*/

            al_draw_bitmap(Board.bm, CameraX(ScreenWidth/2 - Board.w/2), CameraY(ScreenHeight/2 - Board.h/2 - 50), NULL);

            al_draw_text(fontB26,DARKRED,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2),ALLEGRO_ALIGN_LEFT,"1 Bullet          2 coins");
            al_draw_text(fontB26,DARKRED,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 35),ALLEGRO_ALIGN_LEFT,"5 Bullets        8 coins");
            al_draw_text(fontB26,DARKRED,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 70),ALLEGRO_ALIGN_LEFT,"+10 HP            2 coins");
            al_draw_text(fontB26,DARKRED,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 105),ALLEGRO_ALIGN_LEFT,"FULL HP        10 coins");
            al_draw_text(fontB26,DARKRED,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 150),ALLEGRO_ALIGN_LEFT,"CONFIRM");

            if(pivot == 0)
                al_draw_text(fontB26,BLACK,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2),ALLEGRO_ALIGN_LEFT,"1 Bullet          2 coins");
            else if(pivot == 1)
                al_draw_text(fontB26,BLACK,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 35),ALLEGRO_ALIGN_LEFT,"5 Bullets        8 coins");
            else if(pivot == 2)
                al_draw_text(fontB26,BLACK,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 70),ALLEGRO_ALIGN_LEFT,"+10 HP            2 coins");
            else if(pivot == 3)
                al_draw_text(fontB26,BLACK,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 105),ALLEGRO_ALIGN_LEFT,"FULL HP        10 coins");
            else if(pivot == 4)
                al_draw_text(fontB26,BLACK,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 150),ALLEGRO_ALIGN_LEFT,"CONFIRM");

            if(greentimer > 0)
            {
                --greentimer;

                if(pivot == 0)
                    al_draw_text(fontB26,GREEN2,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2),ALLEGRO_ALIGN_LEFT,"1 Bullet          2 coins");
                else if(pivot == 1)
                    al_draw_text(fontB26,GREEN2,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 35),ALLEGRO_ALIGN_LEFT,"5 Bullets        8 coins");
                else if(pivot == 2)
                    al_draw_text(fontB26,GREEN2,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 70),ALLEGRO_ALIGN_LEFT,"+10 HP            2 coins");
                else if(pivot == 3)
                    al_draw_text(fontB26,GREEN2,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 105),ALLEGRO_ALIGN_LEFT,"FULL HP        10 coins");
                else if(pivot == 4)
                    al_draw_text(fontB26,GREEN2,CameraX(ScreenWidth/2 - W/2 + 20),CameraY(ScreenHeight/2 - H/2 + 150),ALLEGRO_ALIGN_LEFT,"CONFIRM");

            }

            al_flip_display();
            al_clear_to_color(LevelColor);
        }
        else if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        if(events.keyboard.keycode == ALLEGRO_KEY_DOWN) pivot = Min(4,pivot+1);
        else if(events.keyboard.keycode == ALLEGRO_KEY_UP) pivot = Max(0,pivot-1);
        else if(events.keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            if(pivot == 4) exit_shop = true;
            else if(pivot == 0 && Anastasia.coins >= 2)
            {
                Anastasia.coins -= 2;
                Anastasia.bullets = Min(99,Anastasia.bullets + 1);
                greenpivot = 0;
                greentimer = 30;
            }
            else if(pivot == 1 && Anastasia.coins >=8)
            {
                Anastasia.coins -=8;
                Anastasia.bullets = Min(99,Anastasia.bullets + 5);
                greenpivot = 1;
                greentimer = 30;
            }
            else if(pivot == 2 && Anastasia.coins >=2)
            {
                Anastasia.hp = Min(100,Anastasia.hp + 10);
                Anastasia.coins -= 2;
                greenpivot = 2;
                greentimer = 30;
            }
            else if(pivot == 3 && Anastasia.coins >= 10)
            {
                Anastasia.hp = 100;
                Anastasia.coins -= 10;
                greenpivot = 3;
                greentimer = 30;
            }
        }
        else if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            exit_shop = true;
    } while(!exit_shop);
    al_play_sample(shops,Veffects*1./100,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
}

#endif // SHOP_H_INCLUDED
