#pragma once
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <osg/Point>
#include <osg/Multisample>
#include <osgUtil/SmoothingVisitor>
#include "PointIntersector.h"

#include <QString>
class OSGPickHandler :
	public osgGA::GUIEventHandler
{
public:
	OSGPickHandler(osgViewer::Viewer* viewer);
	virtual ~OSGPickHandler();
	/**����*/
	void Reset();
	/**��һ����*/
	void OnePoint();
	/**��������*/
	void TwoMeause();
	void DrawTips(osg::Vec3 pos);
protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);
private:
	//����һ��ѡ�е�
	osg::ref_ptr<osg::Geode> createSelPoint(QString name, osg::Vec3& pos);
	
	//osg::Geode* DrawOnePoint(QString name,osg::Vec3& pos);
	osg::ref_ptr<osg::Group> mPickGroup;
	osg::ref_ptr<osgViewer::Viewer> mViewer;
	//����������
	int allowPointsNum = 1;
	osg::ref_ptr<osg::Geode> mOnePoint;
	osg::ref_ptr<osg::Geode> mTwoPoint;
	/*std::string mOnePointName;
	std::string mTwoPointName;
	osg::Vec3 mOnePoint;
	osg::Vec3 mTwoPoint;*/
};

