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

  if ( show.isEnabledOnce( true ) ) {
    buffer->begin();
    contourFinder.draw();
    buffer->end();
  }
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

  float xNorm = 0.0;
  float yNorm = 0.0;

  ofxCvBlob norm;
  norm.area = 0.0;

  ofFloatPixels data;
  data.allocate( 2, count + 1, OF_IMAGE_COLOR_ALPHA );
  for ( int index = 0; index < count; index ++ ) {
    ofFloatColor pix;
    if ( index < nBlobs ) {
      const ofxCvBlob & blob = contourFinder.blobs[index];
      data.setColor( 0, index + 1, normalizeBlob0( blob ) );
      data.setColor( 1, index + 1, normalizeBlob1( blob ) );
      norm.area += blob.area;
      xNorm += blob.centroid.x * blob.area;
      yNorm += blob.centroid.y * blob.area;
      if ( index )
        norm.boundingRect.growToInclude( blob.boundingRect );
      else 
        norm.boundingRect = blob.boundingRect;
    } else {
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

  ofTexture tex;
  tex.allocate( data );

  buffer->setSize( 2, count + 1, GL_RGBA32F_ARB );
  buffer->begin();
  glDisable( GL_CULL_FACE );
  ofDisableBlendMode( );
  ofDisableDepthTest();

  tex.draw( 0, 0 );
  buffer->end();
}

void ofxLoopin::blobs::Blobs::_dispatchBlobs() {
  ofxLoopin::control::Event event;

  int nBlobs = contourFinder.nBlobs;
  event.type = "blobs";
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
