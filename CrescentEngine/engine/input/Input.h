//
// Created by manan on 18/08/2021.
//

#ifndef CRESCENTENGINE_INPUT_H
#define CRESCENTENGINE_INPUT_H

#include <tuple>

namespace crescent

{

    class Input
    {
        // make this class a singleton
    protected:
        static Input*                                               s_pInstance;
    public:
        inline static bool                                          IsKeyPressed( int keyCode ) { return s_pInstance->IsKeyPressedImpl(keyCode); }
        inline static bool                                          IsMouseButtonPressed( int button ) { return s_pInstance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float>                       GetMouseXY() { return s_pInstance->GetMouseXYImpl(); }
    private:
        virtual bool                                                IsKeyPressedImpl(int keyCode) = 0;
        virtual bool                                                IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float>                             GetMouseXYImpl() = 0;
    };

}

#endif //CRESCENTENGINE_INPUT_H
