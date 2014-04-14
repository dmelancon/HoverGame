//
//  particleSystem.cpp
//  Box2d
//
//  Created by Dan on 3/9/14.
//
//

#include "particleSystem.h"
#include "cinder/Rand.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Vbo.h"

particleSystem::particleSystem(){} //dummy constructor

particleSystem::particleSystem( int size, ci::Vec2f mPos, float ang){
    std::vector<ci::Vec3f> positions;
    std::vector<uint32_t> indices;
     x = 0;
    angle = ang;
    mParticles.resize(size);
    static int i = 0;
    for(std::list<Particle>::iterator it = mParticles.begin(); it != mParticles.end(); ++it){

        it->mPosition = ci::Vec3f(mPos.x+ci::randFloat(-7.5f,7.5f), mPos.y+ci::randFloat(-7.5f,7.5f), ci::randFloat(-7.5f,7.5f));
        it->mLife = ci::randFloat(5,40);
        it->mVelocity = ci::Vec3f::zero();
       it->mAcceleration = ci::Vec3f(ci::randFloat(-1,1),ci::randFloat(-1.0,1.0f),ci::randFloat(-1.0,1.0f));;
        indices.push_back(i++);
        positions.push_back(ci::Vec3f(it->mPosition.x,it->mPosition.y ,0));
    }
    ci::gl::VboMesh::Layout layout1;
    layout1.setStaticPositions();
    layout1.setStaticIndices();
    
    myMesh = ci::gl::VboMesh::create( size, size, layout1, GL_POINTS);
    myMesh->bufferPositions(positions);
    myMesh->bufferIndices(indices);
    myMesh->unbindBuffers();

}
particleSystem::~particleSystem(){}
void particleSystem::update(){
    std::vector<ci::Vec3f> positions;


    for(std::list<Particle>::iterator it = mParticles.begin(); it != mParticles.end();){
        if(it->mLife <= 0){
          it =  mParticles.erase(it);
            
        }
        else {
            it->mAcceleration += ci::Vec3f(ci::randFloat(-.5,.5),ci::randFloat(-.5,.5),ci::randFloat(-.5,.5));
            it->mVelocity += it->mAcceleration;
            it->mPosition += it->mVelocity;
            it->mAcceleration *= 0;
            it->mLife--;
            positions.push_back(ci::Vec3f(it->mPosition.x,it->mPosition.y ,0));
            ++it;
            }
    }
    x+=.08;
}
bool particleSystem::isDead(){
    
    if(mParticles.size()==0){
        return true;
    }else{
        return false;
    }
}

void particleSystem::draw(){
       for(std::list<Particle>::iterator it = mParticles.begin(); it != mParticles.end(); ++it){

            ci::gl::pushMatrices();
            ci::gl::translate(it->mPosition);

            ci::gl::color(1.0,0,0);
            glPointSize(5-x);

            ci::gl::draw( myMesh );
           //ci::gl::drawSolidCircle(ci::Vec2f(0.0f,0.0f),5-x);
            ci::gl::rotate(angle);
            ci::gl::popMatrices();
        }
    
}