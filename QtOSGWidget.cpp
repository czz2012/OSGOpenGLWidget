#pragma execution_character_set("utf-8")
#ifdef _DEBUG
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgUtild.lib")
#else
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgUtil.lib")
#endif

#include "QtOSGWidget.h"
/**
1������ͼ�������ĺ�ͼ�δ���
2����ͼ�������ĸ��ӵ����
3�����������Ϊ����ͼ
*/
QtOSGWidget::QtOSGWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	_mViewer(new osgViewer::Viewer),
	_mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(this->x(),this->y(),this->width(),this->height()))
{
	//setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
	this->setMinimumSize(100, 100);
}

QtOSGWidget::~QtOSGWidget()
{
}
/**
����OpenGL��Դ��״̬
*/
void QtOSGWidget::initializeGL() {
	//����һ��������ͷ������ͼ��������
	//osg::ref_ptr<osg::Camera> camera = new osg::Camera();
	//camera->setViewport(0, 0, this->width(), this->height());
	//camera->setClearColor(osg::Vec4(0.9f, 0.8f, 0.0f, 1.0f));
	///*float aspectRatio = static_cast<float>(this->width()) / static_cast<float>(this->height());
	//camera->setProjectionMatrixAsPerspective(30.f, aspectRatio, 0.1f, 1000.f);*/
	//camera->setProjectionMatrixAsPerspective(30, (double)this->width() / this->height(), 1, 1000);
	//camera->setGraphicsContext(_mGraphicsWindow.get());
	////��������������۲���
	//_mViewer->setCamera(camera.get());

	osg::Camera* camera = _mViewer->getCamera();
	camera->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	camera->setProjectionMatrixAsPerspective(30, (double)this->width() / this->height(), 1, 1000);
	camera->setViewport(0, 0, this->width(), this->height());
	camera->setGraphicsContext(_mGraphicsWindow.get());

	/*osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator();
	osg::ref_ptr<osgGA::FlightManipulator> manipulator2 = new osgGA::FlightManipulator;*/
	osg::ref_ptr<QtCameraManipulator> manipulator = new QtCameraManipulator;
	manipulator->setAllowThrow(false);
	_mViewer->setCameraManipulator(manipulator.get());
	//_mViewer->addEventHandler(new osgViewer::StatsHandler);
	//_mViewer->addEventHandler(new osgViewer::ThreadingHandler());
	//_mViewer->addEventHandler(new osgViewer::HelpHandler);
	//_mViewer->addEventHandler(new osgGA::StateSetManipulator(_mViewer->getCamera()->getOrCreateStateSet()));
	//_mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
	_mViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
	_mViewer->realize();

	
	//osg::ref_ptr<osg::Group> pGroup = _mViewer->getSceneData()->asGroup();
	osg::ref_ptr<osg::Group> root =  new osg::Group();
	
	QByteArray barr = QString("root").toLocal8Bit();
	char* bdata = barr.data();
	root->setName(bdata);
	//std::cout << root->getName() << std::endl;
	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(root.get());
	//_mViewer->setSceneData(root);
	//_mViewer->realize();
	root->addChild(createQuad().get());
	//root->addChild(createCloud().get());
	//root->addChild(createCoordinate().get());
	//root->addChild(createShape().get());

	//�ӹ۲��߻�ȡ�ڵ�ķ�ʽ
	//geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
	//����OpenGL��Ȳ���
	//stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

	//�Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	_mViewer->setSceneData(root);
	_mViewer->realize();
	//glEnable(GL_DEPTH_TEST);


	
}
/**
�ڳ�������ʱ��ȾOpenGL
*/
void QtOSGWidget::paintGL() {
	_mViewer->frame();
}
/**
����OpenGL�ӿڣ�ͶӰ��
*/
void QtOSGWidget::resizeGL(int w, int h) {
	this->getEventQueue()->windowResize(this->x(), this->y(), w, h);
	_mGraphicsWindow->resized(this->x(), this->y(), w, h);
	osg::Camera* camera = _mViewer->getCamera();
	//camera->setViewport(this->x(), this->y(), w, h);
	//������������˳��
	camera->setProjectionMatrixAsPerspective(30, (double)w / h, 1, 1000);
	camera->setViewport(0, 0, w, h);
}
/**
��ȡOSG�¼�����
*/
osgGA::EventQueue* QtOSGWidget::getEventQueue()const {
	return _mGraphicsWindow->getEventQueue();
};
void QtOSGWidget::mouseDoubleClickEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton:
		button = 1;
		break;
	case Qt::MidButton:
		button = 2;
		break;
	case Qt::RightButton:
		button = 3;
		break;
	}
	getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);
	QOpenGLWidget::mouseDoubleClickEvent(event);
}
void QtOSGWidget::mouseMoveEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	getEventQueue()->mouseMotion(event->x(), event->y());
	QOpenGLWidget::mouseMoveEvent(event);
}
void QtOSGWidget::mousePressEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton:
		button = 1;
		break;
	case Qt::MidButton:
		button = 2;
		break;
	case Qt::RightButton:
		button = 3;
		break;
	}
	getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
	QOpenGLWidget::mousePressEvent(event);
}
void QtOSGWidget::mouseReleaseEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton:
		button = 1;
		break;
	case Qt::MidButton:
		button = 2;
		break;
	case Qt::RightButton:
		button = 3;
		break;
	}
	getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
	QOpenGLWidget::mouseReleaseEvent(event);
}
void QtOSGWidget::wheelEvent(QWheelEvent *event) {
	setKeyboardModifiers(event);
	getEventQueue()->mouseScroll(event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
	QOpenGLWidget::wheelEvent(event);
}
bool QtOSGWidget::event(QEvent *event) {
	bool handled = QOpenGLWidget::event(event);
	switch (event->type())
	{
	case QEvent::MouseButtonPress:
	case QEvent::MouseButtonRelease:
	case QEvent::MouseMove:
	case QEvent::Wheel:
	case QEvent::MouseButtonDblClick:
	case QEvent::KeyPress:
	case QEvent::KeyRelease:
		this->update();
		break;
	default:
		break;
	}
	return handled;
}
void QtOSGWidget::setKeyboardModifiers(QInputEvent* event) {
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier);
	unsigned mask = 0;
	if (modkey & Qt::ShiftModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
	}
	if (modkey & Qt::AltModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
	}
	if (modkey & Qt::ControlModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
	}
	getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
}
void QtOSGWidget::keyPressEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);
	//QByteArray KeyData = event->text().toLocal8Bit();
	/*const char* cKey = KeyData.data();
	osgGA::GUIEventAdapter::KeySymbol symbol = osgGA::GUIEventAdapter::KeySymbol(event->key());*/
	//getEventQueue()->keyPress();
	switch (event->key())
	{
	case Qt::Key_F:
	{
		//�ӹ۲��߻�ȡ�ڵ�ķ�ʽ
		osg::Geode* geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
		int count = geode->getNumDrawables();
		for (int i = 0; i < count; ++i) {
			osg::ShapeDrawable* draw = dynamic_cast<osg::ShapeDrawable*> (geode->getDrawable(i));
			std::string name = draw->getName();
			if (name == "zidingyi1") {
				draw->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
			}
		}
	}
		break;
	case Qt::Key_D:
	{
		//�ӹ۲��߻�ȡ�ڵ�ķ�ʽ
		osg::Geode* geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
		int count = geode->getNumDrawables();
		for (int i = 0; i < count; ++i) {
			osg::Drawable* draw = geode->getDrawable(i);
			std::string name = draw->getName();
			if (name == "zidingyi1") {
				geode->removeDrawable(draw);
			}
		}
	}
		break;
	default:
		break;
	}
	QOpenGLWidget::keyPressEvent(event);
}
void QtOSGWidget::keyReleaseEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);

	QOpenGLWidget::keyReleaseEvent(event);
}

