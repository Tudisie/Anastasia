#ifndef BEG2_H_INCLUDED
#define BEG2_H_INCLUDED

#include "beg3.h"

void beg2()
{
    bool closebeg2 = false;
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
        {"Storyline",ScreenWidth/2,ScreenHeight/5+50},
        {"Creative",ScreenWidth/2,ScreenHeight/5*2+50},
        {"Tutorial",ScreenWidth/2,ScreenHeight/5*3+50},
        {"Go Back",ScreenWidth/2,ScreenHeight/5*4+50}
                    };
    int noptions = 4;

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool draw, done;
    draw = true;
    done = false;

    while(!closebeg2)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(events.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    closebeg2 = true;
                    break;
                case ALLEGRO_KEY_UP:
                    pivot = Max(pivot-1,0);
                    break;
                case ALLEGRO_KEY_DOWN:
                    pivot = Min(pivot+1,noptions-1);
                    break;
                case ALLEGRO_KEY_ENTER:
                    if(pivot == 0) beg3();
                    else if(pivot == 1) CreativeMode();
                    else if(pivot == 2) Tutorial();
                    else closebeg2 = true; // pivot == 3
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
            al_draw_text(font2, DARKRED, ScreenWidth/2, ScreenHeight/5 - 100, ALLEGRO_ALIGN_CENTRE, name);

            for(int k = 0; k < noptions; ++k)
            {
                al_draw_text(font1,DARKRED,opt[k].x,opt[k].y,ALLEGRO_ALIGN_CENTRE,opt[k].name);
            }

            al_draw_text(font1,CYAN,opt[pivot].x,opt[pivot].y,ALLEGRO_ALIGN_CENTRE,opt[pivot].name);
            al_draw_bitmap(petalsWally,0,0,NULL);

            al_flip_display();
        }
    }

    al_stop_timer(timer);

    al_unregister_event_source(event_queue,al_get_timer_event_source(timer));
    al_destroy_timer(timer);
}

#endif // BEG2_H_INCLUDED
