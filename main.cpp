#include "IFSOperationViewer.h"

#include<ifs.h>
#include<stdio.h>

#define NUMBEROFCOLUMNS 64
#define NUMBEROFROWS 64

int main(int argc, char **argv)
{



QApplication app(argc, argv);

IFSOperationViewer *myIFSOperationViewer = new IFSOperationViewer();

myIFSOperationViewer->show();

return app.exec();

return 0;
}
