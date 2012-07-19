/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/pipes/misc/Track.hpp>
#include <libRacv/tools/points.hpp>
#include <libRacv/tools/rectangle.hpp>

#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

namespace racv
{

  Track::Track()
  {
    this->secondChance = true;
  }

  Pipe::PipeMsg
  Track::processing(Pipe::PipeMsg msg)
  {
    //si pas de souvenir et data dans msg on sauv et on return
    if ((this->corners.size() == 0)) // || (this->savedImgs.size() != msg.imgs->size()))
    {
      if ((*msg.data)[0])
      {
        for (int i = 0; i < msg.data->size(); i++)
        {
          cv::Mat *copyMat = new cv::Mat();
          (*msg.imgs)[i]->copyTo(*copyMat);
          this->savedImgs.push_back(copyMat);

          std::vector<cv::Rect> *rects = (std::vector<cv::Rect> *) racv::mat2VectRect(*(*msg.data)[i]);

          cv::Mat searchMask(cv::Size((*msg.imgs)[i]->cols, (*msg.imgs)[i]->rows), CV_8U); //on créé un masque de recherche

          cv::Mat inGray(cv::Size((*msg.imgs)[i]->cols, (*msg.imgs)[i]->rows), CV_8U); //on fait une copie en niveau de gris
          cv::cvtColor(*(*msg.imgs)[i], inGray, CV_RGB2GRAY, 1);

          for (std::vector<cv::Rect>::iterator roi = rects->begin(); roi < rects->end(); roi++)
          {
            searchMask.setTo(false);
            searchMask(*roi).setTo(true);

            std::vector<cv::Point2f> corners; //recherche des points d'intérêts
            cv::goodFeaturesToTrack(inGray, corners, 500, 0.01, 5, searchMask);
            this->corners.push_back(corners);
          }
        }
      }
      return msg;
    }

    bool hasTracked = false;

    for (int i = 0; i < msg.imgs->size(); i++)
    {

      cv::Mat *image = (*msg.imgs)[i];
      cv::Mat *oldImage = this->savedImgs[i];

      for (std::vector<std::vector<cv::Point2f> >::iterator corners = this->corners.begin();
          corners < this->corners.end(); corners++)
      {
        std::vector<cv::Point2f> nextPts;
        std::vector<uchar> status;
        std::vector<float> err; //suivi de ces points d'intérêts
        cv::calcOpticalFlowPyrLK(*oldImage, *image, *corners, nextPts, status, err);

        std::vector<cv::Point2f> points = racv::filterOut(nextPts, status);

        int nbFound = points.size();

        float errmoy = 0.0;
        int cnt = 1;
        for (std::vector<float>::iterator error = err.begin(); error < err.end(); error++, cnt++)
        {
          errmoy = (errmoy + *error) / cnt;
        }

        //std::cout << "errmoy: " << errmoy << " found: " << nbFound << "/" << corners->size() << std::endl;

        if (errmoy < 2.5 && nbFound == corners->size()) //FIXME vérifier la pertinence de ce seuil
        {
          cv::Rect newDetection = racv::computeRectangle(points);
          if (!(*msg.data)[i])
            (*msg.data)[i] = new cv::Mat(0, 4, CV_32F);
          (*msg.data)[i]->push_back(*racv::rect2mat(newDetection));
          hasTracked = true;
        }
      }
    }

    if (!hasTracked)
    {
        this->corners.clear();
        this->savedImgs.clear();
        this->secondChance = true;
    }

    return msg;
  }

  Track::~Track()
  {
  }

} /* namespace racv */
