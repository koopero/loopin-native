#include "./Blobs.hpp"

void ofxLoopin::blobs::Blobs::renderBuffer( ofxLoopin::base::Buffer * buffer  ) {
  if ( !enable.isEnabledOnce() ) {
    return;
  }

  ofxLoopin::control::Event event;
  if ( !buffer || !buffer->isAllocated() ) {
    event.type = "error";
    event.data["error"] = "buffer not allocated";
    dispatch( event );
    return;
  }

  ofPixels pixels;
  ofFbo &fbo = buffer->getFbo();

  fbo.readToPixels( pixels );
  pixels.setImageType( OF_IMAGE_GRAYSCALE );
  cvImage.setFromPixels( pixels );
  contourFinder.findContours(cvImage, minArea, maxArea, count, holes, approx );

  event.type = "blobs";
  for ( int index = 0; index < contourFinder.nBlobs; index ++ ) {
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

  dispatch( event );

  ofFloatPixels data;
  // data.allocate( 16, 16 );

  if ( !show.isEnabledOnce() ) {
    return;
  }

  buffer->begin();
  contourFinder.draw();
  buffer->end();
};

void ofxLoopin::blobs::Blobs::renderBlobData() {

};