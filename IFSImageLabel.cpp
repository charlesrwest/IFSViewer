#include "IFSImageLabel.h"

/*
This function initializes the object with a NULL for the IFSImage and a minimum size of 1,1.
@param inputParent: The parent widget for this label
*/
IFSImageLabel::IFSImageLabel(QWidget *inputParent) : QLabel(inputParent)
{
this->setMinimumSize(1,1);
this->ifsImage=NULL;
setMouseTracking(true); //Be informed whenever the mouse crosses over this label
}

/*
This function returns what would be the appropriate high for the image to maintain its aspect ratio with the given width
@param inputWidth: The width to find a height for
@return: The appropriate height 
*/
int IFSImageLabel::heightForWidth(int inputWidth)
{
return ((qreal)pixmap0.height()*inputWidth)/pixmap0.width();
}

/*
This function tells Qt the size that the widget would prefer.
@return: The appropriate size
*/
QSize IFSImageLabel::sizeHint()
{
int width = this->width();
return QSize(width, heightForWidth(width));
}

/*
This function converts from the widget coordinate system to the coordinate system of the scaled QPixmap associated with the image
@param inputPoint: The point in widget space
@return: The point in picture space
*/
QPoint IFSImageLabel::convertFromLabelToPictureCoordinates(QPoint inputPoint)
{
if(this->pixmap() == NULL)
{
return QPoint(0.0,0.0);
}
double yOffset = -(this->height() - this->pixmap()->height())/2.0;

double xOffset = -(this->width() - this->pixmap()->width())/2.0;

double scaleFactor = ((double) pixmap0.width())/((double) this->pixmap()->width());

return QPoint((inputPoint.x() + xOffset)*scaleFactor, (inputPoint.y() + yOffset)*scaleFactor);
}



/*
This signal updates the QPixmap in this image and updates the QPixmap in the inherited QLabel to match
@param inputPixmap: The QPixmap to use
*/
void IFSImageLabel::setPixmap(const QPixmap &inputPixmap)
{
pixmap0 = inputPixmap;
QLabel::setPixmap(pixmap0);
}

/*
This function loads a new IFS image for display.  It deletes the previously stored IFS image (if any) and causes the QPixmaps and widgets to update.
*/
void IFSImageLabel::setIFSImage(IFSHDR *inputIFSImage)
{
if(inputIFSImage == NULL)
{
return;
}

if(ifsImage != NULL)
{
ifsfree(ifsImage, IFS_FR_ALL);
}

ifsImage = inputIFSImage;
setPixmap(convertFromIFSIMGFloatToQPixmap(ifsImage));

QResizeEvent sameSizeEvent(QSize(width(), height()), QSize(width(), height()));
resizeEvent(&sameSizeEvent);
}

/*
This function generates a scaled QPixmap in reaction to the widget changing size
@param inputEvent: The event object with the details of the resize
*/
void IFSImageLabel::resizeEvent(QResizeEvent *inputEvent)
{
if(pixmap0.width() != 0)
{
QLabel::setPixmap(pixmap0.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
}

/*
This function is called when the mouse moves over the label.  It computes and emits signals corresponding to the row, column and value of the associated image pixels
@param inputEvent: The event related to the mouse moving
*/
void IFSImageLabel::mouseMoveEvent(QMouseEvent *inputEvent)
{
//Don't update if we don't have an image
if(ifsImage == NULL)
{
return;
}

QPoint position(convertFromLabelToPictureCoordinates(QPoint(inputEvent->x(),inputEvent->y())));

double scaleFactor = ((double) pixmap0.width())/((double) this->pixmap()->width());

if(position.x() >= 0 && position.x() < this->pixmap()->width()*scaleFactor && position.y() >= 0 && position.y() < this->pixmap()->height()*scaleFactor && position.x() < ifsdimen(ifsImage, 0) && position.y() < ifsdimen(ifsImage, 1))
{
emit imageCursorColumn(position.x());
emit imageCursorRow(position.y());
emit imageCursorValue(ifsfgp(ifsImage,position.y(), position.x()));
}
}
