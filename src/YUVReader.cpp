#include "YUVReader.hpp"

YUVReader::~YUVReader()
{
    file.close();
}

bool YUVReader::assertFrame(char *buffer)
{
    string frame_header(buffer, 5);
    return frame_header == "FRAME";
}

YUVReader::YUVReader(string filename)
{
    file.open(filename, ios::binary);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }
    // read untill first space
    getline(file, this->file_header);
    
    istringstream iss(file_header);
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};

    // get height and width
    this->width = stoi(tokens[1].substr(1));
    this->height = stoi(tokens[2].substr(1));
    this->frame_size = this->width * this->height;

    // get number of frames
    int count = 0;

    string line;
    string search = "FRAME";
    streampos oldpos = file.tellg(); // stores the position
    while (getline(file, line))
    {
        if (line.find(search) != string::npos)
        {
            count++;
        }
    }
    file.clear();               // clear fail and eof bits
    file.seekg(oldpos); // get back to the position
    this->n_frames = count;

}

int YUVReader::get_n_frames()
{
    return this->n_frames;
}

bool YUVReader::end_of_file()
{
    return file.eof();
}

Mat YUVReader::get_nextFrame()
{
    char *FRAME_buffer = new char[5];

    file.read(FRAME_buffer, 5);
    if (!assertFrame(FRAME_buffer))
    {
        cout << "Error reading frame" << endl;
        file.seekg(0, std::ios::cur); // Go to the current position in the file
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        cout << contents << endl;

        exit(1);
    }

    file.ignore(1);
    Mat frame(height, width, CV_8UC3);

    //read pixels
    char *frame_buffer_y = new char[frame_size];
    file.read(frame_buffer_y, frame_size);
    char *frame_buffer_u = new char[frame_size];
    file.read(frame_buffer_u, frame_size);
    char *frame_buffer_v = new char[frame_size];
    file.read(frame_buffer_v, frame_size);

    // convert to Mat
    for (int i = 0; i < frame_size; i++)
    {
        frame.at<Vec3b>(i) = Vec3b(frame_buffer_y[i], frame_buffer_u[i], frame_buffer_v[i]);
    }
    // delete buffer
    delete[] frame_buffer_y;
    delete[] frame_buffer_u;
    delete[] frame_buffer_v;
    delete[] FRAME_buffer;
    this->read_frames++;
    return frame;
}

string YUVReader::get_file_header()
{
    return this->file_header;
}

bool YUVReader::nextFrame_exists()
{
    return this->read_frames < this->n_frames;
}

int YUVReader::get_frame_size()
{
    return this->frame_size;
}