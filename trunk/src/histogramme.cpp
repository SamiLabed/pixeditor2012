#include "include/openCv.h"
#include "include/image.h"

RgbHisto histogramme(RgbImageFloat img, int width, int height)
{
    int x, y, i;
    RgbHisto res;
    int windowWidth = 300;
    int windowHeight = 500;
    int histoR[256];
    int histoG[256];
    int histoB[256];
    int maxR = 0;
    int maxG = 0;
    int maxB = 0;
    float tmpR, tmpG, tmpB;
    int tempR, tempG, tempB;

    res.histR = cvCreateImage(cvSize(windowWidth, windowHeight), IPL_DEPTH_32F, 3);
    res.histG = cvCreateImage(cvSize(windowWidth, windowHeight), IPL_DEPTH_32F, 3);
    res.histB = cvCreateImage(cvSize(windowWidth, windowHeight), IPL_DEPTH_32F, 3);

    for (i=0; i<256; i++){
        histoR[i] = 0;
        histoG[i] = 0;
        histoB[i] = 0;
    }

    /* Calcul de l'histogramme */
    for (x=0; x<width; x++)
    {
        for (y=0; y<height; y++)
        {
            tmpR = img[x][y].r*255;
            tempR = (int)tmpR;
            histoR[tempR]++;
            tmpG = img[x][y].g*255;
            tempG = (int)tmpG;
            histoG[tempG]++;
            tmpB = img[x][y].b*255;
            tempB = (int)tmpB;
            histoB[tempB]++;
            if (histoR[tempR] > histoR[maxR])
                maxR = tempR;
            if (histoG[tempG] > histoG[maxG])
                maxG = tempG;
            if (histoB[tempB] > histoB[maxB])
                maxB = tempB;
            //printf("histoR[%d] = %d\nhistoG[%d] = %d\nhistoB[%d] = %d\n", tempR, histoR[tempR], tempG, histoG[tempG], tempB, histoB[tempB]);

        }
    }

    /* Dessin de l'histogramme */
    for (x=0; x<256; x++)
    {
        cvLine(res.histR, cvPoint(x, windowHeight-1), cvPoint(x, ((windowHeight-1)-histoR[x]/10)), cvScalar(0, 0, 255), 1);
        //if (histoR[x]<256) cvLine(res.histR, cvPoint(x, histoR[x]+1), cvPoint(x,0), cvScalar(255, 255, 255), 1);
        cvLine(res.histG, cvPoint(x, windowHeight-1), cvPoint(x, ((windowHeight-1)-histoG[x]/10)), cvScalar(0, 255, 0), 1);
        cvLine(res.histB, cvPoint(x, windowHeight-1), cvPoint(x, ((windowHeight-1)-histoB[x]/10)), cvScalar(255, 0, 0), 1);
    }

    return res;
}
