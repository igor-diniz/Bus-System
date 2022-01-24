#include <dirent.h>
#include <list>
#include <string>
#include <iostream>
#include <FileReader.h>

using namespace std;

int main(void) {
    FileReader f;
    f.fillListOfFiles();
    return(0);
}