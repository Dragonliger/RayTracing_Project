# **RayTracing in one weekend project**
<h3 align="right">by Alex Castelan</h3>

![Render from the program](https://i.imgur.com/SiId1AO.png)

## Introduction
The challenge was to build a functioning raytracing renderer in C++ following [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html), adding new features and modifying it as required. 

The program introduces many important concepts that modern renderers have, like setting up a camera, primitives, diffuse shading and materials.

Some features that I added to the program are exporting to an image format using the STB image library and a simple use of multi-threading for the sampling process.

# How to build and run
The program was made in Visual Studio 2019. To run build it using Visual Studio and then open a command line in /debug to run just call the .exe followed by the output image name like:
` .\RayTracing.exe image` It will count down the remaining horizontal lines until the image is produced. If the process is interrupted no image will be produced.

## First step: Setting a basic viewport

![It may be just a gradient but it's 3D](https://i.imgur.com/M4OgsK3.png)

The first step is to output an image, I used the [STB Library](https://github.com/nothings/stb) to help me output a bpm image instead of using the suggested PPM one, it felt like it made more sense. The main difference is that the channel values were written sequentially which had some repercutions in sectioning the program. Using a basic viewport the program simulates a gradient background.