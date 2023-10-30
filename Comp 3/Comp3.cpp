#pragma warning(disable : 4996) //i got a warning stopping me from useing something in ctime because its
                                //depricated/unsafe. This will ignore it.
#include<iostream>
#include <ctime>
#include"Comp3.h"

using namespace std;

Folder root("Root");
Folder* Current = &root;

void FindLargest(Folder* parentFolder){
    File* Largest = nullptr;
    for(int i = 0; i < parentFolder->getFileCount(); i++)
    {
        File* file = parentFolder->getFiles(i);
        if (Largest == nullptr)                         //Takes the first thing ass largest
            Largest = file;
        else if (Largest->getSize() < file->getSize())  //Check if the next one is larger
            Largest = file;
    }
    Largest->LookFile();
}

void Rename(Folder* parentFolder)
{
    string Name;
    cout << "New Name:";
    cin >> Name;
    int choice;
    cout << "Select the thing to rename:" << endl;

    // Display the list of subfolders in the current folder
    for (int i = 0; i < parentFolder->getFolderCount(); i++) {
        Folder* subfolder = parentFolder->getSubfolder(i);
        if (subfolder) {
            cout << i + 1 << ". " << subfolder->getName() << endl;
        }
    }
    // Display the current folder
    cout <<  parentFolder->getFolderCount() + 1 << ". Here:" << Current->getName() << endl;
    // Display the files in the current folder
    for (int i = 0; i < parentFolder->getFileCount(); i++) {
        File* files = parentFolder->getFiles(i);
        cout << parentFolder->getFolderCount() + i + 2 << ". " << files->getName() << endl;
    }
    cout << "Enter the number of the thing: ";
    cin >> choice;

    //If you pick a folder
    if (choice >= 1 && choice <= parentFolder->getFolderCount()) {
        Folder* selectedFolder = parentFolder->getSubfolder(choice - 1);
        if (selectedFolder) {
            cout << "Folder '" << selectedFolder->getName() << "' has been renamed to'" << Name << "'." << endl;
            selectedFolder->setName(Name);
        }
    }
    //if you pick the current folder
    if (choice == parentFolder->getFolderCount()+1)
    {
        cout << "Folder '" << Current->getName() << "' has been renamed to'" << Name << "'." << endl;
        Current->setName(Name);
    }
    //if you pick a file
    if (choice >=parentFolder->getFolderCount()+2  && choice <= parentFolder->getFolderCount()+1+parentFolder->getFileCount())
    {
        File* selectedFile = parentFolder->getFiles(choice - 2 - parentFolder->getFolderCount());
        cout << "File '" << selectedFile->getName() << "' has been renamed to'" << Name << "'." << endl;
        selectedFile->setName(Name);
    }
}

void ChangeCurrent(Folder* parentFolder) {
    int choice;
    cout << "Select the folder to be the current folder" << endl;
    //Displays all subfolders in current folder
    for (int i = 0; i < parentFolder->getFolderCount(); i++) {
        Folder* subfolder = parentFolder->getSubfolder(i);
        if (subfolder) {
            cout << i + 1 << ". " << subfolder->getName() << endl;
        }
    }
    //Displays current folder
    cout <<  parentFolder->getFolderCount() + 1 << ". Here:" << Current->getName() << endl;
    cout << "Enter the number of the folder: ";
    cin >> choice;
    //if you pick a Subfolder
    if (choice >= 1 && choice <= parentFolder->getFolderCount()) {
        Folder* selectedFolder = parentFolder->getSubfolder(choice - 1);
        Current = selectedFolder;
        cout << "Folder '" << selectedFolder->getName() << "' has been set to current folder." << endl;
        }
    //if you pick the current folder
    else if(choice == parentFolder->getFolderCount()+1)
    {
        cout << "Folder '" << Current->getName() << "' has been set to current folder." << endl;
    }
    else{
        cout << "Invalid choice." << endl;
    }
}

