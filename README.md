# Multithreaded Software Ray Tracer
![MainScene](/Screenshots/MainScene_Animated.gif)

## Description
This project was one of two school assignments during my first graphics programming course. Its goal was to introduce creating a 3D world from scratch, having zero beforehand knowledge about anything graphics programming related. It wasn’t easy, but it was very rewarding to see the slightest progress as I discover more about it.

I continued the project in my free time to polish and refine it a bit more. I made it into a little framework, to make it easier to create new scenes with different objects to render. Numerous parts of code were revisited over time and profiled/optimized where necessary.

## Topics Covered
* Linear Algebra (Vector- and Matrix math)
* Ray Intersections (Plane, Sphere, Triangle)
* Orthographic/Perspective Camera
* Orthonormal Base (ONB)
* Rendering Equation
* Hard Shadows
* BRDF's (Lambert, Phong, Cook-Torrance)
* Physically Based Rendering (PBR)
* OBJ Parser

Though with all the progress, this Ray Tracer can definitely be expanded upon in terms of optimization or extra features such as Accelerated Structures, Indirect Lighting, Reflections, Soft Shadows and Anti-Aliasing to name a few.

![BunnyScene](/Screenshots/BunnyScene.png)

## Most Interesting Code Snippets
[Pixel Loop and Pixel Shading](https://github.com/jarnepeire/RayTracer/blob/main/source/ERenderer.cpp)

[BRDF's](https://github.com/jarnepeire/RayTracer/blob/main/source/BRDF.cpp)

## Contributors
Credits to [Matthieu Delaere](https://www.linkedin.com/in/matthieu-delaere/), a lecturer at Howest DAE for writing the base files (math library timer, color structs, SDL window). 
