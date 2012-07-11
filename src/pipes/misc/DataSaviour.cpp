/*
 * Copyright (c) 2011 Rémi AUGUSTE
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contact: Rémi Auguste <remi.auguste@gmail.com>
 */

#include <libRacv/pipes/misc/DataSaviour.hpp>

namespace racv
{

    DataSaviour::DataSaviour()
    {
    }

    DataSaviour::~DataSaviour()
    {
    }

    Pipe::PipeMsg
    DataSaviour::processing(Pipe::PipeMsg msg)
    {
        this->savedData = new std::vector<cv::Mat *>();
        *this->savedData = *msg.data; // = operator copies the data from one vector to another
        return msg;
    }

    Pipe::PipeMsg
    DataSaviour::postprocessing(Pipe::PipeMsg msg)
    {
        if ((*msg.data)[0])
        {
            for (std::vector<cv::Mat *>::iterator data = msg.data->begin(); data < msg.data->end(); data++)
            {
                this->savedData->push_back(*data);
            }
            msg.data = this->savedData;
        }
        return msg;
    }

} /* namespace racv */