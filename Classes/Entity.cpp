//
//  Entity.cpp
//  Collision
//
//  Created by WuZheng on 15/3/1.
//
//

#include "Entity.h"
#include "Const.h"
#include "CCDrawNode.h"

Entity * Entity::create()
{
    Entity * ret = new (std::nothrow) Entity();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool Entity::init()
{
    _cx = 0;
    _cy = LEVEL_HEIGHT-1;
    _xr = 0.5;
    _yr = 0.5;
    _xx = (_cx + _xr) * GRID_SIZE;
    _yy = (_cy + _yr) * GRID_SIZE;
    _radius = 0.5 * GRID_SIZE;
    _frict = 0.85;
    _collidesWalls = true;
    
    _sprite = DrawNode::create();
    _sprite->drawDot(Vec2(_radius,_radius), _radius, Color4F::RED);
    this->addChild(_sprite);
    this->setPosition(_xx, _yy);
    return true;
}

void Entity::pos(float x, float y)
{
    _xx = x;
    _yy = y;
}

void Entity::setLevel(bool (*level)[LEVEL_HEIGHT])
{
    _level = level;
}

bool Entity::hasCollision(int cx, int cy)
{
    if (cx < 0 || cx > LEVEL_WIDTH-1 || cy < 0 || cy > LEVEL_HEIGHT-1) {
        return true;
    }
    else {
        return _level[cx][cy];
    }
}

bool Entity::onGround()
{
    return this->hasCollision(_cx, _cy-1) && (_yr<=_radius);
}

void Entity::update()
{
    float r2g = 0.9 * (_radius / GRID_SIZE); // 假设会挤压可以缩小体积
    // X component
    _xr += _dx;
    _dx = _dx*_frict;
    if (_collidesWalls) {
        if (hasCollision(_cx-1, _cy) && _xr <= r2g) {
            _dx = 0;
            _xr = r2g;
        }
        if (hasCollision(_cx+1, _cy) && _xr >= 1-r2g) {
            _dx = 0;
            _xr = 1-r2g;
        }
    }
    while (_xr > 1) {
        _cx++;
        _xr--;
    }
    while (_xr < 0) {
        _cx--;
        _xr++;
    }
    
    // Y component
//    _dy -= gravity;
    _yr += _dy;
    _dy = _dy*_frict;
    if (_collidesWalls) {
        if (hasCollision(_cx, _cy-1) && _yr <= r2g) {
            _dy = 0;
            _yr = r2g;
        }
        if (hasCollision(_cx, _cy+1) && _yr >= 1-r2g) {
            _dy = 0;
            _yr = 1-r2g;
        }
    }
    while (_yr > 1) {
        _yr--;
        _cy++;
    }
    while (_yr < 0) {
        _yr++;
        _cy--;
    }
    
    _xx = (_cx+_xr)*GRID_SIZE;
    _yy = (_cy+_yr)*GRID_SIZE;
    this->setPosition((int)_xx, (int)_yy);
}