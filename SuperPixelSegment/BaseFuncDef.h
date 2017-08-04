/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: BaseFuncDef.h 			                                         */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2011/01/23                                                          */
/*                                                                           */
/* Description: ���峣�ú꺯��                                               */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*****************************************************************************/

#ifndef _BASE_FUNC_DEF_H_
#define _BASE_FUNC_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif /* end of __cplusplus */

#include "BaseConstDef.h"
#include "BaseTypeDef.h"
//#include <math.h>

#ifndef PLATFORM_CCS
#include <malloc.h>
#pragma comment(lib,"IQmath_pc.lib")
#endif
/******************************************************************************
 *                              ���峣�ú꺯��
******************************************************************************/

// ƴ���ַ���: ���纯������������
#define DefStrcat(A,B)      A ## B
#define DefStrcat2(A,B)     DefStrcat(A,B)
#define DefStrcat3(A,B,C)   DefStrcat2(DefStrcat2(A,B),C)

/******************************************************************************
 *                                ��ѧ�ຯ��
******************************************************************************/

#if 0
// �Ż� round(float*int)
IQfloat = _FtoIQN(float,Q);
ret = _IQNint(IQfactor*int+IQ0_5,Q);
#endif

/* ���������������룬���Ǹ��� */
/* ceil(-1.8) = -2, ceil(1.2) = 2 */
#ifndef round2
#define round2(x)               ((x) < 0 ? ((int)((x)-0.5)) : ((int)((x)+0.5)))
#endif

/* ������������������� */
#ifndef roundIntDivInt
#define roundIntDivInt(x,y)     ((2*(x)+(y))/(2*(y)))
#endif

/* x�ĸ�����ȥ�������������������� */
/* c��������ת��int */
/* int(-1.2) = -1, int(1.2) = 1 */

/* �մ���x����С�������������������ƶ� */
/* c���Ժ���ceil */
/* ceil(-1.2) = -1, ceil(1.2) = 2 */

/* �����������ceil */

// 4�д�����ֵ�ĺ꺯��ʵ��

// ��ʽ1: ��Ч
#ifndef ceilIntDivInt
#define ceilIntDivInt(x,y)  ((x)/(y)*(y) == (x) ? (x)/(y):((x)/(y)+1))
#endif

#if 0
// ��ʽ2: ����ֵ�ڲ�����
#ifndef ceilIntDivInt
#define ceilIntDivInt(x,y,z){int temp = (x)/(y); z = (temp*(y) == (x)) ? temp:(temp+1);}
#endif

// ��ʽ3: ֻ֧��GCC������
#ifndef ceilIntDivInt
#define ceilIntDivInt(x,y)  ({int temp = (x)/(y); (temp*(y) == (x)) ? temp:(temp+1);})
#endif

// ��ʽ4: ����
INLINE int ceilIntDivInt(int x,int y)   {int temp = x/y; return (temp*y == x) ? temp:(temp+1);}
#endif

/* �մ���x����С�������������������ƶ� */
/* c���Ժ���floor */
/* floor(-1.2) = -2, floor(1.2) = 1 */
/*
#ifndef floor
#define floor(x,y)                                  \
{                                                   \
    int xiM = (int)(x);                             \
    if (x >= 0 || xiM-(x) < FLOAT_EPS) y = xiM;     \
    else y = xiM-1;                                 \
}
#endif
*/

/* ���ź��� */
#ifndef sgn
#define sgn(x)                  ((x) >= 0 ? 1 : -1)
#endif

/* �߽纯�� */
#ifndef bound
#define bound(x,mina,maxa)      (x < mina ? mina : (x > maxa ? maxa : x))
#endif

/* �Ƕ�ת�� */
#ifndef deg2rad
#define deg2rad(x)              ((x)*MATH_PI/180)
#endif

#ifndef rad2deg
#define rad2deg(x)              ((x)*180/MATH_PI)
#endif

