/*
 * Input test scene.
 * 
 * In this scene we learn of to implement input coming from a keyboard and a gamepad.
 * 
 */
#pragma once
#include "axmol.h"

#include "steam/steam_api.h"
#include "steam/isteaminput.h"
#include <chrono>

USING_NS_AX;


class InputScene: public ax::Scene
{
    enum class GameState
    {
        init = 0,
        update,
        pause,
        end,
        menu1,
        menu2,
    };
    
public:
    bool init() override;
    void update(float delta) override;

    void handleSteamInput();
    void testControllerIndices();

    // Keyboard
    void onKeyPressed(ax::EventKeyboard::KeyCode code, ax::Event* event);
    void onKeyReleased(ax::EventKeyboard::KeyCode code, ax::Event* event);

    InputHandle_t inputHandle = 0;
    InputAnalogActionHandle_t inputAnalogueHandle = 1;
    InputDigitalActionHandle_t inputDigitalActionHandle = 2;

    Sprite* spriteA;

private:
    entt::registry registry;
};


bool InputScene::init()
{
   
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin      = _director->getVisibleOrigin();
    auto safeArea    = _director->getSafeAreaRect();
    auto safeOrigin  = safeArea.origin;

    // IMPORTANT: RUN THIS TWO LINES BEFORE ANYTHING
    SteamInput()->RunFrame();
    int numControllers = SteamInput()->GetConnectedControllers(&inputHandle);
    AXLOG("Connected controllers: %i", numControllers);
    // without it this it won't connect the controller (that's a terrible function name as it leads to think that 
    // it just gets the connected controls. Also, not running GetConnectController() at the beginning make spriteA
    // nullptr in the loop... WTF????) 
   
    spriteA = Sprite::create("HelloWorld.png");
    spriteA->setPosition(visibleSize/2);
    addChild(spriteA);

    scheduleUpdate();
    
    return true;
}

void InputScene::update(float delta)
{
    static float posXTest = 0.0;        // Quick static var for testing
    spriteA->setPositionX(posXTest);

    SteamInput()->RunFrame(); // Update Steam Input state
    
    auto actionSetHandle = SteamInput()->GetActionSetHandle("ship_controls");
    
    auto fireActionHndl =  SteamInput()->GetDigitalActionHandle("fire_lasers");

    if (fireActionHndl)
    {
        auto fireActionData = SteamInput()->GetDigitalActionData(inputHandle, fireActionHndl);
        if (fireActionData.bState)
        {
            posXTest += delta * 20;
            AXLOG("X fired");     
        }
    }
    
}
