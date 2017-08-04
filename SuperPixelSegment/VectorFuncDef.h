/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: VectorFuncDef.h			                                     */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2011/01/23                                                          */
/*                                                                           */
/* Description: ����������templateʵ�֣����ݸ�����������                     */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/

#include "BaseConstDef.h"
#include "BaseTypeDef.h"
#include "BaseFuncDef.h"

#ifndef VECTOR_SUFFIX
#error "VECTOR_SUFFIX must be defined"
#endif

#ifndef VECTOR_TYPE
#error "VECTOR_TYPE must be defined"
#endif

/*******************************************************************************
    Func Name: VectorPlus
 Date Created: 2011-02-10
       Author: zhusong
     Function: ������
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE *B, ��������B
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *C, ������
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorPlus

#define _VectorPlus     DefStrcat2(VectorPlus,VECTOR_SUFFIX)
void _VectorPlus(IN VECTOR_TYPE *A, IN VECTOR_TYPE *B, OUT VECTOR_TYPE *C, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        C[i] = A[i]+B[i];
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorPlusConst
 Date Created: 2011-02-10
       Author: zhusong
     Function: ������
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE t, ����
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *B, ������
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorPlusConst

#define _VectorPlusConst    DefStrcat2(VectorPlusConst,VECTOR_SUFFIX)
void _VectorPlusConst(IN VECTOR_TYPE *A, OUT VECTOR_TYPE *B, IN VECTOR_TYPE t, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        B[i] = A[i]+t;
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorMul
 Date Created: 2011-02-10
       Author: zhusong
     Function: �����������ĵ��
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE *B, ��������B
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *C, ������
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorMul

#define _VectorMul      DefStrcat2(VectorMul,VECTOR_SUFFIX)
void _VectorMul(IN VECTOR_TYPE *A, IN VECTOR_TYPE *B, OUT VECTOR_TYPE *C, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        C[i] = A[i]*B[i];
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorMulConst
 Date Created: 2011-02-10
       Author: zhusong
     Function: �����볣����
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE t, ����
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *B, ������
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorMulConst

#define _VectorMulConst     DefStrcat2(VectorMulConst,VECTOR_SUFFIX)
void _VectorMulConst(IN VECTOR_TYPE *A, OUT VECTOR_TYPE *B, IN VECTOR_TYPE t, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        B[i] = A[i]*t;
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorDivConst
 Date Created: 2011-02-10
       Author: zhusong
     Function: �����볣����
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE t, ����
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *B, ������
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorDivConst

#define _VectorDivConst     DefStrcat2(VectorDivConst,VECTOR_SUFFIX)
void _VectorDivConst(IN VECTOR_TYPE *A, OUT VECTOR_TYPE *B, IN VECTOR_TYPE t, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        B[i] = A[i]/t;
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorSub
 Date Created: 2011-02-10
       Author: zhusong
     Function: ������
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE *B, ��������B
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *C, ������
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorSub

#define _VectorSub      DefStrcat2(VectorSub,VECTOR_SUFFIX)
void _VectorSub(IN VECTOR_TYPE *A, IN VECTOR_TYPE *B, OUT VECTOR_TYPE *C, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        C[i] = A[i]-B[i];
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorPlusMul
 Date Created: 2011-02-10
       Author: zhusong
     Function: ���� + ������
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE *B, ��������B
               IN VECTOR_TYPE *C, ��������C
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *D, �˼�����
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorPlusMul

#define _VectorPlusMul      DefStrcat2(VectorPlusMul,VECTOR_SUFFIX)
void _VectorPlusMul(IN VECTOR_TYPE *A, IN VECTOR_TYPE *B, IN VECTOR_TYPE *C, OUT VECTOR_TYPE *D, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        D[i] = A[i] + B[i]*C[i];
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorPlusMulConst
 Date Created: 2011-02-10
       Author: zhusong
     Function: ���� + �����볣����
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE *B, ��������B
               IN VECTOR_TYPE t, ����
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *C, �˼�����
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorPlusMulConst

#define _VectorPlusMulConst     DefStrcat2(VectorPlusMulConst,VECTOR_SUFFIX)
void _VectorPlusMulConst(IN VECTOR_TYPE *A, IN VECTOR_TYPE *B, OUT VECTOR_TYPE *C, IN VECTOR_TYPE t, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        C[i] = A[i] + B[i]*t;
    }

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorDot
 Date Created: 2011-02-10
       Author: zhusong
     Function: �������
        Input: IN VECTOR_TYPE *A, ��������A
               IN VECTOR_TYPE *B, ��������B
               IN int n, ����ά��
       Output: ��
       Return: VECTOR_TYPE, ���
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorDot

#define _VectorDot     DefStrcat2(VectorDot,VECTOR_SUFFIX)
VECTOR_TYPE _VectorDot(IN VECTOR_TYPE *A, IN VECTOR_TYPE *B, IN int n)
{
    int i;
    VECTOR_TYPE sum = 0;

    for (i = 0;i < n;i++)
    {
        sum += A[i]*B[i];
    }

    return sum;
}

#endif

/*******************************************************************************
    Func Name: VectorCross3
 Date Created: 2011-02-10
       Author: zhusong
     Function: 3ά�������
        Input: IN VECTOR_TYPE *A, ��������A(3*1)
               IN VECTOR_TYPE *B, ��������B(3*1)
       Output: OUT VECTOR_TYPE *C, �������(3*1)
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorCross3

#define _VectorCross3     DefStrcat2(VectorCross3,VECTOR_SUFFIX)
void _VectorCross3(IN VECTOR_TYPE *A, IN VECTOR_TYPE *B, OUT VECTOR_TYPE *C)
{
    C[0] = A[1]*B[2]-A[2]*B[1];
    C[1] = A[2]*B[0]-A[0]*B[2];
    C[2] = A[0]*B[1]-A[1]*B[0];

    return;
}

#endif

/*******************************************************************************
    Func Name: VectorNorm2
 Date Created: 2011-02-10
       Author: zhusong
     Function: ����2������ƽ��
        Input: IN VECTOR_TYPE *A, ��������
               IN int n, ����ά��
       Output: ��
       Return: VECTOR_TYPE, ����ƽ��
      Caution: ��Ҫ�ں����������sqrt����õ�ʵ�ʷ���ֵ
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorNorm2

#define _VectorNorm2     DefStrcat2(VectorNorm2,VECTOR_SUFFIX)
VECTOR_TYPE _VectorNorm2(IN VECTOR_TYPE *A, IN int n)
{
    int i;
    VECTOR_TYPE sum2 = 0;

    for (i = 0;i < n;i++)
    {
        sum2 += A[i]*A[i];
    }

    return sum2;
}

#endif

/*******************************************************************************
    Func Name: VectorNormInf
 Date Created: 2011-02-10
       Author: zhusong
     Function: ���������
        Input: IN VECTOR_TYPE *A, ��������
               IN int n, ����ά��
       Output: ��
       Return: VECTOR_TYPE, ����
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorNormInf

#define _VectorNormInf     DefStrcat2(VectorNormInf,VECTOR_SUFFIX)
VECTOR_TYPE _VectorNormInf(IN VECTOR_TYPE *A, IN int n)
{
    int i;
    VECTOR_TYPE temp;
    VECTOR_TYPE norm = gabs(A[0]);

    for (i = 1;i < n;i++)
    {
        temp = gabs(A[i]);
        if (norm < temp)    norm = temp;
    }

    return norm;
}

#endif

/*******************************************************************************
    Func Name: VectorDist
 Date Created: 2011-02-10
       Author: zhusong
     Function: ��������
        Input: IN VECTOR_TYPE *a, ����a
               IN VECTOR_TYPE *b, ����b
               IN int n, ����ά��
               IN int type, ��������
       Output: 
       Return: VECTOR_TYPE, ����
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorDist

#define _VectorDist     DefStrcat2(VectorDist,VECTOR_SUFFIX)
VECTOR_TYPE _VectorDist(IN VECTOR_TYPE *a, IN VECTOR_TYPE *b, IN int n, IN int type)
{
    int i;
    VECTOR_TYPE dist;
    VECTOR_TYPE sum = 0;

    switch(type)
    {
        case VECTOR_DIST_MANHATTAN:
        {
            for (i = 0;i < n;i++)
            {
                dist = a[i]-b[i];
                sum += gabs(dist);
            }
            break;
        }
        case VECTOR_DIST_EUCLIDEAN:
        {
            for (i = 0;i < n;i++)
            {
                dist = a[i]-b[i];
                sum += dist*dist;
            }
            break;
        }
        case VECTOR_DIST_INF:
        {
            for (i = 0;i < n;i++)
            {
                dist = a[i]-b[i];
                dist = gabs(dist);
                if (dist > sum) sum = dist;
            }
            break;
        }
        default:    break;
    }

    return sum;
}

#endif

/*******************************************************************************
    Func Name: VectorCurcleDist
 Date Created: 2011-02-10
       Author: zhusong
     Function: ���������ھ���
        Input: IN VECTOR_TYPE *a, ����a
               IN VECTOR_TYPE *b, ����b
               IN VECTOR_TYPE circle, ��������
               IN int n, ����ά��
               IN int type, ��������
       Output: 
       Return: VECTOR_TYPE, ����
      Caution: 
      Description: ���ݷ�Χ[0 circle)��һ�����ڶ����Ƕ�����
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorCurcleDist

#define _VectorCurcleDist     DefStrcat2(VectorCurcleDist,VECTOR_SUFFIX)
VECTOR_TYPE _VectorCurcleDist(IN VECTOR_TYPE *a, IN VECTOR_TYPE *b, IN VECTOR_TYPE circle, IN int n, IN int type)
{
    int i;
    VECTOR_TYPE dist;
    VECTOR_TYPE cdist;
    VECTOR_TYPE sum = 0;

    switch(type)
    {
        case VECTOR_DIST_MANHATTAN:
        {
            for (i = 0;i < n;i++)
            {
                dist = a[i]-b[i];
                dist = gabs(dist);
                cdist = (dist < (circle-dist)) ? dist : (circle-dist);
                sum += cdist;
            }
            break;
        }
        case VECTOR_DIST_EUCLIDEAN:
        {
            for (i = 0;i < n;i++)
            {
                dist = a[i]-b[i];
                dist = gabs(dist);
				cdist = (dist < (circle - dist)) ? dist : (circle - dist);
                sum += cdist*cdist;
            }
            break;
        }
        case VECTOR_DIST_INF:
        {
            for (i = 0;i < n;i++)
            {
                dist = a[i]-b[i];
                dist = gabs(dist);
				cdist = (dist < (circle - dist)) ? dist : (circle - dist);
                if (cdist > sum)    sum = cdist;
            }
            break;
        }
        default:    break;
    }

    return sum;
}

#endif

/*******************************************************************************
    Func Name: VectorReverse
 Date Created: 2011-02-10
       Author: zhusong
     Function: ������ת
        Input: IN VECTOR_TYPE *A, ��������A
               IN int n, ����ά��
       Output: OUT VECTOR_TYPE *B, ��ת����B
       Return: 
      Caution: A,B���ܹ����ڴ�
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifndef _VectorReverse

#define _VectorReverse      DefStrcat2(VectorReverse,VECTOR_SUFFIX)
void _VectorReverse(IN VECTOR_TYPE *A, OUT VECTOR_TYPE *B, IN int n)
{
    int i;
    VECTOR_TYPE *p = A+n-1;

    for (i = 0;i < n;i++)
    {
        B[i] = p[-i];
    }

    return;
}

#endif

#undef VECTOR_SUFFIX
#undef VECTOR_TYPE

#undef _VectorPlus
#undef _VectorPlusConst
#undef _VectorMul
#undef _VectorMulConst
#undef _VectorDivConst
#undef _VectorSub
#undef _VectorPlusMul
#undef _VectorPlusMulConst
#undef _VectorDot
#undef _VectorCross3
#undef _VectorNorm2
#undef _VectorNormInf
#undef _VectorDist
#undef _VectorCurcleDist
#undef _VectorReverse

