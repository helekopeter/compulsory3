#pragma once
#include <iostream>
#include <string>
#include <cstdlib> //For random
#include <ctime>   //For time and date

class File {
public:
    // Default constructor (needed this or else it got mad)
    File() : name("Unnamed"), size(0) {}
    // Cooler constructor
    File(const std::string& name) : name(name), size(rand() % 100)
    {
        updateDate();
    }

    std::string getDate() const {
        return date;
    }
    
    std::string getName() const {
        return name;
    }

    void setName(std::string newName) {
        name = newName;
    }

    int getSize() const {
        return size;
    }

    void LookFile() const
    {
        std::cout << "Name:" << name << " Size:" << size << " date:" << date << std::endl;
    }
    

private:
    std::string name;
    int size;
    std::string date;

    void updateDate() {
        time_t now = time(0);
        date = ctime(&now);
    }
};

class Folder {
public:
    Folder(const std::string& name) : name(name), filecount(0), foldercount(0){
        updateDate();
        //initialize array
        for (int i = 0; i < 5; i++) {
            subfolders[i] = nullptr;
        }
    }

    Folder* getParent() const {
        return parent;
    }

    void setParent(Folder* folder) {
        parent = folder;
    }
    
    std::string getName() const {
        return name;
    }

    void setName(std::string newname) {
        name = newname;
    }
    
    int getFolderCount() const {
        return foldercount;
    }

    int getFileCount() const {
        return filecount;
    }

    
    Folder* getSubfolder(int index) {
        if (index >= 0 && index < foldercount) {
            return subfolders[index];
        } else {
            return nullptr;
        }
    }

    File* getFiles(int index) {
        if (index >= 0 && index < filecount) {
            return &files[index];
        } else {
            return nullptr;
        }
    }
    
    void addFile(const File& file) {
        if (filecount < 10) {
            files[filecount] = file;
            filecount++;
        }
        else
        {
            std::cout<<"FOLDER IS FULL. FILE WAS NOT ADDED."<< std::endl;
        }
    }

    void addFolder(Folder* folder) {
        if (foldercount < 5) {
            subfolders[foldercount++] = folder; 
            folder->setParent(this);
        }
        else
        {
            std::cout<<"FOLDER IS FULL. FOLDER WAS NOT ADDED."<< std::endl;
        }
    }

    void Look() const {
        //Display this folders info
        
        if(parent == nullptr) //Check if folder has parrents
        {
            std::cout << "Folder: " << name << " Size: ";
        }
        else
        {
            std::cout << "Folder: "<< parent->getName() <<"/"<< name << " Size: ";
        }
        
        //Folder Size Counter
        int foldersize = 0;
        for (int i = 0; i < filecount; i++) {
            foldersize = foldersize + files[i].getSize();
        }
        std::cout << foldersize<<" Date: "<<date;

        //List Files
        for (int i = 0; i < filecount; i++) {
                std::cout << "File:" << files[i].getName() << " Size:" << files[i].getSize() << " Date: " << files[i].getDate();
        }

        //Look in subfolders
        for (int i = 0; i < foldercount; i++) {
            if (subfolders[i]) {
                std::cout << std::endl;
                subfolders[i]->Look();
            }
        }
    }

private:
    int filecount;
    int foldercount;
    std::string name;
    File files[10];
    Folder* subfolders[5];
    std::string date;
    Folder* parent = nullptr;

    void updateDate() {
        time_t now = time(0);
        date = ctime(&now);
    }
};