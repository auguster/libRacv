/*
 * Reservoir.h
 *
 *  Created on: 17 janv. 2011
 *      Author: auguster
 */

#ifndef RESERVOIR_H_
#define RESERVOIR_H_

#include <opencv2/highgui/highgui.hpp>

#include <string>

#include "Pipe.hpp"

namespace racv
{
	class Reservoir
	{
	public:
		/**
		 * Ouverture du flux de donnée
		 * filename: nom du fichier à ouvrir (si vide on passe sur la caméra)
		 */
		Reservoir(std::string filename);

		/**
		 * capture: passage manuel de la capture à exploiter
		 */
		Reservoir(cv::VideoCapture *capture);

		virtual ~Reservoir();

		/**
		 *
		 */
		Pipe *plugPipe(Pipe* next);

		/**
		 *
		 */
		void flood();

		cv::VideoCapture *getCapture();

		cv::Size frameSize();

	private:
		cv::VideoCapture *capture;
		Pipe *next;
	};
}

#endif /* RESERVOIR_H_ */
