/*
 *  Created on: 25 mars 2011
 *  Version: 0.1.1
 *
 *  Author: Rémi AUGUSTE
 *  Email: remi.auguste@lifl.fr
 */

#ifndef LIBREMICV_HPP_
#define LIBREMICV_HPP_

#include <vector>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace racv
{

#include <colorNormalization/colorNormalization.hpp>
#include <detection.hpp>
#include <person.hpp>
#include <points.hpp>

void test();

} // namespace racv


#endif /* LIBREMICV_HPP_ */
