#ifndef CAMERAEFFECTS_H_INCLUDED
#define CAMERAEFFECTS_H_INCLUDED

float cameraPositionX,cameraPositionY;

void CameraUpdate() //cameraPositionXY function by Anastasia
{
    cameraPositionX =  -(ScreenWidth/2) + Anastasia.x + Anastasia.w/2;
    cameraPositionY = -(ScreenHeight/2) + Anastasia.y + Anastasia.h/2;

    if(cameraPositionX < 0) cameraPositionX = 0;
    if(cameraPositionY < 0) cameraPositionY = 0;

    if(cameraPositionX > MapWidth - ScreenWidth) cameraPositionX = MapWidth - ScreenWidth;
    if(cameraPositionY > MapHeight - ScreenHeight) cameraPositionY = MapHeight - ScreenHeight;
}

inline int CameraX(int x) //element's coordonate x adjusted depending on the Camera
{
    return cameraPositionX + x;
}

inline int CameraY(int y) //element's coordonate y adjusted depending on the Camera
{
    return cameraPositionY + y;
}

#endif // CAMERAEFFECTS_H_INCLUDED
