#ifndef BEG3_H_INCLUDED
#define BEG3_H_INCLUDED

inline void beg3()
{
    int pivot = 0;
    int wait = 25;
    bool chose = false;

    do
    {
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(BLACK);
            if(pivot == 0)
                al_draw_text(font1,CYAN,ScreenWidth/2,ScreenHeight/2 - 50,ALLEGRO_ALIGN_CENTRE,"Continue"),
                al_draw_text(font1,DARKRED,ScreenWidth/2,ScreenHeight/2 + 50,ALLEGRO_ALIGN_CENTRE,"New Game");
            else
                al_draw_text(font1,DARKRED,ScreenWidth/2,ScreenHeight/2 - 50,ALLEGRO_ALIGN_CENTRE,"Continue"),
                al_draw_text(font1,CYAN,ScreenWidth/2,ScreenHeight/2 + 50,ALLEGRO_ALIGN_CENTRE,"New Game");

            al_flip_display();
        }
        else if(events.keyboard.keycode == ALLEGRO_KEY_DOWN) pivot = 1;
        else if(events.keyboard.keycode == ALLEGRO_KEY_UP) pivot = 0;
        else if(events.keyboard.keycode == ALLEGRO_KEY_ENTER && wait <= 0)
        {
            chose = true;
            if(pivot == 1)
            {
                remove("Info.txt");
                std::ofstream fout("Info.txt");
                fout<<"1\n100 3 0\n0 0";
                fout.close();
            }
            Game();
        }
        else if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE && wait <= 0)
            chose = true;

        wait = Max(0,wait-1);
    } while(!chose);
}

#endif // BEG3_H_INCLUDED
