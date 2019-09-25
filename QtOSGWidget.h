#pragma once
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QEvent>

#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>
#include <osgUtil/SmoothingVisitor>

#include <iostream>

#include "QtCameraManipulator.h"

class QtOSGWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	QtOSGWidget(QWidget *parent = nullptr);
	~QtOSGWidget();
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
		 ��ȡ3D����
	*/
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
public slots:
	void onCylinder();
	void onQuad();
	void onCloud();
	void onShape();
	void onGlider();
	void onClear();
private:
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
	osg::ref_ptr<osgViewer::Viewer> _mViewer;
};