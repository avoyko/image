#include "producer/producer.h"

int main(int argc, char** argv) {
    try {
        Producer producer(argc, argv);
        producer.Run();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return -1;
    } catch (...) {
        return -2;
    }
}
