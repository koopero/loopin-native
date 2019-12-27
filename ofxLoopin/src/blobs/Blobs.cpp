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
  event.data["num"] = contourFinder.nBlobs;
  event.data["width"] = cvImage.getWidth();
  event.data["pwidth"] = pixels.getWidth();
  event.data["pchan"] = pixels.getBytesPerPixel();
  event.data["cchan"] = cvImage.getPixels().getBytesPerPixel();

  dispatch( event );

  buffer->begin();
  cvImage.draw( 0, 0 );
  contourFinder.draw();
  buffer->end();
};
