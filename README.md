# OpenGL-exp
Experimentation of OpenGL using GLFW, following [this awesome tutorial](https://learnopengl.com/ "learnopengl.com").

# Dependencies
In order to compile and run this little engine, you will need :
  * Run this command to have all the native libraries :
  ```
  sudo apt-get install libglew-dev libsdl2-dev libglm-dev libfreetype6-dev freeglut3-dev build-essential libgl1-mesa-dev libgdiplus
  ```
  * [Assimp](https://github.com/assimp/assimp) Clone their repo into your downloads folder (or any else) and open a terminal :
    ```
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    ```
  * [glfw3](https://github.com/glfw/glfw) same as Assimp :
    ```
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
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
    cd ../bin
    ./OpenGLTuto
    ```
    
### Enjoy !
