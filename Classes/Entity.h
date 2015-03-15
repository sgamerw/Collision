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
public:
    static Vector<Entity *> ALL;
    float   _xx;
    float   _yy;
    float   _dx;
    float   _dy;
    float   _weight;
    bool    _repel; // 是否会被击退
    
    void pos(float x, float y);
    static Entity * create();
    bool init();
    void update();
    void setLevel(bool (*level)[LEVEL_HEIGHT]);
    bool hasCollision(int cx, int cy);
    bool onGround();
    void _register();
    void _unRegister();
    bool isClose(Entity *en);
    void setGrid(int cx, int cy);
    
private:
    int     _cx; // 所在格子的x坐标
    int     _cy; // 所在格子的y坐标
    float   _xr; // 在格子内的x位置百分比
    float   _yr; // 在格子内的y位置百分比
    float   _radius; // 半径
    float   _frict; // 摩擦力
    bool    _collidesWalls; // 是否会与墙发生碰撞
    bool    (*_level)[LEVEL_HEIGHT];
    
    DrawNode * _sprite;
};

#endif
