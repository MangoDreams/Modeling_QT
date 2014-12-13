#include "Mesh.h"

void Mesh::load( const char* filename )
{
    std::string line,s;
    std::ifstream myFile(filename);
    Tuple3u face;
    Vector3f v;

    while(std::getline(myFile,line)){
        std::stringstream ss(line);
        ss >> s;

        if(s == "v"){
            ss >> v[0] >> v[1] >> v[2];
            bindVertices.push_back(v);
        }

        else if(s == "f"){

            ss >> face[0] >> face[1] >> face[2];
            faces.push_back(face);
        }

    }

    // make a copy of the bind vertices as the current vertices

    currentVertices = bindVertices;
}

void Mesh::draw()
{
    unsigned int a,b,c;
    Vector3f Va,Vb,Vc;
    Vector3f N;
    for(int i = 0; i < faces.size(); i++){

            a = faces[i][0];
            b = faces[i][1];
            c = faces[i][2];

            Va = currentVertices[a-1];
            Vb = currentVertices[b-1];
            Vc = currentVertices[c-1];

            N = (Vector3f::cross((Vb - Va),(Vc - Vb))).normalized();

            glBegin(GL_TRIANGLES);
                glNormal3f(N[0],N[1],N[2]);
                glVertex3f(Va[0],Va[1],Va[2]);
                glNormal3f(N[0],N[1],N[2]);
                glVertex3f(Vb[0],Vb[1],Vb[2]);
                glNormal3f(N[0],N[1],N[2]);
                glVertex3f(Vc[0],Vc[1],Vc[2]);
            glEnd();
    }
}

void Mesh::loadAttachments( const char* filename)
{
    // 2.2. Implement this method to load the per-vertex attachment weights
    // this method should update m_mesh.attachments

    std::string line;
    std::ifstream myFile(filename);
    float f;

    while(std::getline(myFile,line)){

        std::stringstream ss(line);
        std::vector<float> attachment;

        while(ss.good()){
            ss >> f;
            if(ss.good()) attachment.push_back(f);
        }

        attachments.push_back(attachment);
    }
}
