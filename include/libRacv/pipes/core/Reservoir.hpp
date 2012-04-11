/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#ifndef RESERVOIR_H_
#define RESERVOIR_H_

#include <opencv2/highgui/highgui.hpp>

#include <string>

#include "Pipe.hpp"

namespace racv
{
	class Pipe; //forward reference (for mutual inclusion)

	class Reservoir
	{
	public:
		Reservoir();

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
