#include "./Blobs.hpp"

void ofxLoopin::blobs::Blobs::renderBuffer( ofxLoopin::base::Buffer * buffer  ) {
  if ( !enable.isEnabledOnce() ) {
    return;
  }

  if ( !buffer || !buffer->isAllocated() ) {
    ofxLoopin::control::Event event;
    event.type = "error";
    event.data["error"] = "buffer not allocated";
    dispatch( event );
    return;
  }

  ofPixels data;
  ofFbo &fbo = buffer->getFbo();

  fbo.readToPixels( data );
  data.setImageType( OF_IMAGE_GRAYSCALE );
  cvImage.setFromPixels( data );
  _normWidth = cvImage.getWidth();
  _normHeight = cvImage.getHeight();
  _normMinArea = minArea;
  _normMaxArea = maxArea;

  contourFinder.findContours(cvImage, minArea, maxArea, count, holes, approx );

  int nBlobs = contourFinder.nBlobs;

  if ( dispatchBlobs.isEnabledOnce( nBlobs ) )
    _dispatchBlobs();


  ofxLoopin::base::Buffer * pixelBuffer = pixels.getPointer();
  if ( pixelBuffer )
    renderBlobData( pixelBuffer );

  // if ( show.isEnabledOnce( true ) ) {
  //   buffer->begin();
  //   contourFinder.draw();
  //   buffer->end();
  // }
};

ofFloatColor ofxLoopin::blobs::Blobs::normalizeBlob0( const ofxCvBlob & blob ) {
  ofFloatColor pix;
  pix.r = blob.centroid.x / _normWidth;
  pix.g = blob.centroid.y / _normHeight;
  pix.b = (blob.area - _normMinArea ) / ( _normMaxArea - _normMinArea ) ;
  pix.a = 1.0;
  return pix;
}

ofFloatColor ofxLoopin::blobs::Blobs::normalizeBlob1( const ofxCvBlob & blob ) {
  ofFloatColor pix;
  pix.r = blob.boundingRect.getLeft() / _normWidth;
  pix.g = blob.boundingRect.getTop() / _normHeight;
  pix.b = blob.boundingRect.getRight() / _normWidth;
  pix.a = blob.boundingRect.getBottom() / _normHeight;
  return pix;
}

void ofxLoopin::blobs::Blobs::renderBlobData( ofxLoopin::base::Buffer * buffer ) {
  int nBlobs = contourFinder.nBlobs;

  auto renderer = ofGetCurrentRenderer();
  // renderer->loadIdentityMatrix();
  // ofMatrix4x4 mat;
  // mat.makeIdentityMatrix();
  // renderer->loadViewMatrix( mat );

  // cerr << "renderBlobData " << nBlobs << " " << renderer->getCurrentViewMatrix() <<  endl;

  float xNorm = 0.0;
  float yNorm = 0.0;

  ofxCvBlob norm;
  norm.area = 0.0;

  if ( !nBlobs && !_hasRenderedBlobs )
    return;

  ofFloatPixels data;
  data.allocate( 2, count + 1, OF_IMAGE_COLOR_ALPHA );

  // if ( nBlobs > 0 )
  //   data.setColor( ofFloatColor( 0,0.1,0,1 ) );
  // else 
  //   data.setColor( ofFloatColor( 0.1,0,0,1 ) );


  for ( int index = 0; index < count; index ++ ) {
    ofFloatColor pix;

    if ( index < nBlobs ) {
      // cerr << "renderBlobData?!?! " << index << " " << nBlobs <<  endl;

      const ofxCvBlob & blob = contourFinder.blobs[index];
      data.setColor( 0, index + 1, normalizeBlob0( blob ) );
      // data.setColor( 0, index + 1, ofFloatColor( 0,1,0,1 ) );
      data.setColor( 1, index + 1, normalizeBlob1( blob ) );
      // data.setColor( 0, index + 1, ofFloatColor( 1,1,0,1 ) );

      norm.area += blob.area;
      xNorm += blob.centroid.x * blob.area;
      yNorm += blob.centroid.y * blob.area;
      if ( index ) {
        norm.boundingRect.growToInclude( blob.boundingRect );
      } else { 
        norm.boundingRect = blob.boundingRect;
      }
    } else {
      // cerr << "renderBlobData!? " << index << " " << nBlobs << " " << _normWidth <<  endl;
      data.setColor( 0, index + 1, ofFloatColor( 0,0,0,0 ) );
      data.setColor( 1, index + 1, ofFloatColor( 0,0,0,0 ) );
    }
  }

  if ( norm.area ) {
    norm.centroid.x = xNorm / norm.area;
    norm.centroid.y = yNorm / norm.area;
    data.setColor( 0, 0, normalizeBlob0( norm ) );
    data.setColor( 1, 0, normalizeBlob1( norm ) );
  } else {
    data.setColor( 0, 0, ofFloatColor( 0,0,0,0 ) );
    data.setColor( 1, 0, ofFloatColor( 0,0,0,0 ) );
  }


  // data.setColor( 0, 0, ofFloatColor( 1,0,1,1 ) );

  ofTexture tex;
  tex.allocate( data );
  tex.loadData( data );
  buffer->setSize( 2, count + 1, GL_RGBA32F_ARB );
  buffer->begin();

  glDisable( GL_CULL_FACE );
  ofDisablePointSprites();
  ofSetDepthTest( false );
  ofDisableBlendMode( );
  glDisable( GL_BLEND );

  ofDrawRectangle( 0,0,4,4);
  ofClear( 0,30, 60, 0.0 );
  tex.draw( 0, 0, 2, 17 );
  buffer->end();
  buffer->bufferIsNew = false;

  tex.clear();
  data.clear();
  _hasRenderedBlobs = true;

}

void ofxLoopin::blobs::Blobs::_dispatchBlobs() {
  ofxLoopin::control::Event event;

  int nBlobs = contourFinder.nBlobs;
  event.type = "blobs";
  event.data["blobs"] = ofJson::array();
  for ( int index = 0; index < nBlobs; index ++ ) {
    ofJson blobJ;
    const ofxCvBlob &blob = contourFinder.blobs[index];

    blobJ["a"] = blob.area;
    blobJ["cx"] = blob.centroid.x;
    blobJ["cy"] = blob.centroid.y;
    blobJ["bx"] = blob.boundingRect.x;
    blobJ["by"] = blob.boundingRect.y;
    blobJ["bw"] = blob.boundingRect.width;
    blobJ["bh"] = blob.boundingRect.height;
    blobJ["nPts"] = blob.nPts;
    event.data["blobs"][index] = blobJ;
  }

  event.data["w"] = cvImage.getWidth();
  event.data["h"] = cvImage.getHeight();

  dispatch( event );

}
