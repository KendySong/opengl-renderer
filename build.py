import os
import shutil

if __name__ == '__main__' :
    os.system('premake5 gmake')  
    os.system('mingw32-make -j 8 -C build')  
    
    #shaderfiles = os.listdir('shaders')
    #for shader in shaderfiles :      
    #    shutil.copyfile('shaders/' + shader, 'build/bin/Release/' + shader)
    os.system('start build/bin/Release/opengl-renderer.exe')