#include "FramesReader.hpp"

FramesReader::~FramesReader() {
    if (file.is_open()) {
        file.close();
    }
}

bool FramesReader::assertFrame(char *buffer) {
    string frameHeader(buffer, 5);
    return frameHeader == "FRAME";
}

FramesReader::FramesReader(string filename) {
    openFile(filename);
    readHeader();
}

void FramesReader::openFile(string filename) {
    file.open(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }
}

void FramesReader::readHeader() {
    getline(file, this->fileHeader);

    istringstream iss(fileHeader);
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};

    this->width = stoi(tokens[1].substr(1));
    this->height = stoi(tokens[2].substr(1));
    this->frameSize = this->width * this->height;

    int count = countFrames();
    this->framesNumber = count;
}

int FramesReader::countFrames() {
    int count = 0;
    string line;
    string search = "FRAME";
    streampos oldpos = file.tellg();

    while (getline(file, line)) {
        if (line.find(search) != string::npos) {
            count++;
        }
    }

    file.clear();
    file.seekg(oldpos);
    return count;
}

int FramesReader::getNumFrames() {
    return this->framesNumber;
}

bool FramesReader::endOfFile() {
    return file.eof();
}

Mat FramesReader::getNextFrame() {
    char *FRAME_buffer = new char[5];

    file.read(FRAME_buffer, 5);
    if (!assertFrame(FRAME_buffer)) {
        handleFrameReadError();
    }

    file.ignore(1);
    Mat frame(height, width, CV_8UC3);

    char *frame_buffer_y = new char[frameSize];
    file.read(frame_buffer_y, frameSize);
    char *frame_buffer_u = new char[frameSize];
    file.read(frame_buffer_u, frameSize);
    char *frame_buffer_v = new char[frameSize];
    file.read(frame_buffer_v, frameSize);

    for (int i = 0; i < frameSize; i++) {
        frame.at<Vec3b>(i) = Vec3b(frame_buffer_y[i], frame_buffer_u[i], frame_buffer_v[i]);
    }

    delete[] frame_buffer_y;
    delete[] frame_buffer_u;
    delete[] frame_buffer_v;
    delete[] FRAME_buffer;

    this->readFrames++;
    return frame;
}

void FramesReader::handleFrameReadError() {
    cout << "Error reading frame" << endl;
    file.seekg(0, std::ios::cur);
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    cout << contents << endl;
    exit(1);
}

bool FramesReader::nextFrameExists() {
    return this->readFrames < this->framesNumber;
}

int FramesReader::getFrameSize() {
    return this->frameSize;
}
