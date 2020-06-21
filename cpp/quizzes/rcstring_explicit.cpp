#include <cstddef>
#include <cstring>
class String
{
    explicit String(const char *s = "");
    String& operator=(const String& other_)
    {
        RC *prev_rc = m_rc;

        m_rc = other_.m_rc;
        ++m_rc->m_count;

        if (--prev_rc->m_count == 0) { delete prev_rc; prev_rc == NULL; }
    
        return *this;
    }

    

private:
    struct RC
    {
        char *m_str;
        size_t m_count;
    };

    RC *m_rc;
};

String& operator=(const String&str1, const char *other_str)
    {
        RC *prev_rc = m_rc;

        m_rc = new RC();

        m_rc->m_str = strdup(other_str);
        m_rc->m_count = 1;

        if (--prev_rc->m_count == 0) { delete prev_rc; prev_rc = NULL; }

        return *this;
    }