//
//  Entity.h
//  Collision
//
//  Created by WuZheng on 15/3/1.
//
//

#ifndef Collision_Entity_h
#define Collision_Entity_h

#include "cocos2d.h"
#include "Const.h"
USING_NS_CC;

class Entity : public Node
{
private:
    
    int _cx;
    int _cy;
    float _xr;
    float _yr;
    float _radius;
    
    bool (*_level)[LEVEL_HEIGHT];
    
    DrawNode * _sprite;
public:
    float _xx;
    float _yy;
    float _dx;
    float _dy;
    
    void pos(float x, float y);
    static Entity * create();
    bool init();
    void update();
    void setLevel(bool (*level)[LEVEL_HEIGHT]);
    bool hasCollision(int cx, int cy);
    bool onGround();
};

#endif
