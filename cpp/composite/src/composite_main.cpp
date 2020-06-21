#include <iostream>

#include "composite.hpp"

using namespace std;
using namespace ilrd;


int main()
{
    const size_t NUM_FILES = 4;
    const size_t NUM_FOLDERS = 4;
    
    string file_names[NUM_FILES] = {"file1", "file2", "file3", "file4"};
    std::size_t file_sizes[NUM_FILES] = {15, 0, 20, 10};
    
    string folder_names[NUM_FOLDERS] = {"folder1", "folder2", "folder3", "folder4"};

    RegularFile *files[NUM_FILES];
    Folder *folders[NUM_FOLDERS];
    
    for (size_t i = 0; i < NUM_FILES; ++i)
    {
        files[i] = new RegularFile(file_names[i], file_sizes[i]);
    }

    for (size_t i = 0; i < NUM_FOLDERS; ++i)
    {
        folders[i] = new Folder(folder_names[i]);
    }

    for (size_t i = 0; i < NUM_FILES / 2; ++i)
    {
        folders[0]->Add(files[i]);
    }

    for (size_t i = NUM_FILES / 2; i < NUM_FILES; ++i)
    {
        folders[1]->Add(files[i]);
    }

    folders[1]->Add(folders[0]);
    folders[1]->Add(folders[1]); // shouldn't add

    for (size_t i = 0; i < NUM_FILES; ++i)
    {
        if (files[i]->GetName() != file_names[i]) cout << "GetName() failed" << endl;
    }

    for (size_t i = 0; i < NUM_FILES; ++i)
    {
        if (files[i]->GetSize() != file_sizes[i]) cout << "GetSize() failed" << endl;
    }

    for (size_t i = 0; i < NUM_FOLDERS; ++i)
    {
        if (folders[i]->GetName() != folder_names[i]) cout << "GetName() failed" << endl;
    }
    
    folders[0]->Remove(files[0]);

    for (size_t i = 0; i < NUM_FILES; ++i)
    {
        files[i]->PrintContents();
    }

    for (size_t i = 0; i < NUM_FOLDERS; ++i)
    {
        folders[i]->PrintContents();
    }

    folders[3]->Add(folders[0]);
    folders[3]->Add(folders[1]);
    folders[3]->Add(folders[2]);
    folders[3]->PrintContents();
    folders[3]->Remove(folders[1]);
    folders[3]->Remove(folders[2]);
    folders[3]->PrintContents();

    for (size_t i = 0; i < NUM_FILES; ++i)
    {
        delete files[i];
    }

    for (size_t i = 0; i < NUM_FOLDERS; ++i)
    {
        delete folders[i];
    }

    return 0;
}
