 #include <opencv2/opencv.hpp> // how we import open cv2
 #include <iostream>
 using namespace cv;
   //idk what i'm doing
  int main(int argc, char* argv[]) //gets arguments
  { //this is the proper way to put the parenthesis thingy
  std::string fileLocation = argv[1];
  Mat hsv,img = imread(fileLocation);


  cvtColor(img, hsv, CV_BGR2HSV);
  std::vector<cv::Mat> channels;
  split(hsv, channels); //splitting the channels

  Mat hueOrig = channels.at(0).clone();
  Mat threshLower, threshUpper;
  Mat result;

  threshold(hueOrig, threshLower, 0, 255, CV_THRESH_BINARY);
  threshold(hueOrig, threshUpper, 50, 255, CV_THRESH_BINARY_INV);

  result = threshLower & threshUpper;
  imshow("Hue", result);

  Mat edges;
  std::vector<std::vector<Point> > contours;
  //thresholding...
  Canny(result, edges, 0, 25, 3, false);
  imshow("Cannied", edges);
  bool done = true;
  bool Find = false;
  cv::findContours(edges, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
  int scaling = 5;
  std::vector<Point> approxContour;

  for(int i = 0; i < contours.size(); i++) //contours.size()??
  {

    approxPolyDP(contours[i], approxContour, cv::arcLength(cv::Mat(contours.at(i)), done), done);
    //from the powerpoint

    if (approxContour.size() == 10) //not sure what this size is
    {

     cv::drawContours(img, contours, i , Scalar(255,0,0), scaling);

     std::cout << cv::contourArea(approxContour, Find); //

     imshow("This is the image", img);
    }
  }
  waitKey(0); //important stuff
  return 0;
}
