#include "TheBotFace.hpp"

TheBotFace::TheBotFace() : LeftEye(*this), RightEye(*this), Blink(*this), Look(*this), Behavior(*this), Expression(*this)
{
    Serial.println("TheBotFace()");
    /*this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    centerX = screenWidth / 2;
    centerY = screenHeight / 2;
    this->eyeSize = eyeSize;*/
    LeftEye.IsMirrored = true;
    Behavior.Clear();
    Behavior.Timer.Start();
    previousEmotion = eEmotions::EMOTIONS_COUNT;
}

void TheBotFace::setScreenDimensions(uint16_t screenWidth, uint16_t screenHeight)
{
    Serial.println("TheBotFace setScreenDimensions");
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    centerX = screenWidth / 2;
    centerY = screenHeight / 2;
}

void TheBotFace::setEyeSize(uint16_t eyeSize)
{
    Serial.println("TheBotFace setEyeSize");
    this->eyeSize = eyeSize;
}

void TheBotFace::setup()
{
    Serial.println("TheBotFace setup");
}

void TheBotFace::LookFront()
{
    Look.LookAt(0.0, 0.0);
}

void TheBotFace::LookRight()
{
    Look.LookAt(-1.0, 0.0);
}

void TheBotFace::LookLeft()
{
    Look.LookAt(1.0, 0.0);
}

void TheBotFace::LookTop()
{
    Look.LookAt(0.0, 1.0);
}

void TheBotFace::LookBottom()
{
    Look.LookAt(0.0, -1.0);
}

void TheBotFace::Wait(unsigned long milliseconds)
{
    unsigned long start;
    start = millis();
    while (millis() - start < milliseconds)
    {
        Draw();
    }
}

void TheBotFace::DoBlink()
{
    Blink.Blink();
}

void TheBotFace::loop()
{
    if (RandomBehavior)
        Behavior.Update();
    if (RandomLook)
        Look.Update();
    if (RandomBlink)
        Blink.Update();
    Draw();
}

void TheBotFace::Draw()
{
    // Clear the display
    theScreen.clear();
    // Draw left eye
    LeftEye.CenterX = centerX - eyeSize / 2 - eyeInterDistance;
    LeftEye.CenterY = centerY;
    LeftEye.Draw();
    // Draw right eye
    RightEye.CenterX = centerX + eyeSize / 2 + eyeInterDistance;
    RightEye.CenterY = centerY;
    RightEye.Draw();

    if (previousEmotion != Behavior.CurrentEmotion)
    {
        previousEmotion = Behavior.CurrentEmotion;
        uint8_t zz = (uint8_t)previousEmotion;
        String zzText = "";
        switch (zz)
        {
        case eEmotions::Angry:
            zzText = "Angry";
            break;
        case eEmotions::Annoyed:
            zzText = "Annoyed";
            break;
        case eEmotions::Awe:
            zzText = "Awe";
            break;
        case eEmotions::Focused:
            zzText = "Focused";
            break;
        case eEmotions::Frustrated:
            zzText = "Frustrated";
            break;
        case eEmotions::Furious:
            zzText = "Furious";
            break;
        case eEmotions::Glee:
            zzText = "Glee";
            break;
        case eEmotions::Happy:
            zzText = "Happy";
            break;
        case eEmotions::Normal:
            zzText = "Normal";
            break;
        case eEmotions::Sad:
            zzText = "Sad";
            break;
        case eEmotions::Scared:
            zzText = "Scared";
            break;
        case eEmotions::Skeptic:
            zzText = "Skeptic";
            break;
        case eEmotions::Sleepy:
            zzText = "Sleepy";
            break;
        case eEmotions::Squint:
            zzText = "Squint";
            break;
        case eEmotions::Surprised:
            zzText = "Surprised";
            break;
        case eEmotions::Suspicious:
            zzText = "Suspicious";
            break;
        case eEmotions::Unimpressed:
            zzText = "Unimpressed";
            break;
        case eEmotions::Worried:
            zzText = "Worried";
            break;
        }
        Serial.println(zzText);
    }
    theScreen.draw();
}
