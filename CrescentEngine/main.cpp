#include <iostream>

#include "renderer/RenderingEngine.h"

int main()
{
    crescent::RenderingEngine r_engine = crescent::RenderingEngine();
    r_engine.Initialize(1600, 900, "CrescentEngine");
    r_engine.Run();

    // At last:
    r_engine.Release();
    return 0;
}