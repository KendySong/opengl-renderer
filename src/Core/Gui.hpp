#pragma once
#include <vector>
#include <string>

#include "../Graphics/Mesh.hpp"
#include "../Graphics/RenderType.hpp"

class Gui
{
public :
    Gui();
    void settings(int fps);
    void scene(std::vector<Mesh>& meshes);
    void mainMenu(std::vector<Mesh>& meshes, Shader* shader);
    
    static const char* RenderTypeStr(RenderType type);
    
private :
    std::string m_gpuName;
    std::string m_versionName;
    const char* m_mode;
};