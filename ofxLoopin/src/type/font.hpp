class ofxLoopinFont :  public ofxLoopinControl, public ofxLoopinLoader
{
  ofxLoopinControlNumber simplifyAmt = 0.3;
  ofxLoopinControlNumber size        = 64;
  ofxLoopinControlNumber lineHeight  = 80;


  void loaderLoadFile( const string &filename ) {

  }


private:
  ofxTrueTypeFontUC font_;
};
