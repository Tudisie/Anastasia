#ifndef TUTORIAL_H_INCLUDED
#define TUTORIAL_H_INCLUDED

void Tutorial()
{
    al_stop_sample(&idbegin);
    Run(0);
    al_stop_sample(&idmusic);
    al_play_sample(beginsong,Vmusic*1./100,0,1.0,ALLEGRO_PLAYMODE_LOOP,&idbegin);
}


#endif // TUTORIAL_H_INCLUDED
