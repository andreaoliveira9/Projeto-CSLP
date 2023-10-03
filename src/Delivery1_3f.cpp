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
    VideoCapture video("../../vid/akiyo_qcif.y4m");

    if (!video.isOpened())
    {
        cerr << "Failed to open video." << endl;
        return -1;
    }

    int k1, k2, b1, b2;
    getGaussianKernelSize(k1, k2);
    getBlurKernelSize(b1, b2);

    Mat frame, gaussian_blured_image, blured_image;
    // Gaussian
    while (true)
    {
        video >> frame;

        if (frame.empty())
            break;

        resize(frame, frame, Size(500, 500));

        // Apply Gaussian blur
        gaussian_blur(frame, k1, k2, gaussian_blured_image);
        // Apply regular blur
        regular_blur(frame, b1, b2, blured_image);

        // Display the frames
        imshow("Gaussian Blured Video", gaussian_blured_image);
        imshow("Blured Video", blured_image);

        // Break the loop if 'q' is pressed
        if (waitKey(30) == 'q')
            break;
    }
}