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

It does this by sending rays towards a viewport that establishes what the colors of it should be. The rays are essentially vectors that have an origin in the center of the space and shoot out forward into the shape of the viewport, in this case rectangular and with a 16:9 aspect ratio.

After getting the values from the rays in the scene we store them in a one dimensional array that then goes through STB to create a BMP image file.

## Second step: Normals with a small hiccup

![Sphere painted in Normals](https://i.imgur.com/Roct9cq.png)

The following step is to create our first object, in this case a sphere which is ideal because of it's simple equation that allows us to make one quickly and get all of its related geometric properties. 

To render a sphere it is really important to understand what is the outside and what is the inside of the sphere as we only want to render what is outside. To do that we calculate a unit vector coming from the place the ray hit and use it to calculate the color.

At this point we are also including different objects so we introduce a list of primitives to hold all of our objects, in this case two spheres.

![Normals but my equation is slightly off](https://i.imgur.com/QbeO6Re.png)

But there is also the possibility that you get an equation wrong and you accidentally turn the shading into a squared wave of color that becomes smaller at the edges like this.

## Third step: 