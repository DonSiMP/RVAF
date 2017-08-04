/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: ImageRegionFeature.h 			                                 */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2014/12/29                                                          */
/*                                                                           */
/* Description: ͼ����������                                                 */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/
#ifndef _IMAGE_REGION_FEATURE_H_
#define _IMAGE_REGION_FEATURE_H_

#ifdef __cplusplus
extern "C"{
#endif /* end of __cplusplus */

#include "BaseConstDef.h"
#include "BaseTypeDef.h"
#include "BaseFuncDef.h"
#include <string.h>

#include "DataTypeConvert.h"
#include "ImageColor.h"
#include "VectorBasic.h"


#define FEA_NUM_STAT    4
#define FEA_NUM_GEO     11
#define FEA_NUM_LOC     4


#define FEA_Q_VEC               16
#define FEA_S_VEC               65536
#define FEA_Q_STAT              8
#define FEA_S_STAT              256

#define FEA_MAX_STAT_DIFF       0.125
#define FEA_MAX_STAT_DIFF_Q     8192
#define FEA_MAX_STAT_NUM        2048


// ��
typedef struct tagMomentIntInfo
{
    int m00;        // ��׾�
    int m01;        // x����һ�׾�
    int m10;        // y����һ�׾�
    int64 m11;      // xy����Ķ��׾�
    int64 m02;      // x����Ķ��׾�
    int64 m20;      // y����Ķ��׾�

}MomentIntInfo;

// �����е�ֱ��
typedef struct tagImageRegionLine
{
    int rowcol;                         // �л���
    int start;                          // ��ʼλ��
    int end;                            // ��ֹλ��
    int mark;                           // ����������

    struct tagImageRegionLine *next;

}ImageRegionLine;

// image line info
typedef struct tagImageLineInfo
{
    int *LineCount;             // ÿ��������ֱ�߸���
    int *LineNumber;            // ÿ�л�����ֱ�߸���
    int *LinePos;               // ÿ�л�������ʼֱ������
    ImageRegionLine *LineList;  // ֱ��(��ɨ�跽����)
    ImageRegionLine **LineHead; // ÿ�������Ӧ��ֱ������ͷ
    ImageRegionLine **LineTail; // ÿ�������Ӧ��ֱ������β

}ImageLineInfo;

// ͼ��ͳ����Ϣ
typedef struct tagIrfStatInfo
{
	double mean;        // ��ֵ
	double var;         // ��׼��
	double skew;        // ƫ��ϵ��
	double kurt;        // ���ϵ��

}IrfStatInfo;

typedef struct tagIrfStatInfoInt
{
	int mean;       // ��ֵ
	int var;        // ��׼��
	int skew;       // ƫ��ϵ��
	int kurt;       // ���ϵ��

}IrfStatInfoInt;

// ������״��Ϣ
typedef struct tagIrfGeoInfo
{
	double area;            // ���
	double perimeter;       // ��׼��
	double circularity1;    // Բ��1(�ܳ������)
	double circularity2;    // Բ��2(�ؼ���)

	// �������ľ�
	double m11;
	double m02;
	double m20;

    // ��Բ���Ծ�
    double longaxis;        // ����
    double shortaxis;       // ����
    double eccentricity;    // ƫ����
    double angle;           // �����

}IrfGeoInfo;

// λ����Ϣ: ��ͼ������Ϊԭ��
typedef struct tagIrfLocationInfo
{
	double x;
	double y;
	double d;   // ����
	double a;   // ����

}IrfLocationInfo;

// ������ȡ�ṹ
typedef struct tagIrfFeaInfo
{
    // ����
    BOOL isRgbStat;
    BOOL isGeo;
    BOOL isLoc;

    // ͼ����Ϣ
    Matrix_S grayImage;
    Matrix_S matseq[3];

    // ������Ϣ
    int *pointnum;
    int *pointpos;
    POINT3D_S *point;
    ImageLineInfo horline;
    ImageLineInfo verline;
    MomentIntInfo *mom;
    double *color;
    IMAGE32_S edgeImage;
    int *edgenum1;          // �ظ���Ե
    int *edgenum2;          // ���ظ���Ե

    // ͳ������
    IrfStatInfo *stat;
    IrfStatInfoInt *statint;
    IrfGeoInfo *geo;
    IrfLocationInfo *loc;

    // ͼ���ڴ���Ϣ
    int maxHeight;
    int maxWidth;
    int maxChannel;
    int maxRegionnum;

}IrfFeaInfo;


// �ӿں���
extern void IrfFeaturePara(OUT IrfFeaInfo *feainfo);
extern void IrfFeatureInit(OUT IrfFeaInfo *feainfo);
extern void IrfFeatureDestroy(OUT IrfFeaInfo *feainfo);
extern void IrfFeatureMemoryAdapt(OUT IrfFeaInfo *feainfo, 
                                  IN int height, 
                                  IN int width,
                                  IN int regionnum);
extern void IrfFeatureProc(IN IrfFeaInfo *feainfo,
                           IN IMAGE32_S *markImage,
                           IN Matrix_S *colorImage, 
                           IN int regionnum,
                           OUT double *feature,
                           IN int feanum);
extern int IrfFeatureNum(IN IrfFeaInfo *feainfo, IN int channel);


// �ڲ�����
extern void IrfStat2Vector(IN IrfStatInfo *stat, 
                           IN int regionnum,
                           IN double *feature,
                           IN int step);
extern void IrfGeo2Vector(IN IrfGeoInfo *geo, 
                          IN int regionnum,
                          IN double *feature,
                          IN int step);
extern void IrfLoc2Vector(IN IrfLocationInfo *loc, 
                          IN int regionnum,
                          IN double *feature,
                          IN int step);

extern void IrfFeatureGeoLoc(IN int *edgenum,
                             IN MomentIntInfo *geoMoment,
                             OUT IrfGeoInfo *geoStat,
                             OUT IrfLocationInfo *locStat,
                             IN int height,
                             IN int width,
                             IN int regionnum);
extern void IrfFeatureStatistics(IN double *image,
                                 IN POINT3D_S *point,
                                 IN int *pointnum,
                                 IN int regionnum,
                                 OUT IrfStatInfo *stat);
extern void IrfStatOne(IN double *image, 
                       IN POINT3D_S *point,
                       IN int pointnum,
                       OUT IrfStatInfo *stat);


extern void IrfRegionInfo(IN IrfFeaInfo *feainfo,
                          IN IMAGE32_S *markImage,
                          IN int regionnum);
extern void IrfArea(IN IMAGE32_S *markImage, OUT int *area, IN int regionnum);
extern void IrfPoint(IN IMAGE32_S *markImage, 
                     IN int *pos,
                     OUT POINT3D_S *point,
                     OUT int *area, 
                     IN int regionnum);
extern void IrfLine(IN IMAGE32_S *markImage,
                    IN int regionNum,
                    OUT ImageLineInfo *line, 
                    IN int direct);
extern void IrfEdgeFromLine(IN ImageLineInfo *line, 
                            IN int regionNum,
                            INOUT IMAGE32_S *edgeImage,
                            OUT int *edgenum1,
                            OUT int *edgenum2,
                            IN int direct);

extern void IrfGeomomentFromLine(IN ImageLineInfo *line, 
                                 OUT MomentIntInfo *geoMoment, 
                                 IN int regionNum,
                                 IN int height);

extern void RegionLineInit(OUT ImageLineInfo *L, 
                           IN int maxVertexNum,
                           IN int maxLineNum,
                           IN int maxLineGroup);
extern void RegionLineDestroy(OUT ImageLineInfo *L, 
                              IN int maxVertexNum,
                              IN int maxLineNum,
                              IN int maxLineGroup);

extern void HistAccum(IN int *h1, OUT int *h2, IN int n);



extern void IrfFeatureProcInt(IN IrfFeaInfo *feainfo,
                              IN IMAGE32_S *markImage,
                              IN IMAGE_S *colorImage, 
                              IN int regionnum,
                              OUT int *feature,
                              IN int feanum);
extern void IrfFeatureStatisticsInt(IN PIXEL *image,
                                    IN int channel,
                                    IN POINT3D_S *point,
                                    IN int *pointnum,
                                    IN int regionnum,
                                    OUT IrfStatInfoInt *stat);
extern void IrfStatOneInt(IN PIXEL *image, 
                          IN int channel,
                          IN POINT3D_S *point,
                          IN int pointnum,
                          OUT IrfStatInfoInt *stat);
extern void IrfStat2VectorInt(IN IrfStatInfoInt *stat, 
                              IN int regionnum,
                              IN int *feature,
                              IN int step);
extern void IrfGeo2VectorInt(IN IrfGeoInfo *geo, 
                             IN int regionnum,
                             IN int *feature,
                             IN int step);
extern void IrfLoc2VectorInt(IN IrfLocationInfo *loc, 
                             IN int regionnum,
                             IN int *feature,
                             IN int step);


#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif
