#include <cstring>
class String
{
public:
    String(char * s_ = "") : m_s(new char[strlen(s_) + 1])
    {
        memcpy(m_s, s_, strlen(s_));
    }

    String(const String& other_)
    {
        memcpy(m_s, other_.m_s, strlen(other_.m_s));
    }

    // I haven't finished this... 
    String& operator=(const String& other_)
    {
        char *tmp = strdup(other_.m_s);

        delete[] m_s;
        
        m_s = strdup(tmp);
        
        return *this;
    }

    char& operator[](int pos)
    {
        return m_s[pos];
    }

private:
    char *m_s;
};

int main()
{
    String s1("aaa");
    String s2 = "bbb";
    String s3(s2);
    String s4;
    
    s4 = s2;
    s3[2] = 'k';
}