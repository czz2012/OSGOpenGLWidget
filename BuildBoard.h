#pragma once
#include <QString>
#include <osgViewer/Viewer>
#include <osg/StateAttribute>
#include <osgText/Text>
#include <osg/ShapeDrawable>
#include <osg/Camera>
#include <osg/Point>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
class BuildBoard :
	public osg::Referenced
{
public:
	//BuildBoard(QString id, osg::Vec3 selPointPos, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera);
	BuildBoard(QString id, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera);
	virtual ~BuildBoard();
	/**
		����Box���
	*/
	virtual void CreateBox( osg::Vec4 boxColor = osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f),float width = 120,float height = 80);
	/**
	����Box��λ��
	*/
	virtual void UpdateBoxPos();	
	/**
	����Text��ǩ
	*/
	osg::ref_ptr<osgText::Text> CreateText(std::string id, QString str, int fontSize = 10, std::string fontfamily = "msyh.ttc");
	osg::ref_ptr<osg::Geometry> CreateIcon(std::string id, osg::Vec4 color);
	osg::ref_ptr<osg::Geode> createSelPoint(QString name, osg::Vec3& pos);
	osg::ref_ptr<osg::Geode> CreateLine(QString name, osg::Vec4 color, std::vector<osg::Vec3> list);
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
protected:	
	//����ѡ����Ƶ�λ��
	virtual void ResetSelPos(osg::Vec3 selPointPos);
protected:
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
	//box���λ��
	std::vector<osg::Vec3> _boxrelpos;
	
	//Box��ԭ��λ�ã�������ѡ�еĵ������֮���û��϶���������Ļ���꣩
	osg::Vec3 mBoxPos;
	//�ƶ������ԭ����������λ�õ�ƫ��
	osg::Vec3 mMovePosOffset;	
public:
	//���
	std::string mId;	
	//�Ƿ������ƶ������
	bool IsAllowMove = false;
	//ѡ�е��Ƶ�λ�ã��������꣩
	osg::Vec3 mSelPointPos;
};

