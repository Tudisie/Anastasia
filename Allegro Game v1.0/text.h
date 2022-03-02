#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

int texty[10]; //maximum 10 lines with texty[] y coordinate
char textline[10][100]; // lined text
int held = 0;

void reset()
{
    for(int i=0; i<10; ++i)
        memset(textline[i],'\0',sizeof(textline[i]));
    held = 0;
}

inline void fade_text(char s[]) // the text is ordered in n lines
{
    reset();

    int n = 1;
    char *p = strchr(s,'*');

    while(p != NULL)
    {
        ++n;
        p = strchr(p+1,'*');
    }

    ALLEGRO_FONT *font1;
    font1 = al_load_font("fonts\\Bohemian.ttf",28,NULL);

    bool done,draw;
    done = false;
    draw = true;

    float opacity = 0;

    texty[0] = ScreenHeight/2 - al_get_font_line_height(font1)*n/2;
    for(int i=1; i<n; ++i)
        texty[i] = texty[i-1] + al_get_font_line_height(font1);

    if(n == 1)
        strcpy(textline[0],s);
    else //multiple lines
    {
        char aux[100];
        memset(aux,'\0',sizeof(aux));
        int nn = 0;

        char *pant = s;
        char *p = strchr(s,'*');
        strncpy(aux,pant, p - pant);
        while(p != NULL)
        {
            strcpy(textline[nn],aux);
            textline[nn][strlen(textline[nn])] = '\0';
            ++nn;
            pant = p;
            p = strchr(p+1,'*');

            memset(aux,'\0',sizeof(aux));

            if(p != NULL)
                strncpy(aux,pant+1, p - pant -1);
            else strcpy(aux,pant+1);
        }

        strcpy(textline[nn++],aux);
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    ALLEGRO_KEYBOARD_STATE keyState;

    char skip_text[35];
    if(language == 0) strcpy(skip_text,"Hold Z to skip the story");
        else strcpy(skip_text,"Tine apasat Z pentru a sari peste");

    while(!done && !close_story)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);
        al_get_keyboard_state(&keyState);

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            if(al_key_down(&keyState,ALLEGRO_KEY_Z)) ++held;
                else held = 0;
            draw = true;
        }
        if(draw)
        {
            draw = false;

            al_clear_to_color(al_map_rgb(12,12,12));

            for(int i=0; i<n; ++i)
                al_draw_text(font1,color(255,0,0,opacity),ScreenWidth/2 , texty[i],ALLEGRO_ALIGN_CENTER,textline[i]);

            if(held > 0)
                al_draw_text(font1,GREEN2,20, ScreenHeight - 80,ALLEGRO_ALIGN_LEFT,skip_text);
            else al_draw_text(font1,RED,20, ScreenHeight - 80,ALLEGRO_ALIGN_LEFT,skip_text);
            al_flip_display();
            opacity += 0.006;

            if(opacity > 1) done = true;
        }

        if(held >= 60) close_story = true;
    }

    char continue_text[35];
    if(language == 0)
        strcpy(continue_text,"Press ENTER to continue..");
    else
        strcpy(continue_text,"Apasa ENTER pentru a continua...");
    al_draw_text(font1,RED,ScreenWidth - 20, ScreenHeight - 80,ALLEGRO_ALIGN_RIGHT,continue_text);
    al_flip_display();

    ALLEGRO_EVENT events;

    do
    {
        al_wait_for_event(event_queue,&events);
        al_get_keyboard_state(&keyState);

        if(al_key_down(&keyState,ALLEGRO_KEY_Z)) ++held;
            else held = 0;

        al_draw_filled_rectangle(0,ScreenHeight - 100, 600, ScreenHeight,al_map_rgb(12,12,12));
        if(held > 0)
            al_draw_text(font1,GREEN2,20, ScreenHeight - 80,ALLEGRO_ALIGN_LEFT,skip_text);
        else al_draw_text(font1,RED,20, ScreenHeight - 80,ALLEGRO_ALIGN_LEFT,skip_text);

        al_flip_display();

        if(held >= 60) close_story = true;
    } while(events.keyboard.keycode != ALLEGRO_KEY_ENTER && !close_story);

    done = false;

    if(opacity > 1)
    {
        opacity = 1;
        while(!done && !close_story)
        {
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue,&events);
            al_get_keyboard_state(&keyState);

            if(events.type == ALLEGRO_EVENT_TIMER)
            {
                if(al_key_down(&keyState,ALLEGRO_KEY_Z)) ++held;
                    else held = 0;
                draw = true;
            }
            if(draw)
            {
                draw = false;

                al_clear_to_color(al_map_rgb(12,12,12));

                for(int i=0; i<n; ++i)
                    al_draw_text(font1,color(255,0,0,opacity),ScreenWidth/2 , texty[i],ALLEGRO_ALIGN_CENTER,textline[i]);

                if(held > 0)
                    al_draw_text(font1,GREEN2,20, ScreenHeight - 80,ALLEGRO_ALIGN_LEFT,skip_text);
                else al_draw_text(font1,RED,20, ScreenHeight - 80,ALLEGRO_ALIGN_LEFT,skip_text);
                al_flip_display();
                opacity -= 0.006;

                if(opacity < 0) done = true;
            }
            if(held >= 60) close_story = true;
        }
    }

    al_destroy_timer(timer);
    al_destroy_font(font1);
}

#endif // TEXT_H_INCLUDED
