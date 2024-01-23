#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

//横向きに反転
void x_reverse(std::vector<cv::Mat>& images, int index)//x_rev
{
    cv::flip(images[index], images[index], 1);
}

//縦向きに反転
void y_reverse(std::vector<cv::Mat>& images, int index)//y_rev
{
    cv::flip(images[index], images[index], 0);
}

//前の画像削除
void back_remove(std::vector<cv::Mat>& images, int index)//b_rm
{
    images.at(index - 1) = 0;
}

//次の画像削除
void forward_remove(std::vector<cv::Mat>& images, int index)//f_rm
{
    images.at(index + 1) = 0;
}

//前の画像と入れ替え
void change(std::vector<cv::Mat>& images, int index)//change
{
    cv::Mat tmp = images.at(index);
    images.at(index) = images.at(index - 1);
    images.at(index - 1) = tmp;
}

//何もせん
void no_command()//stay
{
}

//1234 to 4321
void R(std::vector<cv::Mat>& images)//R
{
    std::reverse(images.begin(), images.end());
}

//1234 to 3412
void eight(std::vector<cv::Mat>& images)//eight
{
    for (int i = 0; i < 2; i++) {
        auto it = images.begin();
        cv::Mat removedElement = *it;
        images.erase(it);
        images.push_back(removedElement);
    }
}

//1234 to 2143
void U(std::vector<cv::Mat>& images)//U
{
    std::swap(images[0], images[1]);
    std::swap(images[2], images[3]);
}

void command_organaize(std::vector<std::string>& commands)
{
    for (int i = 0; i < commands.size(); i++) {
        if (commands.at(i) == "b_com_rm") {
            commands.at(i - 1) = "stay";
        }
        if (commands.at(i) == "f_com_rm") {
            commands.at(i + 1) = "stay";
        }
    }
}

void command_run(std::vector<std::string>& commands, std::vector<cv::Mat>& images)
{
    for (int i = 0; i < commands.size(); i++) {
        if (commands.at(i) == "x_rev") x_reverse(images, i);
        else if (commands.at(i) == "y_rev") y_reverse(images, i);
        else if (commands.at(i) == "b_rm") back_remove(images, i);
        else if (commands.at(i) == "f_rm") forward_remove(images, i);
        else if (commands.at(i) == "change") change(images, i);
        else if (commands.at(i) == "stay") no_command();
        else if (commands.at(i) == "R") R(images);
        else if (commands.at(i) == "eight") eight(images);
        else if (commands.at(i) == "U") U(images);
    }
}

int main(int argc, char* argv[]) {

    if (argc != 6) {
        return 1;
    }

    //命令を1まとめに
    std::vector<std::string> commands;
    for (int i = 1; i < 6; i++) {
        commands.push_back(argv[i]);
    }

    // 画像を読み込む
    cv::Mat image0 = cv::imread("./resource/0.png");
    cv::Mat image1 = cv::imread("./resource/R.jpg");
    cv::Mat image2 = cv::imread("./resource/2.jpg");
    cv::Mat image3 = cv::imread("./resource/3.jpg");

    //画像を1まとめに
    std::vector<cv::Mat> images;
    images.push_back(image0);
    images.push_back(image1);
    images.push_back(image2);
    images.push_back(image3);

    // 正規化したいサイズを指定
    cv::Size normalizedSize(150, 150);
    // 画像を正規化
    for (int i = 0; i < 4; ++i) {
        cv::resize(images[i], images[i], normalizedSize);
    }

   command_organaize(commands);
   command_run(commands, images);

   // 画像を縦に連結
   cv::Mat concatenatedImage;
   cv::vconcat(images[0], images[1], concatenatedImage);
   cv::vconcat(concatenatedImage, images[2], concatenatedImage);
   cv::vconcat(concatenatedImage, images[3], concatenatedImage);

   // 連結した画像を表示
   cv::imshow("Concatenated Image", concatenatedImage);

   // 何かキーが押されるまで待機
   cv::waitKey(0);

    return 0;
}