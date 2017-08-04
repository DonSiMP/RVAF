/*****************************************************************************/
/*                                                                           */
/*                            ���ɵ�ͼ����ƽ̨                             */
/*                                                                           */
/* FileName: TimeStat.c    			                                         */
/*                                                                           */
/* Author: zhusong                                                           */
/*                                                                           */
/* Version: 1.01                                                             */
/*                                                                           */
/* Date: 2011/01/23                                                          */
/*                                                                           */
/* Description: �㷨ʱ��ͳ�ƹ���                                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif /* end of __cplusplus */

#include "TimeStat.h"

clock_t overheadClock;
int64 overheadTime;

/*******************************************************************************
    Func Name: TsClock
 Date Created: 2011-01-23
       Author: zhusong
     Function: clock����ͳ�ƴ�������ʱ����
        Input: 
       Output: 
       Return: double, ����ʱ��(��λs������ms)
      Caution: 
      Description: ��׼C���Ժ���
                   clock�������ص���CPU�ķ��ڱ������ϵ�ʱ��
                   ���;��sleep������CPU��Դ���ͷţ�sleepʱ�佫����ͳ�ơ�
                   ����ֵʵ���Ǻķ��ڱ������ϵ�CPUʱ��Ƭ������
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
double TsClock()
{
    clock_t t = 0;

    TsClockInit();
    
    TsClockStart(t);

    /*
        code...
    */

    TsClockEnd(t);

    return (double)(t)/CLOCKS_PER_SEC;
}

/*******************************************************************************
    Func Name: TsTime
 Date Created: 2011-01-23
       Author: zhusong
     Function: gettimeofday����ͳ�ƴ�������ʱ����
        Input: 
       Output: 
       Return: double, ����ʱ��(��λs������us)
      Caution: 
      Description: Windows: QueryPerformanceFrequency && QueryPerformanceCounter
                   Linux: gettimeofday
                   ֱ����ȡӲ��ʱ�ӽ������㣬���Ƚϸ�(us)
                   ֻ�ܼ������ʼʱ��ͽ���ʱ��Ĳ�ֵ�����ܵ���̨�����Ӱ�졣
                   �����̨��æ��������ȫ��ʵ��ӳ����������������ʱ��
--------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
--------------------------------------------------------------------------------  
  YYYY-MM-DD                                                           
                                                                              
*******************************************************************************/
double TsTime()
{
    double t = 0;

    TsTimeInit();
    TsTimeStart(t);

    /*
        code...
    */

    TsTimeEnd(t);
    TsGetTime(t);

    return t;
}



#ifdef __cplusplus
}
#endif /* end of __cplusplus */
