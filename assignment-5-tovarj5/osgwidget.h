//  ***********************************
//  This class is a used to display 
//  Openscenegraph in a Qt window.
//  
//  This is based upon the work of
//  https://github.com/Submanifold/QtOSG.git
//
//  The was created for
//  MEEN / CEEN 570 - Brigham Young University
//  by Prof. Corey McBride
//  ***********************************


#ifndef MEEN_570_OSGWIDGET
#define MEEN_570_OSGWIDGET

#include <QOpenGLWidget>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>



class OSGWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OSGWidget( QWidget* parent = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();

protected:

  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );

  virtual void mouseMoveEvent( QMouseEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );
  virtual void wheelEvent( QWheelEvent* event );

  virtual bool event( QEvent* event );

private:
  void create_box();
  void create_triangle();

  virtual void go_home();
  virtual void on_resize( int width, int height );

  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
  osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
  osg::ref_ptr<osg::Group> mRoot;
  osg::ref_ptr<osgGA::TrackballManipulator> mManipulator;
};

#endif
