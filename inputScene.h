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


    InputHandle_t inputHandle;
    InputActionSetHandle_t gameplaySet;
    InputActionSetHandle_t currentGameplaySet;


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

            
    // Check contected controllers
    int numControllers = SteamInput()->GetConnectedControllers(&inputHandle);
    AXLOG(">>> %i", numControllers);

    
    scheduleUpdate();

    return true;
}


void InputScene::handleSteamInput()
{
       
}


void InputScene::testControllerIndices()
{

}


void InputScene::update(float delta)
{
    if (SteamInput())
    {
        SteamInput()->RunFrame(); // Update Steam Input state
    }


    int numControllers = SteamInput()->GetConnectedControllers(&inputHandle);
    //AXLOG(">>> %i controllers connected.", numControllers);


    // Ensure we have the correct action set handle
    gameplaySet = SteamInput()->GetActionSetHandle("ship_controls");
    if (gameplaySet != 0) {
        SteamInput()->ActivateActionSet(0, gameplaySet);
    }

    // Get the handle for the 'fire_lasers' button action (from the vdf)
    InputDigitalActionHandle_t fireAction = SteamInput()->GetDigitalActionHandle("fire_lasers");
    
    if (fireAction != 0) {
        // Get the action data (for a button action, not a trigger)
        InputDigitalActionData_t actionData = SteamInput()->GetDigitalActionData(inputHandle, fireAction);
        
        // Check if the button is pressed (bState will be true if pressed)
        if (actionData.bState) {
            AXLOG(">>> Fire button pressed!");
        }
    }
}
