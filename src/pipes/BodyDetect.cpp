/*
 * BodyDetect.cpp
 *
 *  Created on: 10 juin 2011
 *      Author: remi
 */

#include <pipes/BodyDetect.hpp>

#include <opencv2/imgproc/imgproc.hpp>

namespace racv
{

	BodyDetect::BodyDetect()
	{
		this->next = NULL;
		this->detector = new cv::CascadeClassifier("/usr/local/share/opencv/haarcascades/haarcascade_mcs_upperbody.xml");
	}

	BodyDetect::~BodyDetect()
	{
	}

	Pipe::PipeMsg BodyDetect::processing(Pipe::PipeMsg msg)
	{
		Pipe::PipeMsg temp;
		temp.log = msg.log;

		for (std::vector<cv::Mat *>::iterator image = msg.data->begin(); image < msg.data->end(); image++)
		{
			std::vector<cv::Rect> bodies;

			racv::smartDetect(*this->detector, **image, bodies);

			for (std::vector<cv::Rect>::iterator body = bodies.begin(); body < bodies.end(); body++)
			{
				cv::Mat *bodyImage;

				cv::Size bodySize = body->size();
				cv::Point bodyCenter(body->x + body->width / 2, body->y + body->height / 2);

				/**
				 * FIXME mettre le code dans singleFrameProcessing et mettre un cadre autour des parties détectées
				 * histoire de tester le détecteur
				 * en revanche il faut garder ce code intact pour après les tests
				 */

				bodyImage = new cv::Mat(bodySize, (*image)->type());

				cv::getRectSubPix(**image, bodySize, bodyCenter, *bodyImage);

				temp.data->push_back(bodyImage);
			}

		}

		return msg;
	}
}
