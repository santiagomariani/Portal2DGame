#include <iostream>
#include "disparo.h"
#include "bloque_roca.h"
#include "contact_listener.h"
#include "sensor.h"

bool dataEsSensor(b2Fixture *fixture) {
    return fixture->GetUserData();
}

bool dataEsCuerpo(b2Fixture *fixture) {
    return fixture->GetBody()->GetUserData();
}

Sensor* obtenerSensor(b2Fixture *fixture) {
    return (Sensor*)(fixture->GetUserData());
}

Cuerpo* obtenerCuerpo(b2Fixture *fixture) {
    return (Cuerpo*)(fixture->GetBody()->GetUserData());
}

void ContactListener::BeginContact(b2Contact* contact){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();

    if (dataEsSensor(fixture_A)) {
        Sensor *sensor_A = obtenerSensor(fixture_A);
        if (!dataEsCuerpo(fixture_B)) return;
        Cuerpo *cuerpo_B = obtenerCuerpo(fixture_B);
        sensor_A->empezarContacto(cuerpo_B);
    } else if (dataEsCuerpo(fixture_A)){
        Cuerpo *cuerpo_A = obtenerCuerpo(fixture_A);
        if (dataEsSensor(fixture_B)) {
            Sensor *sensor_B = obtenerSensor(fixture_B);
            sensor_B->empezarContacto(cuerpo_A);
        } else if (dataEsCuerpo(fixture_B)){
            Cuerpo *cuerpo_B = obtenerCuerpo(fixture_B);
            cuerpo_A->empezarContacto(cuerpo_B);
            cuerpo_B->empezarContacto(cuerpo_A);
        }
    }
}

void ContactListener::EndContact(b2Contact* contact){
	b2Fixture* fixture_A = contact->GetFixtureA();
	b2Fixture* fixture_B = contact->GetFixtureB();

    if (dataEsSensor(fixture_A)) {
        Sensor *sensor_A = obtenerSensor(fixture_A);
        if (!dataEsCuerpo(fixture_B)) return;
        Cuerpo *cuerpo_B = obtenerCuerpo(fixture_B);
        sensor_A->terminarContacto(cuerpo_B);
    } else if (dataEsCuerpo(fixture_A)){
        Cuerpo *cuerpo_A = obtenerCuerpo(fixture_A);
        if (dataEsSensor(fixture_B)) {
            Sensor *sensor_B = obtenerSensor(fixture_B);
            sensor_B->terminarContacto(cuerpo_A);
        } else if (dataEsCuerpo(fixture_B)){
            Cuerpo *cuerpo_B = obtenerCuerpo(fixture_B);
            cuerpo_A->terminarContacto(cuerpo_B);
            cuerpo_B->terminarContacto(cuerpo_A);
        }
    }
}
