#include <iostream>
#include "composite.hpp"

namespace ilrd
{

I_File::~I_File() {}

void I_File::Add(const I_File* object_) { (void)object_; }

void I_File::Remove(const I_File* object_) { (void)object_; }

void I_File::PrintContents(int tab_num) const { (void)tab_num; }

/*****************************************************************************/

RegularFile::RegularFile(std::string name_, size_t size_) : m_name(name_), m_size(size_)
{

}

RegularFile::~RegularFile() {}

void RegularFile::PrintContents(int tab_num) const
{
    (void)tab_num;
    std::cout << "(f)" << GetName() << std::endl;
}

std::size_t RegularFile::GetSize() const { return m_size; }

std::string RegularFile::GetName() const { return m_name; }

/*****************************************************************************/

Folder::Folder(std::string name_) : m_files(), m_name(name_), m_size(0), m_validSize(false) {}

Folder::~Folder() {}

void Folder::Add(const I_File* object_)
{
    if (this == object_) return;
    
    m_files.push_back(const_cast<I_File *>(object_));
    m_validSize = false;
}

void Folder::Remove(const I_File* object_)
{
    m_files.remove(const_cast<I_File *>(object_));
    m_validSize = false;
}

void Folder::PrintContents(int tab_num) const
{
    std::cout << "(d)" << GetName() << std::endl;

    for (std::list<I_File *>::const_iterator it = m_files.begin(); it != m_files.end(); ++it)
    {
        for (int i = 0; i <= tab_num; ++i)
        {
            std::cout << "\t";
        }
        (*it)->PrintContents(tab_num + 1);
    }
}

std::size_t Folder::GetSize() const
{
    if (m_validSize) return m_size;

    std::size_t size = 0;

    for (std::list<I_File *>::const_iterator it = m_files.begin(); it != m_files.end(); ++it)
    {
        size += (*it)->GetSize();
    }
    
    m_size = size;
    m_validSize = true;

    return m_size;
}

std::string Folder::GetName() const { return m_name; }

} //ilrd
