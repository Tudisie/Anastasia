#ifndef BEG_H_INCLUDED
#define BEG_H_INCLUDED

#include "Game.h"
#include "creativemode.h"
#include "tutorial.h"
#include "Options.h"
#include "Story.h"
#include "beg2.h"

bool Exit;

void beg()
{
    al_play_sample(beginsong,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idbegin);
    int pivot = 0;
    char name[] = "Anastasia";

    struct Opening{
        char name[10];
        int x,y; //position

        Opening(char n[],int posx,int posy)
        {
           strcpy(name,n);
           x = posx;
           y = posy;
        }
    };

    Opening opt[] = {
        {"Start",ScreenWidth/2,ScreenHeight/5+50},
        {"Options",ScreenWidth/2,ScreenHeight/5*2+50},
        {"Story",ScreenWidth/2,ScreenHeight/5*3+50},
        {"Exit",ScreenWidth/2,ScreenHeight/5*4+50}
                    };
    int noptions = 4;

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    Exit = false;
    bool draw, done;
    draw = true;
    done = false;

    while(al_drop_next_event(event_queue));

    //Loading Screen.
   /* for(int k=0; k < noptions; ++k)
        for(float op = 0; op <= 1.0 && !done; op += 0.04)
        {
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue,&events);

            if(events.type == ALLEGRO_EVENT_TIMER)
                draw = true;

            if(draw)
            {
                draw = false;
                al_clear_to_color(BLACK);

                //Title
                al_draw_bitmap(rose.bm,50,ScreenHeight - rose.h,NULL);
                al_draw_text(font2, RED, ScreenWidth/2, ScreenHeight/5 - 100, ALLEGRO_ALIGN_CENTRE, name);

                for(int ant = k-1; ant >= 0; --ant)
                    al_draw_text(font1,RED,opt[ant].x,opt[ant].y,ALLEGRO_ALIGN_CENTRE,opt[ant].name);

                al_draw_text(font1,color(255,0,0,op),opt[k].x,opt[k].y,ALLEGRO_ALIGN_CENTRE,opt[k].name);
                al_draw_bitmap(petalsWally,0,0,NULL);

                fall_gif();

                al_flip_display();
            }
        }*/

    //Time to choose
    while(!Exit)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(events.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    Exit = true;
                    break;
                case ALLEGRO_KEY_UP:
                    pivot = Max(pivot-1,0);
                    break;
                case ALLEGRO_KEY_DOWN:
                    pivot = Min(pivot+1,noptions-1);
                    break;
                case ALLEGRO_KEY_ENTER:
                    al_stop_timer(timer);
                    if(pivot == 0) beg2();
                    else if(pivot == 1) Options();
                    else if(pivot == 2) Story();
                    else Exit = true; // pivot == 3
                    al_start_timer(timer);
                    break;
            }
        }
        else if(events.type == ALLEGRO_EVENT_TIMER)
            draw = true;

        if(draw)
        {
            draw = false;

            al_clear_to_color(BLACK);
            al_draw_bitmap(rose.bm,50,ScreenHeight - rose.h,NULL);
            al_draw_text(font2, RED, ScreenWidth/2, ScreenHeight/5 - 100, ALLEGRO_ALIGN_CENTRE, name);

            for(int k = 0; k < noptions; ++k)
                al_draw_text(font1,RED,opt[k].x,opt[k].y,ALLEGRO_ALIGN_CENTRE,opt[k].name);

            al_draw_text(font1,CYAN,opt[pivot].x,opt[pivot].y,ALLEGRO_ALIGN_CENTRE,opt[pivot].name);
            al_draw_bitmap(petalsWally,0,0,NULL);

            fall_gif();

            al_flip_display();
        }
    }

    al_unregister_event_source(event_queue,al_get_timer_event_source(timer));
    al_destroy_timer(timer);
}

#endif // BEG_H_INCLUDED
