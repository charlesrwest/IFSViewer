#include "IFSOperationViewer.h"

/*
This function initializes the IFSOperationViewer and gets the inherited main window ready.
*/
IFSOperationViewer::IFSOperationViewer()
{
loadedIFSImage = NULL;
setupUi(this);

//Setup IFSImageLabels
leftImageLabel = new IFSImageLabel(imageFrame);
leftImageLabel->setObjectName(QString::fromUtf8("leftImageLabel"));
leftImageLabel->setScaledContents(false);
leftImageLabel->setAlignment(Qt::AlignCenter);

horizontalLayout_2->addWidget(leftImageLabel);

rightImageLabel = new IFSImageLabel(imageFrame);
rightImageLabel->setObjectName(QString::fromUtf8("rightImageLabel"));
rightImageLabel->setAlignment(Qt::AlignCenter);

horizontalLayout_2->addWidget(rightImageLabel);

//Set the slider for 3D images invisible until it is needed
threeDFramePositionLabel->setHidden(true);
threeDFramePositionSlider->setHidden(true);





//Initialize the file open action
action_Open->setShortcut(QKeySequence::Open);
action_Open->setStatusTip(tr("Load a IFS image for processing and viewing"));

//Initialize the save action
action_Save->setShortcut(QKeySequence::Save);
action_Save->setStatusTip(tr("Save the result of processing"));

//Connect the image labels to the values for the position
connect(leftImageLabel, SIGNAL(imageCursorRow(int)), rowPositionLabel, SLOT(setNum(int)));
connect(rightImageLabel, SIGNAL(imageCursorRow(int)), rowPositionLabel, SLOT(setNum(int)));

connect(leftImageLabel, SIGNAL(imageCursorColumn(int)), columnPositionLabel, SLOT(setNum(int)));
connect(rightImageLabel, SIGNAL(imageCursorColumn(int)), columnPositionLabel, SLOT(setNum(int)));

connect(leftImageLabel, SIGNAL(imageCursorValue(double)), imageValueLabel, SLOT(setNum(double)));
connect(rightImageLabel, SIGNAL(imageCursorValue(double)), imageValueLabel, SLOT(setNum(double)));

//Add action signals
connect(action_Open, SIGNAL(triggered()), this, SLOT(openFile()));
connect(action_Save, SIGNAL(triggered()), this, SLOT(saveFile()));

//Connect buttons
connect(applyButton, SIGNAL(clicked()), this, SLOT(applyOperation()));
connect(swapButton, SIGNAL(clicked()), this, SLOT(swap()));

//Connect slider
connect(threeDFramePositionSlider, SIGNAL(valueChanged(int)), this, SLOT(setFrame(int)));
connect(threeDFramePositionSlider, SIGNAL(valueChanged(int)), threeDFramePositionLabel, SLOT(setNum(int)));

//Set up function details and the function list
populateFunctionDetailsAndList();

//Connect list to parameters
connect(operationListBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(setupParameterWidgets(const QString&)));

//Set the function list to the first item
if(operationListBox->count() > 0)
{
operationListBox->setCurrentRow(0);
}

}

/*
This function attempts to load a IFS Image from the given path and save it in the leftImageLabel widget (which stores and displays it). Only 2D and 3D images are permitted
@param inputPath: The path to the IFSImage  
@return: 1 if successful and 0 otherwise
*/
int IFSOperationViewer::openNewIFSImage(const char *inputPath)
{
loadedIFSImage = loadFloatImageWithUnknownDimensions(inputPath);
if(loadedIFSImage == NULL)
{
fprintf(stderr, "Error, unable to load image\n");
return 0;
}

if(loadedIFSImage->ifsdims != 2 && loadedIFSImage->ifsdims != 3)
{
fprintf(stderr, "Error, the loaded image had %d dimensions (should be 2 or 3)\n", loadedIFSImage->ifsdims);
return 0;
}

//If it is a 2D image, we pretty much just stick it in the left label
if(loadedIFSImage->ifsdims == 2)
{
//Make sure the 3D image stuff is hidden
threeDFramePositionLabel->setHidden(true);
threeDFramePositionSlider->setHidden(true);

leftImageLabel->setIFSImage(loadedIFSImage);
}

//In the 3D case, things are a little more tricky
if(loadedIFSImage->ifsdims == 3)
{
//Populate the slider and then make both the 3D slider and label visible
threeDFramePositionSlider->setMinimum(0);
threeDFramePositionSlider->setMaximum(ifsdimen(loadedIFSImage, 2)-1);
threeDFramePositionSlider->setValue(0);

threeDFramePositionLabel->setNum(0);
setFrame(0);

threeDFramePositionLabel->setHidden(false);
threeDFramePositionSlider->setHidden(false);

}


//leftImageLabel->setIFSImage(loadedIFSImage);
return 1;
}

