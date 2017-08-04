/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: ImageMatchEadp.h 			                                     */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2015/05/05                                                          */
/*                                                                           */
/* Description: Eadp�㷨                                                     */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/
#ifndef _IMAGE_MATCH_EADP_H_
#define _IMAGE_MATCH_EADP_H_

#ifdef __cplusplus
extern "C"{
#endif /* end of __cplusplus */

#include "BaseConstDef.h"
#include "BaseTypeDef.h"
#include "BaseFuncDef.h"
#include <string.h>

#include "ctmf.h"
#include "ctmfopt.h"
//#include "ImageMedian3x3.h"
#include "ImageGradient.h"
#include "ImageMatchCost.h"
#include "ImageMatchAggregation.h"
#include "ImageMatchPostprocess.h"

typedef struct tagImEadpInfo
{
    // �ⲿ��Ϣ
    int imagenum;
    int height;
    int width;
    int channel;
    int dlength;
    IMAGE_S *src[2];

    // ����
    int mode;
    int guildmr;        // guild image ��ֵ�˲��뾶
    int dispmr;         // ����label����ֵ�˲��뾶
    float sg;
    float sc;
    float r1;
    float r2;

    // �ڲ���Ϣ
    int *imagecost;
    IMAGE_S filter[2];
    IMAGE32_S Gx[2];
    IMAGE32_S Gy[2];
    ImaScanTreeIntInfo aggr;
    ImppInvalidInfo invalid;

    // ����Ӳ�
    PIXEL *left;
    PIXEL *right;
    PIXEL *sparse;
    PIXEL *fill;
    PIXEL *dense;

}ImEadpInfo;

extern void ImageMatchEadpPara(INOUT ImEadpInfo *eadp);
extern void ImageMatchEadpInit(INOUT ImEadpInfo *eadp);
extern void ImageMatchEadpDestroy(INOUT ImEadpInfo *eadp);
extern void ImageMatchEadpProc(INOUT ImEadpInfo *eadp);
extern void EadpGradient(INOUT ImEadpInfo *eadp);
extern void ImageGrayMedian3x3(IN IMAGE_S *src, OUT IMAGE_S *filter);
extern void ImageColorMedian3x3(IN IMAGE_S *src, OUT IMAGE_S *filter);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif
