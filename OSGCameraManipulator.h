#pragma once
#include <osgGA/CameraManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/Viewer>
#include <osg/Camera>
#include <osg/ComputeBoundsVisitor>
#include <iostream>
/**
�Զ���OSG���������
*/
class OSGCameraManipulator :
	public osgGA::TrackballManipulator
{
public:
	OSGCameraManipulator();
	virtual ~OSGCameraManipulator();
//	///**
//	//��������ڴ�һ��������л�����һ�������ʱ���ã���������һ�����������ͼ���󴫹�����
//	//�����Ϳ������趨�Լ��ĳ�ʼλ���ˡ�
//	//*/
//	virtual void setByMatrix(const osg::Matrixd& matrix) {
//
//	}
//
//	/**
//	������������ⲿֱ�ӵ���Viewer��setViewByMatrix����ʱ�������õľ��󴫹�������
//	�������ס�¸��ĵ�λ��
//	*/
//	virtual void setByInverseMatrix(const osg::Matrixd& matrix)
//	{
//	}
//
//	/** 
//		SetByMatrix������Ҫ�ľ����������������õ��ģ���������һ����������ݾ���
//	*/
//	virtual osg::Matrixd getMatrix() const {
//		osg::Matrixd mat;
//		mat.makeRotate(_rotate.x(), osg::X_AXIS, _rotate.y(), osg::Y_AXIS, _rotate.z(), osg::Z_AXIS);
//		std::cout << "getMatrix" << std::endl;
//		return mat* osg::Matrixd::translate(_position);
//	}
//
//	/** 
//	��ͼ���󣨹۲�����Ǳ任����������)   ���������Ҫ�ķ������������ÿ֡�ᱻ���ã������ص�ǰ����ͼ����
//��������������ʱ��Ĵ����ı��Լ���״̬�������� getInverseMatrix ������ʱ���ı�
//�������������λ����̬����������� void Viewer::updateTraversal()�б�����
// _camera->setViewMatrix(_cameraManipulator->getInverseMatrix());
//	*/
//	virtual osg::Matrixd getInverseMatrix() const {
//		osg::Matrixd mat;
//		mat.makeRotate(_rotate.x(), osg::X_AXIS, _rotate.y(), osg::Y_AXIS, _rotate.z(), osg::Z_AXIS);
//		return osg::Matrixd::inverse(mat* osg::Matrixd::translate(_position));
//	}
	/**
	������������������������һ����GUI�¼��Ĺ����ߣ��ڶ�����������handle������GUI
���з�������������GUIEventHandler���������¼���GUI����һЩ������
���Ҫ�����¼��������Դ�GUIEventHandler�̳г��Լ����࣬Ȼ�󸲸�handle����������
������¼�����osgProducer::Viewer��ά��һ��GUIEventHandler���У��¼���������������δ�
�ݣ�handle�ķ���ֵ��������¼��Ƿ�����ú����GUIEventHandler�����������true����ֹͣ
�����������false�������GUIEventHandler���л������������¼�������Ӧ��
	*/
	//virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	virtual bool performMovement();
	virtual void computeHomePosition(const osg::Camera *camera = NULL, bool useBoundingBox = false);
private:
	//����Ҽ�������
	//bool IsRightButton = false;
	////�ӵ�λ��
	//osg::Vec3f _position;
	////�ӵ㷽��
	//osg::Vec3f _rotate;
	//float _speed;
	//float _angle;
};

