SoftwareRenderer Rasterizer    
===============   


Description      
------------      

This project's purpose is to realise a fully 3D renderer Software.    


# Architecture    
<pre>
├── renderer.sln   
├── app   
│   ├── app.vcxproj   
│   ├── src   
│   │   └── main.cpp   
|   └── assets
|       ├── girl.jpeg
|       ├── rd_shit.jpeg
|       ├── viking_room.jpeg
|       └── viking_room.obj
|       └── triangleWireframe.png
│── renderer   
│   ├── renderer.vcxproj   
│   ├── include*   
│   │   └── rdr   
│   │       └── renderer.h   
│   └── src   
│       ├── renderer.cpp   
│       ├── renderer_impl.hpp   
│       └── andyours...   
└── scene   
    ├── scene.vcxproj   
    ├── include   
    │└── scn   
    │   └── scene.h   
    └── src   
        ├── scene.cpp   
        └── scene_impl.hpp   
 
</pre>
# FeaturesRenderer    

## Implementation of rendering pipeline        

- Transformation Model/View/Projection/viewport   
- Triangle's filling      
- Colors interpolation   
- Textures interpolation + Loading    
- Depth test / 3D object


## Directive    

We started by displaying a wireframe Triangle. 

![wireframe Triangle](./app/assets/triangleWireframe.png)   




Library used 
-------------

- GLFW3   
- IMGUI   
- GLAD   
- KHR   
- STD_IMAGE   
- TINYOBJ   
- ToolBox ( personnal math library that contains matrix and vectors)



Made with
------------
- VisualStudio
- C++

Interesting Link
----------------

- Texture : https://learnopengl.com/Getting-started/Textures     
- Camera understanding : https://www.geertarien.com/blog/2017/07/30/breakdown-of-the-lookAt-function-in-OpenGL/    
- 3D model loader : https://vulkan-tutorial.com/Loading_models   





