#ifndef ENDING_H_INCLUDED
#define ENDING_H_INCLUDED

void ending()
{
    for(int i=0; i<53; ++i)
        al_destroy_bitmap(Anastasia.bm[i]);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    al_destroy_font(fontB26);
    al_destroy_font(font1);
    al_destroy_font(font1B);
    al_destroy_font(font2);

    al_destroy_sample(beginsong);
}

#endif // ENDING_H_INCLUDED
