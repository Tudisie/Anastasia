#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

char codetxt[100]; // for cheats
int len;
bool beat = false;

char difname[][10]={"","EASY","MEDIUM","HARD","INSANE"};
char langname[][10]={"English","Romanian"};
//aux
int dif,mv,ev;
bool lang;

ALLEGRO_COLOR difcolor;

struct Opening{
        char name[20];
        int x,y; //position

        Opening(char n[],int posx,int posy)
        {
           strcpy(name,n);
           x = posx;
           y = posy;
        }
    };

Opening opt[] = {
    {"Music Volume : %d",20,ScreenHeight/6 - 100},
    {"Effects Volume : %d",20,ScreenHeight/6*2 - 100},
    {"Language : %s",20,ScreenHeight/6*3 -100},
    {"Difficulty : %s",20,ScreenHeight/6*4 - 100},
    {"Code :  %s",20,ScreenHeight/6*5 - 100}
                };
int noptions = 5;

inline void Verify_Cheat()
{
    if(codetxt[0] != '\0')
        beat = true;

    if(strcmp(codetxt,"gravity") == 0)
        if(gravity == 0.25) gravity = 0.1;
            else gravity = 0.25;
    if(strcmp(codetxt,"creative") == 0)
        creative = 1 - creative;
    if(strcmp(codetxt,"godmode") == 0)
        godmode = 1,cheatgodmode = true;
    codetxt[0] = '\0';
    len = 0;
}

void Drawing2(const int& pivot)
{
    draw = false;

    al_clear_to_color(BLACK);

    al_draw_textf(font1B,OUTLINE,opt[0].x,opt[0].y,ALLEGRO_ALIGN_LEFT,opt[0].name,mv);
    al_draw_textf(font1,RED,opt[0].x,opt[0].y,ALLEGRO_ALIGN_LEFT,opt[0].name,mv);

    al_draw_textf(font1B,OUTLINE,opt[1].x,opt[1].y,ALLEGRO_ALIGN_LEFT,opt[1].name,ev);
    al_draw_textf(font1,RED,opt[1].x,opt[1].y,ALLEGRO_ALIGN_LEFT,opt[1].name,ev);

    al_draw_textf(font1B,OUTLINE,opt[2].x,opt[2].y,ALLEGRO_ALIGN_LEFT,opt[2].name,langname[lang]);
    al_draw_textf(font1,RED,opt[2].x,opt[2].y,ALLEGRO_ALIGN_LEFT,opt[2].name,langname[lang]);

    al_draw_textf(font1B,OUTLINE,opt[3].x,opt[3].y,ALLEGRO_ALIGN_LEFT,opt[3].name,difname[dif]);
    al_draw_textf(font1,RED,opt[3].x,opt[3].y,ALLEGRO_ALIGN_LEFT,opt[3].name,difname[dif]);

    al_draw_textf(font1B,OUTLINE,opt[4].x,opt[4].y,ALLEGRO_ALIGN_LEFT,opt[4].name,codetxt);
    al_draw_textf(font1,RED,opt[4].x,opt[4].y,ALLEGRO_ALIGN_LEFT,opt[4].name,codetxt);

    //pivot
    if(pivot == 0)
        al_draw_textf(font1,CYAN,opt[0].x,opt[0].y,ALLEGRO_ALIGN_LEFT,opt[0].name,mv);
    else if(pivot == 1)
        al_draw_textf(font1,CYAN,opt[1].x,opt[1].y,ALLEGRO_ALIGN_LEFT,opt[1].name,ev);
    else if(pivot == 2)
        al_draw_textf(font1,CYAN,opt[2].x,opt[2].y,ALLEGRO_ALIGN_LEFT,opt[2].name,langname[lang]);
    else if(pivot == 3)
        al_draw_textf(font1,CYAN,opt[3].x,opt[3].y,ALLEGRO_ALIGN_LEFT,opt[3].name,difname[dif]);
    else if(pivot == 4)
        al_draw_textf(font1,CYAN,opt[4].x,opt[4].y,ALLEGRO_ALIGN_LEFT,opt[4].name,codetxt);

    al_draw_bitmap(rose.bm,800,ScreenHeight - rose.h,NULL);
    char exit_txt[] = "Press ESCAPE to go back.";
    al_draw_text(fontB36,GREEN2,ScreenWidth - 20,ScreenHeight - 60, ALLEGRO_ALIGN_RIGHT,exit_txt);

    if(beat)
    {
        gif(bear,ScreenWidth - 460,160);
        gif_found(bear);
    }
}

