//
// Created by manan on 21/08/2021.
//

#ifndef CRESCENTENGINE_CUSTOMMATH_H
#define CRESCENTENGINE_CUSTOMMATH_H

namespace crescent
{
    template <typename T>
    inline T lerp(const T& a, const T& b, const float t)
    {
        return (1.0f - t) * a + b * t;
    }
}

#endif //CRESCENTENGINE_CUSTOMMATH_H
