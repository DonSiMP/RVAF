/*
Stereo Vision Algorithm Framework, Copyright(c) 2016-2018, Peng Chao
OpenCVʵ����������
*/


#include "CVDesciptorLayer.h"
#include <opencv2\nonfree\nonfree.hpp>

using namespace pc;

namespace svaf{

// ���캯��
CVDesciptorLayer::CVDesciptorLayer(LayerParameter& layer) : Layer(layer)
{
	type = layer.cvdescriptor_param().type(); // ������������
	brieflength = layer.cvdescriptor_param().brief_param().length(); // ����������
	// ���������������ʹ�����������OpenCV��
	switch (type)
	{
	case svaf::CVDescriptorParameter_DespType_SIFT:
		ptr = &CVDesciptorLayer::Sift;
		despname = "SIFT";
		break;
	case svaf::CVDescriptorParameter_DespType_SURF:
		ptr = &CVDesciptorLayer::Surf;
		despname = "SURF";
		break;
	case svaf::CVDescriptorParameter_DespType_BRIEF:
		ptr = &CVDesciptorLayer::Brief;
		despname = "Brief";
		break;
	case svaf::CVDescriptorParameter_DespType_BRISK:
		ptr = &CVDesciptorLayer::Brisk;
		despname = "BRISK";
		break;
	case svaf::CVDescriptorParameter_DespType_ORB:
		ptr = &CVDesciptorLayer::ORB;
		despname = "ORB";
		break;
	case svaf::CVDescriptorParameter_DespType_FREAK:
		ptr = &CVDesciptorLayer::Freak;
		despname = "FREAK";
		break;
	case svaf::CVDescriptorParameter_DespType_OPPONENT:
		ptr = &CVDesciptorLayer::OppenentColor;
		despname = "Oppenent";
	default:
		break;
	}

}

// ��������
CVDesciptorLayer::~CVDesciptorLayer()
{
}

// �������������㷨
bool CVDesciptorLayer::Run(vector<Block>& images, vector<Block>& disp, LayerParameter& layer, void* param){
	
	(this->*ptr)(images, disp);

	return true;
}

// OpenCV����SIFT��������
bool CVDesciptorLayer::Sift(vector<Block>& images, vector<Block>& disp){
	Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create(despname);
	for (int i = 0; i < images.size(); ++i){
		extractor->compute(images[i].image, images[i].keypoint, images[i].descriptors);
	}
	return true;
}

// OpenCV����SURF��������
bool CVDesciptorLayer::Surf(vector<Block>& images, vector<Block>& disp){
	Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create(despname);
	for (int i = 0; i < images.size(); ++i){
		extractor->compute(images[i].image, images[i].keypoint, images[i].descriptors);
	}
	return true;
}

// OpenCV����Brief��������
bool CVDesciptorLayer::Brief(vector<Block>& images, vector<Block>& disp){
	BriefDescriptorExtractor extractor(brieflength);
	for (int i = 0; i < images.size(); ++i){
		extractor.compute(images[i].image, images[i].keypoint, images[i].descriptors);
	}
	return true;
}

// OpenCV����Brisk��������
bool CVDesciptorLayer::Brisk(vector<Block>& images, vector<Block>& disp){
	Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create(despname);
	for (int i = 0; i < images.size(); ++i){
		extractor->compute(images[i].image, images[i].keypoint, images[i].descriptors);
	}
	return true;
}

// OpenCV����ORB��������
bool CVDesciptorLayer::ORB(vector<Block>& images, vector<Block>& disp){
	Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create(despname);
	for (int i = 0; i < images.size(); ++i){
		extractor->compute(images[i].image, images[i].keypoint, images[i].descriptors);
	}
	return true;
}

// OpenCV����Freak��������
bool CVDesciptorLayer::Freak(vector<Block>& images, vector<Block>& disp){
	Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create(despname);
	for (int i = 0; i < images.size(); ++i){
		extractor->compute(images[i].image, images[i].keypoint, images[i].descriptors);
	}
	return true;
}

bool CVDesciptorLayer::OppenentColor(vector<Block>& images, vector<Block>& disp){
	
	// Adapt to color
	return true;
}

}
