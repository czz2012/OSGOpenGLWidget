#pragma once
#include "BuildBoard.h"
class MeasureBuildBoard :
	public BuildBoard
{
public:
	MeasureBuildBoard(QString id,unsigned int pos1Index ,osg::Vec3 pos1, unsigned int pos2Index, osg::Vec3 pos2, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera);
	virtual ~MeasureBuildBoard();

	/**
	����Box���
	*/
	virtual void CreateBox(osg::Vec4 boxColor = osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f), float width = 120, float height = 80);
	/**
	����Box��λ��
	*/
	virtual void UpdateBoxPos();
	/**
	���ñ���
	*/
	void SetTitle(QString str);
	void SetStrX(QString str);
	void SetStrY(QString str);
	void SetStrZ(QString str);
public:
	//���ֱ�ǩ
	osg::ref_ptr<osgText::Text> mTitle;
	osg::ref_ptr<osgText::Text> mTxtX;
	osg::ref_ptr<osgText::Text> mTxtY;
	osg::ref_ptr<osgText::Text> mTxtZ;
	//X��Y��Zͼ��
	osg::ref_ptr<osgText::Text> _XLabel;
	osg::ref_ptr<osgText::Text> _YLabel;
	osg::ref_ptr<osgText::Text> _ZLabel;
	osg::ref_ptr<osg::Geometry> mXIcon;
	osg::ref_ptr<osg::Geometry> mYIcon;
	osg::ref_ptr<osg::Geometry> mZIcon;
private:
	int _padding = 5;
	//x��y��zС�������
	int _cubwidth = 30;
	int _cubHeight = 15;
	//С�������λ��
	std::vector<osg::Vec3> _cubrelpos;
};

