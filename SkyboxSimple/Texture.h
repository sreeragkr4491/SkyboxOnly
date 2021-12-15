#pragma once

// GL Includes
//#define GLEW_STATIC
#include <GL/glew.h>
#include <map>
#include <vector>
//#include <vector>
//******* vvvviiiiii must add it using name space
using namespace std;
class TextureLoading
{
public:
	// for checking the texture loading 
    static GLuint LoadTexture( GLchar *path )
    {
        //Generate texture ID and load texture data
        GLuint textureID;
        glGenTextures( 1, &textureID );
        
        int imageWidth, imageHeight;
        
        unsigned char *image = SOIL_load_image( path, &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
        
		        
        return textureID;
    }
	// for manage the faces of the cube for skybox.
    static GLuint LoadCubemap( vector<const GLchar * > faces)
    {
        GLuint textureID;
        glGenTextures( 1, &textureID );
        
        int imageWidth, imageHeight;
        unsigned char *image;
        
        glBindTexture( GL_TEXTURE_CUBE_MAP, textureID );
        
        for ( GLuint i = 0; i < faces.size( ); i++ )
        {
            image = SOIL_load_image( faces[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
            glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
            SOIL_free_image_data( image );
        }
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        glBindTexture( GL_TEXTURE_CUBE_MAP, 0);
        
        return textureID;
    }
};
