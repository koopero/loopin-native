#include "./Blobs.hpp"

void ofxLoopin::blobs::Blobs::renderBuffer( ofxLoopin::base::Buffer * buffer  ) {
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
  // cvGrayImage.setFromColorImage( cvImage );
  // cvGrayImage.threshold( 30 );

  contourFinder.findContours(cvImage, 5, (340*240)/4, 4, false, true);

  event.type = "blobs";
  for ( int index = 0; index < contourFinder.nBlobs; index ++ ) {
    ofJson blob;

    blob["cx"] = contourFinder.blobs[index].centroid.x;
    blob["cy"] = contourFinder.blobs[index].centroid.y;
    blob["bx"] = contourFinder.blobs[index].boundingRect.x;
    blob["by"] = contourFinder.blobs[index].boundingRect.y;
    blob["bw"] = contourFinder.blobs[index].boundingRect.width;
    blob["bh"] = contourFinder.blobs[index].boundingRect.height;

    event.data["blobs"][index] = blob;
  }

  dispatch( event );

  buffer->begin();
  cvImage.draw( 0, 0 );
  contourFinder.draw();
  buffer->end();
};