#if 0
// c���Ժ���
/* ˫�����Һ��� */
#ifndef sinh
#define sinh(x)                ((exp(x)-exp(-x))/2)
#endif

/* ˫�����Һ��� */
#ifndef cosh
#define cosh(x)                ((exp(x)+exp(-x))/2)
#endif
#endif



/* ����x��y������ݶ������(0 2��), arctan(cos(a), sin(a), a) */
#define arctan(dxM, dyM, angleM)                    \
{                                                   \
    angleM = atan((dyM)/(dxM));                     \
    if ((dxM) < 0)              angleM += MATH_2PI;  \
    else if ((dyM) < 0)         angleM += MATH_2PI; \
}

/* �����ݽϴ�ֵ */
//#ifndef max
//#define max(a,b)                (((a) > (b)) ? (a) : (b))
//#endif

/* �����ݽ�Сֵ */
//#ifndef min
//#define min(a,b)                (((a) < (b)) ? (a) : (b))
//#endif

/* �����ݽϴ�ͽ�Сֵ */
#ifndef maxmin
#define maxmin(x0, x1, xmin, xmax, flag)            \
{                                                   \
    if (x0 < x1)                                    \
    {                                               \
        xmin = x0;                                  \
        xmax = x1;                                  \
        flag = 0;                                   \
    }                                               \
    else                                            \
    {                                               \
        xmin = x1;                                  \
        xmax = x0;                                  \
        flag = 1;                                   \
    }                                               \
}
#endif

/* �����ݽ�Сֵ */
#ifndef gabs
#define gabs(a)                 (((a) > 0) ? (a) : (-(a)))
#endif

/* ���ݵ������С��һ�� */
//#ifndef scale
//#define scale(data,maxM,minM)   (((data)-(minM))/((maxM)-(minM)))
//#endif

/* �����ݽ��� */
#ifndef swapAB
#define swapAB(a,b,temp)        \
{                               \
    temp = a;                   \
    a = b;                      \
    b = temp;                   \
}
#endif

/* �жϸ�����Ϊ�� */
#ifndef isFloatZero
#define isFloatZero(x)          (fabs(x) < FLOAT_EPS)
#endif
#ifndef isDoubleZero
#define isDoubleZero(x)         (fabs(x) < DOUBLE_EPS)
#endif
#ifndef isNumericZero
#define isNumericZero(x,eps)    (fabs(x) < (eps))
#endif
#ifndef isFloatInt
#define isFloatInt(x)           (fabs(x-(int)x) < FLOAT_EPS)
#endif


#ifdef PLATFORM_SSE
extern __m128 mm_absfloat_mask;
extern void mmAbsFloatMaskInit();
#define _mm_abs_ps(x) _mm_and_ps(x, mm_absfloat_mask)
#endif

extern int digitInt(IN int x, IN int n);
extern int squareSum(IN int n);
extern int BitCountU64(IN int64 x);
extern int BitCountU32(IN int x);

extern double gibbs(double x, double sigma);
extern double gaussian(double x, double sigma);
extern void memsetint(int *a, int n, int x);
extern void Tabel1ExpFloat(OUT float *table, IN int length, IN float sigma);
extern void Tabel2ExpFloat(OUT float *table, IN int len1, IN int len2, IN float sigma);



/******************************************************************************
 *                               �ڴ��ຯ��
******************************************************************************/

#ifndef PLATFORM_CCS

#ifndef MALLOC
#define MALLOC(size)            malloc(size)
#endif

#ifndef FREE
#define FREE(p,size)            free(p)
#endif

#else

extern int DDR2;
extern int IRAM;
extern int L1DSRAM;

#ifndef MALLOC
#define MALLOC(size)            MEM_alloc(DDR2, size, 4)
#endif

#ifndef FREE
#define FREE(p, size)           MEM_free(DDR2, p, size)
#endif


#endif


