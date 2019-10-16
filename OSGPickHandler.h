#pragma once
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <osg/Point>
#include <osg/Multisample>
#include <osgUtil/SmoothingVisitor>
#include <osgText/Text>

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

#include "PointIntersector.h"
#include <vector>
#include <QString>
/**
	����Ϣ��UIҳ��
*/
class PointBuildBoard:public osg::Referenced {
public :
	PointBuildBoard(std::string id, osg::Vec3 selPointPos, osg::ref_ptr<osgViewer::Viewer> viewer,osg::ref_ptr<osg::Camera> camera);
	~PointBuildBoard();
	/**
		����Box���
	*/
	void CreateBox( osg::Vec4 boxColor = osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f),float width = 120,float height = 80);
	//����ѡ����Ƶ�λ��
	void ResetSelPos(osg::Vec3 selPointPos);
	/**
		����Box��λ��
	*/
	void UpdateBoxPos();
	/**
	����Text��ǩ
	*/
	osg::ref_ptr<osgText::Text> CreateText(std::string id, QString str, int fontSize = 10);
	//osg::ref_ptr<osg::Node> createHUD(osgViewer::Viewer* viewer);
	/**
	���ñ���
	*/
	void SetTitle(QString str);
	void SetStrX(QString str);
	void SetStrY(QString str);
	void SetStrZ(QString str);
	osg::ref_ptr<osg::Geometry> CreateIcon(std::string id, osg::Vec4 color);
	/**
		�ж��Ƿ񱻵��
	*/
	bool IsCheckClick(osg::Vec3 pos);
	osg::Vec3 GetBoxOrigin() {
		return mBoxPos;
	}
	/**
		����Box���λ��
	*/
	void SetBoxPosition(osg::Vec3 pos) {
		mSelPointPos = pos;
	}
	/**
		��¼�ƶ�ʱ������boxԭ���ƫ��
	*/
	void RecordMoveOffset(osg::Vec3 pos);
	/**
		�ƶ����λ��
	*/
	void MoveBuildBoard(osg::Vec3 pos);
private:
	int _padding = 5;
	
	//x��y��zС�������
	int _cubwidth = 15;
	std::vector<osg::Vec3> _cubrelpos;
	osg::ref_ptr<osgViewer::Viewer> _viewer;
	//����HUD���
	osg::ref_ptr<osg::Camera> _camera;
	osg::ref_ptr<osg::Geode> _geode;
	//����Box
	osg::ref_ptr<osg::Geometry> _boxGm;
	//����������ָʾ���
	osg::ref_ptr<osg::Geometry> _triangleGm;
	//Box�Ŀ�͸�
	int _wbox = 120;
	int _hbox = 80;
	std::vector<osg::Vec3> _boxrelpos;
	//ѡ�е��Ƶ�λ�ã��������꣩
	osg::Vec3 mSelPointPos;
	//Box��ԭ��λ�ã�������ѡ�еĵ������֮���û��϶���������Ļ���꣩
	osg::Vec3 mBoxPos;
	osg::ref_ptr<osgText::Text> _XLabel;
	osg::ref_ptr<osgText::Text> _YLabel;
	osg::ref_ptr<osgText::Text> _ZLabel;
	//�ƶ������ԭ����������λ�õ�ƫ��
	osg::Vec3 mMovePosOffset;
public:
	//���
	std::string mId;
	//���ֱ�ǩ
	osg::ref_ptr<osgText::Text> mTitle;
	osg::ref_ptr<osgText::Text> mTxtX;
	osg::ref_ptr<osgText::Text> mTxtY;
	osg::ref_ptr<osgText::Text> mTxtZ;
	//X��Y��Zͼ��
	osg::ref_ptr<osg::Geometry> mXIcon;
	osg::ref_ptr<osg::Geometry> mYIcon;
	osg::ref_ptr<osg::Geometry> mZIcon;
	
	//�Ƿ������ƶ������
	bool IsAllowMove = false;
};
class OSGPickHandler :
	public osgGA::GUIEventHandler
{
public:
	OSGPickHandler(osgViewer::Viewer* viewer);
	~OSGPickHandler();
	/**����*/
	void Reset();
	/**��һ����*/
	void OnePoint();
	/**��������*/
	void TwoMeause();
	void DrawTips(unsigned int primitiveIndex,osg::Vec3 pos);
	/**
		����PointBuildBoard����
	*/
	void UpdateBoard();
	//osg::ref_ptr<osg::Node> createHUD(osgViewer::Viewer* viewer);
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
	osg::ref_ptr<PointBuildBoard> mOneBoard;
	osg::ref_ptr<PointBuildBoard> mTwoBoard;
	//����HUD���
	osg::ref_ptr<osg::Camera> mHUDCamera;
	/*std::string mOnePointName;
	std::string mTwoPointName;
	osg::Vec3 mOnePoint;
	osg::Vec3 mTwoPoint;*/
};

