
// Add these headers at the top of your file
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <SOIL/SOIL.h> // or stb_image_write.h if you prefer

// In your main loop, after rendering but before glfwSwapBuffers:
// ...
void captureFrame(int frameNumber) {
    // Allocate memory for the pixels
    unsigned char* pixels = new unsigned char[WIDTH * HEIGHT * 3];

    // Read pixels from the framebuffer
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
1
    // Generate filename with leading zeros
    std::ostringstream ss;
    ss << "frame_" << std::setw(5) << std::setfill('0') << frameNumber << ".png";
    std::string filename = ss.str();

    // OpenGL reads from bottom to top, but most image formats are top to bottom
    // So we need to flip the image vertically
    unsigned char* flippedPixels = new unsigned char[WIDTH * HEIGHT * 3];
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            for (int c = 0; c < 3; ++c) {
                flippedPixels[(y * WIDTH + x) * 3 + c] = pixels[((HEIGHT - 1 - y) * WIDTH + x) * 3 + c];
            }
        }
    }

    // Save the image
    SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_PNG, WIDTH, HEIGHT, 3, flippedPixels);

    // Free memory
    delete[] pixels;
    delete[] flippedPixels;

    std::cout << "Saved frame: " << filename << std::endl;
}

// Then in your main render loop:
int frameCount = 0;
while(!glfwWindowShouldClose(window))
{
    // Your existing rendering code
    // ...

    // After rendering but before swapping buffers
    captureFrame(frameCount);
    frameCount++;

    glfwSwapBuffers(window);
    glfwPollEvents();
}
