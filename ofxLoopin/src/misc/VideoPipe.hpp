class VideoPipe : 
  public base::Render, 
  public ofThread 
{
public:
  void threadedFunction() override {
    while( isThreadRunning() ) {
      
    };
  };
};