#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <fstream>

bool creativemode;

short Map[200][500],FrontMap[200][500],BackMap[200][500],BackMap2[200][500],MonsterMap[200][500];
short Last[200],LastF[200],LastB[200],LastBB[200],LastM[200]; //it won't copy the ending '0's from any map
// Last[i] = j, last element from line i in Map[]  which is not equal to 0 is on j position
int Mapx; //Mapx is varying. For each line the number of elements is in Map[i][0].
int Mapy;

float MapWidth,MapHeight;

inline int Number(char *&p)
{
    int sol = 0;
    while(*p >= '0' && *p <= '9')
    {
        sol = sol*10 + *p - '0';
        ++p;
    }
    return sol;
}

/* at loading map you init the monsters, so you do't need to actualize them depending on the map*/
void LoadMap(short M[][500], int &Mx,int &My, const char *filename)
{
    int lastx;
    std::ifstream fin(filename);

    char s[3000];

    Mx = My = 0;

    if(fin.is_open())
    {
        int number;
        fin.getline(s,3000);
        while(s[0] != '\0' && s[0] != '\n')
        {
            lastx = 0;
            int n = strlen(s);
            int x = 0;

            char *p = s;
            while(*p != '\0' && s[0] != '\n')
            {
                M[My][x] = Number(p);
                if(M[My][x] != 0) lastx = x;
                while(*p == ' ') ++p;
                if(M == MonsterMap)
                {
                    if(M[My][x] == 1) //mike
                        mike.q.push_back({BLOCK_SIZE * x - mike.w/2 + 20, BLOCK_SIZE * My - mike.h + 90, 1 , 100, x, My, 0});
                    else if(M[My][x] == 2) //laica
                        laica.q.push_back({BLOCK_SIZE * x - laica.w/2 + 20, BLOCK_SIZE * My - laica.h + 90, 1 , 40, x, My, 0});
                    else if(M[My][x] == 3) //rabbit
                        rabbit.q.push_back({BLOCK_SIZE * x - rabbit.w/2 + 20, BLOCK_SIZE * My - rabbit.h + 95, 1 , 100, x, My, 0});
                    else if(M[My][x] == 4)
                        ork.q.push_back({BLOCK_SIZE * x - ork.w/2 + 20, BLOCK_SIZE * My - ork.h + 95, 1 , 60, x, My, 0});
                    else if(M[My][x] == 5)
                        flydragon.q.push_back({BLOCK_SIZE * x - flydragon.w/2 + 20, BLOCK_SIZE * My - flydragon.h + 85, 1 , 40, x, My, 0});
                    else if(M[My][x] == 6)
                        monster.q.push_back({BLOCK_SIZE * x - monster.w/2 + 20, BLOCK_SIZE * (My+1) - monster.h + 65, 1 , 1000, x, My, 0});

                }
                ++x;
            }

            if(M == Map) Last[My] = lastx;
            else if(M == BackMap) LastB[My] = lastx;
            else if(M == BackMap2) LastBB[My] = lastx;
            else if(M == FrontMap) LastF[My] = lastx;
            else LastM[My] = lastx;

            Mx = Max(Mx,lastx+1);
            fin.getline(s,3000);
            ++My;
        }
    }
    else if(creativemode && M == Map)
    {
        My = 50; Mx = 150;

        for(int i=0; i<My; ++i)
            for(int j=0; j<Mx; ++j)
                Map[i][j] = FrontMap[i][j] = BackMap[i][j] = BackMap2[i][j] = 0;

        for(int i = 0; i < 150; ++i)
            M[My-1][i] = 4;
        Last[49] = 149;
    }

    fin.close();

    MapHeight = BLOCK_SIZE * Mapy;
    MapWidth  = BLOCK_SIZE * Mapx;
}

