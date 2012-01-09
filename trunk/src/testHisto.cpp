#include "include/openCv.h"
#include "include/image.h"

void PPHisto(char* chemin)
{

    IplImage* img = 0;
    IplImage* imgfloat = 0;
    int height, width;
    //int step, channels;
    //uchar *data;
    //RgbPixelFloat *rgb;
    //int i, j;
    //int k;

    // load an image

    img = cvLoadImage(chemin, 1);
    //img = cvLoadImage("/home/cr3wsti/workspace/pixeditor/bin/Debug/lena.jpg", 1);

    imgfloat = cvCreateImage(cvGetSize(img), IPL_DEPTH_32F, 3);
    cvConvertScale(img, imgfloat, 1/255.);

    if (!img)
    {
        printf("Could not load image file: %s\n", chemin);
        exit(0);
    }

    // get the image data
    height    = img->height;
    width     = img->width;
    //step      = img->widthStep;
    //channels  = img->nChannels;
    //data      = (uchar *)img->imageData;
    //rgb       = (RgbPixelFloat *) imgfloat->imageData;

    RgbImageFloat imgA(imgfloat);

    // create a window
    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Image", 100, 100);

    // show the image
    cvShowImage("mainWin", imgfloat);

    // wait for a key
    cvWaitKey(0);

    // release the image
    cvReleaseImage(&img);


    ///////// Histogrammes //////////


    RgbHisto pHist = histogramme(imgA, width, height);

    cvNamedWindow("HistoR", CV_WINDOW_AUTOSIZE);
    cvShowImage("HistoR", pHist.histR);
    cvWaitKey(0);
    cvReleaseImage(&pHist.histR);

    cvNamedWindow("HistoG", CV_WINDOW_AUTOSIZE);
    cvShowImage("HistoG", pHist.histG);
    cvWaitKey(0);
    cvReleaseImage(&pHist.histG);

    cvNamedWindow("HistoB", CV_WINDOW_AUTOSIZE);
    cvShowImage("HistoB", pHist.histB);
    cvWaitKey(0);
    cvReleaseImage(&pHist.histB);

}
