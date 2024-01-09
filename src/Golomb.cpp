#include "Golomb.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

GolombEncoder::GolombEncoder(string file_path)
{
    bitStream.setToWrite(file_path);
    this->set_m(3);
    this->bitstreamSize = 0;
}

void GolombEncoder::set_m(int m)
{
    if (m == 0)
    {
        return;
    }
    this->mEnc = m;
    this->b = ceil(log2(m));
}

int GolombEncoder::get_m()
{
    return mEnc;
}

long double GolombEncoder::getBitstreamSize() const
{
    return bitstreamSize;
}

int GolombEncoder::optimal_m(Mat &frame)
{
    double u = 0;
    Scalar mean_values = mean(abs(frame));

    for (int n = 0; n < frame.channels(); n++)
        u += mean_values[n];
    u /= frame.channels();
    if (u < 0.01)
        return 2;
    int s = ceil(log2(u) - 0.05 + 0.6 / u);

    s = (0 > s) ? 0 : s;
    return pow(2, s);
}

void GolombEncoder::encode(int num)
{
    int q, r;

    if (num < 0) {
        bitStream.writeBit(1);
        this->bitstreamSize++; 
    } else {
        bitStream.writeBit(0);
        this->bitstreamSize++; 
    }

    num = abs(num);

    q = num / mEnc;
    // cout << "q = " << num << " / " << m << " = " << q << "\n";
    r = num % mEnc;
    // cout << "r = " << num << " % " << m << " = " << r << "\n";

    for (int i = 0; i < q; i++) {
        bitStream.writeBit(1);
        this->bitstreamSize++; 
    }

    bitStream.writeBit(0);
    this->bitstreamSize++;

    if (mEnc % 2 == 0) {
        bitStream.writeNBits(r, b);
        this->bitstreamSize += b;
    } else if (r < pow(2, b + 1) - mEnc) {
        bitStream.writeNBits(r, b);
        this->bitstreamSize += b;
    } else {
        bitStream.writeNBits(r + pow(2, b + 1) - mEnc, b + 1);
        this->bitstreamSize += (b + 1);
    }
}

void GolombEncoder::finishEncoding()
{
    bitStream.close();
}

GolombDecoder::GolombDecoder(string file_path)
{
    bitStream.setToRead(file_path);
    this->set_m(3);
}

void GolombDecoder::set_m(int m)
{
    if (m == 0)
    {
        return;
    }
    this->mEnc = m;
    this->b = ceil(log2(m));
}

int GolombDecoder::get_m()
{
    return mEnc;
}

int GolombDecoder::decode()
{
    unsigned int r;
    signed int num;
    int q, signal;

    unsigned char bit;

    q = 0;

    if (bitStream.getEOF())
        return 0;

    signal = bitStream.readBit() & 1;

    while (true)
    {
        if ((bitStream.readBit() & 1) == 0)
            break;
        q++;
    }

    r = bitStream.readNBits(b);
    num = q * mEnc + r;

    if (mEnc % 2 == 0)
        if (!signal)
            return num;
        else
            return -1 * num;
    else if (r < pow(2, b + 1) - mEnc)
    {
        if (!signal)
            return num;
        else
            return -1 * num;
    }
    else
    {
        num = q * mEnc + (2 * r + (bitStream.readBit() & 1)) - pow(2, b + 1) + mEnc;
        if (!signal)
            return num;
        else
            return -1 * num;
    }
}

