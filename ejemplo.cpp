//
// Created by seba on 10/05/19.
//

#include "Box2D/Box2D.h"

int ejemplo(){

    // world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    //body definition
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    //shape definition
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.density = 1;

    //a static body
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    b2Body* staticBody = world.CreateBody(&myBodyDef);

    //add four walls to the static body
    polygonShape.SetAsBox( 20, 1, b2Vec2(0, 0), 0);//ground
    staticBody->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox( 20, 1, b2Vec2(0, 40), 0);//ceiling
    staticBody->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox( 1, 20, b2Vec2(-20, 20), 0);//left wall
    staticBody->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox( 1, 20, b2Vec2(20, 20), 0);//right wall
    staticBody->CreateFixture(&myFixtureDef);


    //set up dynamic body
    b2BodyDef circle_body_def;
    circle_body_def.type = b2_dynamicBody;
    circle_body_def.position.Set(0, 2);
    b2Body* circle_body = world.CreateBody(&circle_body_def);

    //add circle fixture
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 2);
    circleShape.m_radius = 0.5f;
    b2FixtureDef circle_fixture_def;
    circle_fixture_def.shape = &circleShape;
    circle_fixture_def.density = 1;
    circle_body->CreateFixture(&circle_fixture_def);

    // set constant velocity
    b2Vec2 vel = circle_body->GetLinearVelocity();
    vel.y = 0;
    vel.x = 5;
    circle_body->SetLinearVelocity(vel);

    // simulation
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    for (int32 i = 0; i < 400;){
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = circle_body->GetPosition();
        float32 angle = circle_body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        i+=7;
    }
    return 0;
}