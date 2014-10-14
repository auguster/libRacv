/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/detection.hpp>

#include <opencv2/imgproc/imgproc.hpp>

namespace racv
{

	void smartDetect(cv::CascadeClassifier detector, cv::Mat &frame, std::vector<cv::Rect> &rectList)
	{
		if (rectList.size() <= 0)
		{
			detector.detectMultiScale(frame, rectList, 1.3);
			return;
		}

		cv::Mat smallerFrame;
		std::vector<cv::Rect> list;
		double scaleLevel = 0.125;
		//tries to find at least the same number of object as before at the same scalelevel
		while (scaleLevel <= 1 && list.size() < ((rectList.size() > 0) ? rectList.size() : 1))
		{
			cv::resize(frame, smallerFrame, cv::Size(), scaleLevel, scaleLevel);
			detector.detectMultiScale(smallerFrame, list, 1.3);
			scaleLevel *= 2;
		}
		scaleLevel /= 2;

		rectList.clear();

		for (std::vector<cv::Rect>::iterator rect = list.begin(); rect < list.end(); rect++)
		{
			cv::Rect fullSize = *rect;
			fullSize.x /= scaleLevel;
			fullSize.y /= scaleLevel;
			fullSize.height /= scaleLevel;
			fullSize.width /= scaleLevel;
			rectList.push_back(fullSize);
		}
	}

} // namespace racv
