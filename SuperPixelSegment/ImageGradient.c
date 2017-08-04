/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: ImageGradient.c 	                                             */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2012/11/16                                                          */
/*                                                                           */
/* Description: ͼ���ݶ�                                                     */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif /* end of __cplusplus */
#include "math.h"
#include "ImageGradient.h"


/*******************************************************************************
    Func Name: ImageGradient1
 Date Created: 2011-01-26
       Author: zhusong
     Function: ͼ��2�����ݶ�-1��΢��
        Input: IN IMAGE_S *srcImage, Դͼ��
               IN int type, 
       Output: OUT IMAGE32_S *Gx, x������ݶ�
               OUT IMAGE32_S *Gy, y������ݶ�
       Return: ��
      Caution: 
      Description: gx = I(x+1)-I(x), gy = I(y+1)-I(y)
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void ImageGradient1(IN IMAGE_S *srcImage, 
                    OUT IMAGE32_S *Gx, 
                    OUT IMAGE32_S *Gy,
                    IN int type)
{
    PIXEL *src = srcImage->data;
    int width = srcImage->width;
    int height = srcImage->height;
    int channel = srcImage->channel;
    int widthc = width*channel;
    int *gradx = Gx->data;
    int *grady = Gy->data;

    int x, y;
    PIXEL *p;
    int *gx, *gy;
    RECT_S *rect = NULL;
    int left, right, top, bottom;

    RectEnsure(rect);

    Gx->width = width;
    Gx->height = height;
    Gx->channel = 1;
    Gy->width = width;
    Gy->height = height;
    Gy->channel = 1;

    // ��ͼ���ݶ�
    src += top*widthc + left*channel;
    gx = gradx + top*width;
    gy = grady + top*width;
    for(y = top; y < bottom; y++, src += widthc, gx += width, gy += width)
    {
        p = src;
        for(x = left; x < right; x++, p += channel)
        {
            gx[x] = VectorDistPixelInt(p, p + channel, channel, type);
            gy[x] = VectorDistPixelInt(p, p + widthc, channel, type);
        }

        // ���һ�� y �����ݶ�
        gy[x] = VectorDistPixelInt(p, p + widthc, channel, type);
    }

    // ���һ�� x �����ݶ�
    p = src;
    for(x = left; x < right; x++, p += channel)
    {
        gx[x] = VectorDistPixelInt(p, p + channel, channel, type);
    }

    // �߽��ֵ ���һ�� x �����ݶȺ����һ�� y �����ݶ�
    gx = gradx + top*width + right;
    for(y = top; y <= bottom; y++, gx += width)
    {
        gx[0] = gx[-1];
    }
    gy = grady + bottom*width;
    for(x = left; x <= right; x++)
    {
        gy[x] = gy[x - width];
    }

    return;
}

/*******************************************************************************
    Func Name: ImageGradientX2
 Date Created: 2011-01-26
       Author: zhusong
     Function: ͼ��2�����ݶ�-2��΢��
        Input: IN IMAGE_S *srcImage, Դͼ��
               IN int type, �ݶȾ��뺯��
       Output: OUT IMAGE32_S *Gx, x������ݶ�
       Return: ��
      Caution: 
      Description: ʵ��ֵ����ֵ��ֵ�2�� !

                   �ڲ����ز�����ֵ���:
                   dx(i,j) = [I(i+1,j) - I(i-1,j)]/2;
                   dy(i,j) = [I(i,j+1) - I(i,j-1)]/2;
                   �߽����ز��ò��:
                   dx(i,j) = I(i+1,j) - I(i,j);
                   dy(i,j) = I(i,j+1) - I(i,j);
                   �ȼ��� matlab����[GradX GradY] = gradient(srcImage)
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void ImageGradientX2(IN IMAGE_S *srcImage,
                     OUT IMAGE32_S *Gx,
                     IN int type)
{
    PIXEL *image = srcImage->data;
    int width = srcImage->width;
    int height = srcImage->height;
    int channel = srcImage->channel;
    int channel2 = 2*channel;
    int *gx = Gx->data;

    int x, y;
    PIXEL *px;

    RECT_S *rect = NULL;
    int left, right, top, bottom;

    RectEnsure(rect);

    for(y = top; y <= bottom; y++, gx += width)
    {
        x = left;
        px = image + (y*width+x)*channel;

        // ��˵�
        gx[x] = 2*VectorDistPixelInt(px + channel, px, channel, type);

        // �м��
        for(x++; x < right; x++)
        {
            gx[x] = VectorDistPixelInt(px + channel2, px, channel, type);
            px += channel;
        }

        // �Ҷ˵�
        gx[x] = 2*VectorDistPixelInt(px + channel, px, channel, type);
    }

    Gx->width = width;
    Gx->height = height;
    Gx->channel = 1;

    return;
}

/*******************************************************************************
    Func Name: ImageGradientX2
 Date Created: 2011-01-26
       Author: zhusong
     Function: 
        Input: IN IMAGE_S *srcImage, Դͼ��
               IN int trunc, �ض�ֵ
       Output: OUT IMAGE32_S *Gx, x������ݶ�
       Return: ��
      Caution: 
      Description: -1  0   1
                   -2  0   2
                   -1  0   1
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
void ImageSobelHor(IN IMAGE_S *srcImage,
                   OUT IMAGE32_S *Gx,
                   IN int trunc,
                   IN int c)
{
    int maxv = 2*trunc;
    PIXEL *image = srcImage->data + c;
    int width = srcImage->width;
    int height = srcImage->height;
    int channel = srcImage->channel;
    int *grad = Gx->data;

    int x, y;
    PIXEL *px1,*px2,*px3;
    int sobel;
    int *gx;

    RECT_S *rect = NULL;
    int left, right, top, bottom;

    RectEnsure(rect);

    // �м��
    gx = grad + (top+1)*width;
    for(y = top+1; y < bottom; y++, gx += width)
    {
        x = left+1;
        px1 = image + ((y-1)*width+x)*channel;
        px2 = image + (y*width+x)*channel;
        px3 = image + ((y+1)*width+x)*channel;
        for(; x < right; x++)
        {
            sobel = (px1[channel]-px1[-channel]) + 
                    (px2[channel]-px2[-channel])*2 + 
                    (px3[channel]-px3[-channel]);
            sobel += trunc;
            sobel = (0 > sobel) ? 0 : sobel;
            sobel = (maxv < sobel) ? maxv : sobel;
            gx[x] = sobel;
            px1 += channel;
            px2 += channel;
            px3 += channel;
        }
    }

    // ��Ե
    gx = grad + top*width;
    for(x = left+1; x < right; x++)             gx[x] = gx[x+width];
    gx = grad + bottom*width;
    for(x = left+1; x < right; x++)             gx[x] = gx[x-width];
    gx = grad;
    for(y = top; y <= bottom; y++, gx += width) gx[0] = gx[1];
    gx = grad + right;
    for(y = top; y <= bottom; y++, gx += width) gx[0] = gx[-1];

    Gx->width = width;
    Gx->height = height;
    Gx->channel = 1;

    return;
}

#ifdef __cplusplus
}
#endif /* end of __cplusplus */
