#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

void intro()
{
    char s[] = "A game created by Istrate Sebastian.";
    //fade_text(s,1);

    ALLEGRO_FONT *font1;
    font1 = al_load_font("fonts\\Bohemian.ttf",28,NULL);

    bool done,draw;
    done = false;
    draw = true;

    float opacity = 0;
    al_rest(1);

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while(!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_TIMER)
                draw = true;
        if(draw)
        {
            draw = false;

            al_clear_to_color(al_map_rgb(12,12,12));

            al_draw_text(font1,color(255,0,0,opacity),ScreenWidth/2 , ScreenHeight/2,ALLEGRO_ALIGN_CENTER,s);

            al_flip_display();
            opacity += 0.005;

            if(opacity > 1) done = true;
        }
    }

    done = false;

    if(opacity > 1)
    {
        opacity = 1;
        while(!done)
        {
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue,&events);

            if(events.type == ALLEGRO_EVENT_TIMER)
                    draw = true;
            if(draw)
            {
                draw = false;

                al_clear_to_color(al_map_rgb(12,12,12));

                al_draw_text(font1,color(255,0,0,opacity),ScreenWidth/2 , ScreenHeight/2,ALLEGRO_ALIGN_CENTER,s);

                al_flip_display();
                opacity -= 0.005;

                if(opacity < 0) done = true;
            }
        }
    }

    al_destroy_timer(timer);
    al_destroy_font(font1);
}

#endif // INTRO_H_INCLUDED
