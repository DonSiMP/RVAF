/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: DataIO.cpp    			                                         */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2011/01/25                                                          */
/*                                                                           */
/* Description: ���ݶ�ȡ���湦��                                             */
/*                                                                           */
/* Others: ��һ������Ҫ���ڵ��ԣ�����������matlab��ͼ��������ʵ��Ӧ���޹ء�  */
/*         ����C/C++ʵ��                                                     */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/

#include "DataIO.h"

#ifdef FLATFORM_LINUX
#include <dirent.h>
#else
#include <windows.h>
#endif

#include "math.h"

#include <iostream>
#include <fstream>          // for ifstream && ofstream
#include <sstream>          // for stringstream
#include <vector>
using namespace std;

// #include "Stat.h"
// #include "Sort.h"

#include <io.h>             // for access
#include <direct.h>         // for _mkdir
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif /* end of __cplusplus */

/*******************************************************************************
    Func Name: ReadMatrixData
 Date Created: 2011-01-25
       Author: zhusong
     Function: ��ȡ��������
        Input: IN char *fileName, �ļ���
       Output: OUT int *m_Rows, ���������
               OUT int *m_Cols, ���������
       Return: double *, ��������, ��*��
      Caution: Ҫ���ļ������ݳʾ����Ų����ļ���, ���������ݼ��Կո�ֿ�
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
double *ReadMatrixData0(IN char *filename, OUT int *m_Rows, OUT int *m_Cols)
{
    FILE *pf = NULL;
    int i,j;
    double element;
    long items = 0;
    int m_NumRows;
    int m_NumCols;
    double *m_pData;

    if (FALSE == GetMatrixDataSize(filename, &m_NumRows, &m_NumCols)) return NULL;

    pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

    m_pData = MallocType(double, m_NumRows * m_NumCols);
    if(m_pData == NULL) return NULL;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
            if(fscanf(pf,"%lf",&element) == 1)
            {
                m_pData[j+i*m_NumCols] = element;
                items++;
            }
            else
            {
                i = m_NumRows;
                break;
            }
        }
    }
    fclose(pf);

    if (items != m_NumRows*m_NumCols)
    {
        free(m_pData);
        return NULL;
    }

    *m_Rows = m_NumRows;
    *m_Cols = m_NumCols;
    return m_pData;
}

void ReadMatrixData1(IN char *filename, OUT double *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    double data;

	pf = fopen(filename, "r");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
        	fscanf(pf,"%lf",&data);
            m_pData[j+i*m_NumCols] = data;
        }
    }
    fclose(pf);

    return;
}

double *ReadMatrixData2(IN char *filename, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    double data;
	double *m_pData;

	pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

    m_pData = MallocType(double, m_NumRows * m_NumCols);
    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
        	fscanf(pf,"%lf",&data);
            m_pData[j+i*m_NumCols] = data;
        }
    }
    fclose(pf);

    return m_pData;
}

/*******************************************************************************
    Func Name: SaveMatrixData
 Date Created: 2011-01-25
       Author: zhusong
     Function: �����������
        Input: IN char *fileName, �ļ���
               IN double *m_pData, ��������, ��*��
               IN int m_NumRows, ���������
               IN int m_NumCols, ���������
       Output: 
       Return: ��
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void SaveMatrixData(IN char *filename, IN double *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;

	// pf = fopen(filename, "a");
	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols-1; j++)
        {
            fprintf(pf,"%.15g ", m_pData[j+i*m_NumCols]);
        }
        fprintf(pf,"%.15g\n", m_pData[j+i*m_NumCols]);
        // fprintf(pf,"%.5g\r", m_pData[j+i*m_NumCols]);  // matlab �洢��ʽ
    }
    fclose(pf);

    return;
}

void ReadMatrixFloat1(IN char *filename, OUT float *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    float data;

	pf = fopen(filename, "r");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
        	fscanf(pf,"%f",&data);
            m_pData[j+i*m_NumCols] = data;
        }
    }
    fclose(pf);

    return;
}

float *ReadMatrixFloat2(IN char *filename, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    float data;
	float *m_pData;

	pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

	m_pData = MallocType(float, m_NumRows*m_NumCols);
    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
        	fscanf(pf,"%f",&data);
            m_pData[j+i*m_NumCols] = data;
        }
    }
    fclose(pf);

    return m_pData;
}

void SaveMatrixFloat(IN char *filename, IN float *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols-1; j++)
        {
            fprintf(pf,"%.5g ", m_pData[j+i*m_NumCols]);
        }
        fprintf(pf,"%.5g\n", m_pData[j+i*m_NumCols]);
    }
    fclose(pf);

    return;
}

void SaveMatrixFloat3D(IN char *filename, IN float *m_pData, IN int m_NumRows, IN int m_NumCols, IN int s, IN int d)
{
    FILE *pf = NULL;
	int i,j;
	float *save = m_pData + d;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols-1; j++)
        {
            fprintf(pf,"%.5g ", save[(j+i*m_NumCols)*s]);
        }
        fprintf(pf,"%.5g\n", save[(j+i*m_NumCols)*s]);
    }
    fclose(pf);

    return;
}

void SaveInt64(IN FILE *pf, IN int64 n)
{
#if 0
    if (n >= 10)    SaveInt64(pf, n/10);
    fprintf(pf,"%d", int(n%10));
#else
    int i;
    int s = 60;
    int64 temp;
    for (i = 0;i < 16;i++)
    {
        temp = n >> s;
        temp = temp & 0x0F;
        fprintf(pf,"%x", temp);
        s -= 4;
    }
#endif
}

void SaveMatrixInt64(IN char *filename, IN int64 *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;
#if 1
    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols-1; j++)
        {
            SaveInt64(pf, m_pData[j+i*m_NumCols]);
            fprintf(pf," ");
        }
        SaveInt64(pf, m_pData[j+i*m_NumCols]);
        fprintf(pf,"\n");
    }
    fclose(pf);
#else
    int w,h;
    w = 4;
    h = 3;

    for (i = h; i < m_NumRows-h; i++)
    {
        for (j = w; j < m_NumCols-1-w; j++)
        {
            SaveInt64(pf, m_pData[j+i*m_NumCols]);
            fprintf(pf," ");
        }
        SaveInt64(pf, m_pData[j+i*m_NumCols]);
        fprintf(pf,"\n");
    }
    fclose(pf);
#endif

    return;
}

void ReadMatrixInt1(IN char *filename, OUT int *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    int data;

	pf = fopen(filename, "r");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
        	fscanf(pf,"%d",&data);
            m_pData[j+i*m_NumCols] = data;
        }
    }
    fclose(pf);

    return;
}

int *ReadMatrixInt2(IN char *filename, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    int data;
	int *m_pData;

	pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

    m_pData = MallocType(int, m_NumRows*m_NumCols);
    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
        	fscanf(pf,"%d",&data);
            m_pData[j+i*m_NumCols] = data;
        }
    }
    fclose(pf);

    return m_pData;
}

void SaveMatrixInt(IN char *filename, IN int *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    int data;
    int *src = m_pData;
    BOOL flag = FALSE;

    // pf = fopen(filename, "a");
	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++, src += m_NumCols)
    {
        for (j = 0; j < m_NumCols; j++)
        {
            data = src[j];
            if (flag == TRUE)
            {
                if (data < 0)           fprintf(pf,"000");
                else if (data < 10)     fprintf(pf,"0000");
                else if (data < 100)    fprintf(pf,"000");
                else if (data < 1000)   fprintf(pf,"00");
                else if (data < 10000)  fprintf(pf,"0");
            }
            fprintf(pf,"%d ", data);
            // fprintf(pf,"%d", data);
        }
        fprintf(pf,"\n");
    }

    fclose(pf);

    return;
}

unit32 *ReadMatrixUint(IN char *filename, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    unit32 data;
	unit32 *m_pData;

	pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

	m_pData = MallocType(unit32, m_NumRows*m_NumCols);
    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
        	fscanf(pf,"%u", &data);
            m_pData[j+i*m_NumCols] = data;
        }
    }
    fclose(pf);

    return m_pData;
}

void SaveMatrixUint(IN char *filename, IN unit32 *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    unit32 data;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
            data = m_pData[j+i*m_NumCols];
            fprintf(pf,"%u ", data);
        }
        fprintf(pf,"\n");
    }
    fclose(pf);

    return;
}

void SaveMatrixUshort(IN char *filename, IN ushort *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    int data;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols; j++)
        {
            data = m_pData[j+i*m_NumCols];
            fprintf(pf,"%d ", data);
        }
        fprintf(pf,"\n");
    }
    fclose(pf);

    return;
}

void SaveMatrixUshort2(IN char *filename, IN ushort *m_pData, IN int rowstep, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;
    int data;
    ushort *src = m_pData;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++, src += rowstep)
    {
        for (j = 0; j < m_NumCols; j++)
        {
            data = src[j];
            fprintf(pf,"%d ", data);
        }
        fprintf(pf,"\n");
    }
    fclose(pf);

    return;
}

void SaveMatrixChar(IN char *filename, IN char *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols-1; j++)
        {
            fprintf(pf,"%d ", m_pData[j+i*m_NumCols]);
        }
        fprintf(pf,"%d\n", m_pData[j+i*m_NumCols]);
    }
    fclose(pf);

    return;
}

void SaveMatrixPixel(IN char *filename, IN PIXEL *m_pData, IN int m_NumRows, IN int m_NumCols)
{
    FILE *pf = NULL;
	int i,j;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    for (i = 0; i < m_NumRows; i++)
    {
        for (j = 0; j < m_NumCols-1; j++)
        {
            fprintf(pf,"%d ", (int)m_pData[j+i*m_NumCols]);
        }
        fprintf(pf,"%d \n", (int)m_pData[j+i*m_NumCols]);
    }
    fclose(pf);

    return;
}

void SaveMatrixHex(IN char *filename, IN int *m_pData, IN int m_NumRows, IN int m_NumCols, IN int bits)
{
    FILE *pf = NULL;
	int i, j, k;
    int data;
    int *src;
    int n, start;
    int mask, hex, s;

	pf = fopen(filename, "w");
    if (NULL == pf)     return;

    src = m_pData;
    n = bits/4;
    start = 0xf << (n-1)*4;
    for (i = 0; i < m_NumRows; i++, src += m_NumCols)
    {
        for (j = 0; j < m_NumCols; j++)
        {
            data = src[j];
            mask = start;
            for (k = 0;k < n;k++)
            {
                hex = data & mask;
                s = 4*(n - 1 - k);
                if (s != 0) hex = hex >> s;                
                fprintf(pf,"%x", hex);
                mask = mask >> 4;
            }
            fprintf(pf," ");
        }
        fprintf(pf,"\n");
    }

    fclose(pf);

    return;
}

/*******************************************************************************
    Func Name: GetMatrixDataSize
 Date Created: 2011-01-25
       Author: zhusong
     Function: ��ȡ�ļ����ݵ�����
        Input: IN char *fileName, �ļ���
       Output: OUT int *m_Rows, ���������
               OUT int *m_Cols, ���������
       Return: FALSE, ��ȡʧ��
               TRUE, ��ȡ�ɹ�
      Caution: Ҫ���ļ������ݳʾ����Ų����ļ���, ���������ݼ��Կո�ֿ�
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
BOOL GetMatrixDataSize(IN char *filename, OUT int *m_NumRows, OUT int *m_NumCols)
{
    FILE *pf = NULL;
    int items;
    double element;
    char *buf,*p;
    int size = 1024;
    int len;

    pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

    buf = MallocType(char, size);

    // ��ȡ���ݵ���
    items = 0;
    while (1)
    {
        if (fgets(buf,size,pf) == NULL) break;

        // ���һ��з���λ�ã�û�����ʾ
        if (strrchr(buf,'\n') != NULL)
        {
            // �����ո�
            p = buf;
            while (*p == ' ')           p++;

            // �������ź�����
            if (*p == '-' || *p == '+') p++;

            // ���뱣֤������
            if (*p == '.' || (*p >= '0' && *p <= '9'))  items++;
        }
    }
    if (items <= 0)         return FALSE;
    *m_NumRows = items;

    // ��ȡ���ݵ���
    fseek(pf, 0, SEEK_SET);             // ƫ�Ƶ��ļ���ͷ

    // ��ȡ������һ������
    if (fgets(buf,size,pf) == NULL)     return FALSE;
	while(strrchr(buf,'\n') == NULL)
	{
	    // һ��û�н���������������ڴ�����
	    len = strlen(buf);
		size *= 2;
		buf = (char *)realloc(buf, size);
		if (buf == NULL)
		{
            printf("GetMatrixDataSize error: too large memory (%d)!\n", size);
            fclose(pf);
            return FALSE;
		}
		if(fgets(buf+len,size-len,pf) == NULL)  break;
	}

    // Ԫ�ظ���
    items = 0;
    p = buf;
    while (1)
    {
        if(sscanf(p,"%lf%n",&element,&len) == 1)    items++;
        else                                        break;
        p += len;
    }
    if (items <= 0)         return FALSE;
    *m_NumCols = items;

    free(buf);
    fclose(pf);

    return TRUE;
}

/*******************************************************************************
    Func Name: FileLine
 Date Created: 2011-01-25
       Author: zhusong
     Function: ��ȡ�ļ�����
        Input: IN char *fileName, �ļ���
       Output: 
       Return: int, �ļ�����
      Caution: 
      Description: ����ֻ�лس��Ŀ���
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
int FileLine(IN char *filename)
{
    FILE *pf = NULL;
    int size = 1024;
    char buf[1024];
	int items;
	int times;
	char *pos;

    pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

    // ��ȡ���ݵ���
    items = 0;
	times = 0;
    while (1)
    {
        if (fgets(buf,size,pf) == NULL) 	break;

        // ���һ��з���λ��
		pos = strrchr(buf,'\n');

		if (pos == NULL)						// һ��û�ж���
		{
			times++;
		}
		else if (pos == buf && times == 0)		// ��һ��ֻ��һ���س�
		{
			times = 0;
		}
		else									// ��һ��: ����+�س�
		{
			items++;
			times = 0;
		}
    }

    fclose(pf);

    return items+1;
}

void ReadBinaryInt(IN char *fileName, IN int *data, IN int size)
{
	FILE *pf = NULL;

	pf = fopen(fileName, "rb");
    if (NULL == pf) return;

    fread(data, sizeof(int), size, pf);

    fclose(pf);

	return;
}

void SaveBinaryInt(IN char *fileName, IN int *data, IN int size)
{
	FILE *pf = NULL;

	pf = fopen(fileName, "wb");
    if (NULL == pf) return;

    fwrite(data, sizeof(int), size, pf);

    fclose(pf);

	return;
}

/*******************************************************************************
    Func Name: ImageSaveCcs
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����ͼ��Ϊdsp��ccs���ݸ�ʽ
        Input: IN char *fileName, �ļ���
               IN IMAGE_S img, �������ͼ��
       Output: 
       Return: ��
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
CcsData *ReadCcsData(IN char *filename, OUT int *length)
{
    ulong i;
    ulong temp;
	CcsData *data;
    FILE *pf = NULL;

    pf = fopen(filename, "r");
    if (NULL == pf)     return NULL;

    // ��һ������Ϣͷ
    // MagicNumber  Format  StartingAddress PageNum Length 

    // MagicNumber      �̶�Ϊ1651
    // Format           ָʾ�ļ����ݵĸ�ʽ��1:ʮ������ 2:���� 3:������ 4:�����͡�  
    // StartingAddress  �洢�����ʼ��ַ��  
    // PageNum          �洢���ҳ��ַ��  
    // Length           ���ݳ���
    fscanf(pf,"%x",&temp);
	fscanf(pf,"%x",&temp);
	fscanf(pf,"%x",&temp);
	fscanf(pf,"%x",&temp);
	fscanf(pf,"%x",&temp);

	data = (CcsData *)malloc(temp*sizeof(CcsData));
	for (i = 0;i < temp;i++)
	{
        fscanf(pf,"%x",data+i);
	}
	*length = temp;

    fclose(pf);

	return data;

}

/*******************************************************************************
    Func Name: SaveCcsData
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����Ϊdsp��ccs���ݸ�ʽ
        Input: IN char *fileName, �ļ���
               IN CcsData *srcdata, ����
               IN int size, ���ݸ���
       Output: 
       Return: ��
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void SaveCcsData(IN char* filename, IN CcsData *srcdata, IN int size)
{
    int j;
	CcsData *ccs;

    FILE *pf = NULL;
	char szBuffer[4096];
    char *p = szBuffer;

    pf = fopen(filename, "w");
    if (NULL == pf)     return;

    // ��һ������Ϣͷ
    // MagicNumber  Format  StartingAddress PageNum Length 
    
    // MagicNumber      �̶�Ϊ1651
    // Format           ָʾ�ļ����ݵĸ�ʽ��1:ʮ������ 2:���� 3:������ 4:�����͡�  
    // StartingAddress  �洢�����ʼ��ַ��  
    // PageNum          �洢���ҳ��ַ��  
    // Length           ���ݳ���
    p += sprintf(p, "1651 1 80000000 0 %x\n",size);
    fputs(szBuffer,pf);

    for (j = 0, ccs = srcdata;j < size;j++, ccs++)
    {
        p = szBuffer;

		p += sprintf(p, "%s", "0x");
        for (int i = 0;i < 4;i++)
        {
            if (ccs->pixel[3-i] == 0x00)
            {
                p += sprintf(p, "%s", "00");
            }
            else if (ccs->pixel[3-i] <= 0x0F)
            {
                p += sprintf(p, "%s", "0");
                break;
            }
            else
            {
                break;
            }
        }
        if (ccs->item != 0x00)
            p += sprintf(p, "%X", ccs->item);

        p += sprintf(p, "\n");
        fputs(szBuffer,pf);
    }

    fclose(pf);

	return;
}

void Ccs2Pixel(IN CcsData *data, IN int length, OUT PIXEL *image)
{
    int i, l;

	for (i = 0, l = 0;l < length;i += 4,l++)
    {
        image[i + 0] = data[l].pixel[0];
        image[i + 1] = data[l].pixel[1];
        image[i + 2] = data[l].pixel[2];
        image[i + 3] = data[l].pixel[3];
    }

	return;
}

void Pixel2Ccs(IN PIXEL *image, IN int length, OUT CcsData *data)
{
    int i, l;

    if (length % 4 != 0)
    {
        printf("length error !\n");
    }

	for (i = 0, l = 0;i < length;i += 4,l++)
    {
        data[l].pixel[0] = image[i + 0];
        data[l].pixel[1] = image[i + 1];
        data[l].pixel[2] = image[i + 2];
        data[l].pixel[3] = image[i + 3];
    }

	return;
}

/*******************************************************************************
    Func Name: ReadBinaryPatternData
 Date Created: 2011-01-25
       Author: zhusong
     Function: �����ƶ�ȡģʽʶ���õ���������
        Input: IN char *fileName, �ļ���
               IN double *sample, �������ݾ���
               IN double *label, ������ǩ
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
void ReadBinaryPatternData(IN char *fileName,
                           OUT Matrix_S *sample,
                           IN double **label)
{
	FILE *pf = NULL;
	int i;
	int height;
	int width;
    double *feature;

	pf = fopen(fileName, "rb");
    if (NULL == pf) return;

    fread (&height,sizeof(int),1,pf);
    sample->height = height;

    fread (&width,sizeof(int),1,pf);
    sample->width = width;

    feature = sample->data = MallocType(double, height*width);
    *label = MallocType(double, height);
    
	for (i = 0; i < height; i++)
	{
	    fread(*label+i, sizeof(double), 1, pf);
        fread(feature, sizeof(double), width, pf);
        feature += width;
	}

    fclose(pf);

	return;
}

/*******************************************************************************
    Func Name: SaveBinaryPatternData
 Date Created: 2011-01-25
       Author: zhusong
     Function: �����Ʊ���ģʽʶ���õ���������
        Input: IN char *fileName, �ļ���
               IN double *sample, �������ݾ���
               IN double *label, ������ǩ
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
void SaveBinaryPatternData(IN char *fileName,
                           IN Matrix_S *sample,
                           IN double *label)
{
	FILE *pf = NULL;
	int i;
	int height = sample->height;
	int width = sample->width;
    double *feature = sample->data;

	pf = fopen(fileName, "wb");
    if (NULL == pf) return;

    fwrite(&height, sizeof(int), 1, pf);
    fwrite(&width, sizeof(int), 1, pf);

	for (i = 0; i < height; i++)
	{
	    fwrite(&label[i], sizeof(double), 1, pf);
        fwrite(feature, sizeof(double), width, pf);
        feature += width;
	}

    fclose(pf);

	return;
}

/*******************************************************************************
    Func Name: FileGetNameFromIndex
 Date Created: 2011-01-25
       Author: zhusong
     Function: ���ݱ�Ż�ȡ�ļ���
        Input: IN char dirName[], Ŀ¼��
               IN char suffix[], ��׺��
               IN int bit, λ����һ�����4λ���� 0001.jpg
               IN int i, ���
       Output: OUT char *fileName, �ļ�����Ҫ���仺������СΪFILE_NAME_LENGTH
       Return: 
      Caution: 
      Description: ���Ϊ��λ��
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void FileGetNameFromIndex(IN char *dirName, 
                          OUT char fileName[], 
                          IN char suffix[],
                          IN int bit,
                          IN int index)
{
    int i;
    char *p;
    int zeronum = bit-digitInt(index, 10);

    memset(fileName,0,FILE_NAME_LENGTH*sizeof(char));
	p = fileName;
    if (dirName != NULL)
    {
	    p += sprintf(p, "%s%s", dirName,"\\");
    }

    for (i = 0;i < zeronum;i++)
    {
        p += sprintf(p, "%c", '0');
    }
    p += sprintf(p, "%d%s",index,suffix);

	return;
}

/*******************************************************************************
    Func Name: FileGetNameFromPath
 Date Created: 2011-01-25
       Author: zhusong
     Function: ���ļ�·����ȡ�ļ���
        Input: IN char *path, �ļ�·��
               IN BOOL flag, TRUE, ������׺��
                             FALSE, ��������׺��
       Output: OUT char *filename, �ļ���
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void FileGetNameFromPath(IN char *path, 
                         OUT char *filename, 
                         OUT char *suffix,
                         IN BOOL flag)
{
    int i;
    int n = strlen(path);
    int start = 0;
    int end = 0;

    // ��·��βѰ��Ŀ¼�ָ��� '\'
    for (i = n-1;i >= 0;i--)
    {
        if (path[i] == '\\')
        {
            start = i+1;
            break;
        }
    }

    if (flag == TRUE)
    {
        strcpy(filename,path+start);
        return;
    }

    // ��·��βѰ��Ŀ¼�ָ��� '.'
    for (i = n-1;i >= 0;i--)
    {
        if (path[i] == '.')
        {
            end = i-1;
            break;
        }
    }

    if (suffix != NULL)
    {
        int j;
        for (i = end+1, j = 0;i < n;i++, j++)
        {
            suffix[j] = path[i];
        }
        suffix[j] = '\0';
    }

    if (filename != NULL)
    {
        for (i = start;i <= end;i++)
        {
            filename[i-start] = path[i];
        }
        filename[end-start+1] = '\0';
    }
        
    return;
}

/*******************************************************************************
    Func Name: FileCopy
 Date Created: 2011-01-25
       Author: zhusong
     Function: �����ļ�
        Input: IN char* file1, �ļ���1
               IN char* file2, �ļ���2
       Output: 
       Return: 
      Caution: 
      Description: �����ļ�1���ļ�2
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void FileCopy(IN char* file1, IN char* file2)
{
    FILE *pf1;
    FILE *pf2;
    char buffer[4096];
    int size = 4096;
    int n = size;

    pf1 = fopen(file1, "rb");
    if (NULL == pf1)    return;

    pf2 = fopen(file2, "wb");
    if (NULL == pf1)
    {
        fclose(pf1);
        return;
    }

    while (n == size)
    {
        n = fread(buffer,sizeof(char),size,pf1);
        if (n > 0)  fwrite(buffer,sizeof(char),n,pf2);
    }

    fclose(pf1);
    fclose(pf2);
    return;
}

/*******************************************************************************
    Func Name: FileMerge
 Date Created: 2011-01-25
       Author: zhusong
     Function: �ϲ��ļ�
        Input: IN char* file1, �ļ���1
               IN char* file2, �ļ���2
       Output: 
       Return: 
      Caution: 
      Description: ���ļ�2�����ݺϲ����ļ�1��ĩβ
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void FileMerge(IN char* file1, IN char* file2)
{
    FILE *pf1;
    FILE *pf2;
    char buffer[4096];
    int size = 4096;
    int n = size;

    pf1 = fopen(file1, "ab");
    if (NULL == pf1)    return;

    pf2 = fopen(file2, "rb");
    if (NULL == pf1)
    {
        fclose(pf1);
        return;
    }

    while (n == size)
    {
        n = fread(buffer,sizeof(char),size,pf2);
        if (n > 0)  fwrite(buffer,sizeof(char),n,pf1);
    }

    fclose(pf1);
    fclose(pf2);
    return;
}

/*******************************************************************************
    Func Name: FileClear
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����ļ�
        Input: IN char* filename, �ļ���
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
void FileClear(IN char *filename)
{
    FILE *pf = NULL;
	pf = fopen(filename, "w");
    if (NULL == pf)     return;
    fclose(pf);
    return;
}

/*******************************************************************************
    Func Name: FileExist
 Date Created: 2011-01-25
       Author: zhusong
     Function: �ж��ļ��Ƿ����
        Input: IN char *fileName, �ļ���
       Output: 
       Return: BOOL, TRUE, ����
                     FALSE, ������
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
BOOL FileExist(IN char *filename)
{
    return (access(filename, 0) == 0);
}

/*******************************************************************************
    Func Name: DirCreate
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����Ŀ¼
        Input: IN char *dir, Ŀ¼��
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
void DirCreate(IN char* dir)
{
    if(access(dir,0))
    {
        _mkdir(dir);
    }

    return;
}

/*******************************************************************************
    Func Name: DirCreateRecursion
 Date Created: 2011-01-25
       Author: zhusong
     Function: �ݹ鴴��Ŀ¼
        Input: IN char *dir, Ŀ¼��
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
BOOL DirCreateRecursion(IN char* dir)
{
    int i;
    int len;
    int ret;
    char newdir[FILE_NAME_LENGTH];

    while (1)
    {
        if (_mkdir(dir) == 0)                       return TRUE;

        len = strlen(dir);
        for (i = len-1;i >= 0; i--)
        {
            if (dir[i] == ':')                      return FALSE;
            if (dir[i] == '\\' || dir[i] == '/')    break;
        }
        if (i < 0)                                  return FALSE;

        memcpy(newdir, dir, i*sizeof(char));
        newdir[i] = '\0';
        ret = DirCreateRecursion(newdir);
        if (ret == FALSE)                           return FALSE;
    }
}


int MsgShow = 0;
void MsgOn()
{
    MsgShow = 1;
}
void MsgOff()
{
    MsgShow = 0;
}
#ifdef __cplusplus
}
#endif /* end of __cplusplus */






