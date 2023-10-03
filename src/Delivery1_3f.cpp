#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "functions.cpp"

using namespace std;
using namespace cv;

// Função para obter o tamanho do kernel para o filtro Gaussiano
void getGaussianKernelSize(int &k1, int &k2)
{
    cout << "Gaussian kernel size = k1 x k2\nShould be odd numbers\n";
    // k1 e k2 devem ser numeros impares porque os kernels tem um ponto central e, com numeros impares,
    // garantimos que o ponto central estará no centro do mesmo

    cout << "Enter k1: ";
    cin >> k1;

    if (k1 > 0 && k1 % 2 != 0)
    {
        cout << "Enter k2: ";
        cin >> k2;

        if (k2 > 0 && k2 % 2 != 0)
        {
            return; // Valores válidos foram inseridos
        }
    }

    // Se os valores inseridos não forem válidos, defina os valores padrão (1, 1)
    k1 = 1;
    k2 = 1;
    cout << "Using default values: k1 = 1, k2 = 1" << endl;
}

// Função para obter o tamanho do kernel para o filtro de desfoque
void getBlurKernelSize(int &b1, int &b2)
{
    cout << "Blurring kernel size = b1 x b2\n";

    cout << "Enter b1: ";
    cin >> b1;

    cout << "Enter b2: ";
    cin >> b2;

    if (b1 < 0)
    {
        cout << "b1 não pode ser negativo. Definindo para 0." << endl;
        b1 = 0;
    }

    if (b2 < 0)
    {
        cout << "b2 não pode ser negativo. Definindo para 0." << endl;
        b2 = 0;
    }
}

int main()
{
    Mat initial_image, gaussian_blured_image, blured_image;
    int k1, k2, b1, b2;

    VideoCapture video("../../vid/akiyo_qcif.y4m");

    if (!video.isOpened())
    {
        cerr << "Failed to open video." << endl;
        return -1;
    }

    getGaussianKernelSize(k1, k2);
    getBlurKernelSize(b1, b2);

    // Gaussian
    while (1)
    {
        Mat frame, resized_frame;
        video >> frame;

        if (frame.empty())
            break;

        resize(frame, resized_frame, Size(500, 500));

        gaussian_blured_image = gaussian_blur(resized_frame, k1, k2);

        imshow("Gaussian Blured Video", gaussian_blured_image);

        // Pressionar ESC para sair
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    // Blurring
    while (1)
    {
        Mat frame2, resized_frame2;
        video >> frame2;

        if (frame2.empty())
            break;

        resize(frame2, resized_frame2, Size(500, 500));

        blured_image = regular_blur(resized_frame2, b1, b2);

        imshow("Blured Video", blured_image);

        // Pressionar ESC para sair
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    waitKey(0);
}