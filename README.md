# smooth-gui
Interact with your experiments plot in real time without recompilation


## What problem solves
Interact with your experiment parameters inside your program, to avoid this workflow:
 1. configure the experiment
 2. compile and run the program
 3. save the results to a file
 4. plot the results with your favourite tool (matplotlib, octave, gnuplot)
 5. repeat from step 1 for minor tweaks


## Solution proposed
The user program opens an opengl context and renders the plot of the experiment by providing an appropriate shader. The actual experiment could be run
 * on CPU and its results would be shared with GPU buffers
 * on GPU using special shaders

The interaction with the parameters of the experiment is still an unsolved problem, for the time being I'm using some simple custom sliders (see `gui` experiment)


## What is the product
A collection of files to copy into your project.


## Byproducts
 * learn opengl
 * experiment with immediate mode ui


## Dependencies
 * glfw3


## First steps in development
 * makefile
 * follow the introductive tutorial in [learn opengl](https://learnopengl.com)


## Direction of the project
Doing UI is hard, especially if you want to be efficient with the drawing calls. But solving UI is not everything, what about the rendering of the experiment? Also scientific plotting is hard (who would have thought?).

This project will provide a simple API for simple visualization tasks and opengl experiments. I've come to the realization that for actual scientific research the following tools are more appropriate:
 * python + matplotlib
 * Cpp + ImGui


## Contributors
This project is shaped on my ideal computing experience, which is very niche I know. Feel free to fork this repository and make your own custom engine, or jump on this boat and let's rock it together!
