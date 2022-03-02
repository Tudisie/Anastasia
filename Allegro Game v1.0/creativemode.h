#ifndef CREATIVEMODE_H_INCLUDED
#define CREATIVEMODE_H_INCLUDED

char name[] = "Anastasia";
int noptions2 = 5;
int pivot = 0;

struct Opening2{
        char name[10];
        int x,y; //position

        Opening2(char n[],int posx,int posy)
        {
           strcpy(name,n);
           x = posx;
           y = posy;
        }
    };

Opening2 opt2[] = {
        {"Save01",ScreenWidth/2,ScreenHeight/6+50},
        {"Save02",ScreenWidth/2,ScreenHeight/6*2+50},
        {"Save03",ScreenWidth/2,ScreenHeight/6*3+50},
        {"Delete Saves",ScreenWidth/2,ScreenHeight/6*4+50},
        {"Go back",ScreenWidth/2,ScreenHeight/6*5+50}
                    };

inline void reset_maps()
{
    remove("Maps//Map997.txt");
    remove("Maps//MapF997.txt");
    remove("Maps//MapB997.txt");
    remove("Maps//MapBB997.txt");
    remove("Maps//MapM997.txt");

    remove("Maps//Map998.txt");
    remove("Maps//MapF998.txt");
    remove("Maps//MapB998.txt");
    remove("Maps//MapBB998.txt");
    remove("Maps//MapM998.txt");

    remove("Maps//Map999.txt");
    remove("Maps//MapF999.txt");
    remove("Maps//MapB999.txt");
    remove("Maps//MapBB999.txt");
    remove("Maps//MapM999.txt");

    std::ofstream fout("positionscreative.txt");
    fout<<"200 2907 0 0\n";
    fout<<"200 2907 0 0\n";
    fout<<"200 2907 0 0\n";
    fout.close();
}

inline void DrawingC()
{
    draw = false;

    al_clear_to_color(BLACK);
    al_draw_bitmap(rose.bm,50,ScreenHeight - rose.h,NULL);
    al_draw_text(font2, DARKRED, ScreenWidth/2, ScreenHeight/5 - 100, ALLEGRO_ALIGN_CENTRE, name);

    for(int k = 0; k < noptions2; ++k)
    {
        al_draw_text(font1,DARKRED,opt2[k].x,opt2[k].y,ALLEGRO_ALIGN_CENTRE,opt2[k].name);
    }
    al_draw_text(font1,CYAN,opt2[pivot].x,opt2[pivot].y,ALLEGRO_ALIGN_CENTRE,opt2[pivot].name);
    al_draw_bitmap(petalsWally,0,0,NULL);
}

bool AskQ()
{
    //Are you sure.You want to exit the game?
    int pivot = 0,entertime = 0;
    int X1,X2,Y1,Y2,W,H;

    H = 150; W = 450;
    X1 = ScreenWidth/2- W/2 + 50;
    X2 = ScreenWidth/2+ W/2 - 50;
    Y1 = Y2 = ScreenHeight/2 + H/2 -50; // for NO and YES

    do
    {
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            DrawingC();

            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 12), CameraY(ScreenHeight/2 - H/2 - 12),
                                    CameraX(ScreenWidth/2 + W/2 + 12), CameraY(ScreenHeight/2 + H/2 + 12),GREY);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 10), CameraY(ScreenHeight/2 - H/2 - 10),
                                    CameraX(ScreenWidth/2 + W/2 + 10), CameraY(ScreenHeight/2 + H/2 + 10),BLACK);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2), CameraY(ScreenHeight/2 - H/2),
                                    CameraX(ScreenWidth/2 + W/2), CameraY(ScreenHeight/2 + H/2),GREY);

            al_draw_text(fontB26,RED,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2 - 80),ALLEGRO_ALIGN_CENTRE,"Are you sure");
            al_draw_text(fontB26,RED,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2 - 40),ALLEGRO_ALIGN_CENTRE,"you want to delete the saves?");

            al_draw_text(fontB26,RED,CameraX(X1),CameraY(Y1),ALLEGRO_ALIGN_CENTRE,"NO");
            al_draw_text(fontB26,RED,CameraX(X2),CameraY(Y2),ALLEGRO_ALIGN_CENTRE,"YES");

            if(pivot == 0)
                al_draw_text(fontB26,CYAN,CameraX(X1),CameraY(Y1),ALLEGRO_ALIGN_CENTRE,"NO");
            else
                al_draw_text(fontB26,CYAN,CameraX(X2),CameraY(Y2),ALLEGRO_ALIGN_CENTRE,"YES");

            al_flip_display();
        }
        else if(events.keyboard.keycode == ALLEGRO_KEY_RIGHT) pivot = 1;
        else if(events.keyboard.keycode == ALLEGRO_KEY_LEFT) pivot = 0;
        ++entertime;
    } while(events.keyboard.keycode != ALLEGRO_KEY_ENTER || entertime <= 20);

    return pivot;
}

void CreativeMode()
{
    Mapx = Mapy = 0;
    creativemode = creative = true;
    Anastasia.bullets = 99;
    Anastasia.coins = 0;

    LevelColor = BRIGHT_SKY;
    celest = Sun.bm;

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool draw, done;
    draw = true;
    done = false;

    while(creativemode)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(events.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    creativemode = false;
                    break;
                case ALLEGRO_KEY_UP:
                    pivot = Max(pivot-1,0);
                    break;
                case ALLEGRO_KEY_DOWN:
                    pivot = Min(pivot+1,noptions2-1);
                    break;
                case ALLEGRO_KEY_ENTER:
                    if(pivot == 0)
                    {
                        al_stop_timer(timer);
                        Run(997);
                        al_start_timer(timer);
                    }
                    else if(pivot == 1)
                    {
                        al_stop_timer(timer);
                        Run(998);
                        al_start_timer(timer);
                    }
                    else if(pivot == 2)
                    {
                        al_stop_timer(timer);
                            Run(999);
                        al_start_timer(timer);
                    }
                    else if(pivot == 3)
                    {
                        //char q[] = "Are you sure*you want to delete the saves?";
                        while(al_drop_next_event(event_queue));
                        if(AskQ()) reset_maps();
                    }
                    else creativemode = false; // pivot = 4
                    break;
            }
        }
        else if(events.type == ALLEGRO_EVENT_TIMER)
            draw = true;

        if(draw)
        {
            DrawingC();
            al_flip_display();
        }
    }

    creative = false;
    al_stop_timer(timer);

    al_unregister_event_source(event_queue,al_get_timer_event_source(timer));
    al_destroy_timer(timer);
}


#endif // CREATIVEMODE_H_INCLUDED
