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


class SteamInputScene: public ax::Scene
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

    InputHandle_t inputHandle;
    InputAnalogActionHandle_t inputAnalogueHandle = 1;
    InputDigitalActionHandle_t inputDigitalActionHandle = 2;

    Sprite* spriteA;

private:
    entt::registry registry;
};


bool SteamInputScene::init()
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
    SteamInput()->RunFrame();       // IMPORTANT: RunFrame() or it wont synchronize to detect controls
    InputHandle_t *inputHandles = new InputHandle_t[ STEAM_INPUT_MAX_COUNT ];
    auto connectedControls = SteamInput()->GetConnectedControllers( inputHandles );
    if (connectedControls > 0) { inputHandle = inputHandles[0]; }
    else { ">>> No connected controls found"; }

    spriteA = Sprite::create("HelloWorld.png");
    spriteA->setPosition(visibleSize/2);
    addChild(spriteA);

    scheduleUpdate();
    
    return true;
}



void SteamInputScene::update(float delta)
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
            // Apply basic vibration (main motors)
            SteamInput()->TriggerVibration(inputHandle, 10000, 10000);
            // There are more types like TriggerVibrationExtended(...) that sets rumble on the triggers motors too, etc...
            AXLOG("X fired");     
        }
        else
        {
            SteamInput()->TriggerVibration(inputHandle, 0, 0);
        }
    }
    
}