void MakeFolder(Folder* parentFolder) {
    string Name;
    cout << "Name:";
    cin >> Name;

    Folder* newFolder = new Folder(Name);

    int choice;
    cout << "Select the folder to place the new folder into:" << endl;
    //Displays all subfolders in current
    for (int i = 0; i < parentFolder->getFolderCount(); i++) {
        Folder* subfolder = parentFolder->getSubfolder(i);
        if (subfolder) {
            cout << i + 1 << ". " << subfolder->getName() << endl;
        }
    }
    //Displays current folder
    cout <<  parentFolder->getFolderCount() + 1 << ". Here:" << Current->getName() << endl;
    cout << "Enter the number of the folder: ";
    cin >> choice;
    //If you choose a subfolder
    if (choice >= 1 && choice <= parentFolder->getFolderCount()) {
        Folder* selectedFolder = parentFolder->getSubfolder(choice - 1);
        cout << "Folder '" << Name << "' has been added to folder '" << selectedFolder->getName() << "'." << endl;
        selectedFolder->addFolder(newFolder);
    }
    //If you choose the current folder
    else if(choice == parentFolder->getFolderCount()+1)
    {
        cout << "Folder '" << Name << "' has been added to folder '" << Current->getName() << "'." << endl;
        Current->addFolder(newFolder);
    }
        else{
        cout << "Invalid choice. The folder was not added to any folder." << endl;
    }
}

void MakeFile(Folder* parentFolder) {
    string Name;
    cout << "Name:";
    cin >> Name;
    int choice;
    cout << "Select the folder to place the file into:" << endl;

    // Display the list of subfolders in the current folder
    for (int i = 0; i < parentFolder->getFolderCount(); i++) {
        Folder* subfolder = parentFolder->getSubfolder(i);
        if (subfolder) {
            cout << i + 1 << ". " << subfolder->getName() << endl;
        }
    }
    //Displays current folder
    cout <<  parentFolder->getFolderCount() + 1 << ". Here:" << Current->getName() << endl;
    cout << "Enter the number of the folder: ";
    cin >> choice;
    //If you choose a subfolder
    if (choice >= 1 && choice <= parentFolder->getFolderCount()) {
        Folder* selectedFolder = parentFolder->getSubfolder(choice - 1);
        cout << "File '" << Name << "' has been added to folder '" << selectedFolder->getName() << "'." << endl;
        selectedFolder->addFile(File(Name));
    }
    //if you choose the current folder
    else if(choice == parentFolder->getFolderCount()+1)
    {
        cout << "File '" << Name << "' has been added to folder '" << Current->getName() << "'." << endl;
        Current->addFile(File(Name));
    }else {
        cout << "Invalid choice. The file was not added to any folder." << endl;
    }
}

void Menu() {
    cout << endl << "1. Make File" << endl;
    cout << "2. Make Folder" << endl;
    cout << "3. Print folder info" << endl;
    cout << "4. Enter subfolder" << endl;
    cout << "5. Go up a folder" << endl;
    cout << "6. Rename file/folder" << endl;
    cout << "7. Find largest file" << endl;
    cout << "8. Exit" << endl;
    cout << endl << "You are in: " << Current->getName() << endl;
    int input;
    cin >> input;

    switch (input) {
    case 1: //Make file
        MakeFile(Current);
        Menu();
        break;
    case 2: //Make Folder
        MakeFolder(Current);
        Menu();
        break;
    case 3: //Print info
        Current->Look();
        Menu();
        break;
    case 4: //Change current file
        ChangeCurrent(Current);
        Menu();
        break;
    case 5: //Go up a folder
        if(Current->getParent() != nullptr)
        {
            Current = Current->getParent();
        }
        Menu();
        break;
    case 6: //Rename
        Rename(Current);
        Menu();
        break;
    case 7: //Largest
        FindLargest(Current);
        Menu();
        break;
    case 8: //Exit
        return;
    default:
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Menu();
    }
}

int main() {
    srand(static_cast<unsigned>(time(NULL))); // makes seed for random

    //Makes some folders and files to begin with
    root.addFile(File("File1"));
    root.addFile(File("File2"));

    Folder * subfolder1 = new Folder("Subfolder1");
    subfolder1->addFile(File("File3"));
    subfolder1->addFile(File("File4"));

    Folder * subfolder2 = new Folder("Subfolder2");
    subfolder2->addFile(File("File5"));

    root.addFolder(subfolder1);
    root.addFolder(subfolder2);

    //Start
    root.Look();
    Menu();
    return 0;
}