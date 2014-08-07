#ifndef IFSIMAGELABELH
#define IFSIMAGELABELH

#include<QLabel>
#include<QPixmap>
#include<QResizeEvent>
extern "C"
{
#include<ifs.h>
}
#include "utilityFunctions.h"
#include<vector>

/*
This object inherited from QLabel so that it could provide a few extra features.  It permits a QPixmap to be displayed with scaling that allows for the aspect ratio of the pixmap to be maintained.  It also allows determination of where the mouse is relative to the scaled QPixmap so that the position in the original IFS image can be determined.  In addition, it allows easy displaying and storage of IFSImages.  The image resizing portion of this code was based on an example from stack overflow: http://stackoverflow.com/questions/8211982/qt-resizing-a-qlabel-containing-a-qpixmap-while-keeping-its-aspect-ratio
*/
class IFSImageLabel : public QLabel
{
Q_OBJECT
public:
/*
This function initializes the object with a NULL for the IFSImage and a minimum size of 1,1.
@param inputParent: The parent widget for this label
*/
IFSImageLabel(QWidget *inputParent=0);

/*
This function returns what would be the appropriate high for the image to maintain its aspect ratio with the given width
@param inputWidth: The width to find a height for
@return: The appropriate height 
*/
virtual int heightForWidth(int inputWidth);

/*
This function tells Qt the size that the widget would prefer.
@return: The appropriate size
*/
virtual QSize sizeHint();

/*
This function converts from the widget coordinate system to the coordinate system of the QPixmap associated with the image
@param inputPoint: The point in widget space
@return: The point in picture space
*/
QPoint convertFromLabelToPictureCoordinates(QPoint inputPoint);

QPixmap pixmap0;
IFSHDR *ifsImage;

signals:
/*
This signal sends out the double associated with the value of the image at the mouse cursor point
@param inputValue: The value at the cursor
*/
void imageCursorValue(double inputValue);

/*
This signal sends out the integer associated with the row of the image at the mouse cursor point
@param inputRow: The row at the cursor
*/
void imageCursorRow(int inputRow);

/*
This signal sends out the integer associated with the column of the image at the mouse cursor point
@param inputColumn: The column at the cursor
*/
void imageCursorColumn(int inputColumn);

public slots:

/*
This signal updates the QPixmap in this image and updates the QPixmap in the inherited QLabel to match
@param inputPixmap: The QPixmap to use
*/
void setPixmap(const QPixmap &);

/*
This function loads a new IFS image for display.  It deletes the previously stored IFS image (if any) and causes the QPixmaps and widgets to update.
*/
void setIFSImage(IFSHDR *);

/*
This function generates a scaled QPixmap in reaction to the widget changing size
@param inputEvent: The event object with the details of the resize
*/
void resizeEvent(QResizeEvent *);

/*
This function is called when the mouse moves over the label.  It computes and emits signals corresponding to the row, column and value of the associated image pixels
@param inputEvent: The event related to the mouse moving
*/
void mouseMoveEvent(QMouseEvent *);

private:

};




















#endif