void Options()
{
    //auxiliars
    lang = language;
    dif = Difficulty;
    mv = Vmusic;
    ev = Veffects;

    bool draw,done;
    draw = true;
    done = false;
    int pivot = 0;

    int wait = 0;

    font1 = al_load_font("fonts\\Bohemian.ttf",64,NULL);
    font1B = al_load_font("fonts\\Bohemian.ttf",66,NULL);

    ALLEGRO_TIMER *timeropt = al_create_timer(1.0/FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timeropt));
    al_start_timer(timeropt);

    while(!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);
        al_get_keyboard_state(&keyState);

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            draw = true;

            if(al_key_down(&keyState,ALLEGRO_KEY_BACKSPACE))
            {
                if(len > 0 && wait <= 0)
                        codetxt[--len] = '\0', wait = 6;
                --wait;
            }

            if(al_key_down(&keyState,ALLEGRO_KEY_LEFT))
            {
                if(wait <= 0)
                    if(pivot == 0) mv = Max(0,mv - 5), wait = 8;
                        else if(pivot == 1) ev = Max(0,ev - 5), wait = 8;
                --wait;
            }
            if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT))
            {
                if(wait <= 0)
                    if(pivot == 0) mv = Min(100,mv + 5),wait = 8;
                        else if(pivot == 1) ev = Min(100,ev + 5),wait = 8;
                --wait;
            }
        }
        else if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(events.keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN:
                    ++pivot;
                    if(pivot > noptions - 1) pivot = noptions - 1;
                    break;
                case ALLEGRO_KEY_UP:
                    --pivot;
                    if(pivot < 0) pivot = 0;
                    break;
                case ALLEGRO_KEY_TAB:
                    ++pivot;
                    if(pivot > noptions - 1) pivot = noptions - 1;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    if(pivot == 2) lang = 1-lang;
                    if(pivot == 3) dif = Min(4,dif + 1);
                    break;
                case ALLEGRO_KEY_LEFT:
                    if(pivot == 2) lang = 1-lang;
                    if(pivot == 3) dif = Max(1,dif - 1);
                    break;
                case ALLEGRO_KEY_ENTER:
                    if(pivot == 4)
                        Verify_Cheat();
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_BACKSPACE:
                    break;
                default:
                    int ch = events.keyboard.keycode;

                    if(ch == ALLEGRO_KEY_M)
                    {
                        if(pivot == 0) mv = 0;
                        if(pivot == 1) ev = 0;
                    }
                    if(pivot == 4)
                    {
                        if(ch >= ALLEGRO_KEY_A && ch <= ALLEGRO_KEY_Z)
                            codetxt[len++] = 'a' + ch - ALLEGRO_KEY_A;
                        else if(ch >= ALLEGRO_KEY_0 && ch <= ALLEGRO_KEY_9)
                            codetxt[len++] = '0' + ch - ALLEGRO_KEY_0;
                        else if(ch == ALLEGRO_KEY_SPACE)
                            codetxt[len++] = ' ';
                    }
                    codetxt[len] = '\0';
                    break;
            }

        }

        if(draw)
        {
            Drawing2(pivot);
            al_flip_display();
        }
    }


    //ExitQ & SaveQ
    int pivotq = 0,entertime = 0;
    int H,W,X1,X2,Y1,Y2;

    H = 150; W = 300;
    X1 = ScreenWidth/2- W/2 + 50;
    X2 = ScreenWidth/2+ W/2 - 50;
    Y1 = Y2 = ScreenHeight/2 + H/2 -50; // for NO and YES

    do
    {
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            Drawing2(10); // none of the options. 10 > 4

            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 12), CameraY(ScreenHeight/2 - H/2 - 12),
                                    CameraX(ScreenWidth/2 + W/2 + 12), CameraY(ScreenHeight/2 + H/2 + 12),GREY);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2 - 10), CameraY(ScreenHeight/2 - H/2 - 10),
                                    CameraX(ScreenWidth/2 + W/2 + 10), CameraY(ScreenHeight/2 + H/2 + 10),BLACK);
            al_draw_filled_rectangle(CameraX(ScreenWidth/2 - W/2), CameraY(ScreenHeight/2 - H/2),
                                    CameraX(ScreenWidth/2 + W/2), CameraY(ScreenHeight/2 + H/2),GREY);

            al_draw_text(fontB26,RED,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2 - 75),ALLEGRO_ALIGN_CENTRE,"Do you want");
            al_draw_text(fontB26,RED,CameraX(ScreenWidth/2),CameraY(ScreenHeight/2 - 40),ALLEGRO_ALIGN_CENTRE,"to save the changes?");

            al_draw_text(fontB26,RED,CameraX(X1),CameraY(Y1),ALLEGRO_ALIGN_CENTRE,"NO");
            al_draw_text(fontB26,RED,CameraX(X2),CameraY(Y2),ALLEGRO_ALIGN_CENTRE,"YES");

            if(pivotq == 0)
                al_draw_text(fontB26,CYAN,CameraX(X1),CameraY(Y1),ALLEGRO_ALIGN_CENTRE,"NO");
            else
                al_draw_text(fontB26,CYAN,CameraX(X2),CameraY(Y2),ALLEGRO_ALIGN_CENTRE,"YES");

            al_flip_display();
            al_clear_to_color(BLACK);
        }
        else if(events.keyboard.keycode == ALLEGRO_KEY_RIGHT) pivotq = 1;
        else if(events.keyboard.keycode == ALLEGRO_KEY_LEFT) pivotq = 0;
        ++entertime;
    } while(events.keyboard.keycode != ALLEGRO_KEY_ENTER || entertime <= 20);

    if(pivotq)
    {
        Difficulty = dif;
        language = lang;
        Vmusic = mv;
        Veffects = ev;
    }

    al_destroy_timer(timeropt);
    codetxt[0] = '\0';
    len = 0;

    al_stop_sample(&idbegin);
    al_play_sample(beginsong,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idbegin);
}

#endif // OPTIONS_H_INCLUDED
