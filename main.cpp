#include <iostream>

using namespace std;

#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>
#include <sqlite3.h>


class medicion{};


class Sensor {
public:
    double _dato;
    int _lim;

    Sensor(int lim = 100) {
        _dato = 0.0;
        _lim = lim;
    }

    double leerDato() {
        return _dato;
    }

    virtual void actualizar() {
        _dato = (rand() % _lim * 10) / 10.0;
    }

    std::string mostrarDato() {
        return std::to_string(_dato);
    }

    void acumularEn(double d) {
        _dato += d;
    }

    double promediarEntre(double n) {
        return _dato / n;
    }
};
#endif // SENSOR_H

class Medicion {
private:
    double _datoTemp;
    double _datoHum;
    double _datoPrecip;
    double _datoIntensidad;

public:
    Medicion(double datoTemp = 0.0, double datoHum = 0.0, double datoPrecip = 0.0, double datoIntensidad = 0.0) {
        _datoTemp = datoTemp;
        _datoHum = datoHum;
        _datoPrecip = datoPrecip;
        _datoIntensidad = datoIntensidad;
    }

    void actualizar(double datoTemp, double datoHum, double datoPrecip, double datoIntensidad) {
        _datoTemp = datoTemp;
        _datoHum = datoHum;
        _datoPrecip = datoPrecip;
        _datoIntensidad = datoIntensidad;
    }

    double obtenerDatoTemp() {
        return _datoTemp;
    }

    double obtenerDatoHum() {
        return _datoHum;
    }

    double obtenerDatoPrecip() {
        return _datoPrecip;
    }

    double obtenerDatoIntensidad() {
        return _datoIntensidad;
    }

    std::string mostrarDatos() {
        std::stringstream ss;
        ss << "Dato de temperatura: " << _datoTemp << std::endl;
        ss << "Dato de humedad: " << _datoHum << std::endl;
        ss << "Dato de precipitación: " << _datoPrecip << std::endl;
        ss << "Dato de intensidad: " << _datoIntensidad << std::endl;

        return ss.str();
    }
};


class Sensor_Temp: public Sensor{

    public:
    int lim_t;
    Sensor_Temp(int lim = 45) : Sensor(lim) {
    }
    void actualizar() override {
        _dato = rand() % 36 + 10;
    }
};

class Sensor_Hum: public Sensor{
    public:
    Sensor_Hum(int tamano = 12, int lim = 100) : Sensor(lim) {
    }
    void actualizar() override {
        _dato = rand() % 101;
    }
};

class Sensor_precip: public Sensor{
    public:
    Sensor_precip( int lim = 50) : Sensor(lim) {
    }
    void actualizar() override {
        _dato = rand() % 51;
    }
};

class Sensor_intensidad: public Sensor{
    public:
    Sensor_intensidad(int lim = 2000) : Sensor(lim) {
    }
    void actualizar() override {
         _dato = rand() % 2001;
    }
};


int main()
{

    srand(static_cast<unsigned int>(time(nullptr)));
    Sensor_Temp sensorTemp;
    Sensor_Hum sensorHum;
    Sensor_precip sensorPrecip;
    Sensor_intensidad sensorIntensidad;
    sensorTemp.actualizar();
    sensorHum.actualizar();
    sensorPrecip.actualizar();
    sensorIntensidad.actualizar();
    Medicion med(sensorTemp.leerDato(), sensorHum.leerDato(), sensorPrecip.leerDato(), sensorIntensidad.leerDato());

    med.actualizar(sensorTemp.leerDato(), sensorHum.leerDato(), sensorPrecip.leerDato(), sensorIntensidad.leerDato());
    cout << med.mostrarDatos();

    sqlite3* db;
    int rc = sqlite3_open("db_medidas_sensores.db", &db);

     if(rc != SQLITE_OK) {
        std::cout<<"Error al abrir la base de datos:"<< sqlite3_errmsg(db) << std::endl;
        return 1;
    }

        // Esto inserta los datos
        const char* insertQuery = "INSERT INTO Min_Prom_Max (Prom_temp, Prom_Humedad, Prom_Precipitacion, Prom_Lumen) VALUES ('sensorTemp.leerDato()', 'sensorHum.leerDato()', 'sensorPrecip.leerDato()', 'sensorIntensidad.leerDato()');";
        rc = sqlite3_exec(db, insertQuery, nullptr, 0, nullptr);

    if (rc != SQLITE_OK) {
        std::cout << "Error al insertar datos: " << sqlite3_errmsg(db) << std::endl;
}
    else {
    std::cout << "Datos insertados correctamente." << std::endl;
}

sqlite3_close(db);

return 0;
}


