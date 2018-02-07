#include "Mesh.h"

/**
 * @brief Initialize an empty mesh object
 * 
 */
Mesh::Mesh()
{

}

/**
 * @brief Load a mesh object from file
 * 
 * @param path Relative path to file
 */
Mesh::Mesh(const char* path)
{
    std::vector< GLfloat > temp_vertices;
    std::vector< GLfloat > temp_uvs;

    //I will use objs only, it's fine.
    FILE * file = fopen(path, "r");
    if ( file == NULL )
    {
        printf("Can't open file :/");
    }
    else
    {
        while(true)
        {
            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if(res == EOF)
                break; //End of file.

            //printf("%s\n", lineHeader);
            //parse shit
            if(std::string(lineHeader) == "v") //is this a vertex?
            {
                float x,y,z;
                fscanf(file, "%f %f %f\n", &x, &y, &z);
                temp_vertices.push_back(x);
                temp_vertices.push_back(y);
                temp_vertices.push_back(z);
            }            
            else if(std::string(lineHeader) == "vt") //is this a uv coordinate?
            {
                float x,y;
                fscanf(file, "%f %f\n", &x, &y);
                temp_uvs.push_back(x);
                temp_uvs.push_back(y);
            }
            else if(std::string(lineHeader) == "f")
            {
                unsigned int vertInd[3], uvInd[3];
                fscanf(file, "%d/%d %d/%d %d/%d\n", &vertInd[0], &uvInd[0], &vertInd[1], &uvInd[1], &vertInd[2], &uvInd[2]);

                

                //Let's do the indexing.
                vertices.push_back(temp_vertices[(vertInd[0]-1)*3]);
                vertices.push_back(temp_vertices[(vertInd[0]-1)*3 + 1]);
                vertices.push_back(temp_vertices[(vertInd[0]-1)*3 + 2]);

                vertices.push_back(temp_vertices[(vertInd[1]-1)*3]);
                vertices.push_back(temp_vertices[(vertInd[1]-1)*3 + 1]);
                vertices.push_back(temp_vertices[(vertInd[1]-1)*3 + 2]);

                vertices.push_back(temp_vertices[(vertInd[2]-1)*3]);
                vertices.push_back(temp_vertices[(vertInd[2]-1)*3 + 1]);
                vertices.push_back(temp_vertices[(vertInd[2]-1)*3 + 2]);

                
                texCoords.push_back(temp_uvs[(uvInd[0]-1)*2]);
                texCoords.push_back(temp_uvs[(uvInd[0]-1)*2 + 1]);

                texCoords.push_back(temp_uvs[(uvInd[1]-1)*2]);
                texCoords.push_back(temp_uvs[(uvInd[1]-1)*2 + 1]);
                
                texCoords.push_back(temp_uvs[(uvInd[2]-1)*2]);
                texCoords.push_back(temp_uvs[(uvInd[2]-1)*2 + 1]);
            }
        }
    }
}

void Mesh::render(Texture& texture, Shader& shader, glm::mat4 mvm, Color c)
{
    std::vector<GLfloat> colors;

    for(int i = 0; i < vertices.size()/3; i++)
    {
        colors.push_back(c.r);
        colors.push_back(c.g);
        colors.push_back(c.b);
        colors.push_back(c.a);
    }
    
    GLint dims[4] = {0};
    glGetIntegerv(GL_VIEWPORT, dims);
    int w = dims[2];
    int h = dims[3];
    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)w, (float)h, 0.0f, 1.0f, -1.0f);

    GLuint vbo = -1;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    GLuint tbo = -1;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), &texCoords[0], GL_STATIC_DRAW);

    GLuint cbo = -1;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

    texture.bind(GL_TEXTURE0);

    shader.use();
    glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader.getUniformLocation("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mvm));
    glUniform1i(shader.getUniformLocation("tex"), 0);

    shader.bindArrayBuffer(shader.getAttribLocation("vertexPos"), vbo, GL_FLOAT, 3, 3 * sizeof(GLfloat));
    shader.bindArrayBuffer(shader.getAttribLocation("colorModification"), cbo, GL_FLOAT, 4, 4 * sizeof(GLfloat));
    shader.bindArrayBuffer(shader.getAttribLocation("textureCoords"), tbo, GL_FLOAT, 2, 2 * sizeof(GLfloat));

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);


    GLuint buffers[3] = {vbo, tbo};
    glDeleteBuffers(3, buffers);    
}
