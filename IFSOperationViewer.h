#ifndef IFSOPERATIONVIEWERH
#define IFSOPERATIONVIEWERH


#include<QMainWindow>
#include<QFileDialog>
#include<QLabel>
#include<QLineEdit>
#include "ui_mainWindow.h"

extern "C"
{
#include<ifs.h>
#include<flip.h>
}

#include "utilityFunctions.h"
#include "IFSImageLabel.h"
#include "functionDetails.h"
#include<stdio.h>
#include<vector>
#include<map>
#include<float.h>
#include<QDoubleValidator>



class IFSOperationViewer :  public QMainWindow, public Ui_MainWindow
{
Q_OBJECT

public:
/*
This function initializes the IFSOperationViewer and gets the inherited main window ready.
*/
IFSOperationViewer();

/*
This function attempts to load a IFS Image from the given path and save it in the leftImageLabel widget (which stores and displays it). Only 2D and 3D images are permitted
@param inputPath: The path to the IFSImage  
@return: 1 if successful and 0 otherwise
*/
int openNewIFSImage(const char *inputPath);

/*
This function attempts to save the right hand IFS Image to the given path. 
@param inputPath: The path to save the IFSImage at  
@return: 1 if successful and 0 otherwise
*/
int saveProcessedIFSImage(const char *inputPath);

IFSImageLabel *leftImageLabel;
IFSImageLabel *rightImageLabel;

IFSHDR *loadedIFSImage;
std::vector<QLabel *> parameterLabels;
std::vector<QLineEdit *> parameterLineEdits;
std::map<std::string, functionDetails> functionDetailsMap;

public slots:

/*
This slot opens a file dialog to find a IFS image to load.  It then calls openNewIFSImage to load the IFSImage into the left image label for processing.
*/
void openFile();

/*
This slot opens a file dialog to save the right hand IFS image.  It then calls saveProcessedIFSImage to actually save the file.
*/
void saveFile();

/*
This function moves the IFS image associated with the right label into the left label so that further processing can be carried out on it.
*/
void swap();

/*
This function sets the IFS image of the left label to the frame indicated by the integer argument.
@param inputFrameNumber: The frame number to navigate to
*/
void setFrame(int);

/*
This function sets up widgets to enter the parameters for the operation function call.
@param inputCurrentText: The text associated with the function to set up for
*/
void setupParameterWidgets(const QString &);

/*
This function (normally activated by the Apply button) attempts to apply the selected IFS function to the image in the left label and store the result in the right label.
*/
void applyOperation();


signals:

private:
/*
This function populates the functionDetails vector and the list of function names.
*/
void populateFunctionDetailsAndList();

};















#endif
