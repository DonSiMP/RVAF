/*
Stereo Vision Algorithm Framework, Copyright(c) 2016-2018, Peng Chao
*/

#pragma once
#include <opencv2\opencv.hpp>
#include "../src/Circuit.h"
//#include "../svaf/svaf.pb.h"

using namespace std;
using namespace cv;

namespace svaf{

class Circuit;

// ��ʱ����
class Timer{
public:
	// �����
	void StartWatchTimer(){
		QueryPerformanceFrequency(&m_liPerfFreq);
		QueryPerformanceCounter(&m_liPerfStart);
	}

	// ��ȡ���
	float ReadWatchTimer(){
		char temp[64];
		QueryPerformanceCounter(&liPerfNow);
		dfTim = (((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000.0f) / m_liPerfFreq.QuadPart);//��λΪms
		return dfTim;
	}

	// ��ȡ��������Ϣ����Ļ
	float ReadWatchTimer(char *cstr){
		return ReadWatchTimer(string(cstr));
	}

	float ReadWatchTimer(string str){
		char temp[64];
		QueryPerformanceCounter(&liPerfNow);
		dfTim = (((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000.0f) / m_liPerfFreq.QuadPart);//��λΪms
		sprintf(temp, ": %3f ms\n", dfTim);
		DLOG(INFO) << str << temp;
		return dfTim;
	}

	// ����ֱ����ʽת�������¼��ʱ��
	operator float(){
		return dfTim;
	}

protected:
	LARGE_INTEGER m_liPerfFreq;
	LARGE_INTEGER m_liPerfStart;
	LARGE_INTEGER liPerfNow;
	double dfTim;
};

class Layer
{
public:
	Layer();
	explicit Layer(LayerParameter&);
	~Layer();
	virtual bool Run(vector<Block>&, vector<Block>&, LayerParameter&, void*) = 0;
	void RLOG(std::string);
public:
	// ��̬��Ա�������μ�cpp�ļ�
	static Figures<> *figures;
	static size_t *id;
	static SvafApp task_type;
	static bool gui_mode;
	static Circuit *pCir;
	
protected:
	Timer __t;		// ��¼��ʱ��
	bool  __show;	// �Ƿ���ʾ���
	bool  __save;	// �Ƿ񱣴���
	bool  __bout;	// �Ƿ����������
	bool  __logi;	// �Ƿ��¼��Ϣ
	bool  __logt;	// �Ƿ��¼ʱ��
	string __name;	// �������
	
};

}
