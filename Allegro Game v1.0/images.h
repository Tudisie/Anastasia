#ifndef IMAGES_H_INCLUDED
#define IMAGES_H_INCLUDED

#define BLOCK_SIZE 64

int nblocks = 32,ndarkblocks = 5; //the darkblocks are left to the end of the array so you are able to go through them

char blockname[33][30] ={ // nblocks + 1
"",
"img//Blocks//Box.jpg",
"img//Blocks//Box2.jpg",
"img//Blocks//Box3.jpg",
"img//Blocks//Earth.jpg",
"img//Blocks//Earth2.jpg",
"img//Blocks//Sand.jpg",
"img//Blocks//Stone1.jpg",
"img//Blocks//Stone2.jpg",
"img//Blocks//Stone3.jpg",
"img//Blocks//Stone4.jpg",
"img//Blocks//Brick.jpg",
"img//Blocks//GreyBrick.jpg",
"img//Blocks//Iron.jpg",
"img//Blocks//Iron2.jpg",
"img//Blocks//Iron3.jpg",
"img//Blocks//Wood.jpg",
"img//Blocks//Temple2.jpg",
"img//Blocks//Temple.jpg",
"img//Blocks//Lava.jpg",
"img//Blocks//Lava2.jpg",
"img//Blocks//Crystal.jpg",
"img//Blocks//Chess.jpg",
"img//Blocks//Ice.jpg",
"img//Blocks//Snow.jpg",
"img//Blocks//Grass.jpg",
"img//Blocks//Edge.jpg",
"img//Blocks//Edge2.jpg",
"img//Blocks//DarkTemple.jpg",
"img//Blocks//DarkEarth.jpg",
"img//Blocks//DarkBrick.jpg",
"img//Blocks//DarkStone.jpg",
"img//Blocks//DarkStone2.jpg"
};

int nwater = 33;
ALLEGRO_BITMAP *Cursor, *Block[40];

struct BULLET{
        float x,y;
        float time;
        int dir;
};

struct Obj{
    float x,y;
    float hp;
    int coins;
    int bullets;
    int h,w; // height and width of bitmap
    ALLEGRO_BITMAP *bm[54];
    ALLEGRO_BITMAP *bul;

    std::vector<BULLET> q;

    Obj()
    {
        hp = 100.0;
        bullets = 3;
        coins = 0;
    }

} Anastasia;

ALLEGRO_BITMAP *petalsWally,*icon;

struct Texture{
    ALLEGRO_BITMAP *bm;
    int w,h;
};

Texture img[10];
Texture Mountain;
Texture Tree,DarkTree,Grass,Grass2,Sun,Moon,rose,Spike,Cloud,Grave,Chest,acorn,Spell;
Texture Skull,Window,Sign,Sign2,Flower,Flower2,Board,BoardR,Mushroom;
Texture Apple,Carrot,Broom,Clock,Clock2,Fence,Hat,Leaves,Log,Rainbow,Table,Tent,Tree2,TreeStump,Well,Blood;

struct GIF{
    bool found; //if the gif is found on the map more than once, its bitmaps wouldn't change faster.
    ALLEGRO_BITMAP *bm[48];
    int w,h;
    float time,ntime; // after 'time' timer events, the frame will change, remained 'ntime' timer events to be done
    int k,n; //current image, n images

};

struct posbm{
        float x,y;
        int dir;
        float hp;
        int mapx,mapy; // location on Map[][]
        int affected;
};

struct MOVING_GIF{ //individual gifs
    int w,h;
    ALLEGRO_BITMAP *bm[25];
    float time,ntime;
    bool found;
    int k,n;

    std::vector<posbm> q;
};

MOVING_GIF mike,laica,rabbit,ork,flydragon,monster;

GIF fall,coin,banana,fly,water,spider,spider2,darkcloud,darkcloud2,fire,rain,bear;

