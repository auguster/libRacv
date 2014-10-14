#include <libRacv/skinprop.hpp>

#include <opencv2/imgproc/imgproc.hpp>

double skinprop(cv::Mat &image)
{
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);
	cv::Mat hue(image.size(), CV_8UC1), saturation(image.size(), CV_8UC1), value(image.size(), CV_8UC1);
	std::vector<cv::Mat> channels;
	channels.push_back(hue);
	channels.push_back(saturation);
	channels.push_back(value);
	cv::split(hsv, channels);
	cv::threshold(hue, hue, 18, 255, CV_THRESH_BINARY_INV);
	cv::threshold(saturation, saturation, 50, 255, CV_THRESH_BINARY);
	cv::threshold(value, value, 80, 255, CV_THRESH_BINARY);
	cv::Mat output;
	cv::bitwise_and(hue, saturation, output);
	cv::bitwise_and(output, value, output);
	cv::Scalar sums = cv::sum(output);
	double result = sums[0] / (output.rows * output.cols * 255);
	return result;
}
