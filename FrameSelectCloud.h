#pragma once
/**
���ƿ�ѡ
*/
#include <osg/Referenced>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osg/Point>
#include <osgUtil/SmoothingVisitor>
#include <map>
#include <QString>

class FrameSelectCloud :
	public osg::Referenced
{
public:
	FrameSelectCloud(osg::ref_ptr<osgViewer::Viewer> viewer);
	virtual ~FrameSelectCloud();
	void SetFirstPos(osg::Vec2 pos);
	/**����ѡ���*/
	void DrawSelRect(osg::Vec2 pos);
	//bool FramePick(const osgGA::GUIEventAdapter& ea);
	bool DragFrame(osg::Vec2 curPos);
	//�������ѡ��ĵ�
	void clear();
	void Redraw();
private:
	
	//��ѡ�е�ҳ�ڵ�
	osg::ref_ptr<osg::Geode> mGeode;
	osg::ref_ptr<osgViewer::Viewer> mViewer;
	//��¼�������һ��
	osg::Vec2 mSPos1;
public:
	//�Ƿ������϶�
	bool IsAllowDrag = false;
	////ѡ�еĶ�����
	std::map<unsigned int, osg::Vec3> list;
	QString mSelNodeName;
	//����HUD���
	osg::ref_ptr<osg::Camera> mHUDCamera;
};

