#include <opencv2/opencv.hpp>
#include <iostream>

//using namespace cv;
//using namespace std;

int main(int argc, char const *argv[])
{
    cv::Mat in_frame,out_frame;
    const char win1[]="Захват...",win2[]="Запись...";
    double fps=25;//число кадров в секунду
    char file_out[]="./recorded.avi";

    cv::VideoCapture inVid(0); //открыть камеру по умолчанию

    if(!inVid.isOpened())
    {
        std::cout<<"Ошибка! Камера не готова...";
        return -1;
    }

    // get one frame from camera to know frame size and type
    inVid>>in_frame;
    if(in_frame.empty())
    {
        std::cout<<"ERROR! blank frame grabbed\n";
    }
    bool isColor = (in_frame.type() == CV_8UC3);

    //Получаем ширину и высоту входного видедо
    //int width=(int)inVid.get(cv::CAP_PROP_FRAME_WIDTH);
    //int height=(int)inVid.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::VideoWriter recVid;
    int codec=cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    recVid.open(file_out,codec,fps,in_frame.size(),isColor);
    //(file_out,cv::VideoWriter
    //        ::fourcc('M', 'J', 'P', 'G'),fps,cv::Size(width,height));
    if(!recVid.isOpened())
    {
        std::cout<<"Ошибка! Видеофайл не открыт...";
        return -1;
    }

    //Создаем два окна для исходного и конечного видео
    cv::namedWindow(win1);
    cv::namedWindow(win2);

    std::cout << "Writing videofile: " << file_out << std::endl
         << "Press any key to terminate" << std::endl;

    while(true)
    {
        //читаем кадр с камеры(захват и декодирование)
        inVid>>in_frame;
        //преобразуем кадр в полутоновый формат
        cv::cvtColor(in_frame,out_frame,cv::COLOR_BGR2GRAY);

        //Записываем кадр в видеофайл(кодирование и сохранение)
        recVid.write(in_frame);
        cv::imshow(win1,in_frame); //показываем кадр в окне
        cv::imshow(win2,out_frame);
        if(cv::waitKey(1000/fps)>=0)
            break;
    }

    inVid.release(); //закрываем камеру

    return 0;
}
