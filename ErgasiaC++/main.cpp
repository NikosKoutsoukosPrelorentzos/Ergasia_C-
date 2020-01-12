#include "ppm.h"
#include "array2d.h"
#include "Image.h"
#include "Filter.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include <string>
#include <vector>


int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage: filter -f [filter1] [params] ... -f [filterk] [params] [image file name] " << std :: endl;
		return 1;
	}

	std::vector<Filter*> filters;
	int remainingArgs = argc - 1;
	int i = 1;

	std::string filterArgv = argv[i];
	while (filterArgv == "-f") {
		remainingArgs--;
		i++;

		// Gamma filter
		if (remainingArgs >= 2 && !strcmp(argv[i], "gamma")) {
			i++;
			float gamma = stof(argv[i++]);

			FilterGamma* g = new FilterGamma(gamma);
			remainingArgs -= 2;
			filters.push_back(g);
		}
		// Linear filter
		else if (remainingArgs >= 7 && !strcmp(argv[i], "linear")) {
			i++;
			float aR = stof(argv[i++]);
			float aG = stof(argv[i++]);
			float aB = stof(argv[i++]);
			math::Vec3<float> a(aR, aG, aB);

			float cR = stof(argv[i++]);
			float cG = stof(argv[i++]);
			float cB = stof(argv[i++]);
			math::Vec3<float> c(cR, cG, cB);

			FilterLinear* f = new FilterLinear(a, c);
			remainingArgs -= 7;
			filters.push_back(f);
		}
		// Error handling
		else {
			std::cout << "Problem!!! After -f filter should be specified ";
			return 1;
		}
		filterArgv = argv[i];
	}

	if (remainingArgs < 1) {
		std::cout << "No image specified";
		return 1;
	}

	std::string imageFileName = argv[i];
	Image im;
	im.load(imageFileName, PPM_FORMAT);

	// Apply filters
	for (unsigned int i = 0; i < filters.size(); i++) {
		im = (*filters[i]) << im;
	}

	std::string saveFileName = "filtered_" + imageFileName;
	im.save(saveFileName, PPM_FORMAT);

	// Delete filters
	for (unsigned int i = 0; i < filters.size(); i++) {
		delete filters[i];
	}
	return 0;
}