#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#define BLACK al_map_rgb(0,0,0)
#define WHITE al_map_rgb(255,255,255)
#define YELLOW al_map_rgb(255,255,0)
#define CYAN al_map_rgb(58,222,255)
#define GREY al_map_rgb(54,55,56)
#define RED al_map_rgb(255,0,0)
#define DARKRED al_map_rgb(160,0,24)
#define BRIGHT_SKY al_map_rgb(135,206,235)
#define OUTLINE al_map_rgb(0,0,0)
#define GREEN2 al_map_rgb(13,132,0)

inline ALLEGRO_COLOR color(float R,float G,float B,float op)
{
    return al_map_rgba(R*op,G*op,B*op,op);
}

#endif // COLOR_H_INCLUDED