/*
This function attempts to save the right hand IFS Image to the given path. 
@param inputPath: The path to save the IFSImage at  
@return: 1 if successful and 0 otherwise
*/
int IFSOperationViewer::saveProcessedIFSImage(const char *inputPath)
{
if(inputPath == NULL)
{
fprintf(stderr, "Cannot save image to NULL path\n");
return 0;
}

if(rightImageLabel->ifsImage == NULL)
{
fprintf(stderr, "Error, there is not a proccessed ifs image to save\n");
return 0;
}

if(save2DFloatImage(rightImageLabel->ifsImage, inputPath)!=1)
{
fprintf(stderr, "Error saving ifs image\n");
}

return 1;
}


/*
This slot opens a file dialog to find a IFS image to load.  It then calls openNewIFSImage to load the IFSImage into the left image label for processing.
*/
void IFSOperationViewer::openFile()
{
QString fileName;
fileName = QFileDialog::getOpenFileName(this, tr("Load IFS Image"), ".", tr("IFS Images (*.ifs *.IFS)"));
if(!fileName.isEmpty())
{
if(openNewIFSImage(fileName.toAscii().constData()) != 1)
{
fprintf(stderr, "Error loading %s\n", fileName.toAscii().constData());
}
}

}

/*
This slot opens a file dialog to save the right hand IFS image.  It then calls saveProcessedIFSImage to actually save the file.
*/
void IFSOperationViewer::saveFile()
{
QString fileName = QFileDialog::getSaveFileName(this, tr("Save IFS Image"), ".", tr("IFS Images (*.ifs *.IFS)"));
if(fileName.isEmpty())
{
return;
}

if(saveProcessedIFSImage(fileName.toAscii().constData()) != 1)
{
fprintf(stderr, "Error saving ifs image to %s\n", fileName.toAscii().constData());
}
}



/*
This function moves the IFS image associated with the right label into the left label so that further processing can be carried out on it.
*/
void IFSOperationViewer::swap()
{
if(rightImageLabel->ifsImage == NULL)
{
return;
}

//Allocate a buffer to put the image in
IFSHDR *buffer = create2DFloatImage(ifsdimen(rightImageLabel->ifsImage, 0), ifsdimen(rightImageLabel->ifsImage, 1));
if(buffer == NULL)
{
//Image allocation failed
fprintf(stderr, "There was a failure when allocating space for the swap operation\n");
return;
}

//Copy the image into the buffer
if(flcp(rightImageLabel->ifsImage, buffer) != 1)
{
fprintf(stderr, "Error copying the swap image into a buffer\n");
ifsfree(buffer, IFS_FR_ALL);
return;
}

//Put the image in the left label
leftImageLabel->setIFSImage(buffer);
}

/*
This function sets the IFS image of the left label to the frame indicated by the integer argument.
@param inputFrameNumber: The frame number to navigate to
*/
void IFSOperationViewer::setFrame(int inputFrameNumber)
{
if(loadedIFSImage == NULL)
{
fprintf(stderr, "Error, attempting to set frame without a loaded image\n");
return;
}

if(loadedIFSImage->ifsdims != 3)
{
fprintf(stderr, "Error, attempting to set frame when the loaded image isn't 3D\n");
return;
}

if(inputFrameNumber < 0)
{
fprintf(stderr, "Error, attempting to set a negative frame index\n");
return;
}

if(ifsdimen(loadedIFSImage, 2)-1 < inputFrameNumber)
{
fprintf(stderr, "Error, attempting to load a frame index that is greater than the number of frames - 1\n");
return; 
}

//Get the frame
IFSHDR *buffer = ifsslice(loadedIFSImage, "f", inputFrameNumber);
if(buffer == NULL)
{
fprintf(stderr, "Error taking slice of 3D image\n");
return;
}

//Load the frame into the label
leftImageLabel->setIFSImage(buffer);
}

