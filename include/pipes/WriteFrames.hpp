/*
 * WriteFrames.hpp
 *
 *  Created on: 26 sept. 2011
 *      Author: remi
 */

#ifndef WRITEFRAMES_HPP_
#define WRITEFRAMES_HPP_

#include "Pipe.hpp"

namespace racv
{

	class WriteFrames: public Pipe
	{
	private:
		int frameCounter;
		std::string prefix;
	public:
		/**
		 * If this constructor is used then the frames' filename will just be the frame number
		 */
		WriteFrames();

		/**
		 * \param prefix will be put on the frames' filename before the frame number
		 */
		WriteFrames(std::string prefix);
		virtual ~WriteFrames();
		void processingSingleFrame(cv::Mat *image);
	};

}

#endif /* WRITEFRAMES_HPP_ */