void QtOSGWidget::onCylinder() {
	osg::ref_ptr<osg::Group> pGroup = _mViewer->getSceneData()->asGroup();
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createCylinder();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//�Ż���������
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
void QtOSGWidget::onQuad() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createQuad();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//�Ż���������
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
void QtOSGWidget::onCloud() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createCloud();
	root->addChild(node.get());
	//_mViewer->setSceneData(NULL);
	_mViewer->setCameraManipulator(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	osg::ref_ptr<QtCameraManipulator> manipulator = new QtCameraManipulator;
	manipulator->setAllowThrow(false);
	_mViewer->setCameraManipulator(manipulator.get());
	//if (isEmpty) {
		//�Ż���������
		/*osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();*/
	//}
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	/*_mViewer->getCamera()->setViewMatrixAsLookAt(osg::Vec3(1000,1000,2000),
		osg::Vec3(1000, 1000, 1000),
		osg::Vec3d(0.0f, 0.0f, 1.0f)
		);*/
	this->update();
}
void QtOSGWidget::onShape() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createShape();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//�Ż���������
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
void QtOSGWidget::onGlider() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createOSGGlider();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//�Ż���������
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
//class DelAllNodeVistor :public osg::NodeVisitor {
//public:
//	DelAllNodeVistor(osg::Group* node) :osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
//		root = node;
//	}
//	/*virtual void apply(osg::Group& node) {
//		std::string name = node.getName();
//		std::cout <<"Group : " <<name << std::endl;
//	}*/
//	virtual void apply(osg::Node& node) {
//		if (node.getName() == "root") {
//			traverse(node);
//		}
//		else {
//			std::string name = node.getName();
//			std::cout << "Node : " << name << std::endl;
//			root->removeChild(&node);
//		}
//	}
//	/*virtual void apply(osg::Geode& node) {
//		std::string name = node.getName();
//		std::cout << "Geode : " << name << std::endl;
//		traverse(node);
//	}
//	virtual void apply(osg::Geometry& geometry) {
//		std::string name = geometry.getName();
//		std::cout << "Geometry : " << name << std::endl;
//		traverse(geometry);
//	}*/
//private:
//	osg::ref_ptr<osg::Group> root;
//};
void QtOSGWidget::onClear() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	if (root.valid()) {
		/*DelAllNodeVistor vistor(root.get());
		root->accept(vistor);*/
		int childCount = root->getNumChildren();
		for (int i = childCount - 1; i >= 0; --i) {
			root->removeChild(i);
		}
	}
	//_mViewer->realize();
	//root->accept(DelAllNodeVistor());
	this->update();
}
void QtOSGWidget::onRecHeightRamp(int axis, QColor beginColor, QColor endColor) {
	osg::Geode* cloudGeode = dynamic_cast<osg::Geode*>(getChildNode("CloudPoints"));
	if (cloudGeode == nullptr) {
		return;
	}
	osg::Vec3 direct;
	switch (axis)
	{
	case 1:
		direct = osg::X_AXIS;
		break;
	case 2:
		direct = osg::Y_AXIS;
		break;
	case 3:
		direct = osg::Z_AXIS;
		break;
	}
	qreal r, g, b;
	beginColor.getRgbF(&r, &g, &b);
	//��ʼ��ɫ
	osg::Vec4 bcolor(r, g, b, 1.0f);
	endColor.getRgbF(&r, &g, &b);
	//������ɫ
	osg::Vec4 ecolor(r, g, b, 1.0f);
	ChangedCloudColor(cloudGeode, direct, bcolor, ecolor);
}
void QtOSGWidget::computeNodePosition(osg::Node* node, const osg::Camera *camera, bool useBoundingBox) {
	/*_mViewer->getCameraManipulator()->computeHomePosition(camera);
	return;*/
		osg::BoundingSphere boundingSphere;

		//OSG_INFO << " CameraManipulator::computeHomePosition(" << camera << ", " << useBoundingBox << ")" << std::endl;

		if (useBoundingBox)
		{
			// compute bounding box
			// (bounding box computes model center more precisely than bounding sphere)
			osg::ComputeBoundsVisitor cbVisitor;
			node->accept(cbVisitor);
			osg::BoundingBox &bb = cbVisitor.getBoundingBox();

			if (bb.valid()) boundingSphere.expandBy(bb);
			else boundingSphere = node->getBound();
		}
		else
		{
			// compute bounding sphere
			boundingSphere = node->getBound();
		}

		/*OSG_INFO << "    boundingSphere.center() = (" << boundingSphere.center() << ")" << std::endl;
		OSG_INFO << "    boundingSphere.radius() = " << boundingSphere.radius() << std::endl;*/

		double radius = osg::maximum(double(boundingSphere.radius()), 1e-6);

		// set dist to default
		double dist = 3.5f * radius;

		if (camera)
		{

			// try to compute dist from frustum
			double left, right, bottom, top, zNear, zFar;
			if (camera->getProjectionMatrixAsFrustum(left, right, bottom, top, zNear, zFar))
			{
				double vertical2 = fabs(right - left) / zNear / 2.;
				double horizontal2 = fabs(top - bottom) / zNear / 2.;
				double dim = horizontal2 < vertical2 ? horizontal2 : vertical2;
				double viewAngle = atan2(dim, 1.);
				dist = radius / sin(viewAngle);
			}
			else
			{
				// try to compute dist from ortho
				if (camera->getProjectionMatrixAsOrtho(left, right, bottom, top, zNear, zFar))
				{
					dist = fabs(zFar - zNear) / 2.;
				}
			}
		}
		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		osg::ComputeBoundsVisitor boundVisitor;
		node->accept(boundVisitor);
		osg::BoundingBox boundingBox = boundVisitor.getBoundingBox();
		float length = boundingBox.xMax() - boundingBox.xMin();
		float width = boundingBox.yMax() - boundingBox.yMin();
		float height = boundingBox.zMax() - boundingBox.zMin();
		osg::Vec3 direct;
		if (length <= width && length <= height) {
			direct = osg::X_AXIS;
		}
		else if (width <= length && width <= height) {
			direct = osg::Y_AXIS;
		}
		else {
			direct = osg::Z_AXIS;
		}
		osg::Vec3f cesh = boundingSphere.center();
		_mViewer->getCamera()->setViewMatrixAsLookAt(boundingSphere.center() + direct* dist,
			boundingSphere.center(),
			osg::Vec3d(0.0f, 0.0f, 1.0f)
			);
		/*_mViewer->getCameraManipulator()->setHomePosition(boundingSphere.center() + direct* dist,
			boundingSphere.center(),
			osg::Vec3d(0.0f, 0.0f, 1.0f),
			true);*/
}
/**
�ȵ����ļ�
*/
float minX, maxX, minY, maxY, minZ, maxZ;
osg::ref_ptr<osg::Vec3Array> QtOSGWidget::ReadModelFile(std::string filePath) {
	osg::ref_ptr<osg::Vec3Array> list = new osg::Vec3Array;
	FILE* pfData = fopen(filePath.c_str(), "r");
	if (pfData == NULL) {
		return list;
	}
	bool first = true;
	while (!feof(pfData)) {
		float fx, fy, fz;
		std::fscanf(pfData, "%f", &fx);
		std::fscanf(pfData, "%f", &fy);
		std::fscanf(pfData, "%f", &fz);
		if (first) {
			minX = maxX = fx;
			minY = maxY = fy;
			minZ = maxZ = fz;
			first = false;
		}
		else {
			minX = std::min(minX, fx);
			maxX = std::max(maxX, fx);
			minY = std::min(minY, fy);
			maxY = std::max(maxY, fy);
			minZ = std::min(minZ, fz);
			maxZ = std::max(maxZ, fz);
		}
		list->push_back(osg::Vec3f(fx, fy, fz));
	}
	fclose(pfData);
	//std::ifstream fileIn(filePath, std::ios::in);//��ȡ�ļ�
	//std::string line;//��ȡ��ÿһ�е��ַ�

	//std::getline(fileIn, line);//��ȡ��һ��
	//std::stringstream sstr(line);//����תһ��
	//std::string token;
	/*bool rgbIsInt;
	int lineInNum = 0;
	while (getline(sstr, token, ' '))
	{
	lineInNum++;
	if (lineInNum >= 3)
	{
	if (stof(token) > 1)
	{
	rgbIsInt = true;
	}

	}

	}*/
	return list;
}
//�����ı���
osg::ref_ptr<osg::Node> QtOSGWidget::createQuad() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	QByteArray barr = QString("�ı���").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	//�����������飬ע��˳����ʱ��
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	//���ö�������
	geom->setVertexArray(v.get());
	int test = v->size();

	//������������
	//osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	//vt->push_back(osg::Vec2(0.0f, 0.0f));
	//vt->push_back(osg::Vec2(1.0f, 0.0f));
	//vt->push_back(osg::Vec2(1.0f, 1.0f));
	//vt->push_back(osg::Vec2(0.0f, 1.0f));
	////������������
	//geom->setTexCoordArray(0, vt.get());

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	//������ɫ����
	geom->setColorArray(vc.get());
	//������ɫ�󶨷�ʽΪ��������
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//������������
	//osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	////���÷�������
	//geom->setNormalArray(nc.get());
	////���÷��߰󶨷�ʽΪȫ������
	//geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//���ͼԪ����ͼ��ԪΪ�ı���
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));

	//��ͼԪ�����Ҷ�ӽڵ�
	geode->addDrawable(geom.get());

	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	//�Զ����ɶ��㷨��(������addDrawable��)
	osgUtil::SmoothingVisitor::smooth(*(geom.get()));

	return geode.get();
}
osg::ref_ptr<osg::Node> QtOSGWidget::createCylinder() {
	//�������Բ��
	osg::ref_ptr<osg::Cylinder> cylinder = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), 0.25f, 0.5f);
	osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(cylinder);
	QByteArray barr = QString("zidingyi1").toLocal8Bit();
	char* bdata = barr.data();
	sd->setName(barr);
	sd->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	//Ҷ�ӽڵ�
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(sd);
	barr = QString("Բ��").toLocal8Bit();
	bdata = barr.data();
	geode->setName(bdata);
	//osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();
	//osg::ref_ptr<osg::Material> material = new osg::Material;
	//material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
	//stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);
	return geode;
}
osg::ref_ptr<osg::Node> QtOSGWidget::createOSGGlider() {
	osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFile("glider.osg");
	QByteArray barr = QString("�ɻ�").toLocal8Bit();
	char* bdata = barr.data();
	node->setName(bdata);
	return node.get();
}
osg::ref_ptr<osg::Node> QtOSGWidget::createCloud() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//std::string name = geode->getName();
	QByteArray barr = QString("CloudPoints").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(barr);
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	//�����������飬ע��˳����ʱ��
	osg::ref_ptr<osg::Vec3Array> v = ReadModelFile("model.txt");
	//���ö�������
	geom->setVertexArray(v.get());
	int test = v->size();

	//������ɫ����
	//osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	////��ʼ��ɫ
	//osg::Vec4 bcolor(1.0f, 0.0f, 0.0f, 1.0f);
	////������ɫ
	//osg::Vec4 ecolor(0.0f, 1.0f, 0.0f, 1.0f);
	//osg::Vec4 diffcolor = (ecolor - bcolor)*((double)1 / (maxY - minY));

	//for (auto p = v->begin(); p != v->end(); ++p) {
	//	float x = p->x();
	//	float y = p->y();
	//	float z = p->z();
	//	osg::Vec4 c = bcolor + diffcolor * y;
	//	vc->push_back(c);
	//}
	////������ɫ����
	//geom->setColorArray(vc.get());
	////������ɫ�󶨷�ʽΪ��������
	//geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//������������
	//osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	////���÷�������
	//geom->setNormalArray(nc.get());
	////���÷��߰󶨷�ʽΪȫ������
	//geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));

	//��ͼԪ�����Ҷ�ӽڵ�
	geode->addDrawable(geom.get());

	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	//�Զ����ɶ��㷨��(������addDrawable��)
	osgUtil::SmoothingVisitor::smooth(*(geom.get()));

	return geode.get();
}
//osg::ref_ptr<osg::Node>  QtOSGWidget::createCloud() {
//	//������
//	osg::ref_ptr<osg::Vec3Array> coords = ReadModelFile("model.txt");
//	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
//
//	geometry->setVertexArray(coords);
//	int size1 = coords->size();
//	int size2 = coords->referenceCount();
//
//	//��ɫ
//	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
//
//	//��ʼ��ɫ
//	osg::Vec4 bcolor(1.0f, 0.0f, 0.0f, 1.0f);
//	//������ɫ
//	osg::Vec4 ecolor(0.0f, 1.0f, 0.0f, 1.0f);
//	osg::Vec4 diffcolor = (ecolor - bcolor)*((double)1 / (maxY - minY));
//
//	for (auto p = coords->begin(); p != coords->end(); ++p) {
//		float x = p->x();
//		float y = p->y();
//		float z = p->z();
//		osg::Vec4 c = bcolor + diffcolor * ((y - minY) / (maxY - minY));
//		vc->push_back(c);
//	}
//	/*vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
//	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));*/
//	//������ɫ����
//	geometry->setColorArray(vc.get());
//	//������ɫ�󶨷�ʽΪ��������
//	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//
//	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
//	normals->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
//	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, coords->size()));
//
//	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//	geode->addDrawable(geometry);
//	//root->addChild(geode.get());
//	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
//	return geode.get();
//}
osg::ref_ptr<osg::Node> QtOSGWidget::createShape() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	QByteArray barr = QString("Ԥ���弸����").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);
	float radius = 0.8f;
	float height = 1.0f;
	//��ϸ�̶�
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);
	//����
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 0, 0), radius), hints));
	//������
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0, 0.0), 2 * radius), hints));
	//Բ׶
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0), radius, height), hints));
	//Բ��
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), radius, height), hints));
	//̫�ղ�
	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height), hints));
	return geode.get();
}
osg::Node* QtOSGWidget::getChildNode(std::string name) {
	osg::ref_ptr<osg::Node> rNode = _mViewer->getSceneData();
	if (rNode == nullptr) {
		return nullptr;
	}
	if (rNode->getName() == name) {
		return rNode;
	}
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(rNode.get());
	if (!root.valid()) {
		return nullptr;
	}
	int childcount = root->getNumChildren();
	for (int i = 0; i < childcount; ++i) {
		osg::ref_ptr<osg::Node> node = root->getChild(i);
		if (node->getName() == name) {
			return node;
		}
	}
	return nullptr;
}
void QtOSGWidget::ChangedCloudColor(osg::Geode* geode, osg::Vec3 axis, osg::Vec4 begColor, osg::Vec4 endColor) {
	//double diffFactor = 0.0;
	/*if (axis == osg::X_AXIS) {
	diffFactor = ;
	}
	else if (axis == osg::Y_AXIS) {
	diffFactor = ;
	}
	else if (axis == osg::Z_AXIS) {
	diffFactor = ;
	}*/
	axis.normalize();
	osg::Vec3 diffFactor = osg::componentMultiply(osg::Vec3(1 / (maxX - minX), 1 / (maxY - minY), 1 / (maxZ - minZ)), axis);

	////int geomNum = cloudGeode->getNumDrawables();
	osg::ref_ptr<osg::Geometry> cloudGeom = dynamic_cast<osg::Geometry*>(geode->getDrawable(0));
	osg::ref_ptr<osg::Vec3Array> v = dynamic_cast<osg::Vec3Array*>(cloudGeom->getVertexArray());
	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	////��ʼ��ɫ
	//osg::Vec4 bcolor(1.0f, 0.0f, 0.0f, 1.0f);
	////������ɫ
	//osg::Vec4 ecolor(0.0f, 1.0f, 0.0f, 1.0f);
	osg::Vec4 diffcolor = (endColor - begColor);
	for (auto p = v->begin(); p != v->end(); ++p) {
		/*float x = p->x();
		float y = p->y();
		float z = p->z();*/
		osg::Vec4 c = begColor + diffcolor * (((*p) - osg::Vec3(minX, minY, minZ)) * diffFactor);
		float cx, cy, cz;
		if (c.x() < 0) {
			cx = 0.0;
		}
		else if (c.x() > 1) {
			cx = 1.0;
		}
		else {
			cx = c.x();
		}
		if (c.y() < 0) {
			cy = 0.0;
		}
		else if (c.y() > 1) {
			cy = 1.0;
		}
		else {
			cy = c.y();
		}
		if (c.z() < 0) {
			cz = 0.0;
		}
		else if (c.z() > 1) {
			cz = 1.0;
		}
		else {
			cz = c.z();
		}
		vc->push_back(osg::Vec4(cx, cy, cz, 1.0f));
	}
	//������ɫ����
	cloudGeom->setColorArray(vc.get());
	//������ɫ�󶨷�ʽΪ��������
	cloudGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	this->update();
}
//����������
osg::ref_ptr<osg::Node> QtOSGWidget::createCoordinate() {
	//�������漸����Ϣ�Ķ���
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();	
	//�����ĸ�����
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1000.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 1000.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1000.0f));
	geom->setVertexArray(v.get());

	//Ϊÿ������ָ��һ����ɫ
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //����ԭ��Ϊ��ɫ
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); //x red
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //����ԭ��Ϊ��ɫ
	c->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)); //y green
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //����ԭ��Ϊ��ɫ
	c->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)); //z blue
													 //���ûָ����ɫ����Ϊ��ɫ
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//������
	//geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4)); //XZ
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2)); //X
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 2, 2)); //Y
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 4, 2)); //Z

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::OFF);
	geode->addDrawable(geom.get());
	QByteArray barr = QString("CustomCoordinate").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);

	/*osg::ref_ptr<osg::Group> newroot = new osg::Group();
	newroot->addChild(geode.get());*/

	return geode;
}