/*
This function (normally activated by the Apply button) attempts to apply the selected IFS function to the image in the left label and store the result in the right label.
*/
void IFSOperationViewer::applyOperation()
{
if(leftImageLabel->ifsImage == NULL)
{
return;
}

//If any of the parameter widgets are empty, set them to 0.0
for(int i=0; i<parameterLineEdits.size(); i++)
{
if(parameterLineEdits[i]->text() == QString(""))
{
parameterLineEdits[i]->setText("0.0");
}
}

//Get the parameters
std::vector<float> parameters;
for(int i=0; i<parameterLineEdits.size(); i++)
{
bool isOkay=false;
parameters.push_back(parameterLineEdits[i]->text().toFloat(&isOkay));
if(!isOkay)
{
fprintf(stderr, "One of the function parameters was non-numeric\n");
return;
}
}

std::string functionName = std::string(operationListBox->currentItem()->text().toAscii().constData());

//Allocate buffer space for the operation
IFSHDR *buffer = create2DFloatImage(ifsdimen(leftImageLabel->ifsImage, 0), ifsdimen(leftImageLabel->ifsImage, 1));
if(buffer == NULL)
{
//Image allocation failed
fprintf(stderr, "There was a failure when allocating space for the result of the operation\n");
return;
}

//Do the appropriate function given the current text value
/*
if(functionName == "flabsolute")
{
if(flabsolute(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else*/ if(functionName == "fladds")
{
if(fladds(leftImageLabel->ifsImage, buffer, parameters[0]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flclip")
{
if(flclip(leftImageLabel->ifsImage, buffer, parameters[0]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flcp")
{
if(flcp(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldivs")
{
if(fldivs(leftImageLabel->ifsImage, buffer, parameters[0]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flexp")
{
if(flexp(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flln")
{
if(flln(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flmults")
{
if(flmults(leftImageLabel->ifsImage, buffer, parameters[0]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flneg")
{
if(flneg(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flrec")
{
if(flrec(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flsq")
{
if(flsq(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flsqrt")
{
if(flsqrt(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flsubs")
{
if(flsubs(leftImageLabel->ifsImage, buffer, parameters[0]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flthresh")
{
if(flthresh(leftImageLabel->ifsImage, buffer, parameters[0], parameters[1]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flone_border")
{
if(flone_border(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flpad")
{
if(flpad(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flplanar")
{
if(flplanar(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flshx")
{
if(flshx(leftImageLabel->ifsImage, parameters[0], buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flshxy")
{
if(flshxy(leftImageLabel->ifsImage, parameters[0], parameters[1], buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flshy")
{
if(flshy(leftImageLabel->ifsImage, parameters[0], buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flzero_border")
{
if(flzero_border(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flDoG")
{
if(flDoG(leftImageLabel->ifsImage, buffer, parameters[0], parameters[1], parameters[2]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "flGabor")
{
if(flGabor(leftImageLabel->ifsImage, buffer, parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldx")
{
if(fldx(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldx_back")
{
if(fldx_back(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldx_forw")
{
if(fldx_forw(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldxx")
{
if(fldxx(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldxy")
{
if(fldxy(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldy")
{
if(fldy(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldy_back")
{
if(fldy_back(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldy_forw")
{
if(fldy_forw(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else if(functionName == "fldyy")
{
if(fldyy(leftImageLabel->ifsImage, buffer) != functionDetailsMap[functionName].expectedReturnValue)
{
fprintf(stderr, "%s returned an error\n", functionName.c_str());
ifsfree(buffer, IFS_FR_ALL);
return;
}
}
else
{
fprintf(stderr, "Error, function operation %s not found\n", functionName.c_str());
}

rightImageLabel->setIFSImage(buffer);
}


/*
This function sets up widgets to enter the parameters for the operation function call.
@param inputCurrentText: The text associated with the function to set up for
*/
void IFSOperationViewer::setupParameterWidgets(const QString & inputCurrentText)
{
std::string functionName(inputCurrentText.toAscii().constData());


functionDetails detailsBuffer(functionDetailsMap[functionName]);

//Clear the existing widgets
for(int i=0; i<parameterLabels.size(); i++)
{
delete parameterLabels[i];
}
parameterLabels.clear();

for(int i=0; i<parameterLineEdits.size(); i++)
{
delete parameterLineEdits[i];
}
parameterLineEdits.clear();

//Populate the widgets
QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
for(int i=0; i<detailsBuffer.arguments.size(); i++)
{
parameterLabels.push_back(new QLabel(parameterGroupBox));
parameterLabels.back()->setText(detailsBuffer.arguments[i].c_str());
parameterLabels.back()->setSizePolicy(sizePolicy);
parametersLayout->addWidget(parameterLabels.back(), i, 0, 1, 1);

parameterLineEdits.push_back(new QLineEdit(parameterGroupBox));
//Set to only allow floating point numbers
parameterLineEdits.back()->setValidator( new QDoubleValidator(-FLT_MAX, FLT_MAX, 6,this) );
//Set the default value to 0.0
parameterLineEdits.back()->setText(QString("0.0"));
//Set it not to expand
parameterLineEdits.back()->setSizePolicy(sizePolicy);
//Put it in the layout
parametersLayout->addWidget(parameterLineEdits.back(), i, 1, 1, 1);

}
}

/*
This function populates the functionDetails vector and the list of function names.
*/
void IFSOperationViewer::populateFunctionDetailsAndList()
{
//Populate function details list
functionDetails functionDetailsBuffer;

//Set function name
functionDetailsBuffer.functionName = "flabsolute";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;


//Set function name
functionDetailsBuffer.functionName = "fladds";
//Add parameters
functionDetailsBuffer.arguments.push_back("Scalar to add");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flclip";
//Add parameters
functionDetailsBuffer.arguments.push_back("Maximum value");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flcp";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldivs";
//Add parameters
functionDetailsBuffer.arguments.push_back("Divisor");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flexp";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flln";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flmults";
//Add parameters
functionDetailsBuffer.arguments.push_back("Amount to multiply by");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flneg";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flrec";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flsq";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flsqrt";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flsubs";
//Add parameters
functionDetailsBuffer.arguments.push_back("Amount to subtract");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flthresh";
//Add parameters
functionDetailsBuffer.arguments.push_back("Threshold");
functionDetailsBuffer.arguments.push_back("Value to change to");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flone_border";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flpad";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flplanar";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flshx";
//Add parameters
functionDetailsBuffer.arguments.push_back("Shift amount");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();


//Set function name
functionDetailsBuffer.functionName = "flshxy";
//Add parameters
functionDetailsBuffer.arguments.push_back("X shift amount");
functionDetailsBuffer.arguments.push_back("Y shift amount");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flshy";
//Add parameters
functionDetailsBuffer.arguments.push_back("Shift amount");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 1;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flzero_border";
//Add parameters
functionDetailsBuffer.expectedReturnValue = 0;
//Set expected return value
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flDoG";
//Add parameters
functionDetailsBuffer.arguments.push_back("Sigma");
functionDetailsBuffer.arguments.push_back("Order");
functionDetailsBuffer.arguments.push_back("Direction");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "flGabor";
//Add parameters
functionDetailsBuffer.arguments.push_back("Sigma");
functionDetailsBuffer.arguments.push_back("Theta");
functionDetailsBuffer.arguments.push_back("Lambda");
functionDetailsBuffer.arguments.push_back("Gamma");
functionDetailsBuffer.arguments.push_back("Psi");
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldx";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldx_back";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldx_forw";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldxx";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldxy";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldy";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldy_back";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldy_forw";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Set function name
functionDetailsBuffer.functionName = "fldyy";
//Add parameters
//Set expected return value
functionDetailsBuffer.expectedReturnValue = 0;
//Add to map
functionDetailsMap[functionDetailsBuffer.functionName] = functionDetailsBuffer;
//Clear buffer
functionDetailsBuffer.functionName = "";
functionDetailsBuffer.arguments.clear();

//Add function names to list widget
for(std::map<std::string, functionDetails>::iterator it = functionDetailsMap.begin(); it != functionDetailsMap.end(); it++)
{
operationListBox->addItem(QString(it->first.c_str()));
}

}

