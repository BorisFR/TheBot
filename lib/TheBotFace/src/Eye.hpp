/***************************************************
Copyright (c) 2020 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#ifndef _EYE_h
#define _EYE_h

#include <Arduino.h>
#include "Animations.hpp"
#include "EyeConfig.hpp"
#include "EyeDrawer.hpp"
#include "EyeTransition.hpp"
#include "EyeTransformation.hpp"
#include "EyeVariation.hpp"
#include "EyeBlink.hpp"

class TheBotFace;

class Eye
{
protected:
    TheBotFace &_face;

    void Update();
    void ChainOperators();

public:
    Eye(TheBotFace &face);

    uint16_t CenterX;
    uint16_t CenterY;
    bool IsMirrored = false;

    EyeConfig Config;
    EyeConfig *FinalConfig;

    EyeTransition Transition;
    EyeTransformation Transformation;
    EyeVariation Variation1;
    EyeVariation Variation2;
    EyeBlink BlinkTransformation;

    void ApplyPreset(const EyeConfig preset);
    void TransitionTo(const EyeConfig preset);
    void Draw();
};

#endif