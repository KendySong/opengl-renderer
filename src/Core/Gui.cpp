#include "Gui.hpp"

const char* Gui::RenderTypeStr(RenderType type)
{
    switch(type)
    {
        case RenderType::Color :
            return "Color";

        case RenderType::Texture :
            return "Texture";

        case RenderType::Shader :
            return "Shader";

        default :
            return "Unknown";
    }
}