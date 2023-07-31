#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "include/stb_image_resize.h"

int main (int argc, char* argv[]) {
	int width;
	int height;
	int channels;

	if (argc < 2) {
		printf("Image path not provided, Usage: ./ascii path_to_image invert");
	}

	unsigned char * img = stbi_load(argv[1], &width, &height, &channels, 0);

	if (!img) {
		printf("Error loading the image, may be invalid path");
		return 1;
	}

	int new_height  = height;
	int new_width = width;
	while (new_height > 400 || new_width > 400) {
		new_height = new_height / 2;
		new_width = new_width / 2;
	}

	unsigned char* resized_image_data = (unsigned char*)malloc((new_height * new_width * channels));

	stbir_resize_uint8(img, width, height, 0, resized_image_data, new_width, new_height,0, channels);

	int num_pixels = new_height * new_width * channels;
	int previous = 0;
	char *draw_arr = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

	for (int i = 0; i < num_pixels; i += channels) {
		unsigned char r = resized_image_data[i];
		unsigned char g = resized_image_data[i+1];
		unsigned char b = resized_image_data[i+2];
		int brightness = (21*r + 72*g + 7*b)/100;
		int original = (brightness * 64)/255;
		int inverted = 64 - (brightness * 64)/255;

		if (argc == 2) {
			printf("%c", draw_arr[original]);
			printf("%c", draw_arr[original]);
			printf("%c", draw_arr[original]);
		} else {
			printf("%c", draw_arr[inverted]);
			printf("%c", draw_arr[inverted]);
			printf("%c", draw_arr[inverted]);
		}
		
		if ((i + channels)/ (new_width * channels)> previous) {
			previous = (i + channels) / (new_width * channels);
			printf("\n");
		}
	}
	stbi_image_free(img);
	free(resized_image_data);

	return 0;
}