/* ����type���͵��ڴ� */
#ifndef MallocType
#define MallocType(type, size)      (type* )MALLOC((size)*sizeof(type))
#endif

#ifndef FreeType
#define FreeType(p, type, size)     FREE(p, (size)*sizeof(type))
#endif


/* �ֽڶ����ڴ����� */
#ifdef PLATFORM_SSE

#ifndef mm_MallocType
#define mm_MallocType(type, size)       (type *)_mm_malloc(size*sizeof(type), 16)
#endif

#ifndef mm_FreeType
#define mm_FreeType(p, type, size)      _mm_free(p);
#endif

#else

#ifndef mm_MallocType
#define mm_MallocType(type, size)       MallocType(type, size)
#endif

#ifndef mm_FreeType
#define mm_FreeType(p, type, size)      FreeType(p, type, size)
#endif

#endif


/* cache�ڴ����� */
#ifdef PLATFORM_CCS

#ifndef ram_MallocType
#define ram_MallocType(type, size)      (type *)MEM_alloc(IRAM, size*sizeof(type), 4)
#endif

#ifndef ram_FreeType
#define ram_FreeType(p, type, size)     MEM_free(IRAM, p, size*sizeof(type));
#endif

#else

#ifndef ram_MallocType
#define ram_MallocType(type, size)      mm_MallocType(type, size)
#endif

#ifndef ram_FreeType
#define ram_FreeType(p, type, size)     mm_FreeType(p, type, size)
#endif

#endif

/******************************************************************************
 *                               ͼ���ຯ��
******************************************************************************/

#ifndef RectEnsure
#define RectEnsure(r)               \
{                                   \
    if (r == NULL)                  \
    {                               \
        left = 0;                   \
        right = width-1;            \
        top = 0;                    \
        bottom = height-1;          \
    }                               \
    else                            \
    {                               \
        left = r->left;             \
        right = r->right;           \
        top = r->top;               \
        bottom = r->bottom;         \
    }                               \
}
#endif

/* ͼ����8����λ */
#ifndef IMAGE_TOP
#define IMAGE_TOP(pImage,width)         ((pImage)-(width))
#endif
#ifndef IMAGE_BOTTOM
#define IMAGE_BOTTOM(pImage,width)      ((pImage)+(width))
#endif
#ifndef IMAGE_LEFT
#define IMAGE_LEFT(pImage,width)        ((pImage)-1)
#endif
#ifndef IMAGE_RIGHT
#define IMAGE_RIGHT(pImage,width)       ((pImage)+1)
#endif
#ifndef IMAGE_LEFTTOP
#define IMAGE_LEFTTOP(pImage,width)     ((pImage)-(width)-1)
#endif
#ifndef IMAGE_RIGHTTOP
#define IMAGE_RIGHTTOP(pImage,width)    ((pImage)-(width)+1)
#endif
#ifndef IMAGE_LEFTBOTTOM
#define IMAGE_LEFTBOTTOM(pImage,width)  ((pImage)+(width)-1)
#endif
#ifndef IMAGE_RIGHTBOTTOM
#define IMAGE_RIGHTBOTTOM(pImage,width) ((pImage)+(width)+1)
#endif

// ͼ����ƽ��
#define POINT_MOVE(src, dst, x, y)  \
{                                   \
    dst.x = src.x + x;              \
    dst.y = src.y + y;              \
}

// ͼ������ת
// IN POINT_S src: ����ת�ĵ�����
// IN POINT64_S dst: ��ת��ĵ�����
// IN POINT_S origin: ��ת���
// IN double angle: ��ת��
#define POINT_ROTATE(src, dst, origin, angle)                   \
{                                                               \
    int widthM = src.x-origin.x;                                \
    int heightM = src.y-origin.y;                               \
    dst.x = origin.x + widthM*cos(angle) - heightM*sin(angle);  \
    dst.y = origin.y + widthM*sin(angle) + heightM*cos(angle);  \
}

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif
