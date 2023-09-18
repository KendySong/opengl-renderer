#include <map>
#include <vector>
#include <string>
#include <functional>

class MenuNode
{
public :
    MenuNode() = default;
    MenuNode(const char* name);
    MenuNode(const char* name, std::function<void()> action);
    void display();
   
    std::function<void()> action;
    std::map<std::string, MenuNode> childs;

private :
    const char* m_name;
    std::string x;
};