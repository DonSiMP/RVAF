/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: ImageCensus.c 	                                                 */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2012/11/16                                                          */
/*                                                                           */
/* Description: ͼ��Census�任                                               */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif /* end of __cplusplus */

#include "ImageCensus.h"
// #include <emmintrin.h>

/*******************************************************************************
    Func Name: ImageCensus
 Date Created: 2012-10-24
       Author: zhusong
     Function: ͼ��Census�任
        Input: IN IMAGE_S *srcImage, Դͼ��
               IN int m, ģ����
               IN int n, ģ����
       Output: OUT IMAGE64_S *dstImage, Ŀ��ͼ��
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void ImageCensus(IN IMAGE_S *srcImage, 
                 OUT IMAGE64_S *dstImage,
                 IN int m,
                 IN int n)
{
    int x, y;
    int i, j;
    int w = 2*m+1;
    int width = srcImage->width;
    int height = srcImage->height;
    PIXEL *srcdata = srcImage->data;
    int64 *dstdata = dstImage->data;

    int x1 = m;
    int x2 = width-1-m;
    int y1 = n;
    int y2 = height-1-n;

    int off;
    PIXEL cur;
    PIXEL *src;
    PIXEL *p,*q;
    int64 *dst;
    int64 mask, maskb, masks;
    int64 val;

    dstImage->width = width;
    dstImage->height = height;
    dstImage->channel = 1;
    memset(dstdata, 0, width*height*sizeof(int64));

    p = srcdata;
    off = y1*width;
    src = srcdata + off;
    dst = dstdata + off;
    for(y = y1;y <= y2;y++, src += width, dst += width, p += width)
    {
        for(x = x1;x <= x2;x++)
        {
            cur = src[x];
            q = p + x;
            mask = 1;
            val = 0;
            for(i = -n;i <= n;i++,q += width)// ����ͼ����ÿ���㣬����m*n�Ĵ���
            {
                for(j = -m;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
    }

    // ���±߽� ����+��ֵ
    y = y1-1;
    off = y*width;
    src = srcdata + off;
    dst = dstdata + off;
    maskb = 1;
    maskb <<= w;
    for(;y >= 0;y--, src -= width, dst -= width, maskb <<= w)
    {
        // ��Ч��������
        masks = 0;
        mask = maskb;
        for(i = -y;i <= n;i++)
        {
            for(j = -m;j <= m;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
        }
        // ��Ч��������
        masks = ~masks;

        for(x = x1;x <= x2;x++)
        {
            // ��Ч�����ֵ
            val = dst[x+width] & masks;

            // ��Ч�������
            cur = src[x];
            q = srcdata + x;
            mask = maskb;
            for(i = -y;i <= n;i++,q += width)
            {
                for(j = -m;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
    }

    y = y2+1;
    off = y*width;
    src = srcdata + off;
    dst = dstdata + off;
    p = src - n*width;
    for(y = n-1;y >= 0;y--, src += width, dst += width, p += width)
    {
        masks = 0;
        mask = 1;
        for(i = -n;i <= y;i++)
        {
            for(j = -m;j <= m;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
        }
        masks = ~masks;

        for(x = x1;x <= x2;x++)
        {
            val = dst[x-width] & masks;

            cur = src[x];
            q = p + x;
            mask = 1;
            for(i = -n;i <= y;i++,q += width)
            {
                for(j = -m;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
    }

    // ���ұ߽� ����+��ֵ
    for(x = x1-1;x >= 0;x--)
    {
        masks = 0;
        mask = 1;
        for(i = -n;i <= n;i++,q += width)
        {
            mask <<= (m-x);
            for(j = -x;j <= m;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
        }
        masks = ~masks;

        dst = dstdata;
        for(y = 0;y < y1;y++, dst += width)
        {
            dst[x] = dst[x+1];
        }
        p = srcdata + x;
        src = p + y1*width;
        for(;y <= y2;y++, src += width, dst += width, p += width)
        {
            val = dst[x+1] & masks;

            q = p;
            mask = 1;
            for(i = -n;i <= n;i++,q += width)
            {
                mask <<= (m-x);
                for(j = -x;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
        for(;y < height;y++, dst += width)
        {
            dst[x] = dst[x+1];
        }
    }

    for(x = x2+1;x < width;x++)
    {
        off = width-1-x;
        masks = 0;
        mask = 1;
        for(i = -n;i <= n;i++)
        {
            for(j = -m;j <= off;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
            mask <<= (m-off);
        }
        masks = ~masks;

        dst = dstdata;
        for(y = 0;y < y1;y++, dst += width)
        {
            dst[x] = dst[x-1];
        }
        p = srcdata + x;
        src = p + y1*width;
        for(;y <= y2;y++, src += width, dst += width, p += width)
        {
            val = dst[x-1] & masks;

            q = p;
            mask = 1;
            for(i = -n;i <= n;i++,q += width)
            {
                for(j = -m;j <= off;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
                mask <<= (m-off);
            }
            dst[x] = val;
        }
        for(;y < height;y++, dst += width)
        {
            dst[x] = dst[x-1];
        }
    }

    return;
}

void ImageCensus32(IN IMAGE_S *srcImage, 
                   OUT IMAGE32_S *dstImage,
                   IN int m,
                   IN int n)
{
    int x, y;
    int i, j;
    int w = 2*m+1;
    int width = srcImage->width;
    int height = srcImage->height;
    PIXEL *srcdata = srcImage->data;
    int *dstdata = dstImage->data;

    int x1 = m;
    int x2 = width-1-m;
    int y1 = n;
    int y2 = height-1-n;

    int off;
    PIXEL cur;
    PIXEL *src;
    PIXEL *p,*q;
    int *dst;
    int mask, maskb, masks;
    int val;

    dstImage->width = width;
    dstImage->height = height;
    dstImage->channel = 1;
    memset(dstdata, 0, width*height*sizeof(int));

    p = srcdata;
    off = y1*width;
    src = srcdata + off;
    dst = dstdata + off;
    for(y = y1;y <= y2;y++, src += width, dst += width, p += width)
    {
        for(x = x1;x <= x2;x++)
        {
            cur = src[x];
            q = p + x;
            mask = 1;
            val = 0;
            for(i = -n;i <= n;i++,q += width)
            {
                for(j = -m;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
    }

    // ���±߽� ����+��ֵ
    y = y1-1;
    off = y*width;
    src = srcdata + off;
    dst = dstdata + off;
    maskb = 1;
    maskb <<= w;
    for(;y >= 0;y--, src -= width, dst -= width, maskb <<= w)
    {
        // ��Ч��������
        masks = 0;
        mask = maskb;
        for(i = -y;i <= n;i++)
        {
            for(j = -m;j <= m;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
        }
        // ��Ч��������
        masks = ~masks;

        for(x = x1;x <= x2;x++)
        {
            // ��Ч�����ֵ
            val = dst[x+width] & masks;

            // ��Ч�������
            cur = src[x];
            q = srcdata + x;
            mask = maskb;
            for(i = -y;i <= n;i++,q += width)
            {
                for(j = -m;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
    }

    y = y2+1;
    off = y*width;
    src = srcdata + off;
    dst = dstdata + off;
    p = src - n*width;
    for(y = n-1;y >= 0;y--, src += width, dst += width, p += width)
    {
        masks = 0;
        mask = 1;
        for(i = -n;i <= y;i++)
        {
            for(j = -m;j <= m;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
        }
        masks = ~masks;

        for(x = x1;x <= x2;x++)
        {
            val = dst[x-width] & masks;

            cur = src[x];
            q = p + x;
            mask = 1;
            for(i = -n;i <= y;i++,q += width)
            {
                for(j = -m;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
    }

    // ���ұ߽� ����+��ֵ
    for(x = x1-1;x >= 0;x--)
    {
        masks = 0;
        mask = 1;
        for(i = -n;i <= n;i++,q += width)
        {
            mask <<= (m-x);
            for(j = -x;j <= m;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
        }
        masks = ~masks;

        dst = dstdata;
        for(y = 0;y < y1;y++, dst += width)
        {
            dst[x] = dst[x+1];
        }
        p = srcdata + x;
        src = p + y1*width;
        for(;y <= y2;y++, src += width, dst += width, p += width)
        {
            val = dst[x+1] & masks;

            q = p;
            mask = 1;
            for(i = -n;i <= n;i++,q += width)
            {
                mask <<= (m-x);
                for(j = -x;j <= m;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
            }
            dst[x] = val;
        }
        for(;y < height;y++, dst += width)
        {
            dst[x] = dst[x+1];
        }
    }

    for(x = x2+1;x < width;x++)
    {
        off = width-1-x;
        masks = 0;
        mask = 1;
        for(i = -n;i <= n;i++)
        {
            for(j = -m;j <= off;j++)
            {
                masks |= mask;
                mask <<= 1;
            }
            mask <<= (m-off);
        }
        masks = ~masks;

        dst = dstdata;
        for(y = 0;y < y1;y++, dst += width)
        {
            dst[x] = dst[x-1];
        }
        p = srcdata + x;
        src = p + y1*width;
        for(;y <= y2;y++, src += width, dst += width, p += width)
        {
            val = dst[x-1] & masks;

            q = p;
            mask = 1;
            for(i = -n;i <= n;i++,q += width)
            {
                for(j = -m;j <= off;j++)
                {
                    if (cur < q[j]) val |= mask;
                    mask <<= 1;
                }
                mask <<= (m-off);
            }
            dst[x] = val;
        }
        for(;y < height;y++, dst += width)
        {
            dst[x] = dst[x-1];
        }
    }

    return;
}

/*******************************************************************************
    Func Name: ImageHamming
 Date Created: 2012-10-24
       Author: zhusong
     Function: ͼ���Hamming����
        Input: IN IMAGE64_S *I1, ͼ��1
               IN IMAGE64_S *I2, ͼ��2
               IN RECT_S *r1, ͼ��1�����������
               IN RECT_S *r2, ͼ��2�����������
               IN RECT_S *r, ����������Ŀ��ͼ�������
       Output: OUT IMAGE_S *I, ͼ��Hamming����
       Return: 
      Caution: 
      Description: 
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void ImageHamming(IN IMAGE64_S *I1,
                  IN IMAGE64_S *I2,
                  IN RECT_S *r1,
                  IN RECT_S *r2,
                  IN RECT_S *r,
                  OUT IMAGE_S *I)
{
    int i,j;
    int w1 = I1->width;
    int h1 = I1->height;
    int w2 = I2->width;
    int h2 = I2->height;
    int w = I->width;
    int h = I->height;

    int width, height;
    int width1, height1;
    int width2, height2;
    int64 *src1,*src2;
    int64 *p1, *p2;
    int64 temp;
    PIXEL *dst;

    // ȷ��ͼ������
    if (r == NULL)
    {
        dst = I->data;
        width = w;
        height = h;
    }
    else
    {
        dst = I->data + r->top*w + r->left;
        width = r->right-r->left+1;
        height = r->bottom-r->top+1;
    }

    if (r1 == NULL)
    {
        src1 = I1->data;
        width1 = w1;
        height1 = h1;
    }
    else
    {
        src1 = I1->data + r1->top*w1 + r1->left;
        width1 = r1->right-r1->left+1;
        height1 = r1->bottom-r1->top+1;
    }

    if (r2 == NULL)
    {
        src2 = I2->data;
        width2 = w2;
        height2 = h2;
    }
    else
    {
        src2 = I2->data + r2->top*w2 + r2->left;
        width2 = r2->right-r2->left+1;
        height2 = r2->bottom-r2->top+1;
    }

    // ͼ��ƥ��
    if (width != width1 || width != width2 ||
        height != height1 || height != height2)
    {
        printf("ImageHamming error!\n");
        return;
    }

    memset(I->data, 0, w*h*sizeof(PIXEL));

    // ͼ��hamming����
    p1 = src1;
    p2 = src2;
    for (i = 0;i < height;i++)
    {
        for (j = 0;j < width;j++)
        {
            temp = p1[j] ^ p2[j];
#if 1
            dst[j] = (PIXEL)BitCountU64(temp);
#else
            dst[j] = (PIXEL)_mm_popcnt_u64(temp);
#endif
        }
        dst += w;
        p1 += w1;
        p2 += w2;
    }

    return;
}

void ImageHamming32(IN IMAGE32_S *I1,
                    IN IMAGE32_S *I2,
                    IN RECT_S *r1,
                    IN RECT_S *r2,
                    IN RECT_S *r,
                    OUT IMAGE_S *I)
{
    int i,j;
    int w1 = I1->width;
    int w2 = I2->width;
    int w = I->width;
    int h = I->height;

    int width, height;
    int *src1,*src2;
    int *p1, *p2;
    int temp;
    PIXEL *dst;

#ifdef PLATFORM_CCS
    mix32 bitcount;
    unit8 *ui8 = bitcount.ui8; 
#endif

    // ȷ��ͼ������
    if (r == NULL)
    {
        dst = I->data;
        width = w;
        height = h;
    }
    else
    {
        dst = I->data + r->top*w + r->left;
        width = r->right-r->left+1;
        height = r->bottom-r->top+1;
    }

    if (r1 == NULL)
    {
        src1 = I1->data;
    }
    else
    {
        src1 = I1->data + r1->top*w1 + r1->left;
    }

    if (r2 == NULL)
    {
        src2 = I2->data;
    }
    else
    {
        src2 = I2->data + r2->top*w2 + r2->left;
    }

    memset(I->data, 0, w*h*sizeof(PIXEL));

    // ͼ��hamming����
    p1 = src1;
    p2 = src2;
    for (i = 0;i < height;i++)
    {
        for (j = 0;j < width;j++)
        {
            temp = p1[j] ^ p2[j];

#ifdef PLATFORM_SSE
            dst[j] = (PIXEL)_mm_popcnt_u32(temp);
#elif defined PLATFORM_CCS
            bitcount.ui32 = _bitc4(temp);
            dst[j] = ui8[0] + ui8[1] + ui8[2] + ui8[3];
#else
            dst[j] = (PIXEL)BitCountU32(temp);
#endif
        }
        dst += w;
        p1 += w1;
        p2 += w2;
    }

    return;
}

#ifdef __cplusplus
}
#endif /* end of __cplusplus */
