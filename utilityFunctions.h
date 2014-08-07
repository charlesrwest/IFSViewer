#ifndef UTILITYFUNCTIONSH
#define UTILITYFUNCTIONSH


#include<stdlib.h>
#include<limits.h>
#include<errno.h>
#include<math.h>
#include<ifs.h>
#include<flip.h>
#include<ifstypes.h>

//QT related stuff
#include<QPixmap>
#include<QImage>



/*

struct IFSDIM has a field (ifsdt) which is a string datatype denoting the type of number format used.  In addition, flip.h defines a macro which allows for easy checking of if a image has float datatype.
*/

/*
This function loads an image from the given path.  If there is something wrong with the path or image, the function gives a detailed error report and returns NULL.

This function checks that the image exists, is of type float, has exactly 2 dimensions and both dimensions are positive.
@param inputPathToReadFrom:  The path to read the image from (if NULL, the function fails with error rather than trying to read from stdin)
@return: An IFS image structure or NULL on failure
*/
IFSHDR *load2DFloatImage(const char *inputPathToReadFrom);

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
IFSHDR *load2DFloatImageWithBoundsChecking(const char *inputPathToReadFrom, int inputMinimumNumberOfColumns, int inputMinimumNumberOfRows, int inputMaximumNumberOfColumns, int inputMaximumNumberOfRows);


/*
This function checks that the image is of type float and has non-negative dimensions.  If then attempts to save the image to the given path.  If a failure occurs, the error is reported and 0 is returned.
@param inputImageToSave: The IFS image to save
@param inputPathToSaveImageTo: The path to save the image to
@return: 1 on success and 0 otherwise
*/
int save2DFloatImage(IFSHDR *inputImageToSave,const char *inputPathToSaveImageTo);


/*
This function loads an image from the given path.  If there is something wrong with the path or image, the function gives a detailed error report and returns NULL.

This function checks that the image exists, is of type float, has exactly 3 dimensions and both dimensions are positive.
@param inputPathToReadFrom:  The path to read the image from (if NULL, the function fails with error rather than trying to read from stdin)
@return: An IFS image structure or NULL on failure
*/
IFSHDR *load3DFloatImage(const char *inputPathToReadFrom);


/*
This function checks that the image is of type float and has non-negative dimensions.  If then attempts to save the image to the given path.  If a failure occurs, the error is reported and 0 is returned.
@param inputImageToSave: The IFS image to save
@param inputPathToSaveImageTo: The path to save the image to
@return: 1 on success and 0 otherwise
*/
int save3DFloatImage(IFSHDR *inputImageToSave,const char *inputPathToSaveImageTo);

/*
This function loads an image from the given path.  If there is something wrong with the path or image, the function gives a detailed error report and returns NULL.

This function checks that the image exists, is of type float and all dimensions are positive.
@param inputPathToReadFrom:  The path to read the image from (if NULL, the function fails with error rather than trying to read from stdin)
@return: An IFS image structure or NULL on failure
*/
IFSHDR *loadFloatImageWithUnknownDimensions(const char *inputPathToReadFrom);

/*
This function uses strtol to load an integer from the string and ensure it is valid.  It stores the result in the memory pointed to by inputIntegerStorage.
@param inputNumberString: The string to get the integer from
@param inputIntegerStorage: Where to store the result
@return: 1 if successful and zero otherwise
*/
int stringToInteger(const char *inputNumberString, int *inputIntegerStorage);

/*
This function uses strtod to load a double from the string and ensure it is valid.  It stores the result in the memory pointed to by inputDoubleStorage.
@param inputNumberString: The string to get the integer from
@param inputDoubleStorage: Where to store the result
@return: 1 if successful and zero otherwise
*/

int stringToDouble(const char *inputNumberString, double *inputDoubleStorage);

/*
This function creates a IFSImage with the given dimensions.  It prints a error message if it is not possible to allocate the image and checks to make sure the arguments are nonnegative.
@param inputNumberOfColumns: The number of columns to be created
@param inputNumberOfRows: The number of rows to be created
@return: the image buffer on success and NULL on failure
*/
IFSHDR *create2DFloatImage(int inputNumberOfColumns, int inputNumberOfRows);

/*
This function is just wraps the given argument to in "Error, inputOperationThatFailed operation failed\n" to stderr
@param inputOperationThatFailedName: The string to wrap and print to stderr
*/
void reportFailure(const char *inputOperationThatFailedName);

/*
This is a function version of the flip CHECKFLOAT macro, since it seems to be causing problems in some areas.
*/
int checkFloat(IFSHDR *inputImage);

/*
This function provides the max operation, since the standard library doesn't include it.
@param inputFirstNumber: The first of the two numbers to take the max of
@param inputSecondNumber: The first of the two numbers to take the max of
@return: The maximum of the two arguments
*/
int max(int inputFirstNumber, int inputSecondNumber);

/*
This function provides the min operation, since the standard library doesn't include it.
@param inputFirstNumber: The first of the two numbers to take the min of
@param inputSecondNumber: The first of the two numbers to take the min of
@return: The minimum of the two arguments
*/
int min(int inputFirstNumber, int inputSecondNumber);

/*
This function takes a 2D (float) IFS image and converts it to a QPixmap for display.  The image is checked to insure it is a 2D float image and has valid dimensions.  It returns a zero width QPixmap on error.  In the process of conversion, the pixels are normalized to 0-255.  This is done by calculating the min and max for the image and then shifting and scaling the value of each pixel until it fits in the appropriate range.
@param inputIFSImage: The IFS image to convert
@return: The equivalent QPixmap
*/
QPixmap convertFromIFSIMGFloatToQPixmap(IFSHDR *inputIFSImage);



#endif
