#include "OSGWidget.h"

#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/WriteFile>
#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>

#include <cassert>
#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

OSGWidget::OSGWidget( QWidget* parent, Qt::WindowFlags f ):
    QOpenGLWidget( parent,f ),
    mGraphicsWindow{ new osgViewer::GraphicsWindowEmbedded( this->x(),
                                                            this->y(),
                                                            this->width(),
                                                            this->height() ) }
  , mViewer{ new osgViewer::CompositeViewer }
{

    mRoot = new osg::Group;

    create_box();
    create_triangle();

    float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() );
    auto pixelRatio   = this->devicePixelRatio();

    //Set up the camera
    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width() * pixelRatio, this->height() * pixelRatio );

    camera->setClearColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
    camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( mGraphicsWindow );

    //Set up the view
    osgViewer::View* view = new osgViewer::View;
    view->setCamera( camera );
    view->setSceneData( mRoot.get() );
    view->addEventHandler( new osgViewer::StatsHandler );

    //Set up the mouse control
    mManipulator = new osgGA::TrackballManipulator;
    mManipulator->setAllowThrow( false );

    view->setCameraManipulator( mManipulator );
    mManipulator->setTransformation(osg::Vec3d(2,0,0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));

    mViewer->addView( view );
    mViewer->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    mViewer->realize();

    // Set the focus policy so that this widget will recieve keyboard events.
    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );

    // This allows this widget to get mouse move events.
    // This is needed with multiple view ports.
    this->setMouseTracking( true );

    //Reset the camera
    go_home();
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::paintEvent( QPaintEvent* /* paintEvent */ )
{
    this->makeCurrent();

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

    this->paintGL();

    painter.end();

    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
    this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
    mGraphicsWindow->resized( this->x(), this->y(), width, height );

    this->on_resize( width, height );
}

void OSGWidget::keyPressEvent( QKeyEvent* event )
{
    QString keyString   = event->text();
    const char* keyData = keyString.toLocal8Bit().data();

    if( event->key() == Qt::Key_H )
    {
        this->go_home();
        return;
    }

    this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::keyReleaseEvent( QKeyEvent* event )
{
    QString keyString   = event->text();
    const char* keyData = keyString.toLocal8Bit().data();

    this->getEventQueue()->keyRelease( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::mouseMoveEvent( QMouseEvent* event )
{
    auto pixelRatio = this->devicePixelRatio();

    this->getEventQueue()->mouseMotion( static_cast<float>( event->x() * pixelRatio ),
                                        static_cast<float>( event->y() * pixelRatio ) );
}

void OSGWidget::mousePressEvent( QMouseEvent* event )
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch( event->button() )
    {
    case Qt::LeftButton:
        button = 1;
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    auto pixelRatio = this->devicePixelRatio();

    this->getEventQueue()->mouseButtonPress( static_cast<float>( event->x() * pixelRatio ),
                                             static_cast<float>( event->y() * pixelRatio ),
                                             button );

}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch( event->button() )
    {
    case Qt::LeftButton:
        button = 1;
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    auto pixelRatio = this->devicePixelRatio();

    this->getEventQueue()->mouseButtonRelease( static_cast<float>( pixelRatio * event->x() ),
                                               static_cast<float>( pixelRatio * event->y() ),
                                               button );
}

void OSGWidget::wheelEvent( QWheelEvent* event )
{
    event->accept();
    int delta = event->delta();

    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                                 : osgGA::GUIEventAdapter::SCROLL_DOWN;

    this->getEventQueue()->mouseScroll( motion );
}

bool OSGWidget::event( QEvent* event )
{
    bool handled = QOpenGLWidget::event( event );

    // This ensures that the OSG widget is always going to be
    // repainted after the user performed some interaction. 
    // Doing this in the event handler ensures
    // that we don't forget about some event and prevents duplicate code.
    switch( event->type() )
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::Wheel:
        this->update();
        break;

    default:
        break;
    }

    return handled;
}

void OSGWidget::create_triangle()
{
    //Define the geometry of the triangle
   osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
   vertices->push_back(osg::Vec3(0,0,0));
   vertices->push_back(osg::Vec3(1,0,0));
   vertices->push_back(osg::Vec3(.5,1,0));

   osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
   normals->push_back(osg::Vec3(0,0,1));
   normals->push_back(osg::Vec3(0,0,1));
   normals->push_back(osg::Vec3(0,0,1));

   osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt( GL_TRIANGLES );
   indices->push_back(0);
   indices->push_back(1);
   indices->push_back(2);


   //Define the triangle color
   osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
   colors->push_back( osg::Vec4(1, 0, 1, 1) );


   //Create the osg geometry for the triangle
   osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
   geom->setVertexArray( vertices.get() );
   geom->setNormalArray( normals.get() );
   geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
   geom->setColorArray( colors.get() );
   geom->setColorBinding( osg::Geometry::BIND_OVERALL );
   geom->addPrimitiveSet( new osg::DrawArrays(GL_TRIANGLES, 0, 3) );
   geom->addPrimitiveSet( indices.get() );


   //Set material for basic lighting and enable depth tests.
   osg::StateSet* stateSet = geom->getOrCreateStateSet();
   osg::Material* material = new osg::Material;

   material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
   stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
   stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );


   //Create the node to hold the triangle
   osg::ref_ptr<osg::Geode> geode = new osg::Geode;
   geode->addDrawable( geom.get() );

   //Create the parent transform node
   osg::MatrixTransform* transform = new osg::MatrixTransform;
   osg::Matrix matrix = osg::Matrix::rotate(osg::DegreesToRadians((float)90),1,0,0);
   transform->setMatrix(matrix);

   //Add the triangle node to the parent
   transform->addChild(geode);

   //Add the transform to the root
   mRoot->addChild(transform);
}


void OSGWidget::create_box()
{
    //Create the box
    osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, 0.f ), 0.25f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
    sd->setColor( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
    sd->setName( "Box" );

    //Create the node to hold the box
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    // Set material for basic lighting and enable depth tests. Else, the box
    // will suffer from rendering errors.
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );


    //Set up transform parent node.
    osg::MatrixTransform* transform= new osg::MatrixTransform;
    transform->setMatrix(osg::Matrix::translate(10,1,1));

    //Add shape to parent
    transform->addChild(geode);

    //Add transform to root
    mRoot->addChild(transform);

}



void OSGWidget::go_home()
{
    osgViewer::ViewerBase::Views views;
    mViewer->getViews( views );

    for(osgViewer::View* view:views)
    {
        view->home();
    }
}

void OSGWidget::on_resize( int width, int height )
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras( cameras );

    auto pixelRatio = this->devicePixelRatio();

    cameras[0]->setViewport( 0, 0, width * pixelRatio, height * pixelRatio );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if( eventQueue )
        return eventQueue;
    else
        throw std::runtime_error( "Unable to obtain valid event queue");
}

