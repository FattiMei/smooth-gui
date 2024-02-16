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

To interact with the parameters of the computation we are going to use Dear ImGui. I tried to make some sliders but the whole layout and rendering of the UI elements is hard and I prefer to focus on the experiments at the moment.


## What is the product
A collection of files to copy into your project.


## Byproducts
 * learn opengl
 * experiment with immediate mode ui (Dear ImGui)


## Dependencies
 * glfw3
 * ImGui


## First steps in development
 * makefile
 * follow the introductive tutorial in [learn opengl](https://learnopengl.com)


## Contributors
This project is shaped on my ideal computing experience, which is very niche I know. Feel free to fork this repository and make your own custom engine, or jump on this boat and let's rock it together!
