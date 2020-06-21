#ifndef FS_734_COMPOSITE_H
#define FS_734_COMPOSITE_H

#include <iostream>
// #include <cstddef>  // size_t 
#include <list>

namespace ilrd
{

class I_File
{
public:
    virtual ~I_File();

    virtual void Add(const I_File* object_);
    virtual void Remove(const I_File* object_);           
    virtual void PrintContents(int tab_num = 0) const;
    
    virtual std::size_t GetSize() const = 0;
    virtual std::string GetName() const = 0;    
};

class RegularFile: public I_File
{
public:
    explicit RegularFile(std::string name_, size_t size_ = 0);
    ~RegularFile();

    void PrintContents(int tab_num = 0) const;

    std::size_t GetSize() const;
    std::string GetName() const;

private:
    std::string m_name;   
    std::size_t m_size;
};

class Folder: public I_File
{
public:
    explicit Folder(std::string name_);
    ~Folder();

    void Add(const I_File* object_);
    void Remove(const I_File* object_); 
    void PrintContents(int tab_num = 0) const;
    std::size_t GetSize() const;
    std::string GetName() const;

private:
    std::list<I_File *> m_files;
    std::string m_name;       
    mutable std::size_t m_size;
    mutable bool m_validSize;
};

} // namespace ilrd

#endif // FS_734_COMPOSITE_H
