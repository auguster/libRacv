/*
 * Copyright (c) 2012 Rémi AUGUSTE
 * Contact: Rémi Auguste <remi.auguste@lifl.com>
 */

#include <libRacv/drawing/ellipse.hpp>
#include <libRacv/rectangle.hpp>
#include <libRacv/Rect.hpp>
#include <libRacv/Grabcut.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>

#include <iostream>

void setRectInMask(cv::Mat &mask, cv::Rect rect, int value)
{
	(mask(rect)).setTo(cv::Scalar(value));
}

double skin(const cv::Mat &image)
{
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);
	cv::Mat hue(image.size(), CV_8UC1), saturation(image.size(), CV_8UC1), value(image.size(), CV_8UC1);
	std::vector<cv::Mat> channels;
	channels.push_back(hue);
	channels.push_back(saturation);
	channels.push_back(value);
	cv::split(hsv, channels);
	cv::threshold(hue, hue, 18, 255, CV_THRESH_BINARY_INV);
	cv::threshold(saturation, saturation, 50, 255, CV_THRESH_BINARY);
	cv::threshold(value, value, 80, 255, CV_THRESH_BINARY);
	cv::Mat output;
	cv::bitwise_and(hue, saturation, output);
	cv::bitwise_and(output, value, output);
	cv::Scalar sums = cv::sum(output);
	double result = sums[0] / (output.rows * output.cols * 255);
	return result;
}

void faceRectangleOptimisation(const cv::Mat &image, cv::Rect &face)
{
	face.x -= face.height * 1.05 - face.height;
	face.height *= 1.05;
	racv::fitRectangle(image, face);

	cv::Rect originalFace = face;
	double skinref = skin(image(face));

	double oldskinp = skinref;
	//reduces the right border to maximize the skin color proportion
	while (face.width > originalFace.width * 0.75)
	{
		face.width -= 1;
		double skinp = skin(image(face));

		if (skinp < oldskinp)
		{
			face.width++;
			break;
		}
		oldskinp = skinp;
	}

	//reduces the left border to maximize the skin color proportion
	while (face.x < originalFace.x * 1.25 && face.width > originalFace.width * 0.75)
	{
		face.x += 1;
		face.width -= 1;
		double skinp = skin(image(face));

		if (skinp < oldskinp)
		{
			face.x--;
			face.width++;
			break;
		}
		oldskinp = skinp;
	}

	//augment the bottom border to maximize the skin color proportion
	while (face.height < originalFace.height * 1.25)
	{
		face.height += 1;
		double skinp = skin(image(face));

		if (skinp < oldskinp)
		{
			face.height--;
			break;
		}
		oldskinp = skinp;
	}

	//augment the upper border to maximize the skin color proportion
	while (face.y > originalFace.y * 0.75)
	{
		face.y -= 1;
		face.height += 1;
		double skinp = skin(image(face));

		if (skinp < oldskinp)
		{
			face.y++;
			face.height--;
			break;
		}
		oldskinp = skinp;
	}
}

Grabcut::Grabcut(double scale, bool keepBody) :
		isFirstFrame(true), scale(scale), keepBody(keepBody)
{
}

Grabcut::~Grabcut()
{
}

cv::Rect Grabcut::initNeckForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect neck;
	neck.x = (faceRect.x * 2 + faceRect.width) / 2;
	neck.y = (faceRect.y + faceRect.height) / 2;
	neck.width = faceRect.width * 0.5;
	neck.height = faceRect.height;
	neck.x -= neck.width / 2;
	racv::fitRectangle(mask, neck);
	setRectInMask(mask, neck, cv::GC_FGD);
	return neck;
}

cv::Rect Grabcut::initTorsoForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect personRect = faceRect;
	personRect.x -= (personRect.width * 1.5 - personRect.width) / 2;
	personRect.width *= 1.5;
	personRect.height *= 2;
	racv::fitRectangle(mask, personRect);
	cv::Point torsoCenter(personRect.x + personRect.width / 2,
			personRect.y + personRect.height - ((personRect.y + personRect.height) - (faceRect.y + faceRect.height)) * 0.2);
	cv::Size torsoSize(personRect.width * 0.8, ((personRect.y + personRect.height) - (faceRect.y + faceRect.height)) * 0.6);
	racv::drawFilledEllipse(mask, torsoCenter, torsoSize, 0, 180, 360, cv::GC_FGD);
	return personRect;
}

