#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>  
#include <conio.h>    

using namespace std;

const double MAX_SPEED_KMH = 200.0;
const double MASS_KG = 1200.0;
const double DT = 0.02; 
class Engine {
public:
double throttle; 
    
Engine() : throttle(0.0) {}
    
void setThrottle(double value) {
throttle = std::clamp(value, 0.0, 1.0);
}
};
class Brake {
public:
double force; // 0–1
        
Brake() : force(0.0) {}
        
void setForce(double value) {
force = std::clamp(value, 0.0, 1.0);
}
};
class FuelTank {
public:
double capacityLiters;
double levelLiters;
            
FuelTank(double cap = 50.0) : capacityLiters(cap), levelLiters(cap) {}
};
            
class Transmission {
public:
int gear;
Transmission() : gear(1) {}
};
class Dashboard {
public:
void updateDisplay(double speed, double throttle, double brake) {
cout << "Speed: " << speed
<< " km/h | Throttle: " << throttle
<< " | Brake: " << brake << "\r";
cout.flush();

};

class Car {
public:
Engine engine;
Brake brake;
FuelTank fuelTank;
Transmission transmission;
Dashboard* dashboard;
                    
double speedKmh;
                    
Car(Dashboard* d) : dashboard(d), speedKmh(0.0) {}
                    
void setThrottle(double value) { engine.setThrottle(value); }
void setBrake(double value) { brake.setForce(value); }
                    
void update(double dt) {
double accel = 50.0 * engine.throttle;   
double decel = 100.0 * brake.force; 
double accel = 50.0 * engine.throttle;  

                    
double deltaSpeed = (accel - decel - drag) * dt;
speedKmh += deltaSpeed;
                    

if (speedKmh < 0.0) speedKmh = 0.0;
if (speedKmh > MAX_SPEED_KMH) speedKmh = MAX_SPEED_KMH;
                    
if (dashboard)
dashboard->updateDisplay(speedKmh, engine.throttle, brake.force);
}
};
class Command {
public:
virtual void execute(Car& car) = 0;
virtual ~Command() = default;
};
                        
class ThrottleUpCommand : public Command {
double delta;
public:
ThrottleUpCommand(double d = 0.1) : delta(d) {}
void execute(Car& car) override {
car.setThrottle(car.engine.throttle + delta);
}
};
                     
class ThrottleDownCommand : public Command {
double delta;
public:
ThrottleDownCommand(double d = 0.1) : delta(d) {}
void execute(Car& car) override {
car.setThrottle(car.engine.throttle - delta);
}
};
                        
class BrakeCommand : public Command {
double force;
public:
BrakeCommand(double f = 1.0) : force(f) {}
void execute(Car& car) override {
car.setBrake(force);
}
};
                        
class BrakeReleaseCommand : public Command {
public:
void execute(Car& car) override {
car.setBrake(0.0);
}
};
int main() {
Dashboard dashboard;
Car car(&dashboard);
                        
ThrottleUpCommand throttleUp;
ThrottleDownCommand throttleDown;
BrakeCommand brake(1.0);
BrakeReleaseCommand brakeRelease;
                        
cout << "Sterowanie: [↑] gaz, [↓] mniej gazu, [SPACJA] hamulec, [ESC] koniec\n";
                        
bool running = true;
                        
while (running) {
if (_kbhit()) {
int key = _getch();
if (key == 27) { 
running = false;
} else if (key == 224) { 
key = _getch();
if (key == 72) throttleUp.execute(car);     
else if (key == 80) throttleDown.execute(car); 
} else if (key == 32) {
 brake.execute(car);
}
} else {
brakeRelease.execute(car); 
}
car.update(DT);
                        
this_thread::sleep_for(chrono::duration<double>(DT));
}
                        
cout << "\nZakonczono symulacje.\n";
return 0;
}
                                                                    
