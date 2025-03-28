#ifndef THE_BOT_FACE_hpp
#define THE_BOT_FACE_hpp

#include "../../../src/CONFIG.hpp"
#include <Arduino.h>
#include "EyesPreset.hpp"
#include "Eye.hpp"
#include "BlinkAssistant.hpp"
#include "LookAssistant.hpp"
#include "FaceBehavior.hpp"
#include "FaceExpression.hpp"

extern TheScreen theScreen;

class TheBotFace
{
public:
    TheBotFace();
    // TheBotFace(uint16_t screenWidth, uint16_t screenHeight, uint16_t eyeSize);
    void setup();
    void loop();

    void setScreenDimensions(uint16_t screenWidth, uint16_t screenHeight);
    void setEyeSize(uint16_t eyeSize);

    void DoBlink();
    void LookLeft();
    void LookRight();
    void LookFront();
    void LookTop();
    void LookBottom();
    void Wait(unsigned long milliseconds);

    bool RandomBehavior = true;
    bool RandomLook = true;
    bool RandomBlink = true;

    Eye LeftEye;
    Eye RightEye;
    BlinkAssistant Blink;
    LookAssistant Look;
    FaceBehavior Behavior;
    FaceExpression Expression;

private:
    uint16_t screenWidth;
    uint16_t screenHeight;
    uint16_t eyeSize;
    uint16_t centerX;
    uint16_t centerY;
    uint16_t eyeInterDistance = 4;
    eEmotions previousEmotion;

protected:
    void Draw();
};

#endif