cv::Rect Grabcut::initFaceForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	racv::drawEllipseFromRect(mask, faceRect, cv::GC_FGD);
	return faceRect;
}

cv::Rect Grabcut::initForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect faceROI = initFaceForegroundMask(mask, faceRect);
	if (this->keepBody)
	{
		cv::Rect torsoROI = initTorsoForegroundMask(mask, faceRect);
		cv::Rect neckROI = initNeckForegroundMask(mask, faceRect);
		return racv::mergeRect(racv::mergeRect(faceROI, torsoROI), neckROI);
	}
	else
		return faceROI;
}

cv::Rect Grabcut::initNeckProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect neck;
	neck.x = (faceRect.x * 2 + faceRect.width) / 2;
	neck.y = (faceRect.y + faceRect.height) / 2;
	neck.width = faceRect.width * 0.75;
	neck.height = faceRect.height;
	neck.x -= neck.width / 2;
	racv::fitRectangle(mask, neck);
	setRectInMask(mask, neck, cv::GC_PR_FGD);
	return neck;
}

cv::Rect Grabcut::initTorsoProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect personRect = faceRect;
	personRect.x -= (personRect.width * 2 - personRect.width) / 2;
	personRect.width *= 2;
	personRect.height *= 2;
	racv::fitRectangle(mask, personRect);

	cv::Point torsoCenter(personRect.x + personRect.width / 2, personRect.y + personRect.height);
	cv::Size torsoSize(personRect.width, ((personRect.y + personRect.height) - (faceRect.y + faceRect.height)) * 0.8);
	racv::drawFilledEllipse(mask, torsoCenter, torsoSize, 0, 180, 360, cv::GC_PR_FGD);
	return personRect;
}

cv::Rect Grabcut::initFaceProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	racv::scaleRectangleKeepCenter(faceRect, 1.50);
	racv::fitRectangle(mask, faceRect);
	racv::drawEllipseFromRect(mask, faceRect, cv::GC_PR_FGD);
	return faceRect;
}

cv::Rect Grabcut::initProbablyForegroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect faceROI = initFaceProbablyForegroundMask(mask, faceRect);
	if (this->keepBody)
	{
		cv::Rect torsoROI = initTorsoProbablyForegroundMask(mask, faceRect);
		cv::Rect neckROI = initNeckProbablyForegroundMask(mask, faceRect);
		return racv::mergeRect(racv::mergeRect(faceROI, torsoROI), neckROI);
	}
	else
		return faceROI;
}

cv::Rect Grabcut::initNeckProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect neck;
	neck.x = (faceRect.x * 2 + faceRect.width) / 2;
	neck.y = (faceRect.y + faceRect.height) / 2;
	neck.width = faceRect.width;
	neck.height = faceRect.height;
	neck.x -= neck.width / 2;
	racv::fitRectangle(mask, neck);
	setRectInMask(mask, neck, cv::GC_PR_BGD);
	return neck;
}

cv::Rect Grabcut::initTorsoProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect personRect = faceRect;
	personRect.x -= (personRect.width * 2.5 - personRect.width) / 2;
	personRect.width *= 2.5;
	personRect.height *= 2;
	racv::fitRectangle(mask, personRect);

	cv::Point torsoCenter(personRect.x + personRect.width / 2, personRect.y + personRect.height);
	cv::Size torsoSize(personRect.width, ((personRect.y + personRect.height) - (faceRect.y + faceRect.height)) * 0.8);
	racv::drawFilledEllipse(mask, torsoCenter, torsoSize, 0, 180, 360, cv::GC_PR_BGD);
	return personRect;
}

