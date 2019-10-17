#include "BuildBoard.h"


BuildBoard::BuildBoard(QString _id, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera)
	: osg::Referenced(), _viewer(viewer), _camera(camera) 
{
	QByteArray strArr = _id.toLocal8Bit();
	mId = strArr.data();
	_geode = new osg::Geode;
	_geode->setName(mId);
	//����״̬�رյƹ�
	osg::StateSet* stateset = _geode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	_camera->addChild(_geode);
}
//BuildBoard::BuildBoard(QString _id, osg::Vec3 selPointPos, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera)
//	: osg::Referenced(), mSelPointPos(selPointPos), _viewer(viewer), _camera(camera)
//{
//	QByteArray strArr = _id.toLocal8Bit();
//	mId = strArr.data();
//	_geode = new osg::Geode;
//	_geode->setName(mId);
//	//����״̬�رյƹ�
//	osg::StateSet* stateset = _geode->getOrCreateStateSet();
//	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
//	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
//	_camera->addChild(_geode);
//	ResetSelPos(selPointPos);
//}


BuildBoard::~BuildBoard()
{
	_camera->removeChild(_geode);
}
void BuildBoard::CreateBox(osg::Vec4 boxColor, float width, float height) {
	if (_boxGm.valid()) {
		_geode->removeChild(_boxGm);
		_boxGm.~ref_ptr();
	}
	_wbox = width;
	_hbox = height;
	_boxrelpos.clear();
	//Boxλ��ƫ��
	osg::Vec3 z_boxoffset(0.0f, 0.0f, 0.0f);
	_boxrelpos.push_back(z_boxoffset);
	_boxrelpos.push_back(z_boxoffset + osg::X_AXIS*_wbox);
	_boxrelpos.push_back(z_boxoffset + osg::X_AXIS*_wbox + osg::Y_AXIS*_hbox);
	_boxrelpos.push_back(z_boxoffset + osg::Y_AXIS*_hbox);

	_boxGm = new osg::Geometry;
	_boxGm->setName("BoxPanel");
	_geode->addDrawable(_boxGm);
		
	UpdateBoxPos();

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vboxColor = new osg::Vec4Array();
	vboxColor->push_back(boxColor);
	_boxGm->setColorArray(vboxColor);
	//������ɫ�󶨷�ʽΪ��������
	_boxGm->setColorBinding(osg::Geometry::BIND_OVERALL);

	_boxGm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
}
osg::ref_ptr<osgText::Text> BuildBoard::CreateText(std::string id, QString str, int fontSize,std::string fontfamily) {
	//��������
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	text->setName(id);
	text->setFont(fontfamily);
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	text->setText(bdata);//��̬����ID��
	text->setLineSpacing(0.25f);
	text->setCharacterSize(fontSize);	
	text->setColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));
	_geode->addChild(text);
	return text;
}
osg::ref_ptr<osg::Geometry> BuildBoard::CreateIcon(std::string id, osg::Vec4 color) {
	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
	gm->setName(id);
	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(color);
	//������ɫ����
	gm->setColorArray(vc.get());
	//������ɫ�󶨷�ʽΪ��������
	gm->setColorBinding(osg::Geometry::BIND_OVERALL);
	_geode->addDrawable(gm);
	return gm;
}
osg::ref_ptr<osg::Geode> BuildBoard::createSelPoint(QString name, osg::Vec3& pos) {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	QByteArray barr = name.toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::Point> pointSize = new osg::Point;
	pointSize->setSize(10.0);
	stateSet->setAttribute(pointSize, osg::StateAttribute::ON);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	//traits->samples = 16;
	/*osg::Multisample* pms = new osg::Multisample;
	pms->setSampleCoverage(1, true);*/
	stateSet->setMode(GL_POINT_SMOOTH, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	//osg::PointSprite *sprite = new osg::PointSprite();
	//stateSet->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	//�����������飬ע��˳����ʱ��
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(pos);
	//���ö�������
	geom->setVertexArray(v.get());
	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//������ɫ����
	geom->setColorArray(vc.get());
	//������ɫ�󶨷�ʽΪ��������
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//���ͼԪ��
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));

	//��ͼԪ�����Ҷ�ӽڵ�
	geode->addDrawable(geom.get());

	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	//�Զ����ɶ��㷨��(������addDrawable��)
	osgUtil::SmoothingVisitor::smooth(*(geom.get()));
	return geode;
}
osg::ref_ptr<osg::Geode> BuildBoard::CreateLine(QString name, osg::Vec4 color, std::vector<osg::Vec3> list)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	QByteArray barr = name.toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth;
	lineWidth->setWidth(5.0);
	stateSet->setAttribute(lineWidth, osg::StateAttribute::ON);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	stateSet->setMode(GL_POINT_SMOOTH, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	//�����������飬ע��˳����ʱ��
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	for (auto it = list.begin(); it != list.end(); ++it) {
		v->push_back(*it);
	}	
	//���ö�������
	geom->setVertexArray(v.get());
	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(color);
	//������ɫ����
	geom->setColorArray(vc.get());
	//������ɫ�󶨷�ʽΪ��������
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	//���ͼԪ��
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, v->size()));
	//��ͼԪ�����Ҷ�ӽڵ�
	geode->addDrawable(geom.get());
	//�Զ����ɶ��㷨��(������addDrawable��)
	osgUtil::SmoothingVisitor::smooth(*(geom.get()));
	return geode;

}
void BuildBoard::ResetSelPos(osg::Vec3 selPointPos) {
	mSelPointPos = selPointPos;
	//��������ת��Ļ����(ȷ��Box��λ��)
	osg::Camera* _tCamera = _viewer->getCamera();
	osg::Matrix VPW = _tCamera->getViewMatrix() *
		_tCamera->getProjectionMatrix() *
		_tCamera->getViewport()->computeWindowMatrix();
	//��ǰ��ƫ��

	mBoxPos = mSelPointPos * VPW + osg::X_AXIS * 30;
	osg::Viewport* viewport = _tCamera->getViewport();
	unsigned int width = viewport->width();
	unsigned int height = viewport->height();
	float _x = mBoxPos.x();
	float _y = mBoxPos.y();
	float _z = mBoxPos.z();
	if (mBoxPos.x() + _wbox > width) {
		_x = width - _wbox;
	}
	if (mBoxPos.y() + _hbox > height) {
		_y = height - _hbox;
	}
	mBoxPos = osg::Vec3(_x, _y, _z);
}
void  BuildBoard::UpdateBoxPos() {
	if (!_boxGm.valid()) {
		return;
	}
	//UI�����Σ�����ָʾ
	osg::Camera* _tCamera = _viewer->getCamera();
	osg::Matrix VPW = _tCamera->getViewMatrix() *
		_tCamera->getProjectionMatrix() *
		_tCamera->getViewport()->computeWindowMatrix();
	//ѡ�������Ļ�ϵ�����
	osg::Vec3 selPosScreen = mSelPointPos * VPW;

	std::vector<osg::Vec3> vecBoxPos = { _boxrelpos[0] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0) ,
		_boxrelpos[1] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0),
		_boxrelpos[2] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0),
		_boxrelpos[3] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0)
	};

	if (!_triangleGm.valid()) {
		_triangleGm = new osg::Geometry;
		//������ɫ����
		osg::ref_ptr<osg::Vec4Array> vTriangleColor = new osg::Vec4Array();
		vTriangleColor->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
		_triangleGm->setColorArray(vTriangleColor);
		//������ɫ�󶨷�ʽΪ��������
		_triangleGm->setColorBinding(osg::Geometry::BIND_OVERALL);
		_geode->addDrawable(_triangleGm);
	}
	//����Box��Χ���򲻻�������	
	if (vecBoxPos[0].x() <= selPosScreen.x() && vecBoxPos[0].y() <= selPosScreen.y() &&
		selPosScreen.x() <= vecBoxPos[2].x() && selPosScreen.y() <= vecBoxPos[2].y()) {
		//��box�ڲ�
		_triangleGm->setNodeMask(0);
	}
	else {
		_triangleGm->setNodeMask(1);
		osg::ref_ptr<osg::Vec3Array> vertexTrangle = new osg::Vec3Array;
		std::vector<float> vecLen = { (vecBoxPos[0] - selPosScreen).length(),
			(vecBoxPos[1] - selPosScreen).length() ,
			(vecBoxPos[2] - selPosScreen).length(),
			(vecBoxPos[3] - selPosScreen).length()
		};
		//ȡ������Сֵ����
		int minindex = 0;
		for (int i = 1; i < vecLen.size(); ++i) {
			if (vecLen[i] < vecLen[minindex]) {
				minindex = i;
			}
		}
		float factor = 20.0f;
		switch (minindex)
		{
		case 0:
			//���������
			if (vecBoxPos[0].x() > selPosScreen.x()) {
				//���
				vertexTrangle->push_back(vecBoxPos[0]);
				vertexTrangle->push_back(vecBoxPos[0] + osg::Y_AXIS*factor);
			}
			else {
				//�±�
				vertexTrangle->push_back(vecBoxPos[0] + osg::X_AXIS * factor);
				vertexTrangle->push_back(vecBoxPos[0]);
			}
			break;
		case 1:
			if (vecBoxPos[1].x() < selPosScreen.x()) {
				//�ұ�
				vertexTrangle->push_back(vecBoxPos[1] + osg::Y_AXIS * factor);
				vertexTrangle->push_back(vecBoxPos[1]);
			}
			else {
				//�±�
				vertexTrangle->push_back(vecBoxPos[1]);
				vertexTrangle->push_back(vecBoxPos[1] - osg::X_AXIS * factor);
			}
			break;
		case 2:
			if (vecBoxPos[2].x() < selPosScreen.x()) {
				//�ұ�
				vertexTrangle->push_back(vecBoxPos[2]);
				vertexTrangle->push_back(vecBoxPos[2] - osg::Y_AXIS * factor);
			}
			else {
				//�ϱ�				
				vertexTrangle->push_back(vecBoxPos[2] - osg::X_AXIS * factor);
				vertexTrangle->push_back(vecBoxPos[2]);
			}
			break;
		case 3:
			if (vecBoxPos[3].x() > selPosScreen.x()) {
				//���
				vertexTrangle->push_back(vecBoxPos[3] - osg::Y_AXIS * factor);
				vertexTrangle->push_back(vecBoxPos[3]);
			}
			else {
				//�ϱ�	
				vertexTrangle->push_back(vecBoxPos[3]);
				vertexTrangle->push_back(vecBoxPos[3] + osg::X_AXIS * factor);
			}
			break;
		}
		vertexTrangle->push_back(selPosScreen);
		_triangleGm->setVertexArray(vertexTrangle);
	}	
	_triangleGm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
	//////////////////////////////////////
	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
	for (int i = 0; i < vecBoxPos.size(); ++i) {
		vertex->push_back(vecBoxPos[i]);
	}
	_boxGm->setVertexArray(vertex);
}
/**
�ж��Ƿ񱻵��
*/
bool BuildBoard::IsCheckClick(osg::Vec3 pos) {
	/*std::cout << "mBoxPos = (" << mBoxPos.x() << "," << mBoxPos.y() << "),pos = (" << pos.x() << "," << pos.y() << ")" << std::endl;
	std::cout << "mBoxPos.x() < pos.x() " << (mBoxPos.x() < pos.x()) << "\n mBoxPos.x() + _wbox > pos.x() "<< (mBoxPos.x() + _wbox > pos.x())
		<< "\nmBoxPos.y() < pos.y() " << (mBoxPos.y() < pos.y()) << "\nmBoxPos.y() + _hbox > pos.y()" << (mBoxPos.y() + _hbox > pos.y()) << std::endl;*/
	if (mBoxPos.x() < pos.x() && mBoxPos.x() + _wbox > pos.x() && mBoxPos.y() < pos.y() && mBoxPos.y() + _hbox > pos.y()) {
		return true;
	}
	return false;
}
/**
��¼�ƶ�ʱ������boxԭ���ƫ��
*/
void BuildBoard::RecordMoveOffset(osg::Vec3 pos) {
	mMovePosOffset = pos - mBoxPos;
	IsAllowMove = true;
}
/**
�ƶ����λ��
*/
void BuildBoard::MoveBuildBoard(osg::Vec3 pos) {
	if (!IsAllowMove) {
		return;
	}
	mBoxPos = pos - mMovePosOffset;
}