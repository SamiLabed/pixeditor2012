#ifndef FUSION_H
#define FUSION_H
#include "Image.h"
class Fusion
{
public:
    Fusion();
    virtual ~Fusion();
    void calculFusion(RgbImage imbase,RgbImage imgchoisi,float p );
};

#endif // FUSION_H
