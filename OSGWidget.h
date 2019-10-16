#pragma once
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QEvent>

#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/DrawPixels>
#include <osg/Point>
#include <osg/StateAttribute>
#include <osg/PointSprite>
#include <osg/Camera>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>
#include <osgUtil/SmoothingVisitor>
#include <osgText/Text>
#include <osgWidget/Box>

#include <iostream>

#include "OSGCameraManipulator.h"
#include "OSGPickHandler.h"

class OSGWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	/**
		���Ʋ���
	*/
	enum MeauseCloud
	{
		NONE,//��
		RESET,//����
		ONEPOINT,//����һ��
		TWOMEAUSE//��������
	};
	OSGWidget(QWidget *parent = nullptr);
	~OSGWidget();
	/**
		���ҳ����ӽڵ�yan
	*/
	osg::Node* getChildNode(std::string name);
	/**
		//���ĵ�Ҷ�ӽڵ���ɫ��geode��Ҷ�ӽڵ㣬axis�����Ǹ��᷽�������ɫ��begColor:��ʼ��ɫ��endColor��������ɫ
	*/
	void ChangedCloudColor(osg::Geode* geode,osg::Vec3 axis,osg::Vec4 begColor, osg::Vec4 endColor);
protected:
	void initializeGL()override;
	void paintGL()override;
	void resizeGL(int w, int h)override;
	//��osgGA::EventQueue�¼���Qt����¼������
	void mouseDoubleClickEvent(QMouseEvent *event)override;
	void mouseMoveEvent(QMouseEvent *event)override;
	void mousePressEvent(QMouseEvent *event)override;
	void mouseReleaseEvent(QMouseEvent *event)override;
	void wheelEvent(QWheelEvent *event)override;
	void keyPressEvent(QKeyEvent *event)override;
	void keyReleaseEvent(QKeyEvent *event)override;

	bool event(QEvent *event) override;
private:
	osgGA::EventQueue* getEventQueue()const;
	void setKeyboardModifiers(QInputEvent* event);
	/**
		����ڵ�Nodeλ��
	*/
	void computeNodePosition(osg::Node* node, const osg::Camera *camera, bool useBoundingBox);
	/**
		 ��ȡ3D����
	*/
	//osg::ref_ptr<osg::Vec3dArray> ReadModelFile(std::string filename);
	osg::ref_ptr<osg::Vec3Array> ReadModelFile(std::string filename);
	//���ԣ�
	/**
		����Բ��
	*/
	osg::ref_ptr<osg::Node> createCylinder();
	/**
	����OSG�����ģ��
	*/
	osg::ref_ptr<osg::Node> createOSGGlider();
	//�����ı���
	osg::ref_ptr<osg::Node> createQuad();
	//�������Ե���
	osg::ref_ptr<osg::Node> createCloud();
	//����Ԥ���弸����
	osg::ref_ptr<osg::Node> createShape();
	//����������
	osg::ref_ptr<osg::Node> createCoordinate();
	//����HUD
	osg::ref_ptr<osg::Node> createHUD(osgViewer::Viewer*);
public slots:
	void onCylinder();
	void onQuad();
	void onCloud();
	void onShape();
	void onGlider();
	void onClear();
	void onRecHeightRamp(int axis, QColor beginColor, QColor endColor);

	void onSelCloudPoint(OSGWidget::MeauseCloud meause);

	void onTest();
private:
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
	osg::ref_ptr<osgViewer::Viewer> _mViewer;

	osg::ref_ptr<OSGPickHandler> _mPickHandler = nullptr;
};
