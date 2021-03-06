#include "./Camera.hpp"

void ofxLoopin::render::Camera::calculate() {

  model.makeIdentityMatrix();
  // std::cerr << "camera::getMeshAspect() " << getMeshAspect() << endl;

  model.scale( getMeshAspect(), 1, 1 );


  float fov = ofxLoopin::render::Camera::fov;
  float dist = 1.0 / tanf(PI * fov / 360.0f);

  float zoomLin = pow( 2, zoom );

  view.makeIdentityMatrix();
  view.rotate( yaw, 0, 1, 0 );
  view.rotate( pitch, 1, 0, 0 );
  view.rotate( roll, 0, 0, 1 );

  view.translate( 0, 0, -dist * (double) ofxLoopin::render::Camera::distance );

  float focus = ofxLoopin::render::Camera::focus;
  float dof = ofxLoopin::render::Camera::dof;

  float bufferAspect = getBufferAspect();
  // float bufferAspect = 1.0;
  // std::cerr << "camera::calculate " << bufferAspect << endl;
  float _near = max( 0.001, dist + focus - dof / 2.0 );
  float _far = max( 0.001, dist + focus + dof / 2.0 );

  projection.makePerspectiveMatrix( fov, fabs( bufferAspect ), _near, _far );
  projection.scale( zoomLin, zoomLin, 1 );

  // float layerAspect = getLayerAspect();
  // if ( fabs(layerAspect) < fabs(bufferAspect) )
  //   projection.scale( fabs( layerAspect ) / fabs( bufferAspect ), fabs( layerAspect ) / fabs( bufferAspect ), 1 );

  // if ( fabs( aspect ) < 1 )
  //   projection.scale( 1/fabs( aspect ), 1/fabs( aspect ), 1 );

  if ( bufferAspect < 0 ) {
    projection.scale( -1, 1, 1 );
  }

  // std::cerr << "ofxLoopin::render::Camera::make\n"
  //      << "near:\n" << near << "\n"
  //      << "far:\n" << far << "\n"
  //      << "focus:\n" << focus << "\n"
  //      << "dist:\n" << dist << "\n"
  //      << "view:\n" << view << "\n"
  //      << "model:\n" << model << "\n"
  //      << "projection:\n" << projection
  //      << endl
  // ;

}

  void ofxLoopin::render::Camera::loadMatrixes() {
    auto renderer = ofGetCurrentRenderer();

    renderer->matrixMode( OF_MATRIX_MODELVIEW );
    renderer->loadMatrix( getModelView() );

    renderer->matrixMode( OF_MATRIX_PROJECTION );
    renderer->loadMatrix( getProjection() );
  }
