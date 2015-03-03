#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Const.h"
#include <time.h>
#include "Entity.h"

//#define random(x) (rand()%x)

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float delta);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    
private:
    bool _level[LEVEL_WIDTH][LEVEL_HEIGHT];
    Entity * _hero;
};

#endif // __HELLOWORLD_SCENE_H__
