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

the latter choice could be better for performance reasons


## What is the product
At the moment I'm evaluating two options:
 * a collection of examples that cover the frequent use cases, with everything exposed
 * an stb like header file with wrapper functions


## Byproducts
 * learn opengl
 * experiment with immediate mode ui
 * produce software with a long lifespan


## Dependencies
 * glfw3
 * glad


## First steps in development
 * makefile
 * follow the introductive tutorial in [learn opengl](https://learnopengl.com)


## Contributors
This project is shaped on my ideal computing experience, which is very niche I know. Feel free to fork this repository and make your own custom engine, or jump on this boat and let's rock it together!