void SaveMap(short M[][500],const int &Mx,const int &My,const char *filename)
{
    std::ofstream f("auxi.txt");

    for(int i=0; i<My; ++i)
    {
        if(M == Map)
        {
            for(int j=0; j<=Last[i]; ++j)
                f<<M[i][j]<<" ";
        }
        else if(M == FrontMap)
        {
            for(int j=0; j<=LastF[i]; ++j)
                f<<M[i][j]<<" ";
        }
        else if(M == BackMap)
        {
            for(int j=0; j<=LastB[i]; ++j)
                f<<M[i][j]<<" ";
        }
        else if(M == BackMap2)
        {
            for(int j=0; j<=LastBB[i]; ++j)
                f<<M[i][j]<<" ";
        }
        else
        {
            for(int j=0; j<=LastM[i]; ++j)
                f<<M[i][j]<<" ";
        }
        f<<"\n";
    }
    f.close();
    remove(filename);
    rename("auxi.txt",filename);
}

inline void DrawMap(short M[][500]) //without flipping display
{
    int Yi = Max(0,Anastasia.y/BLOCK_SIZE - 8);
    if(Anastasia.y + Anastasia.h >= MapHeight) //dead
        Yi -= 5;
    for(int x,y = Yi; y < Max(0,Anastasia.y/BLOCK_SIZE - 8) + 20; ++y)
        for(x = Max(0,Min(Anastasia.x/BLOCK_SIZE - 15,Mapx - 26)); x < Max(0,Anastasia.x/BLOCK_SIZE - 15) + 30; ++x)
        {
            if(M[y][x] > 0)
            if(M == Map)
            {
                if(M[y][x] <= nblocks)
                    al_draw_bitmap(Block[Map[y][x]],x*BLOCK_SIZE,y*BLOCK_SIZE,NULL);
                else if(M[y][x] == nwater)
                    gif(water,x*BLOCK_SIZE,y*BLOCK_SIZE);
            }
            else if(M == FrontMap)
                switch(M[y][x])
                {
                    case 1: al_draw_bitmap(Tree.bm, (x+1)*BLOCK_SIZE - Tree.w/2, (y+1)*BLOCK_SIZE - Tree.h + 35, NULL);
                    break;
                    case 2: al_draw_bitmap(Grass2.bm, x*BLOCK_SIZE - Grass2.w/2 + 52, y*BLOCK_SIZE - Grass2.h/2 + 34, NULL);
                    break;
                    case 3: al_draw_bitmap(DarkTree.bm, (x+1)*BLOCK_SIZE - DarkTree.w/2 - 25, (y+1)*BLOCK_SIZE - DarkTree.h + 25, NULL);
                    break;
                    case 4: gif(fire,x*BLOCK_SIZE - 20,y*BLOCK_SIZE - 20);
                    break;
                    case 5: al_draw_bitmap(Chest.bm, x*BLOCK_SIZE - 8, y*BLOCK_SIZE + 15, NULL);
                    break;
                    case 6: al_draw_bitmap(acorn.bm, x*BLOCK_SIZE + 20, y*BLOCK_SIZE + 43, NULL);
                    break;
                    case 7: al_draw_bitmap(Flower.bm, x*BLOCK_SIZE, y*BLOCK_SIZE + 25, NULL);
                    break;
                    case 8: al_draw_bitmap(Flower2.bm, x*BLOCK_SIZE, y*BLOCK_SIZE + 25, NULL);
                    break;
                    case 9: al_draw_bitmap(Skull.bm, x*BLOCK_SIZE + 20, y*BLOCK_SIZE + 30, NULL);
                    break;
                    case 10: al_draw_bitmap(Skull.bm, x*BLOCK_SIZE + 5, y*BLOCK_SIZE + 30, ALLEGRO_FLIP_HORIZONTAL);
                    break;
                    case 11: al_draw_bitmap(Mushroom.bm, x*BLOCK_SIZE+ 8, y*BLOCK_SIZE + 12, NULL);
                    break;
                    case 12: al_draw_bitmap(Apple.bm, x*BLOCK_SIZE + 14, y*BLOCK_SIZE + 30, NULL);
                    break;
                    case 13: al_draw_bitmap(Carrot.bm, x*BLOCK_SIZE + 14, y*BLOCK_SIZE + 40, NULL);
                    break;
                    case 14: al_draw_bitmap(Leaves.bm, x*BLOCK_SIZE - Leaves.w/4, y*BLOCK_SIZE + 18, NULL);
                    break;
                    case 15: al_draw_bitmap(Log.bm, x*BLOCK_SIZE - 5, y*BLOCK_SIZE + 45, NULL);
                    break;
                    case 16: al_draw_bitmap(Table.bm, x*BLOCK_SIZE - Table.w/3, y*BLOCK_SIZE, NULL);
                    break;
                    case 17: al_draw_bitmap(TreeStump.bm, x*BLOCK_SIZE - 5, y*BLOCK_SIZE, NULL);
                    break;
                    case 18: al_draw_bitmap(Well.bm, x*BLOCK_SIZE - Well.w/2 + 20, y*BLOCK_SIZE - Well.h/2 - 13, NULL);
                    break;
                }
            else if(M == BackMap)
                switch(M[y][x])
                {
                    case 1: al_draw_bitmap(Grass.bm,(x+1)*BLOCK_SIZE  - Grass.w, (y+1)*BLOCK_SIZE - Grass.h,NULL);
                    break;
                    case 2: al_draw_bitmap(Cloud.bm,x*BLOCK_SIZE - Cloud.w/2,y*BLOCK_SIZE - Cloud.h/2 + 20, NULL);
                    break;
                    case 3: gif(darkcloud, x*BLOCK_SIZE - darkcloud.w/3 , y*BLOCK_SIZE - 15);
                    break;
                    case 4: gif(darkcloud2, x*BLOCK_SIZE - darkcloud2.w/3 + 20 , y*BLOCK_SIZE - 20);
                    break;
                    case 5: gif(spider,x*BLOCK_SIZE,y*BLOCK_SIZE);
                    break;
                    case 6: gif(spider2,x*BLOCK_SIZE,(y+1)*BLOCK_SIZE - 20);
                    break;
                    case 7: al_draw_bitmap(Window.bm,x*BLOCK_SIZE - Window.w/4,y*BLOCK_SIZE - Window.h + 80, NULL);
                    break;
                    case 8: al_draw_bitmap(Clock.bm,x*BLOCK_SIZE - Clock.w/4,(y+1)*BLOCK_SIZE - Clock.h + 2, NULL);
                    break;
                    case 9: al_draw_bitmap(Clock2.bm,x*BLOCK_SIZE - Clock2.w/4,(y+1)*BLOCK_SIZE - Clock2.h + 10, NULL);
                    break;
                    case 10: al_draw_bitmap(Clock2.bm,x*BLOCK_SIZE - Clock2.w/4,(y+1)*BLOCK_SIZE - Clock2.h + 10, ALLEGRO_FLIP_HORIZONTAL);
                    break;
                    case 11: al_draw_bitmap(Hat.bm,x*BLOCK_SIZE - Hat.w/4 + 5,y*BLOCK_SIZE - 14, NULL);
                    break;
                }
            else if(M == BackMap2)
                switch(M[y][x])
                {
                    case 1: al_draw_bitmap(Spike.bm, (x+1)*BLOCK_SIZE - Spike.w - (BLOCK_SIZE - Spike.w)/2,
                                            (y+1)*BLOCK_SIZE - Spike.h, NULL);
                    break;
                    case 2: al_draw_bitmap(Spike.bm, (x+1)*BLOCK_SIZE - Spike.w - (BLOCK_SIZE - Spike.w)/2,
                                            (y+1)*BLOCK_SIZE - Spike.h - 5, ALLEGRO_FLIP_VERTICAL);
                    break;
                    case 3: gif(coin,x*BLOCK_SIZE,y*BLOCK_SIZE);
                    break;
                    case 4: gif(banana,x*BLOCK_SIZE,y*BLOCK_SIZE);
                    break;
                    case 5: gif(fly,x*BLOCK_SIZE,y*BLOCK_SIZE);
                    break;
                    case 6: gif(fly,x*BLOCK_SIZE,y*BLOCK_SIZE,1);
                    break;
                    case 7: al_draw_bitmap(Grave.bm, (x+1)*BLOCK_SIZE - Grave.w/2 - 18, (y+1)*BLOCK_SIZE - Grave.h + 5, NULL);
                    break;
                    case 8: al_draw_bitmap(Sign.bm, (x+1)*BLOCK_SIZE - Sign.w/2 - 18, (y+1)*BLOCK_SIZE - Sign.h + 5, NULL);
                    break;
                    case 9: al_draw_bitmap(Sign.bm, (x+1)*BLOCK_SIZE - Sign.w/2 - 18, (y+1)*BLOCK_SIZE - Sign.h + 5, ALLEGRO_FLIP_HORIZONTAL);
                    break;
                    case 10: al_draw_bitmap(Sign2.bm, (x+1)*BLOCK_SIZE - Sign2.w/2 - 18, (y+1)*BLOCK_SIZE - Sign2.h + 5, NULL);
                    break;
                    case 11: al_draw_bitmap(Broom.bm, (x+1)*BLOCK_SIZE - Broom.w/2 - 18, (y+1)*BLOCK_SIZE - Broom.h + 20, NULL);
                    break;
                    case 12: al_draw_bitmap(Fence.bm, x*BLOCK_SIZE, (y+1)*BLOCK_SIZE - Fence.h + 20, NULL);
                    break;
                    case 13: al_draw_bitmap(Rainbow.bm, (x+1)*BLOCK_SIZE - Rainbow.w/2 - 18, (y+1)*BLOCK_SIZE - Rainbow.h, NULL);
                    break;
                    case 14: al_draw_bitmap(Tent.bm, (x+1)*BLOCK_SIZE - Tent.w/2 - 18, (y+1)*BLOCK_SIZE - Tent.h + 35, NULL);
                    break;
                    case 15: al_draw_bitmap(Tree2.bm, (x-2)*BLOCK_SIZE - 10, (y+1)*BLOCK_SIZE - Tree2.h + 20, NULL);
                    break;
                }
        }
}

