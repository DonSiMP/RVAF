/*
Stereo Vision Algorithm Framework, Copyright(c) 2016-2018, Peng Chao
�����طָBy:���ɣ�
*/

#include "SupixSegLayer.h"
#include "../../SuperPixelSegment/svafinterface.h"

using namespace pc;

namespace svaf{

// ���캯��
SupixSegLayer::SupixSegLayer(LayerParameter& layer) : Layer(layer)
{
	// �����طָ����
	K = layer.supix_param().k(); // K����
	M = layer.supix_param().m(); // �ָ���С
	optint = layer.supix_param().optint();	// �Ƿ�����
	saveseg = layer.supix_param().saveseg(); // ����ָ��ļ�
	segname = layer.supix_param().segname();
}

// ��������
SupixSegLayer::~SupixSegLayer()
{
}

// ���г����طָ��㷨
bool SupixSegLayer::Run(vector<Block>& images, vector<Block>& disp, LayerParameter& layer, void* param){
	for (int i = 0; i < images.size(); ++i){
		Mat mat = SuperPixelSegment(images[i].image, K, M, optint, saveseg, segname);

		if (task_type == SvafApp::S_SUPIX || task_type == SvafApp::B_SUPIX){
			__bout = true;
		} else {
			__bout = false;
		}

		if (__show || __save || __bout){
			disp.push_back(Block(images[i].name + " supix", mat, __show, __save, __bout));
		}
	}
	LOG(INFO) << "superpixel map has been computed.";
	RLOG("superpixel map has been computed.");
	return true;
}

}
