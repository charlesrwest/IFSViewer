#include "utilityFunctions.h"

/*
This function loads an image from the given path.  If there is something wrong with the path or image, the function gives a detailed error report and returns NULL.

This function checks that the image exists, is of type float, has exactly 2 dimensions and both dimensions are positive.
@param inputPathToReadFrom:  The path to read the image from (if NULL, the function fails with error rather than trying to read from stdin)
@return: An IFS image structure or NULL on failure
*/
IFSHDR *load2DFloatImage(const char *inputPathToReadFrom)
{
if(inputPathToReadFrom == NULL)
{
fprintf(stderr, "Error, asked to load an image with a null string for the path\n");
return NULL;
}

IFSHDR *loadedImage = ifsGetImg(inputPathToReadFrom, NULL, FALSE);
if(loadedImage == NULL)
{
fprintf(stderr, "Error, it was not possible to load the image with path %s\n", inputPathToReadFrom);
return NULL; 
}

//Check if the image we loaded is of type float
if( checkFloat(loadedImage) == -1)
{
fprintf(stderr, "Error, the image at path %s has non-float type\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}


//Check the dimensionality of the image
if(loadedImage->ifsdims != 2)
{
fprintf(stderr, "Error, the image loaded from %s has %d dimensions.  This program can only process 2d images\n", inputPathToReadFrom, loadedImage->ifsdims);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

//Make sure the dimensions are non-negative
if(ifsdimen(loadedImage, 0) < 0)
{
fprintf(stderr, "Error, the image loaded from %s a negative column dimension indicator\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

if(ifsdimen(loadedImage, 1) < 0)
{
fprintf(stderr, "Error, the image loaded from %s a negative row dimension indicator\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

//Checks have been passed, so return the image
return loadedImage;
}

/*
This function loads an image from the given path.  If there is something wrong with the path or image, the function gives a detailed error report and returns NULL.

This function checks that the image exists, is of type float, has exactly 3 dimensions and both dimensions are positive.
@param inputPathToReadFrom:  The path to read the image from (if NULL, the function fails with error rather than trying to read from stdin)
@return: An IFS image structure or NULL on failure
*/
IFSHDR *load3DFloatImage(const char *inputPathToReadFrom)
{
if(inputPathToReadFrom == NULL)
{
fprintf(stderr, "Error, asked to load an image with a null string for the path\n");
return NULL;
}

IFSHDR *loadedImage = ifsGetImg(inputPathToReadFrom, NULL, FALSE);
if(loadedImage == NULL)
{
fprintf(stderr, "Error, it was not possible to load the image with path %s\n", inputPathToReadFrom);
return NULL; 
}

//Check if the image we loaded is of type float
if( checkFloat(loadedImage) == -1)
{
fprintf(stderr, "Error, the image at path %s has non-float type\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}


//Check the dimensionality of the image
if(loadedImage->ifsdims != 3)
{
fprintf(stderr, "Error, the image loaded from %s has %d dimensions.  This function can only process 3d images\n", inputPathToReadFrom, loadedImage->ifsdims);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

//Make sure the dimensions are non-negative
if(ifsdimen(loadedImage, 0) < 0)
{
fprintf(stderr, "Error, the image loaded from %s a negative frame dimension indicator\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

if(ifsdimen(loadedImage, 1) < 0)
{
fprintf(stderr, "Error, the image loaded from %s a negative column dimension indicator\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

if(ifsdimen(loadedImage, 2) < 0)
{
fprintf(stderr, "Error, the image loaded from %s a negative row dimension indicator\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

//Checks have been passed, so return the image
return loadedImage;
}

/*
Apparently classic c doesn't have function overloading, so load2DFloatImage can't be used as the function signature.

This function loads an image from the given path.  If there is something wrong with the path or image, the function gives a detailed error report and returns NULL.

This function checks that the image exists, is of type float, has positive dimensions, and has row and column sizes within the acceptable ranges.  Negative values for minimums or maximums indicate that any positive or zero value is acceptable.
@param inputPathToReadFrom:  The path to read the image from (if NULL, the function fails with error rather than trying to read from stdin)
@param inputMinimumNumberOfColumns: This is the minimum number of columns the input image is permitted to have.  It is not used if the parameter value is negative.
@param inputMinimumNumberOfRows: This is the minimum number of rows the input image is permitted to have.  It is not used if the parameter value is negative.
@param inputMaximumNumberOfColumns: This is the maximum number of columns the input image is permitted to have.  It is not used if the parameter value is negative.
@param inputMaximumNumberOfRows: This is the maximum number of rows the input image is permitted to have.  It is not used if the parameter value is negative.
@return: An IFS image structure or NULL on failure
*/
IFSHDR *load2DFloatImageWithBoundsChecking(const char *inputPathToReadFrom, int inputMinimumNumberOfColumns, int inputMinimumNumberOfRows, int inputMaximumNumberOfColumns, int inputMaximumNumberOfRows)
{
//Call the loading function that checks everything except for mins and maxes.
IFSHDR *loadedImage = load2DFloatImage(inputPathToReadFrom);

//Make sure all of those checks where passed and, if they weren't, stop processing the image
if(loadedImage == NULL)
{
return NULL;
}

//Check the number of columns
if(ifsdimen(loadedImage, 0) >= inputMinimumNumberOfColumns && inputMinimumNumberOfColumns >= 0)
{
fprintf(stderr, "Error, image loaded from %s has too few columns\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
} 

if(ifsdimen(loadedImage, 0) <= inputMaximumNumberOfColumns && inputMaximumNumberOfColumns >= 0)
{
fprintf(stderr, "Error, image loaded from %s has too many columns\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
} 

//Check the number of rows
if(ifsdimen(loadedImage, 1) <= inputMinimumNumberOfRows && inputMinimumNumberOfRows >= 0)
{
fprintf(stderr, "Error, image loaded from %s has too few rows\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
} 

if(ifsdimen(loadedImage, 1) <= inputMaximumNumberOfRows && inputMaximumNumberOfRows >= 0)
{
fprintf(stderr, "Error, image loaded from %s has too many columns\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
} 

//All checks were passed
return loadedImage;
}


/*
This function checks that the image is of type float and has non-negative dimensions.  If then attempts to save the image to the given path.  If a failure occurs, the error is reported and 0 is returned.
@param inputImageToSave: The IFS image to save
@param inputPathToSaveImageTo: The path to save the image to
@return: 1 on success and 0 otherwise
*/
int save2DFloatImage(IFSHDR *inputImageToSave, const char *inputPathToSaveImageTo)
{
//Check if the image we are saving is of type float
if(checkFloat(inputImageToSave) == -1)
{
fprintf(stderr, "Error, the image to be saved at path %s has non-float type\n", inputPathToSaveImageTo);
return 0;
}

//Make sure the image is two dimensional
if(inputImageToSave->ifsdims != 2)
{
fprintf(stderr, "Error, the image to be saved at path %s has %d dimensions (should be 2)\n", inputPathToSaveImageTo, inputImageToSave->ifsdims);
} 

//Make sure the dimensions are non-negative
if(ifsdimen(inputImageToSave, 0) < 0)
{
fprintf(stderr, "Error, the image to be saved at %s a negative column dimension indicator\n", inputPathToSaveImageTo);
return 0;
}

if(ifsdimen(inputImageToSave, 1) < 0)
{
fprintf(stderr, "Error, the image to be saved at path %s a negative row dimension indicator\n", inputPathToSaveImageTo);
return 0;
}

//Try to save the image
if(ifsPutImg(inputImageToSave, inputPathToSaveImageTo, NULL, FALSE) != IFS_SUCCESS)
{
fprintf(stderr, "Error saving image to %s\n", inputPathToSaveImageTo);
return 0;
}

return 1;
}

/*
This function checks that the image is of type float and has non-negative dimensions.  If then attempts to save the image to the given path.  If a failure occurs, the error is reported and 0 is returned.
@param inputImageToSave: The IFS image to save
@param inputPathToSaveImageTo: The path to save the image to
@return: 1 on success and 0 otherwise
*/
int save3DFloatImage(IFSHDR *inputImageToSave, const char *inputPathToSaveImageTo)
{
//Check if the image we are saving is of type float
if(checkFloat(inputImageToSave) == -1)
{
fprintf(stderr, "Error, the image to be saved at path %s has non-float type\n", inputPathToSaveImageTo);
return 0;
}

//Make sure the image is three dimensional
if(inputImageToSave->ifsdims != 3)
{
fprintf(stderr, "Error, the image to be saved at path %s has %d dimensions (should be 3)\n", inputPathToSaveImageTo, inputImageToSave->ifsdims);
} 

//Make sure the dimensions are non-negative
if(ifsdimen(inputImageToSave, 0) < 0)
{
fprintf(stderr, "Error, the image to be saved at %s a negative frame dimension indicator\n", inputPathToSaveImageTo);
return 0;
}

if(ifsdimen(inputImageToSave, 1) < 0)
{
fprintf(stderr, "Error, the image to be saved at path %s a negative column dimension indicator\n", inputPathToSaveImageTo);
return 0;
}

if(ifsdimen(inputImageToSave, 2) < 0)
{
fprintf(stderr, "Error, the image to be saved at path %s a negative row dimension indicator\n", inputPathToSaveImageTo);
return 0;
}

//Try to save the image
if(ifsPutImg(inputImageToSave, inputPathToSaveImageTo, NULL, FALSE) != IFS_SUCCESS)
{
fprintf(stderr, "Error saving image to %s\n", inputPathToSaveImageTo);
return 0;
}

return 1;
}


/*
This function loads an image from the given path.  If there is something wrong with the path or image, the function gives a detailed error report and returns NULL.

This function checks that the image exists, is of type float and all dimensions are positive.
@param inputPathToReadFrom:  The path to read the image from (if NULL, the function fails with error rather than trying to read from stdin)
@return: An IFS image structure or NULL on failure
*/
IFSHDR *loadFloatImageWithUnknownDimensions(const char *inputPathToReadFrom)
{
if(inputPathToReadFrom == NULL)
{
fprintf(stderr, "Error, asked to load an image with a null string for the path\n");
return NULL;
}

IFSHDR *loadedImage = ifsGetImg(inputPathToReadFrom, NULL, FALSE);
if(loadedImage == NULL)
{
fprintf(stderr, "Error, it was not possible to load the image with path %s\n", inputPathToReadFrom);
return NULL; 
}

//Check if the image we loaded is of type float
if( checkFloat(loadedImage) == -1)
{
fprintf(stderr, "Error, the image at path %s has non-float type\n", inputPathToReadFrom);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}


//Check the dimensionality of the image
if(loadedImage->ifsdims != 2 && loadedImage->ifsdims != 3)
{
fprintf(stderr, "Error, the image loaded from %s has %d dimensions.  This function can only process 2D and 3D images\n", inputPathToReadFrom, loadedImage->ifsdims);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}

//Make sure the dimensions are non-negative
for(int i=0; i < loadedImage->ifsdims; i++)
{
if(ifsdimen(loadedImage, i) < 0)
{
fprintf(stderr, "Error, the image loaded from %s has %d dimension negative\n", inputPathToReadFrom,i);
ifsfree(loadedImage, IFS_FR_ALL);
return NULL;
}
}



//Checks have been passed, so return the image
return loadedImage;
}


/*
This function uses strtol to load an integer from the string and ensure it is valid.  It stores the result in the memory pointed to by inputIntegerStorage.
@param inputNumberString: The string to get the integer from
@param inputIntegerStorage: Where to store the result
@return: 1 if successful and zero otherwise
*/
int stringToInteger(const char *inputNumberString, int *inputIntegerStorage)
{
long int integerValue;
char *endPointer;

//Check storage
if(inputIntegerStorage == NULL)
{
fprintf(stderr, "Error converting %s to integer.  The pointer to store the result in is NULL\n", inputNumberString);
return 0;
}

//Attempt to convert string to long int
integerValue = strtol(inputNumberString, &endPointer, 0);
if(integerValue == 0L && inputNumberString == endPointer)
{
fprintf(stderr, "Error converting %s to integer.  Format is invalid\n", inputNumberString);
return 0;
}

if(integerValue < INT_MIN || INT_MAX < integerValue)
{
fprintf(stderr, "Error converting %s to integer.  The value it represents is too large to be stored in an integer variable\n", inputNumberString);
}

(*inputIntegerStorage) = integerValue;

//Conversion successful
return 1;
}

/*
This function uses strtod to load a double from the string and ensure it is valid.  It stores the result in the memory pointed to by inputDoubleStorage.
@param inputNumberString: The string to get the integer from
@param inputDoubleStorage: Where to store the result
@return: 1 if successful and zero otherwise
*/
int stringToDouble(const char *inputNumberString, double *inputDoubleStorage)
{
double doubleValue;
char *endPointer;

//Check storage
if(inputDoubleStorage == NULL)
{
fprintf(stderr, "Error converting %s to double.  The pointer to store the result in is NULL\n", inputNumberString);
return 0;
}

//Attempt to convert string to long int
doubleValue = strtod(inputNumberString, &endPointer);
int errnoBuffer = errno;
if(doubleValue == 0.0 && inputNumberString == endPointer)
{
fprintf(stderr, "Error converting %s to double.  Format is invalid\n", inputNumberString);
return 0;
}


if(errnoBuffer == ERANGE && (doubleValue == HUGE_VAL || doubleValue == -HUGE_VAL) )
{
fprintf(stderr, "Error converting %s to double.  The value it represents is too large to be stored in a double variable\n", inputNumberString);
return 0;
}

if(errnoBuffer == ERANGE )
{
fprintf(stderr, "Error converting %s to double.  The value it represents is too small (requires too much precision) to be stored in a double variable\n", inputNumberString);
return 0;
}

(*inputDoubleStorage) = doubleValue;

//Conversion successful
return 1;
}

/*
This function creates a IFSImage with the given dimensions.  It prints a error message if it is not possible to allocate the image and checks to make sure the arguments are nonnegative.
@param inputNumberOfColumns: The number of columns to be created
@param inputNumberOfRows: The number of rows to be created
@return: the image buffer on success and NULL on failure
*/
IFSHDR *create2DFloatImage(int inputNumberOfColumns, int inputNumberOfRows)
{
if(inputNumberOfColumns < 0)
{
fprintf(stderr, "Error, there was an attempt to make a image with a negative number of rows\n");
return NULL;
}

if(inputNumberOfRows < 0)
{
fprintf(stderr, "Error, there was an attempt to make a image with a negative number of rows\n");
return NULL;
}

//Create header parameters to allocate image data buffer
IFSHDR *outputImage=NULL;
int outputImageDimensions[3];
outputImageDimensions[0] = 2;  //Set number of dimensions of the image
outputImageDimensions[1] = inputNumberOfColumns; //Set number of columns
outputImageDimensions[2] = inputNumberOfRows; //Set number of rows

outputImage = ifscreate("float", outputImageDimensions, IFS_CR_ALL, 0);
if(outputImage == NULL)
{
fprintf(stderr, "Error allocating %d x %d image buffer\n", inputNumberOfColumns, inputNumberOfRows);
return NULL;
}

return outputImage;
}


/*
This function is just wraps the given argument to in "Error, inputOperationThatFailed operation failed\n" to stderr
@param inputOperationThatFailedName: The string to wrap and print to stderr
*/
void reportFailure(const char *inputOperationThatFailedName)
{
if(inputOperationThatFailedName == NULL)
{
return;
}

fprintf(stderr, "Error, %s operation failed\n", inputOperationThatFailedName);
}

/*
This is a function version of the flip checkFloat macro, since it seems to be causing problems in some areas.
*/
int checkFloat(IFSHDR *inputImage)
{
if(inputImage->dtype != IFST_32FLT )
{
return -1;
}

return 0;
}

/*
This function provides the max operation, since the standard library doesn't include it.
@param inputFirstNumber: The first of the two numbers to take the max of
@param inputSecondNumber: The first of the two numbers to take the max of
@return: The maximum of the two arguments
*/
int max(int inputFirstNumber, int inputSecondNumber)
{
if(inputFirstNumber > inputSecondNumber)
{
return inputFirstNumber;
}
else
{
return inputSecondNumber;
}
}

/*
This function provides the min operation, since the standard library doesn't include it.
@param inputFirstNumber: The first of the two numbers to take the min of
@param inputSecondNumber: The first of the two numbers to take the min of
@return: The minimum of the two arguments
*/
int min(int inputFirstNumber, int inputSecondNumber)
{
if(inputFirstNumber > inputSecondNumber)
{
return inputSecondNumber;
}
else
{
return inputFirstNumber;
}
}

/*
This function takes a 2D (float) IFS image and converts it to a QPixmap for display.  The image is checked to insure it is a 2D float image and has valid dimensions.  It returns a zero width QPixmap on error.  In the process of conversion, the pixels are normalized to 0-255.  This is done by calculating the min and max for the image and then shifting and scaling the value of each pixel until it fits in the appropriate range.
@param inputIFSImage: The IFS image to convert
@return: The equivalent QPixmap
*/
QPixmap convertFromIFSIMGFloatToQPixmap(IFSHDR *inputIFSImage)
{
//Check if the image we are saving is of type float
if(checkFloat(inputIFSImage) == -1)
{
fprintf(stderr, "Error, the image to be converted to QPixmap is not of type float\n");
QPixmap emptyPixmap;
return emptyPixmap;  //Return QPixmap with zero width and height
}

//Make sure the image is two dimensional
if(inputIFSImage->ifsdims != 2)
{
fprintf(stderr, "Error, the image to be converted to QPixmap has %d dimensions (should be 2)\n", inputIFSImage->ifsdims);
QPixmap emptyPixmap;
return emptyPixmap;  //Return QPixmap with zero width and height
} 

//Make sure the dimensions are non-negative
if(ifsdimen(inputIFSImage, 0) < 0)
{
fprintf(stderr, "Error, the image to be converted to QPixmap has a negative column dimension indicator\n");
QPixmap emptyPixmap;
return emptyPixmap;  //Return QPixmap with zero width and height
}

if(ifsdimen(inputIFSImage, 1) < 0)
{
fprintf(stderr, "Error, the image to be converted to QPixmap has a negative row dimension indicator\n");
QPixmap emptyPixmap;
return emptyPixmap;  //Return QPixmap with zero width and height
}

//Determine min and max of the image
float min=9999999999.9;
float max=-9999999999.9;

float rawValue;
for(int ii=0; ii<ifsdimen(inputIFSImage, 1); ii++)
{
for(int i=0; i<ifsdimen(inputIFSImage, 0); i++)
{
rawValue = ifsfgp(inputIFSImage,ii,i);
if(rawValue < min)
{
min = rawValue;
}
if(rawValue > max)
{
max = rawValue;
}
}
}

//Calculate factors to bring the image into the 0-255 range
float scaleFactor;
if(fabs(max-min)<.01) //A zero range image
{
scaleFactor = -1;
}
else
{
scaleFactor=255.0/(max-min);
}

float shiftFactor = -min*scaleFactor;

//Create a QImage of the appropriate size
QImage image(ifsdimen(inputIFSImage, 0), ifsdimen(inputIFSImage, 1), QImage::Format_RGB32);

//If the image has zero range, just set the image to the value.  Otherwise, scale and shift the values to the 0-255 range.  0xffRRGGBB
if(fabs(max-min)<.01)
{
image.fill(qRgb(min,min,min));
}
else
{ 
float scaledValue;
for(int ii=0; ii<ifsdimen(inputIFSImage, 1); ii++)
{
for(int i=0; i<ifsdimen(inputIFSImage, 0); i++)
{
scaledValue = ifsfgp(inputIFSImage,ii,i)*scaleFactor + shiftFactor;
image.setPixel(i,ii,qRgb(scaledValue,scaledValue,scaledValue));
}
}
}

//Convert from image to QPixmap
QPixmap pixMap;
pixMap.convertFromImage(image);

return pixMap;
}

