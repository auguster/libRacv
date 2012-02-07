/*
 * ExtractRectangles.cpp
 *
 *  Created on: 27 oct. 2011
 *      Author: foloex
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
                std::vector<cv::Rect> *rects = racv::mat2VectRect(*(*msg.data)[image]);
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
