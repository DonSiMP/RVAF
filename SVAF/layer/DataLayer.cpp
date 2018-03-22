/*
Stereo Vision Algorithm Framework, Copyright(c) 2016-2018, Peng Chao
�������ӿ�
*/


#include "DataLayer.h"

namespace svaf{

// ���캯��
DataLayer::DataLayer(LayerParameter& layer) : chns_(0), Layer(layer)
{
	// ���ݽű��ж��Ƿ�ͼ��ת��Ϊ�ҶȻ��ɫ
	if (layer.data_param().has_color()){
		if (layer.data_param().color()){
			chns_ = 3;
		} else{
			chns_ = 1;
		}
	}
}

// ��������
DataLayer::~DataLayer()
{
}

// ����
bool DataLayer::Run(std::vector<Block>& images, vector<Block>& disp, LayerParameter& layer, void* param){
	if (chns_ == 1){
		// ת��Ϊ��ͨ��ͼ����
		for (int i = 0; i < images.size(); ++i){
			if (!images[i].image.empty()){
				if (images[i].image.channels() == 3){
					cvtColor(images[i].image, images[i].image, CV_BGR2GRAY);
				}
			}
		}
	} else{
		// ת��Ϊ��ͨ��ͼ��
		for (int i = 0; i < images.size(); ++i){
			if (!images[i].image.empty()){
				if (images[i].image.channels() == 1){
					cvtColor(images[i].image, images[i].image, CV_GRAY2RGB);
				}
			}
		}
	}

	// �Ƿ������������
	if (task_type == SvafApp::S_SHOW || task_type == SvafApp::B_SHOW || task_type == SvafApp::SITCH ||
		task_type == SvafApp::STEREO_MATCH){
		__bout = true;
	} else {
		__bout = false;
	}

	// ��ʾ�뱣��
	if (__show || __save || __bout){
		for (int i = 0; i < images.size(); ++i){
			disp.push_back(Block(images[i].name, images[i].image, __show, __save, __bout));
		}
	}
	return true;
}

}

