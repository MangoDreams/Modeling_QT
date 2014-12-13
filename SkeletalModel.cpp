#include "SkeletalModel.h"

SkeletalModel::~SkeletalModel(){

    for(int i = 0; i < m_joints.size(); i++){
        delete m_joints[i];
    }
}

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
    loadSkeleton(skeletonFile);

    m_mesh.load(meshFile);
    m_mesh.loadAttachments(attachmentsFile);

    computeBindWorldToJointTransforms();
    updateCurrentJointToWorldTransforms();
}


void SkeletalModel::draw(Matrix4f cameraMatrix, bool skeletonVisible)
{
    // draw() gets called whenever a redraw is required
    // (after an update() occurs, when the camera moves, the window is resized, etc)

    m_matrixStack.clear();
    m_matrixStack.push(cameraMatrix);

    if( skeletonVisible )
    {
        drawJoints();

        drawSkeleton();
    }
    else
    {
        // Clear out any weird matrix we may have been using for drawing the bones and revert to the camera matrix.
        glLoadMatrixf(m_matrixStack.top());

        // Tell the mesh to draw itself.
        m_mesh.draw();
    }
}


void SkeletalModel::loadSkeleton( const char* filename )
{
    // Load the skeleton from file here.

    std::ifstream myFile(filename);
    std::string line;
    Vector3f trans;
    int idx;

    while(std::getline(myFile,line)){
        std::stringstream ss(line);
        ss >> trans[0] >> trans[1] >> trans[2] >> idx;

        Joint* j = new Joint;
        j->transform = Matrix4f::translation(trans);
        if(idx == -1) m_rootJoint = j;
        else m_joints[idx]->children.push_back(j);
        m_joints.push_back(j);

    }

}

void SkeletalModel::traverseJointTree(Joint *j){

    m_matrixStack.push(j->transform);
    glLoadMatrixf(m_matrixStack.top());
    glutSolidSphere(0.025f, 12, 12);

    for(int i = 0; i < j->children.size(); i++){
        traverseJointTree(j->children[i]);
    }

    m_matrixStack.pop();
}


void SkeletalModel::drawJoints( )
{
    traverseJointTree(m_rootJoint);
}


void SkeletalModel::traverseLimbTree(Joint* j){

    Vector3f u,v,w;
    Vector4f c;
    Matrix4f rotate,scale,translate;

    translate =  Matrix4f::translation(0.0f,0.0f,0.5f);

    m_matrixStack.push(j->transform);

    for (int i = 0; i < j->children.size(); i++){

        c = j->children[i]->transform.getCol(3);

        w = c.xyz().normalized();
        v = Vector3f::cross(w,Vector3f(0,0,1)).normalized();
        u = Vector3f::cross(v,w).normalized();

        scale = Matrix4f::scaling(.025,.025,c.xyz().abs());
        rotate = Matrix4f(Vector4f(u,0),Vector4f(v,0),Vector4f(w,0),Vector4f(0,0,0,1));

        glLoadMatrixf(m_matrixStack.top()*rotate*scale*translate);
        glutSolidCube(1.0f);

        traverseLimbTree(j->children[i]);
    }

    m_matrixStack.pop();
}

void SkeletalModel::drawSkeleton()
{
    traverseLimbTree(m_rootJoint);

}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
    // Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
    Matrix3f transform = Matrix3f::rotateX(rX)*Matrix3f::rotateY(rY)*Matrix3f::rotateZ(rZ);
    m_joints[jointIndex]->transform.setSubmatrix3x3(0,0,transform);

}

void SkeletalModel::computeBindWorldTransform(Joint* j){

    m_matrixStack.push(j->transform);
    j->bindWorldToJointTransform = m_matrixStack.top().inverse();

    for(int i = 0; i < j->children.size(); i++){
        computeBindWorldTransform(j->children[i]);
    }

    m_matrixStack.pop();

}

void SkeletalModel::computeBindWorldToJointTransforms()
{
    m_matrixStack.clear();
    computeBindWorldTransform(m_rootJoint);
}

void SkeletalModel::computeCurrentWorldTransform(Joint* j){

    m_matrixStack.push(j->transform);
    j->currentJointToWorldTransform = m_matrixStack.top();

    for(int i = 0; i < j->children.size(); i++){
        computeCurrentWorldTransform(j->children[i]);
    }

    m_matrixStack.pop();

}

void SkeletalModel::updateCurrentJointToWorldTransforms()
{
    m_matrixStack.clear();
    computeCurrentWorldTransform(m_rootJoint);
}

void SkeletalModel::updateMesh(){

    Vector4f oldVertex;

    for(int i = 0; i < m_mesh.bindVertices.size() ; i++){

        oldVertex = Vector4f(m_mesh.bindVertices[i],1);
        Matrix4f temp;

        for(int j = 0; j < m_mesh.attachments[i].size(); j++){
            temp = temp + m_mesh.attachments[i][j]*(m_joints[j+1]->currentJointToWorldTransform)*(m_joints[j+1]->bindWorldToJointTransform);
        }

        m_mesh.currentVertices[i] = (temp*oldVertex).xyz();
    }
}
