/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/pipes/misc/ExtractRectangles.hpp>
#include <libRacv/tools/rectangle.hpp>

#include <iostream>

namespace racv
{

    ExtractRectangles::ExtractRectangles()
    {
    }

    ExtractRectangles::~ExtractRectangles()
    {
    }

    Pipe::PipeMsg
    ExtractRectangles::processing(Pipe::PipeMsg msg)
    {
        if ((*msg.data)[0])
        {
            std::vector<cv::Mat *> *imgs = new std::vector<cv::Mat *>();

            int nbImages = msg.imgs->size();

            for (int image = 0; image < nbImages; image++)
            {
                std::vector<cv::Rect> *rects = (std::vector<cv::Rect> *) racv::mat2VectRect(*(*msg.data)[image]);
                for (std::vector<cv::Rect>::iterator rect = rects->begin(); rect < rects->end(); rect++)
                {
                	if (rect->width < 0 || rect->height < 0)
                		continue;
                    cv::Mat *extract = new cv::Mat(rect->height, rect->width, (*(*msg.imgs)[image]).type());
                    *extract = (*(*msg.imgs)[image])(*rect);
                    imgs->push_back(extract);
                }
            }

            msg.imgs = imgs;
            msg.data->clear();
            //msg.data = NULL; //ca fait planter DataSaviour
        }
        return msg;
    }

} /* namespace racv */
