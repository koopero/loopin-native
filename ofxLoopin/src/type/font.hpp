<<<<<<< HEAD
class ofxLoopinFont :  public ofxLoopinControl, public ofxLoopinLoader
{
  ofxLoopinControlNumber simplifyAmt = 0.3;
  ofxLoopinControlNumber size        = 64;
  ofxLoopinControlNumber lineHeight  = 80;
=======
class ofxLoopinFont :  public ofxLoopinControl
{
  ofxLoopinControlBool   antialias
  ofxLoopinControlNumber simplify    = 0.3;
  ofxLoopinControlNumber size        = 64;
  ofxLoopinControlNumber lineHeight  = 80;
  ofxLoopinControlNumber letterSpacing  = 80;


>>>>>>> blend


  void loaderLoadFile( const string &filename ) {

  }

<<<<<<< HEAD

private:
  ofxTrueTypeFontUC font_;
=======
protected:
  void addSubControls() {

  }



private:
  ofxTrueTypeFontUC font_;
  string filename_;

  void refresh() {
    font_.load( filename_, size, antialias, true, simplify, dpi );
  }
>>>>>>> blend
};