//LOADING AND SAVING ALL THE MAPS

void Loading(const int &Lmap)
{
    int aux,aux2;
    std::stringstream str;

    str<<"Maps//Map"<<Lmap<<".txt";
    LoadMap(Map,Mapx,Mapy,str.str().c_str());

    str.str("");
    str<<"Maps//MapF"<<Lmap<<".txt";
    LoadMap(FrontMap,aux,aux2,str.str().c_str());

    str.str("");
    str<<"Maps//MapB"<<Lmap<<".txt";
    LoadMap(BackMap,aux,aux2,str.str().c_str());

    str.str("");
    str<<"Maps//MapBB"<<Lmap<<".txt";
    LoadMap(BackMap2,aux,aux2,str.str().c_str());

    str.str("");
    str<<"Maps//MapM"<<Lmap<<".txt";
    LoadMap(MonsterMap,aux,aux2,str.str().c_str());
}

void Saving(const int &Lmap)
{
    std::stringstream str;
    char name[30];
    str.str("");
    str<<"Maps//Map"<<Lmap<<".txt";
    strcpy(name,str.str().c_str());
    SaveMap(Map,Mapx,Mapy,name);

    str.str("");
    str<<"Maps//MapF"<<Lmap<<".txt";
    strcpy(name,str.str().c_str());
    SaveMap(FrontMap,Mapx,Mapy,name);

    str.str("");
    str<<"Maps//MapB"<<Lmap<<".txt";
    strcpy(name,str.str().c_str());
    SaveMap(BackMap,Mapx,Mapy,name);

    str.str("");
    str<<"Maps//MapBB"<<Lmap<<".txt";
    strcpy(name,str.str().c_str());
    SaveMap(BackMap2,Mapx,Mapy,name);

    str.str("");
    str<<"Maps//MapM"<<Lmap<<".txt";
    strcpy(name,str.str().c_str());
    SaveMap(MonsterMap,Mapx,Mapy,name);
}


#endif // MAP_H_INCLUDED