cv::Rect Grabcut::initFaceProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	racv::scaleRectangleKeepCenter(faceRect, 1.75);
	racv::fitRectangle(mask, faceRect);
	faceRect.x -= (faceRect.width * 1.5 - faceRect.width) / 2;
	faceRect.width *= 1.5;
	racv::fitRectangle(mask, faceRect);
	racv::drawEllipseFromRect(mask, faceRect, cv::GC_PR_BGD);
	return faceRect;
}

cv::Rect Grabcut::initProbablyBackgroundMask(cv::Mat &mask, cv::Rect faceRect)
{
	cv::Rect faceROI = initFaceProbablyBackgroundMask(mask, faceRect);
	if (this->keepBody)
	{
		cv::Rect torsoROI = initTorsoProbablyBackgroundMask(mask, faceRect);
		cv::Rect neckROI = initNeckProbablyBackgroundMask(mask, faceRect);
		return racv::mergeRect(racv::mergeRect(faceROI, torsoROI), neckROI);
	}
	else
		return faceROI;
}

cv::Rect Grabcut::initBackground(cv::Mat &mask, cv::Rect faceRect)
{
	mask.setTo(cv::GC_BGD);
	return faceRect;
}

cv::Rect Grabcut::initMask(cv::Mat &mask, cv::Rect faceRect)
{
	initBackground(mask, faceRect);
	/**
	 * FIXME:
	 * Ca serait bien de factoriser un peu les codes d'initialisation
	 * Il y a beaucoup de répétitions qui ne varient que d'une valeur ...
	 */
	cv::Rect probablyBackgroundROI = initProbablyBackgroundMask(mask, faceRect);
	cv::Rect probablyForegroundROI = initProbablyForegroundMask(mask, faceRect);
	cv::Rect foregroundROI = initForegroundMask(mask, faceRect);
	return racv::mergeRect(racv::mergeRect(probablyForegroundROI, probablyBackgroundROI), foregroundROI);
}

cv::Rect Grabcut::process(cv::Mat &image, cv::Rect faceRect)
{

	if (this->isFirstFrame)
	{
		this->scaledSize = new cv::Size(image.cols * this->scale, image.rows * this->scale);
		mask.create(*this->scaledSize, CV_8UC1);
		globalMask.create(image.rows, image.cols, CV_8UC1);
	}

	globalMask.setTo(0);
	cv::Rect personRect; //rectangle englobant la personne

	if (faceRect.height > 0 && faceRect.width > 0)
	{
		cv::resize(mask, mask, *scaledSize);
		mask.setTo(cv::GC_BGD);

		faceRectangleOptimisation(image, faceRect);

		cv::resize(mask, mask, image.size());
		personRect = initMask(mask, faceRect);
		cv::resize(mask, mask, *this->scaledSize, 0, 0, 0);

		smartGrabcut(image, mask, personRect);

		cv::resize(mask, mask, globalMask.size()); //for safety reasons ^^

		globalMask |= mask;
	}

	cv::Mat temp;
	image.copyTo(temp);
	image.setTo(0);
	temp.copyTo(image, globalMask);
	if (this->isFirstFrame) this->isFirstFrame = false;
	return personRect;
}

/**
 * Fonction qui applique le grabcut sur une version plus petite de l'image et ensuite agrandi
 * le masque pour qu'il prenne la taille de l'image d'origine
 *
 * /!\ le masque doit être construit plus petit (un resize entraine une perte de donnée)
 *
 * ça devrait aller plus vite et peut être même donner un résultat plus précis
 *
 */
void Grabcut::smartGrabcut(cv::Mat &image, cv::Mat &mask, cv::Rect rect)
{
	cv::Mat croppedImage, croppedMask;

	image.copyTo(croppedImage);
	mask.copyTo(croppedMask);

	cv::resize(croppedImage, croppedImage, croppedMask.size());

	cv::Mat bg, fg; //image temporaire pour le grabcut
	cv::grabCut(croppedImage, croppedMask, rect, bg, fg, 20, cv::GC_INIT_WITH_MASK);

	croppedMask &= 1; //binarisation du masque

	cv::resize(croppedMask, mask, image.size());

	croppedImage.release();
	croppedMask.release();
	bg.release();
	fg.release();
}
