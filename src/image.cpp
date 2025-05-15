#include "../inc/image.hpp"
// #include "../inc/clonableelement.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

// template class ClonableElement<Image>;

Image::Image() : path(""), image(vector<vector<CHAR>>()) {set_expandable(NOT_EXPANDABLE);}

const string& Image::get_path() const {
	return path;
}

void Image::set_path(const string& path) {
	this->path = path;
}

void Image::set_dimensions(const array<int, 2>& dimensions) {
	Element::set_size({dimensions[0], dimensions[1] / 2});

	cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
	cv::Vec3b f_pixel, b_pixel;
	array<int, 3> avg_f_pixel, avg_b_pixel;
	int y_factor = img.rows / dimensions[1], x_factor = img.cols / dimensions[0], pixel_group_size = x_factor * y_factor;

	// if (img.empty()) {
	// 	std::cerr << "Erreur : Impossible de charger l'image!" << std::endl;
	// }

	image.resize(dimensions[1] / 2);

	for (int y = 0; y < dimensions[1]; y += 2) {
		for (int x = 0; x < dimensions[0]; x++) {
			avg_f_pixel = {0, 0, 0};
			avg_b_pixel = {0, 0, 0};

			for (int i = 0; i < x_factor; i++) {
				for (int j = 0; j < y_factor; j++) {
					f_pixel = img.at<cv::Vec3b>(y * y_factor, x * x_factor);
					b_pixel = img.at<cv::Vec3b>((y + 1) * y_factor, x * x_factor);

					for (int k = 0; k < 3; k++) {
						avg_f_pixel[k] += f_pixel[k];
						avg_b_pixel[k] += b_pixel[k];
					}
				}
			}

			for (int k = 0; k < 3; k++) {
				avg_f_pixel[k] /= pixel_group_size;
				avg_b_pixel[k] /= pixel_group_size;
			}

			image[y / 2].push_back({{(uint8_t)avg_f_pixel[2], (uint8_t)avg_f_pixel[1], (uint8_t)avg_f_pixel[0]}, {(uint8_t)avg_b_pixel[2], (uint8_t)avg_b_pixel[1], (uint8_t)avg_b_pixel[0]}});
		}
	}
}

void Image::show() const {
	COLOR f_color;
	COLOR b_color;

	for (int y = 0; y < image.size(); y++) {
		cout << "\e[" << position.y + y << ";" << position.x << 'f';
		for (int x = 0; x < image[y].size(); x++) {
			f_color = image[y][x].f_color;
			b_color = image[y][x].b_color;
			cout << "\e[38;2;" << (int)f_color.r << ";" << (int)f_color.g << ";" << (int)f_color.b << 'm' << "\e[48;2;" << (int)b_color.r << ";" << (int)b_color.g << ";" << (int)b_color.b << 'm' << "▀";
		}
	}
	cout << NORMAL;
}
