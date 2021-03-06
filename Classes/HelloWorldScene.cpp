#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. create level grid
    for (int x = 0; x < LEVEL_WIDTH; x++) {
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            if( y == 0 || (y < LEVEL_HEIGHT-2 && random(1, 100) < 30) ){
                _level[x][y] = true;
                DrawNode *block = DrawNode::create();
                block->drawSolidRect(Vec2(0,0), Vec2(GRID_SIZE, GRID_SIZE), Color4F::GRAY);
                block->setPosition(origin.x+x*GRID_SIZE + GRID_SIZE/2, origin.y+y*GRID_SIZE + GRID_SIZE/2);
                addChild(block);
            }
            else {
                _level[x][y] = false;
                DrawNode *block = DrawNode::create();
                block->drawSolidRect(Vec2(0,0), Vec2(GRID_SIZE, GRID_SIZE), Color4F::WHITE);
                block->setPosition(origin.x+x*GRID_SIZE + GRID_SIZE/2, origin.y+y*GRID_SIZE + GRID_SIZE/2);
                addChild(block);
            }
        }
    }
    
    //////////////////////
    // 3.create hero
    _hero = Entity::create();
    _hero->setLevel(_level);
    this->addChild(_hero);
    
    // 4.create other entities
    Entity *en = Entity::create();
    en->setLevel(_level);
    en->setGrid(1, LEVEL_HEIGHT - 2);
    this->addChild(en);
    
    scheduleUpdate();
    
//    setTouchEnabled(true);
//    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    auto listener = _keyboardListener->create();
    listener->onKeyPressed = []( EventKeyboard::KeyCode keyCode, Event *event ){
        auto hero = static_cast<Entity *>( event->getCurrentTarget() );
        float speed = 0.4;
        if ( keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ) {
            hero->_dy += speed;
        }else if ( keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ) {
            hero->_dy -= speed;
        }else if ( keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ) {
            hero->_dx += speed;
        }else if ( keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ) {
            hero->_dx -= speed;
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority( listener, _hero );
    
    return true;
}

//bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
//{
//    
//    Vec2 p = touch->getLocation();
//    float speed = 0.4;
//    if (p.x > _hero->_xx) {
//        _hero->_dx += speed;
//    }
//    else{
//        _hero->_dx -= speed;
//    }
//    if (p.y > _hero->_yy) {
//        _hero->_dy += speed;
//    }
//    else{
//        _hero->_dy -= speed;
//    }
//    return true;
//}

void HelloWorld::update(float delta)
{
    for (Vector<Entity*>::iterator itor = Entity::ALL.begin(); itor!=Entity::ALL.end(); itor++) {
        (*itor)->update();
    }
}

void HelloWorld::createEntities(int num)
{
    for (int i = 0; i < num; i++) {
        Entity * ent = Entity::create();
        ent->setLevel(_level);
        addChild(ent);
    }
}