/*******************************************************************************
    Func Name: ReadSvmData
 Date Created: 2011-01-25
       Author: zhusong
     Function: ��ȡSvm����
        Input: IN char *fileName, �ļ���
       Output: OUT int *m_Rows, ���������
               OUT int *m_Cols, ���������
               OUT double **sample, �������ݾ���
               OUT double **label, ������ǩ
       Return: 
      Caution: 
      Description: �ļ������ݸ�ʽ
                   label index1:data1 index2:data2 index3:data3...
                   ����
                   label: int
                   index: 1,2,..n �� index1 < index2 < index3
                   data:  double
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void ReadSvmData(IN char *filename,
                 OUT int *m_Rows,
                 OUT int *m_Cols,
                 OUT double **sample,
                 OUT double **label)
{
    string buffer;
    ifstream file;
    istringstream line;

    vector<double> vlabel;
    vector<int> idx;
    vector<double> point;
    vector< vector<int> > vindex;
    vector< vector<double> > vsample;

    int i,j;
    double element;
    int index;
    char separator;
    int items = 0;
    int datanum = 0;
    int feature = 0;
    double *data;
    double *target;

    file.open(filename,ios::in);
    if (file.fail())    return;

    // ��ȡ���ݵ���
    while(getline(file,buffer))
    {
        // �����س����к�ע����
        if (buffer == "")       continue;
        if (buffer[0] == '#')   continue;

        // ����stream��
        line.str(buffer);

/*******************************************************************************/

        // ��ȡ��ǩ
        if (line >> element)
        {
            vlabel.push_back(element);
        }
        else
        {
            printf("label error: line %d\n", items);
            exit(0);
        }

		// ��ȡ����
		while(line >> index)
		{
		    // ������ά��
		    if (feature < index)    feature = index;

		    idx.push_back(index);

            line >> separator;
            if (separator != ':')
            {
                printf("separator error: line %d index %d\n", items,index);
                exit(0);
            }

            line >> element;
            point.push_back(element);
            datanum++;
		}
		vindex.push_back(idx);
        idx.clear();
        vsample.push_back(point);
        point.clear();

