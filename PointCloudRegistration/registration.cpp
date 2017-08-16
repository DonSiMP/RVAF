#include <iostream>
#include <time.h>
#include <limits>
#include <fstream>
#include <vector>

#include <Eigen/Core>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/icp_nl.h>
#include <pcl/registration/ia_ransac.h>
#include <pcl/features/pfh.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/voxel_grid.h> 
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/kdtree/kdtree_flann.h>

using namespace pcl;

namespace pc{

class MyPointRepresentation : public pcl::PointRepresentation <PointNormal> //�̳й�ϵ
{
	using pcl::PointRepresentation<PointNormal>::nr_dimensions_;
public:
	MyPointRepresentation() {
		nr_dimensions_ = 4; // dimention
	}

	//���غ���copyToFloatArray���Զ����Լ�����������
	virtual void copyToFloatArray(const PointNormal &p, float * out) const {
		//< x, y, z, curvature > ����xyz������
		out[0] = p.x;
		out[1] = p.y;
		out[2] = p.z;
		out[3] = p.curvature;
	}
};

Eigen::Matrix4f icpNonLinear(PointCloud<PointNormal>::Ptr src_in, PointCloud<PointNormal>::Ptr tgt,
	int max_iteration, double max_correspondence_distance, double eps){

	PointCloud<PointNormal>::Ptr src(new PointCloud<PointNormal>());
	pcl::copyPointCloud(*src_in, *src);

	pcl::IterativeClosestPointNonLinear<PointNormal, PointNormal> reg;
	reg.setTransformationEpsilon(eps);

	reg.setMaxCorrespondenceDistance(max_correspondence_distance);
	MyPointRepresentation point_representation;
	reg.setPointRepresentation(boost::make_shared<const MyPointRepresentation>(point_representation));
	reg.setInputCloud(src);
	reg.setInputTarget(tgt);
	reg.setMaximumIterations(max_iteration);

	Eigen::Matrix4f Ti = Eigen::Matrix4f::Identity(), prev;
	PointCloud<PointNormal>::Ptr reg_result = src;

	for (int i = 0; i < 30; ++i){
		src = reg_result;
		reg.setInputCloud(src);
		reg.align(*reg_result);
		Ti = reg.getFinalTransformation() * Ti;
		if (fabs((reg.getLastIncrementalTransformation() - prev).sum()) 
			< reg.getTransformationEpsilon()){
			reg.setMaxCorrespondenceDistance(reg.getMaxCorrespondenceDistance() - 0.01);
		}
		prev = reg.getLastIncrementalTransformation();
	}

	//Eigen::Matrix4f targetToSource = Ti.inverse();

	return Ti;
}

}