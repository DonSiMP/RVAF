/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: DataIO.h    			                                         */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2011/01/25                                                          */
/*                                                                           */
/* Description: ���ݶ�ȡ���湦��                                             */
/*                                                                           */
/* Others: ��һ������Ҫ���ڵ��ԣ�����������matlab��ͼ��������ʵ��Ӧ���޹ء���*/
/*         ��C++ʵ��                                                         */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/
#ifndef _DATA_IO_H_
#define _DATA_IO_H_

#include "BaseConstDef.h"
#include "BaseTypeDef.h"
#include "BaseFuncDef.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

// #include <iostream.h>             // for template
#include <iostream>
using namespace std;

#include "DataIOc.h"

extern void ReadSvmData(IN char *filename,
                        OUT int *m_Rows,
                        OUT int *m_Cols,
                        OUT double **sample,
                        OUT double **label);

extern void ReadSvmData(IN char *filename,
                 OUT SparseMatrix_S *sample,
                 OUT double **label);

extern void SaveSvmData(IN char *fileName,
                        IN char *saveMode,
                        IN double *sample,
                        IN double *label,
                        IN int d,
                        IN int n);

extern FileList *FileListSearch(IN char *dir, IN char *postfix);
extern void FileListDestroy(OUT FileList **l);
extern int FileListNum(IN char *dir, IN char *postfix);
extern int FileListNum(IN FileList *L);
extern FileList *DirListSearch(IN char *path, IN int flag);

/*******************************************************************************
    Func Name: SaveArrayData
 Date Created: 2011-01-25
       Author: zhusong
     Function: ������������
        Input: IN char *fileName, �ļ���
               IN int direction, ���ݱ��淽��
               IN char *saveMode, ����ģʽ('a': ��ӣ�'w': ����)
               IN char *dataType, ��������("%d","%f","%g","%c" ����)
               IN dataTypeT *data, ���������������
               IN int n, ���ݸ���
       Output: 
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
template < class dataTypeT >
void SaveArrayData(IN char *fileName,
                   IN int direction,
                   IN char *saveMode,
                   IN char *dataType,
                   IN dataTypeT *data,
                   IN int n)
{
	FILE *pf = NULL;
	char szBuffer[4096];
	char *p = szBuffer;
	int i;

	pf = fopen(fileName, saveMode);

    if (NULL == pf)
    {
        return;
    }

	for (i = 0; i < n; i++)
	{	
		p += sprintf(p, dataType, data[i]);

        if (direction == SAVE_ARRAY_DATA_VERTICAL)
		{
            p += sprintf(p, "%c", '\n');
        }
        else if (direction == SAVE_ARRAY_DATA_HORIZONTAL)
        {
            p += sprintf(p, "%c", ' ');
        }

        if (p - szBuffer > 4080)
        {
            fputs(szBuffer,pf);
            p = szBuffer;
        }
	}
	if (direction == SAVE_ARRAY_DATA_HORIZONTAL)
	{
		p += sprintf(p, "%c", '\n');
	}
    fputs(szBuffer,pf);

    fclose(pf);
	
	return;
}

/*******************************************************************************
    Func Name: PrintMatrixData
 Date Created: 2011-01-25
       Author: zhusong
     Function: ��ӡ��������
        Input: IN dataTypeT *data, ��������, ��*��
               IN char *dataType, ��������("%d","%f","%g","%c" ����)
               IN int m_NumRows, ���������
               IN int m_NumCols, ���������
       Output: 
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
template < class dataTypeT >
void PrintMatrixData(IN dataTypeT *data,
                     IN char *dataType,
                     IN int m_NumRows, 
                     IN int m_NumCols)
{
	int i,j;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
            printf(dataType, data[j+i*m_NumCols]);
            printf(" ");            
        }
        printf("\n"); 
    }
	
	return;
}

/*******************************************************************************
    Func Name: DoubleData
 Date Created: 2011-01-25
       Author: zhusong
     Function: ������ת��Ϊdouble����
        Input: IN dataTypeT *in_data, ����δ֪���͵�����
               IN int n, ���ݸ���
       Output: OUT double *out_data, ���double���͵�����
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
template < class dataTypeT >
void DoubleData(IN dataTypeT *in_data, OUT double *out_data, IN int n)
{
    int i;

    for (i = 0;i < n;i++)
    {
        out_data[i] = (double)in_data[i];
    }
}

#endif