/*******************************************************************************/

        // ���stream
        line.clear();
        items++;
    }

    if (items != vlabel.size())
    {
        printf("line error\n");
        exit(0);
    }

    printf("dense data ratio: %f\n",(double)datanum/(double)(items*feature));

    // ��vector����ȡ����
    target = MallocType(double, items);
    data = MallocType(double, items*feature);
    
    if (data == NULL || target == NULL)
    {
        printf("memory error\n");
        exit(0);
    }
    memset(data,0,items*feature*sizeof(double));

    for (i = 0;i < items;i++)
    {
        target[i] = vlabel[i];
        datanum = vindex[i].size();
        for (j = 0;j < datanum;j++)
        {
            index = vindex[i][j]-1;
            data[i*feature+index] = vsample[i][j];
        }
    }

    *m_Rows = items;
    *m_Cols = feature;
    *sample = data;
    *label = target;

    return;
}

/*******************************************************************************
    Func Name: SaveSvmData
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����Svm����
        Input: IN char *fileName, �ļ���
               IN char *saveMode, ����ģʽ('a': ��ӣ�'w': ����)
               IN double *sample, �������ݾ���
               IN double *label, ������ǩ
               IN int d, ����ά��
               IN int n, ������
       Output: 
       Return: 
      Caution: 
      Description: �ļ������ݸ�ʽ
                   label index1:data1 index2:data2 index3:data3...
                   ����
                   label: int
                   index: 1,2,..d �� index1 < index2 < index3
                   data:  double
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void SaveSvmData(IN char *fileName,
                 IN char *saveMode,
                 IN double *sample,
                 IN double *label,
                 IN int d,
                 IN int n)
{
	FILE *pf = NULL;
	char szBuffer[4096];
	char *p = szBuffer;
	int i,j;
	double c;

	pf = fopen(fileName, saveMode);

    if (NULL == pf) return;

	for (i = 0; i < n; i++)
	{
	    // p += sprintf(p, "%.12g", label[i]);
	    p += sprintf(p, "%g", label[i]);

	    for (j = 0; j < d; j++)
	    {
	        if (p - szBuffer > 4000)
            {
                fputs(szBuffer,pf);
                p = szBuffer;
            }

	        c = sample[i*d+j];
	        if (isDoubleZero(c))    continue;
            // p += sprintf(p, " %d:%.12g", j+1,c);
            p += sprintf(p, " %d:%g", j+1,c);

	    }
		p += sprintf(p, "%c", '\n');
	}

    fputs(szBuffer,pf);

    fclose(pf);

	return;
}


#if 0
void DirCreate(IN char* dir)
{
#if 0
    // ���̷�ʧЧ
    char dirname[FILE_NAME_LENGTH];

    //�ж�Ŀ¼�Ƿ����
    if(access(dir,0))
    {
        sprintf(dirname,"md %s", dir);
        system(dirname);
    }
#else
    if(access(dir,0))
    {
        CreateDirectory(dir, NULL);
    }
#endif

    return;
}

BOOL DirCreateRecursion(IN char* dir)
{
    int i;
    int len;
    int ret;
    char newdir[FILE_NAME_LENGTH];

    while (1)
    {
        if (CreateDirectory(dir, NULL))             return TRUE;

        len = strlen(dir);
        for (i = len-1;i >= 0; i--)
        {
            if (dir[i] == ':')                      return FALSE;
            if (dir[i] == '\\' || dir[i] == '/')    break;
        }
        if (i < 0)                                  return FALSE;

        memcpy(newdir, dir, i*sizeof(char));
        newdir[i] = '\0';
        ret = DirCreateRecursion(newdir);
        if (ret == FALSE)                           return FALSE;
    }
}
#endif

/*******************************************************************************
    Func Name: FileListSearch
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����Ŀ¼�µ��ļ���
        Input: IN char *dir, Ŀ¼��
               IN char *postfix, �ļ���׺��ͨ���
       Output: 
       Return: FileList *, �ļ����б�
      Caution: 
      Description: Linux����Ҫ      #include <dirent.h>
                   Windows����Ҫ    #include <windows.h>
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
#ifdef FLATFORM_LINUX

// δ����
FileList *FileListSearch(IN char *dir)
{
    DIR *directory_pointer = opendir(dir);
    struct dirent *entry;
    FileList start;
    FileList *filesNode;
    
    start.next = NULL;
    filesNode = &start;
    while ((entry = readdir(directory_pointer)) != NULL)
    { 
        filesNode->next = (FileList *)malloc(sizeof(FileList));
        filesNode = filesNode->next; 
        strcpy(filesNode->filename, entry->d_name);
        filesNode->next = NULL;
    }
    closedir(directory_pointer); 
    filesNode = start.next;

    return filesNode;         
}

#else

FileList *FileListSearch(IN char *dir, IN char *postfix)
{

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    char pattern[FILE_NAME_LENGTH];
    FileList temp;
    FileList *list = NULL;
#if 0
    // ƴ�Ӻ�׺��
    strcpy(pattern, dir);
    strcat(pattern, "\\");
    strcat(pattern, postfix);

    // �����ļ�
    hFind = FindFirstFile(pattern, &FindFileData);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        FileList *p, *q;
        int flag;

        temp.next = NULL;
        p = &temp;
        do
        {
            flag = (strcmp(FindFileData.cFileName,".") != 0);
            flag &= (strcmp(FindFileData.cFileName,"..") != 0);
            flag &= (strcmp(FindFileData.cFileName,"Thumbs.db") != 0);

            if (flag != 0)
            {
                q = (FileList *)malloc(sizeof(FileList));
                strcpy(q->filename, dir);
                strcat(q->filename, "\\");
                strcat(q->filename, FindFileData.cFileName);
                FileGetNameFromPath(FindFileData.cFileName, q->name, NULL, FALSE);
                q->next = NULL;
                p->next = q;
                p = q;
            }

        }while (FindNextFile(hFind, &FindFileData) != 0);

        list = temp.next;
    }

    FindClose(hFind);
#endif
    return list;

}

#endif

/*******************************************************************************
    Func Name: FileListDestroy
 Date Created: 2011-01-25
       Author: zhusong
     Function: �����ļ����б�
        Input: 
       Output: OUT FileList **l, ���ٵ��ļ����б�
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void FileListDestroy(OUT FileList **l)
{
    FileList *p = *l;
    FileList *q;
    
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    *l = NULL;

    return;
}

/*******************************************************************************
    Func Name: FileListNum
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����Ŀ¼�µ��ļ�����
        Input: IN char *dir, Ŀ¼��
               IN char *postfix, �ļ���׺��ͨ���
       Output: 
       Return: int, �ļ�����
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
int FileListNum(IN char *dir, IN char *postfix)
{
    int n = 0;
    FileList *result;
    FileList *p;

    result = FileListSearch(dir, postfix);

    p = result;
    while (p != NULL)
    {
        p = p->next;
        n++;
    }
    FileListDestroy(&result);

    return n;
}
int FileListNum(IN FileList *L)
{
    int n = 0;
    FileList *p;

    p = L;
    while (p != NULL)
    {
        p = p->next;
        n++;
    }

    return n;
}

/*******************************************************************************
    Func Name: DirListSearch
 Date Created: 2011-01-25
       Author: zhusong
     Function: ����Ŀ¼�µ���Ŀ¼
        Input: IN char *dir, Ŀ¼��
       Output: 
       Return: FileList *, Ŀ¼���б�
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
FileList *DirListSearch(IN char *path, IN int flag)
{
    struct _finddata_t FileInfo;
    long Handle;
    char str[256];

    int i = 0;
    FileList *list = NULL;
    FileList *p, *tail;

    // ����Ŀ¼�з����������ļ�
    strcpy (str, path);
    strcat(str, "\\*");
    Handle = _findfirst(str, &FileInfo);
    if ( Handle == -1L )    return NULL;

    //�����ҵ����ǵ�ǰ�ļ���"."�����Բ��ô���
    while(!_findnext(Handle,&FileInfo))
    {
        if((FileInfo.attrib & _A_SUBDIR) == 16 && strcmp(FileInfo.name,".."))
        {
            p = (FileList *)malloc(sizeof(FileList));
            p->next = NULL;
            if (flag == FALSE)
            {
                strcpy(p->filename, FileInfo.name);
            }
            else
            {
                strcpy(p->filename, path);
                strcat(p->filename, "\\");
                strcat(p->filename, FileInfo.name);
            }

            if (i == 0) list = p;
            else        tail->next = p;
            tail = p;
            i++;
        }
    }
    _findclose(Handle);

    return list;
}

/*******************************************************************************
    Func Name: CommandDecompose
 Date Created: 2011-01-25
       Author: zhusong
     Function: �����н���
        Input: IN char *command, ������
       Output: OUT int *pos, ������ʼλ��
       		   OUT int *len, �����
       		   OUT int *num, �������
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void CommandDecompose(IN char *command, OUT int *pos, OUT int *len, OUT int *num)
{
	int i, n;
	char c;

	c = command[0];
	for (i = 0, n = 0;c != '\0';i++)
	{
		// �����ָ���
		while (c == ' ' || c == '\t')
		{
			i++;
			c = command[i];
		}

		// ���ַ���
		pos[n] = i;
		while (c != ' ' && c != '\t' && c != '\0')
		{
			i++;
			c = command[i];
		}
		len[n] = i - pos[n];
		n++;
	}

	*num = n;

	return;
}






