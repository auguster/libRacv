/*
 * rectangle.cpp
 *
 *  Created on: 14 juin 2011
 *      Author: remi
 */

#include <rectangle.hpp>

namespace racv
{
	bool isOverlapping(cv::Rect A, cv::Rect B)
	{
		return (((A.x < B.x) && (B.x < (A.x + A.width))) && ((A.y < B.y) && (B.y < (A.y + A.height)))) || (((A.x < (B.x + B.width))
				&& ((B.x + B.width) < (A.x + A.width))) && ((A.y < (B.y + B.height)) && ((B.y + B.height) < (A.y + A.height))));
	}

	void merge(std::vector<cv::Rect> &source, std::vector<cv::Rect> &destination)
	{
		for (std::vector<cv::Rect>::iterator A = source.begin(); A < source.end(); A++)
		{
			for (std::vector<cv::Rect>::iterator B = destination.begin(); B < destination.end(); B++)
			{
				if (isOverlapping(*A, *B))
				{
					break;
				}

				if (B == destination.end())
				{
					destination.push_back(*A);
					break;
				}
			}
		}
	}
}
