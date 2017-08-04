/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: ImageIO.h      			                                     */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2011/01/25                                                          */
/*                                                                           */
/* Description: ͼ���ȡ���湦��                                             */
/*                                                                           */
/* Others: ��һ������Ҫ���ڵ��ԣ���������ʵ��Ӧ���޹ء�����OpenCvͼ�����  */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/

#ifndef _IMAGE_IO_H_
#define _IMAGE_IO_H_

#include "BaseConstDef.h"
#include "BaseTypeDef.h"
#include <stdio.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "DataIO.h"

extern void ImageOpenCv2Hustsong(IN IplImage *pIamge, OUT IMAGE_S *img);
extern void Image16OpenCv2Hustsong(IN IplImage *pIamge, OUT IMAGE32_S *img);
extern IplImage *ImageHustsong2OpenCv(IN IMAGE_S *img, IN RECT_S *rect);
extern void ImageHustsong2OpenCv(IN IMAGE_S *img, OUT IplImage *pIamge, IN RECT_S *rect);
extern void Image16Hustsong2OpenCv(IN IMAGE32_S *img, OUT IplImage *pIamge, IN RECT_S *rect);
extern void ImageHustsong2Parallel(IN IMAGE_S *img, OUT IMAGE_S *img2);

extern bool MatRead(cv::Mat& mat, OUT IMAGE_S *img);
extern void ImageRead(IN char *filename, OUT IMAGE_S *img);
extern void Image16Read(IN char *filename, OUT IMAGE32_S *img);
extern void Image16Read(IN char* filename, OUT IMAGE32_S *img, IN int buffer);
extern void ImageReadParallel(IN char* filename, OUT IMAGE_S *img);
extern void ImageReadChannel(IN char* filename, OUT IMAGE_S *img, IN int channel);
extern void ImageRead(IN char *filename, OUT IMAGE_S *img, IN int buffer);
extern void ImageReadFree(IN char* filename, IN IMAGE_S *img, IN int buffer);

extern void ImageSave(IN char *filename, IN IMAGE_S *img, IN RECT_S *rect);
extern cv::Mat Image16Mat(IN IMAGE32_S *img, IN RECT_S *rect);
extern void Image16Save(IN char* filename, IN IMAGE32_S *img, IN RECT_S *rect);
extern void ImageReadCcs(IN char *filename, OUT IMAGE_S *img);
extern void ImageSaveCcs(IN char *filename, IN IMAGE_S *img);
extern void ImageSaveQuartus(IN char *filename, IN IMAGE_S *img);
extern void ImageInt2Pixel(IN IMAGE32_S *srcImage, OUT IMAGE_S *dstImage, IN RECT_S *rect);
extern void ImageFree(INOUT IMAGE_S *img);
extern void ImageShow(IN char* filename, IN IMAGE_S *img, IN RECT_S *rect);
extern cv::Mat Image2Mat(IN IMAGE_S *img, IN RECT_S *rect);

extern void ImageRawReadCcs(IN char *filename, OUT IMAGE_S *img);
extern void ImageRaw16ReadCcs(IN char *filename, OUT IMAGE_S *img, IN int bits);

/* ͼ������ */
typedef enum tagImageType
{
    IMAGE_TYPE_UNKNOWN = 0, // δ֪
    IMAGE_GRAY_BIT,         // С��8λ�Ҷ�
    IMAGE_GRAY_8,           // 8λ�Ҷ�
    IMAGE_COLOR_BIT,        // С��8λ��ɫ(��ɫ��)
    IMAGE_COLOR_PALETTE,    // 8λ��ɫ(��ɫ��)
    IMAGE_COLOR_RGB,        // 24λ���ɫ
    IMAGE_COLOR_RGBA,       // 32λ���ɫ+alphaͨ��
    IMAGE_TYPE_MAX

}IMAGE_TYPE_E;

typedef enum tagImageDataSeq
{
    IMAGE_SEQ_NORMAL = -1,      // height*width*channel
    IMAGE_SEQ_PARALLEL = -2,    // channel*width*height
    IMAGE_SEQ_MATLAB = -3,      // width*height*channel
    IMAGE_SEQ_MAX

}IMAGE_DATA_SEQ_E;

#endif