inline void load_gif(GIF &g,char *name,int n,int t)
{
    g.n = n;
    g.time = g.ntime = t;
    g.k = 0;
    for(int i=0; i < n; ++i)
    {
        std::stringstream str;
        str<<"img//"<<name<<"//"<<name<<"-"<<i<<".png";
        g.bm[i]  = al_load_bitmap(str.str().c_str());
    }
    g.w = al_get_bitmap_width(g.bm[0]);
    g.h = al_get_bitmap_height(g.bm[0]);
}

inline void load_gif2(GIF &g,char *name,int n,int t) //for spider2, images are named -0,2,4...
{
    g.n = n;
    g.time = g.ntime = t;
    g.k = 0;
    for(int i=0; i < n; ++i)
    {
        std::stringstream str;
        str<<"img//"<<name<<"//"<<name<<"-"<<i*2<<".png";
        g.bm[i]  = al_load_bitmap(str.str().c_str());
    }
    g.w = al_get_bitmap_width(g.bm[0]);
    g.h = al_get_bitmap_height(g.bm[0]);
}



void TextureLoad()
{
    petalsWally = al_load_bitmap("img//PetalsWall.png");
    Anastasia.bul = al_load_bitmap("img//Bullet.png");

    icon = al_load_bitmap("img//icon.png");

    Cloud.bm = al_load_bitmap("img//Cloud.png");
    Cloud.h = al_get_bitmap_height(Cloud.bm);
    Cloud.w = al_get_bitmap_width(Cloud.bm);

    rose.bm = al_load_bitmap("img//Rose2.png");
    rose.w = al_get_bitmap_width(rose.bm);
    rose.h = al_get_bitmap_height(rose.bm);

    Tree.bm = al_load_bitmap("img//Tree.png");
    Tree.w = al_get_bitmap_width(Tree.bm);
    Tree.h = al_get_bitmap_height(Tree.bm);

    DarkTree.bm = al_load_bitmap("img//DarkTree.png");
    DarkTree.w = al_get_bitmap_width(DarkTree.bm);
    DarkTree.h = al_get_bitmap_height(DarkTree.bm);

    Spell.bm = al_load_bitmap("img//Spell2.png");
    Spell.w = al_get_bitmap_width(Spell.bm);
    Spell.h = al_get_bitmap_height(Spell.bm);

    Grave.bm = al_load_bitmap("img//Grave.png");
    Grave.w = al_get_bitmap_width(Grave.bm);
    Grave.h = al_get_bitmap_height(Grave.bm);

    Mushroom.bm = al_load_bitmap("img//Mushroom.png");
    Mushroom.w = al_get_bitmap_width(Mushroom.bm);
    Mushroom.h = al_get_bitmap_height(Mushroom.bm);

    Board.bm = al_load_bitmap("img//Board.png");
    Board.w = al_get_bitmap_width(Board.bm);
    Board.h = al_get_bitmap_height(Board.bm);

    BoardR.bm = al_load_bitmap("img//BoardR.png");
    BoardR.w = al_get_bitmap_width(BoardR.bm);
    BoardR.h = al_get_bitmap_height(BoardR.bm);

    Chest.bm = al_load_bitmap("img//Chest.png");
    Chest.w = al_get_bitmap_width(Chest.bm);
    Chest.h = al_get_bitmap_height(Chest.bm);

    Grass.bm = al_load_bitmap("img//Grass.png");
    Grass.w = al_get_bitmap_width(Grass.bm);
    Grass.h = al_get_bitmap_height(Grass.bm);

    Grass2.bm = al_load_bitmap("img//Grass2.png");
    Grass2.w = al_get_bitmap_width(Grass2.bm);
    Grass2.h = al_get_bitmap_height(Grass2.bm);

    acorn.bm = al_load_bitmap("img//acorn.png");
    acorn.w = al_get_bitmap_width(acorn.bm);
    acorn.h = al_get_bitmap_height(acorn.bm);

    Sun.bm = al_load_bitmap("img//Sun.png");
    Moon.bm = al_load_bitmap("img//Moon.png");

    Spike.bm = al_load_bitmap("img//Spike.png");
    Spike.h = al_get_bitmap_height(Spike.bm);
    Spike.w = al_get_bitmap_width(Spike.bm);

    Skull.bm = al_load_bitmap("img//Skull.png");
    Skull.w = al_get_bitmap_width(Skull.bm);
    Skull.h = al_get_bitmap_height(Skull.bm);

    Window.bm = al_load_bitmap("img//Window.png");
    Window.w = al_get_bitmap_width(Window.bm);
    Window.h = al_get_bitmap_height(Window.bm);

    Sign.bm = al_load_bitmap("img//Sign.png");
    Sign.w = al_get_bitmap_width(Sign.bm);
    Sign.h = al_get_bitmap_height(Sign.bm);

    Sign2.bm = al_load_bitmap("img//Sign2.png");
    Sign2.w = al_get_bitmap_width(Sign2.bm);
    Sign2.h = al_get_bitmap_height(Sign2.bm);

    Flower.bm = al_load_bitmap("img//Flower.png");
    Flower.w = al_get_bitmap_width(Flower.bm);
    Flower.h = al_get_bitmap_height(Flower.bm);

    Flower2.bm = al_load_bitmap("img//Flower2.png");
    Flower2.w = al_get_bitmap_width(Flower2.bm);
    Flower2.h = al_get_bitmap_height(Flower2.bm);

    Apple.bm = al_load_bitmap("img//Apple.png");
    Apple.w = al_get_bitmap_width(Apple.bm);
    Apple.h = al_get_bitmap_height(Apple.bm);

    Carrot.bm = al_load_bitmap("img//Carrot.png");
    Carrot.w = al_get_bitmap_width(Carrot.bm);
    Carrot.h = al_get_bitmap_height(Carrot.bm);

    Broom.bm = al_load_bitmap("img//Broom.png");
    Broom.w = al_get_bitmap_width(Broom.bm);
    Broom.h = al_get_bitmap_height(Broom.bm);

    Clock2.bm = al_load_bitmap("img//Clock2.png");
    Clock2.w = al_get_bitmap_width(Clock2.bm);
    Clock2.h = al_get_bitmap_height(Clock2.bm);

    Clock.bm = al_load_bitmap("img//Clock.png");
    Clock.w = al_get_bitmap_width(Clock.bm);
    Clock.h = al_get_bitmap_height(Clock.bm);

    Fence.bm = al_load_bitmap("img//Fence.png");
    Fence.w = al_get_bitmap_width(Fence.bm);
    Fence.h = al_get_bitmap_height(Fence.bm);

    Hat.bm = al_load_bitmap("img//Hat.png");
    Hat.w = al_get_bitmap_width(Hat.bm);
    Hat.h = al_get_bitmap_height(Hat.bm);

    Leaves.bm = al_load_bitmap("img//Leaves.png");
    Leaves.w = al_get_bitmap_width(Leaves.bm);
    Leaves.h = al_get_bitmap_height(Leaves.bm);

    Log.bm = al_load_bitmap("img//Log.png");
    Log.w = al_get_bitmap_width(Log.bm);
    Log.h = al_get_bitmap_height(Log.bm);

    Rainbow.bm = al_load_bitmap("img//Rainbow.png");
    Rainbow.w = al_get_bitmap_width(Rainbow.bm);
    Rainbow.h = al_get_bitmap_height(Rainbow.bm);

    Table.bm = al_load_bitmap("img//Table.png");
    Table.w = al_get_bitmap_width(Table.bm);
    Table.h = al_get_bitmap_height(Table.bm);

    Tent.bm = al_load_bitmap("img//Tent.png");
    Tent.w = al_get_bitmap_width(Tent.bm);
    Tent.h = al_get_bitmap_height(Tent.bm);

    Tree2.bm = al_load_bitmap("img//Tree2.png");
    Tree2.w = al_get_bitmap_width(Tree2.bm);
    Tree2.h = al_get_bitmap_height(Tree2.bm);

    TreeStump.bm = al_load_bitmap("img//TreeStump.png");
    TreeStump.w = al_get_bitmap_width(TreeStump.bm);
    TreeStump.h = al_get_bitmap_height(TreeStump.bm);

    Well.bm = al_load_bitmap("img//Well.png");
    Well.w = al_get_bitmap_width(Well.bm);
    Well.h = al_get_bitmap_height(Well.bm);

    Blood.bm = al_load_bitmap("img//Blood.png");

    //walls
    Mountain.bm = al_load_bitmap("img//Walls//Mountain.png");
    Mountain.w = al_get_bitmap_width(Mountain.bm);
    Mountain.h = al_get_bitmap_height(Mountain.bm);
}

inline void LoadingSprite(MOVING_GIF &g,int NN,int TIME,const char aux[]) // number of images of g creature, time per frame, folder name
{
    g.n = NN;
    g.found = false;
    g.ntime = g.time = TIME;

    for(int i=0; i<g.n; ++i)
    {
        std::stringstream str;
        str << "img//Creatures//"<<aux<<"//"<<aux<<"-"<<i<<".png";
        g.bm[i]  = al_load_bitmap(str.str().c_str());
    }
    g.w = al_get_bitmap_width(g.bm[0]);
    g.h = al_get_bitmap_height(g.bm[0]);
}

void load_images()
{
    //Loading stuff for Anastasia
    for(int i=1; i<=53; ++i)
    {
        std::stringstream str;
        str << "AnastasiaR/"<< i<<".png";
        Anastasia.bm[i]  = al_load_bitmap(str.str().c_str());
    }

    Anastasia.h = al_get_bitmap_height(Anastasia.bm[1]);
    Anastasia.w = al_get_bitmap_width(Anastasia.bm[1]);

    //Loading Elementar stuff
    Cursor = al_load_bitmap("img//Cursor.png");

    //Loading texture

    for(int i=1; i<=nblocks; ++i)
        Block[i] = al_load_bitmap(blockname[i]);

    TextureLoad();

    load_gif(fall,"Fall",25,6);
    load_gif(bear,"Bear",14,4);
    load_gif(coin,"Coin",4,35);
    load_gif(darkcloud,"DarkCloud",4,35);
    load_gif(darkcloud2,"DarkCloud2",11,10);
    load_gif(spider,"Spider",48,5);
    load_gif2(spider2,"Spider2",45,8);
    load_gif(banana,"Banana",8,10);
    load_gif(fly,"Fly",8,10);
    load_gif(fire,"Fire1",15,10);
    load_gif(rain,"Rain",8,7);

    water.n = 5;
    water.time = water.ntime = 10;
    water.k = 0;
    for(int i=0; i<water.n; ++i)
    {
        std::stringstream str;
        str << "img//Blocks//Water//Water-"<<i<<".png";
        water.bm[i]  = al_load_bitmap(str.str().c_str());
    }


    LoadingSprite(mike,21,4,"Mike");
    LoadingSprite(laica,6,8,"Laica");
    LoadingSprite(rabbit,11,6,"Rabbit");
    LoadingSprite(ork,16,4,"Ork");
    LoadingSprite(flydragon,8,4,"FlyDragon");
    LoadingSprite(monster,17,4,"Monster");
}

inline void fall_gif() //appealing fall frames
{
    --fall.ntime;
    if(fall.ntime <= 0)
    {
        fall.ntime = fall.time;
        ++fall.k;
        if(fall.k >= fall.n)
            fall.k = 0;
    }
    al_draw_bitmap(fall.bm[fall.k],100,ScreenHeight - fall.h, NULL);
}


inline void gif(GIF &g,const int &x, const int &y,const int &flipped = 0)// flipped = 0, no flip, 1- horizontal.
{
    if(g.ntime <= 0)
    {
        g.ntime = g.time;
        ++g.k;
        if(g.k >= g.n)
            g.k = 0;
    }
    g.found = true;
    int flag = (flipped == 0 ? NULL : ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(g.bm[g.k],x,y, flag);
}

inline void gif_found(GIF &g)
{
    if(g.found)
    {
        g.found = false;
        --g.ntime;
    }
}

#endif // IMAGES_H_INCLUDED
