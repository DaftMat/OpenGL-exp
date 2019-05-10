# OpenGL-exp
Experimentation of OpenGL using GLFW, following [this awesome tutorial](https://learnopengl.com/ "learnopengl.com").

# Dependencies
In order to compile and run this little engine, you will need :
  * [GLAD](https://glad.dav1d.de/) with the following settings :
    * Language : C/C++
    * Specification : OpenGL
    * API gl : version 4.6
    * Profile : core
    * No extensions
    * Generate a loader
    * -> Click on generate and you're all set
    
  * [Assimp](https://github.com/assimp/assimp.git) Clone their repo into your downloads folder (or any else) and open a terminal :
    ```
    mkdir build
    cd build
    cmake ..
    make -j16
    ```

# Download repository
To clone this repo, run the command :
    ```
    git clone --recurse-submodules https://github.com/DaftMat/OpenGL-exp.git
    ```
    
# Compile and run
  * To compile, run the following commands from the downloaded repo :
    ```
    mkdir build
    cd build
    cmake ..
    make -j16
    ```
  * Finally, here's the command that runs the OpenGL program :
    ```
    ./OpenGLTuto
    ```
    
### Enjoy !
