#include <vector>
using namespace std;

namespace ilrd
{

class ComponentInterface
{
public:
    virtual ~ComponentInterface() {}
    virtual int Count() { return 0; }
    virtual void AddComponent(ComponentInterface* comp) {}
    virtual void PrintName() {}
};

class Leaf : public ComponentInterface
{
public:
    Leaf(char *name_ = "");
    ~Leaf() {}
    int Count();
    void AddComponent(ComponentInterface* comp);
    void PrintName();
private:
    char *m_name;
};

class Composite : public ComponentInterface
{
public:
    Composite(char *name_ = "");
    ~Composite() {}
    int Count();
    void AddComponent(ComponentInterface* comp);
    void PrintName();
private:
    char *m_name;
    vector<ComponentInterface *> list;
};

} // ilrd
