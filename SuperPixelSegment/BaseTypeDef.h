/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: BaseTypeDef.h 			                                         */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2011/01/23                                                          */
/*                                                                           */
/* Description: ���峣�����ͽṹ                                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*****************************************************************************/

#ifndef _BASE_TYPE_DEF_H_
#define _BASE_TYPE_DEF_H_

#include "BaseConstDef.h"
/******************************************************************************
 *                              �������ͼ�д
******************************************************************************/
// ע: �ڵ�ǰpc(32λ)�ϣ�intΪ4���ֽ�(��longһ��)
typedef int                 BOOL;
typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned long       ulong;

typedef unsigned char       unit8;
typedef unsigned short      unit16;
typedef unsigned int        unit32;

#ifdef PLATFORM_VC6
typedef unsigned __int64    unit64;
#elif defined(PLATFORM_GCC)
typedef unsigned long long  unit64;
#elif defined(PLATFORM_CCS)
typedef unsigned long long  unit64;
#endif

#ifdef PLATFORM_VC6
typedef __int64             int64;
#elif defined(PLATFORM_GCC)
typedef long long           int64;
#elif defined(PLATFORM_CCS)
typedef long long           int64;
#endif

typedef union tagmix32
{
    float f32;
    int i32;
    unit32 ui32;
    ushort ui16[2]; 
    unit8 ui8[4]; 

}mix32;

typedef union tagmix64
{
    double f64;
    int64 i64;
    unit64 ui64;
    struct tagdi32
    {
        unit32 i32low;
        int i32high;
    }di32;
    struct tagdu32
    {
        unit32 ui32low;
        unit32 ui32high;
    }du32;

}mix64;


/******************************************************************************
 *                               ��������
******************************************************************************/

// ϵͳһ������µĸ���
#if FLOAT_TYPE_GEN == 0
    typedef _iq             floatgen;
#elif FLOAT_TYPE_GEN == 1
    typedef float           floatgen;
#else
    typedef double          floatgen;
#endif

// �ָ�ģ�鸡��
#if FLOAT_TYPE_SEG == 0
    typedef _iq             floatseg;
    #define VectorDistFloatSeg      VectorDistInt
#elif FLOAT_TYPE_SEG == 1
    typedef float           floatseg;
    #define VectorDistFloatSeg      VectorDistFloat
#else
    typedef double          floatseg;
    #define VectorDistFloatSeg      VectorDistDouble
#endif

// costģ�鸡��(��ʱ��֧��IQ�Ż�)
#if FLOAT_TYPE_COST == 0
    typedef _iq                     floatcost;
    #define expff(x)                exp(x)

    #define VectorDistFloatCost     VectorDistInt
    #define VectorPlusFloatCost     VectorPlusInt
    #define VectorSubFloatCost      VectorSubInt
    #define VectorMulConstFloatCost VectorMulConstInt
    #define VectorPlusMulConstFloatCost VectorPlusMulConstInt
    #define StatSumFloatCost        StatSumInt
    #define StatMinIndexFloatCost   StatMinIndexInt
    #define StatMinIndex12FloatCost StatMinIndex12Int
#elif FLOAT_TYPE_COST == 1
    typedef float                   floatcost;
    #define expff(x)                (float)exp(x)

    #define VectorDistFloatCost     VectorDistFloat
    #define VectorPlusFloatCost     VectorPlusFloat
    #define VectorSubFloatCost      VectorSubFloat
    #define VectorMulConstFloatCost VectorMulConstFloat
    #define VectorPlusMulConstFloatCost VectorPlusMulConstFloat
    #define StatSumFloatCost        StatSumFloat
    #define StatMinIndexFloatCost   StatMinIndexFloat
    #define StatMinIndex12FloatCost StatMinIndex12Float
#else
    typedef double                  floatcost;
    #define expff(x)                exp(x)

    #define VectorDistFloatCost     VectorDistDouble
    #define VectorPlusFloatCost     VectorPlusDouble
    #define VectorSubFloatCost      VectorSubDouble
    #define VectorMulConstFloatCost VectorMulConstDouble
    #define VectorPlusMulConstFloatCost VectorPlusMulConstDouble
    #define StatSumFloatCost        StatSumDouble
    #define StatMinIndexFloatCost   StatMinIndexDouble
    #define StatMinIndex12FloatCost StatMinIndex12Double
#endif

// fittingģ��ĸ���(��ʱ��֧��IQ�Ż�)
#if FLOAT_TYPE_FITTING == 0
    typedef _iq             floatfit;
    #define StatMaxIndexFloatFit    StatMaxIndexInt
    #define StatMinMaxFloatFit      StatMinMaxInt
#elif FLOAT_TYPE_FITTING == 1
    typedef float           floatfit;
    #define StatMaxIndexFloatFit    StatMaxIndexFloat
    #define StatMinMaxFloatFit      StatMinMaxFloat
#else
    typedef double          floatfit;
    #define StatMaxIndexFloatFit    StatMaxIndexDouble
    #define StatMinMaxFloatFit      StatMinMaxDouble
#endif

// dispģ��ĸ���(��ʱ��֧��IQ�Ż�)
#if FLOAT_TYPE_DISP == 0
    typedef _iq             floatdisp;
#elif FLOAT_TYPE_DISP == 1
    typedef float           floatdisp;    
    #define PointDisp       POINT32f_S
    #define sqrtff(x)       (float)sqrt(x)

    #define MatrixMulVectorCoeff    MatrixMulVectorf
