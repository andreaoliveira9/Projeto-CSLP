#include "FramesReader.hpp"

FramesReader::FramesReader(string filename)
{
    file.open(filename, ios::binary);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }

    getline(file, this->fileHeader);

    istringstream iss(fileHeader);
    vector<string> header{istream_iterator<string>{iss},
                          istream_iterator<string>{}};

    this->width = stoi(header[1].substr(1));
    this->height = stoi(header[2].substr(1));

    int count = countFrames();
    this->framesNumber = count;
}

FramesReader::~FramesReader()
{
    if (file.is_open())
    {
        file.close();
    }
}

bool FramesReader::nextFrameExists()
{
    return this->readedFrames < this->framesNumber;
}

int FramesReader::getFrameSize()
{
    return this->width * this->height;
}

int FramesReader::getNumFrames()
{
    return this->framesNumber;
}

bool FramesReader::endOfFile()
{
    return file.eof();
}

int FramesReader::countFrames()
{
    int count = 0;
    string line;
    string search = "FRAME";
    streampos oldpos = file.tellg();

    while (getline(file, line))
    {
        if (line.find(search) != string::npos)
        {
            count++;
        }
    }

    file.clear();
    file.seekg(oldpos);
    return count;
}

Mat FramesReader::getNextFrame()
{
    char *FRAMEword = new char[5];

    file.read(FRAMEword, 5);
    if (strncmp(FRAMEword, "FRAME", 5) != 0)
    {   
        cout << "Error reading frame header" << endl;
        exit(1);
    }

    file.ignore(1);
    Mat frame(height, width, CV_8UC3);
    
    char *frameY = new char[getFrameSize()];
    char *frameU = new char[getFrameSize()];
    char *frameV = new char[getFrameSize()];

    file.read(frameY, getFrameSize());
    file.read(frameU, getFrameSize());
    file.read(frameV, getFrameSize());

    for (int i = 0; i < getFrameSize(); i++)
    {
        frame.at<Vec3b>(i) = Vec3b(frameY[i], frameU[i], frameV[i]);
    }

    this->readedFrames++;
    return frame;
}
