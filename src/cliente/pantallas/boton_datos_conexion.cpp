#include "boton_datos_conexion.h"

BotonDatosConexion::BotonDatosConexion(Imagen* imagen, bool* corriendo) :
                       Presionable(imagen), corriendo(corriendo){
}

void BotonDatosConexion::presionar(){
    *corriendo = false;
}