#else
    typedef double          floatdisp;
    #define PointDisp       POINT64_S
    #define sqrtff(x)       sqrt(x)

    #define MatrixMulVectorCoeff    MatrixMulVector
#endif

/******************************************************************************
 *                              ����ͼ��������
******************************************************************************/

/* ���� */
typedef unsigned char   PIXEL;

/* ����� */
typedef struct tagPoint
{
	int x;
	int y;

}POINT_S;

typedef struct tagPoint32f
{
	float x;
	float y;

}POINT32f_S;

typedef struct tagPoint64
{
	double x;
	double y;

}POINT64_S;

/* 3D����� */
typedef struct tagPoint3D
{
	int x;
	int y;
    int s;  // ��Ȼ�߶�

}POINT3D_S;
typedef struct tagPoint3D64
{
	double x;
	double y;
    double s;  // ��Ȼ�߶�

}POINT3D64_S;


/* ������ */
typedef struct tagRect
{
    int left;
	int top;
	int right;
	int bottom;

}RECT_S;

typedef struct tagRect2
{
    int x;
	int y;
	int width;
	int height;
    int s;          // �߶�

}RECT2_S;

typedef struct tagRect64
{
    double left;
	double top;
	double right;
	double bottom;

}RECT64_S;

/* ͼ��ṹ */
typedef struct tagImage
{
    PIXEL *data;    // ������
    int width;      // ���
    int height;     // �߶�
    int channel;    // ͨ���� 1, �Ҷ�   3, RGB

}IMAGE_S;

typedef struct tagImage16
{
    short *data;    // ������
    int width;      // ���
    int height;     // �߶�
    int channel;

}IMAGE16_S;

typedef struct tagImage32
{
    int *data;      // ������
    int width;      // ���
    int height;     // �߶�
    int channel;

}IMAGE32_S;

typedef struct tagImage32f
{
    float *data;    // ������
    int width;      // ���
    int height;     // �߶�
    int channel;

}IMAGE32F_S;

typedef struct tagImage64
{
    int64 *data;   // ������
    int width;      // ���
    int height;     // �߶�
    int channel;

}IMAGE64_S;

/* ͼ������ */
typedef struct tagImageSeq
{
    IMAGE_S *M;         // ͼ��ṹ
    PIXEL *buffer;      // ���ݻ�����
    int count;          // ͼ�����
    int size;           // ��������С

}Image_Seq_S;

typedef struct tagImage32Seq
{
    IMAGE32_S *M;       // ͼ��ṹ
    int *buffer;        // ���ݻ�����
    int count;          // ͼ�����
    int size;           // ��������С

}Image32_Seq_S;

/* ����ṹ */
typedef struct tagMatrix
{
    double *data;   // ������
    int width;      // ���
    int height;     // �߶�
    int channel;

}Matrix_S;

/* �����ṹ */
typedef double Vector_S;

/* �������� */
typedef struct tagMatrixSeq
{
    Matrix_S *M;        // ����ṹ
    double *buffer;     // ���ݻ�����
    int count;          // �������
    int size;           // ��������С

}Matrix_Seq_S;

/* ϡ������ */
typedef struct tagSparseVector
{
	int *index;
	double *val;
	int length;

}SparseVector_S;

/* ϡ����� */
typedef struct tagSparseMatrix
{
    SparseVector_S *data;   // ������
    int width;              // ���
    int height;             // �߶�

}SparseMatrix_S;

/* CCS���ݸ�ʽ */
typedef union tagCcsData
{
	PIXEL pixel[4];
	ushort pixel16[2];
	ulong item;
	int data;       // Ҳ��4�ֽ�

}CcsData;

/* �ȼ۵ı�ǩ���� */
typedef struct tagEqualMarkList
{
    int mark;
    struct tagEqualMarkList *next;
    struct tagEqualMarkList *head;
    struct tagEqualMarkList *tail;

}EqualMarkList;

/* ӳ���ϵ */
typedef struct tagRegionMap
{
    int *MarkNumber;            // �ȼ�������Ŀ
    int *MarkPos;               // �ȼ�������MarkSeq����ʼ����
    int *MarkSeq;               // �ȼ�����
    int *MarkLabel;             // ��marklist�ȼ�(ֻ��ӳ��)

}RegionMap;

/* RGB�궨�� */
typedef enum tagImageRgb
{
    IMAGE_COLOR_BLUE = 0,
    IMAGE_COLOR_GREEN,
    IMAGE_COLOR_RED,
    IMAGE_COLOR_MAX

}IMAGE_RGB_E;

/* ������ */
typedef enum tagImageDirect
{
    IMAGE_DIRECT_LEFT = 0,
    IMAGE_DIRECT_RIGHT,
    IMAGE_DIRECT_TOP,
    IMAGE_DIRECT_BOTTOM,
    IMAGE_DIRECT_MAX

}IMAGE_DIRECT_E;

/* �����궨�� */
typedef enum tagDataComplex
{
    DATA_COMPLEX_RE = 0,
    DATA_COMPLEX_IM,
    DATA_COMPLEX_MAX

}DATA_COMPLEX_E;

/* �����������Ͷ��� */
typedef enum tagVectorDist
{
    VECTOR_DIST_MANHATTAN = 1,
    VECTOR_DIST_EUCLIDEAN,
    VECTOR_DIST_MINKOWSKI,
    VECTOR_DIST_INF,
    VECTOR_DIST_MANHATTAN2,
    VECTOR_DIST_MAX

}VECTOR_DIST_E;

#endif
