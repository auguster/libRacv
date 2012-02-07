/*
 *  Created on: 25 mars 2011
 *  Version: 0.1.1
 *
 *  Author: Rémi AUGUSTE
 *  Email: remi.auguste@lifl.fr
 */

#ifndef LIBREMICV_HPP_
#define LIBREMICV_HPP_

#include <libRacv/pipes/pipes.hpp>

#include <libRacv/tools/colorNormalization/colorNormalization.hpp>
#include <libRacv/tools/detection.hpp>
#include <libRacv/tools/points.hpp>
#include <libRacv/tools/color.hpp>
#include <libRacv/tools/matrix.hpp>
#include <libRacv/tools/rectangle.hpp>
#include <libRacv/tools/drawing/drawing.hpp>
#include <libRacv/tools/video.hpp>

namespace racv
{
	/**
	 * Easy way to test if libRacv is working
	 */
	void test();
} // namespace racv


#endif /* LIBREMICV_HPP_ */
