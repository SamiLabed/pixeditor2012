#include "include/image.h"
#include "include/Flou.h"

int main(int argc, char *argv[])
{
    IplImage* img = 0;
    IplImage* imgfloat = 0;
    int height,width,step,channels;
    uchar *data;
    RgbPixelFloat *rgb;
    int i,j,k;


    // load an image
    img=cvLoadImage("lena.jpg");

    imgfloat = cvCreateImage(cvGetSize(img), IPL_DEPTH_32F, 3);
    cvConvertScale(img, imgfloat, 1/255.);


    if(!img)
    {
        printf("Could not load image file: %s\n",argv[1]);
        exit(0);
    }

    // get the image data
    height    = img->height;
    width     = img->width;
    step      = img->widthStep;
    channels  = img->nChannels;
    data      = (uchar *)img->imageData;
    rgb       = (RgbPixelFloat *) imgfloat->imageData;
    printf("Processing a %dx%d image with %d channels\n",height,width,channels);


    // create a window
    cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("mainWin", 100, 100);



    RgbImageFloat imgA(imgfloat);


    Flou f (15, height, width);

    for(i=0; i < height; i++)
    {
        for(j=0; j < width; j++)
        {
            imgA[i][j].b = f.calculMoy(i, j, imgA, 'b');
            imgA[i][j].g = f.calculMoy(i, j, imgA, 'g');
            imgA[i][j].r = f.calculMoy(i, j, imgA, 'r');
        }
    }

    // show the image
    cvShowImage("mainWin", imgfloat );

    // wait for a key
    cvWaitKey(0);

    // release the image
    cvReleaseImage(&img );
    return 0;
}
