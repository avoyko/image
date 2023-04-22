add_executable(
        image_processor
        image_processor.cpp
        bmp_image/BMP.cpp bmp_image/BMP.h cmd/cmd_reader.h cmd/cmd_reader.cpp filters_module/base_filter.cpp filters_module/crop.cpp filters_module/negative.cpp filters_module/grayscale.cpp filters_module/gauss_blur.cpp filters_module/sharp.cpp filters_module/edge_detection.cpp filters_module/sobel.cpp filters_module/base_filter.h filters_module/crop.h filters_module/edge_detection.h filters_module/gauss_blur.h filters_module/grayscale.h filters_module/negative.h filters_module/sharp.h filters_module/sobel.h bmp_image/BMP.cpp producer/producer.cpp producer/producer.h cmd/exceptions.h)


