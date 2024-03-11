////////////////////////////////////////////////////////////////////////////
// Model MODEL2                   SIMLIB/C++
//
// Simple model of queueing system (M/D/1)
//

#include <simlib.h>

int orders = 1672; // 1672/108 =15.48
const double AVG_SPEED = 1.1;
const double BELT_SPEED = 0.8773; // 0.8773 pre belt4 only, 1.3593 pre belt 4 and 3
const bool BELTS_ON_80PLUS1 = false;
const bool BELTS_ON_80PLUS2 = false;
const bool BELTS_ON_80PLUS3 = false;
const bool BELTS_ON_80PLUS4 = true;
// Global objects
Facility Process1("Proces1");
Facility Process2("Proces2");
Facility Process3("Proces3");
Facility Process4("proces4");
Facility Process5("proces5");
Facility Process6("proces6");
Facility Process7("proces7");
Facility Process8("proces8");
Facility Process9("proces9");
Facility Process10("proces10");
Facility Process11("proces11");
Facility Process12("proces12");
Facility Process13("proces13");
Facility Process14("proces14");
Facility Process15("proces15");
Facility Process16("proces16");
Facility Process17("proces17");
Facility Process18("proces18");
Facility Process19("proces19");
Facility Process20("proces20");
Facility Process21("proces21");
Facility Process22("proces22");
Facility Process23("proces23");
Facility Process24("proces24");
Facility Process25("proces25");
Facility Process26("proces26");
Queue UsladnenieQueue("Waiting for getting stored");
Histogram Table("Table of time spent in system", 0, 100, 20);
class Pracovnik2 : public Process { // Customer description
    void Behavior() {
        Seize(Process2, 1);
        Wait(68.8 / AVG_SPEED);
        Release(Process2);
    }
};
class Pracovnik3 : public Process { // Customer description
    void Behavior() {
        Seize(Process3, 1);
        Wait(5 / AVG_SPEED);
        Release(Process3);
    }
};
class Pracovnik4 : public Process { // Customer description
    void Behavior() {
        Seize(Process4, 1);
        Wait(1.5 / AVG_SPEED);
        Release(Process4);
    }
};
class Pracovnik5 : public Process { // Customer description
    void Behavior() {
        Seize(Process5, 1);
        Wait(15 / AVG_SPEED);
        Release(Process5);
    }
};
class Pracovnik6 : public Process { // Customer description
    void Behavior() {
        Seize(Process6, 1);
        double speed = AVG_SPEED;
        if (BELTS_ON_80PLUS1) {
            speed = BELT_SPEED;
        }
        Wait(14 / speed);
        Release(Process6);
    }
};
class Pracovnik7 : public Process { // Customer description
    void Behavior() {
        Seize(Process7, 1);
        double speed = AVG_SPEED;
        if (BELTS_ON_80PLUS2) {
            speed = BELT_SPEED;
        }
        Wait(6 / speed);
        Release(Process7);
    }
};
class Pracovnik8 : public Process { // Customer description
    void Behavior() {
        Seize(Process8, 1);
        double speed = AVG_SPEED;
        if (BELTS_ON_80PLUS3) {
            speed = BELT_SPEED;
        }
        Wait(26.7 / speed);
        Release(Process8);
    }
};
class Pracovnik9 : public Process { // Customer description
    void Behavior() {
        Seize(Process9, 1);
        Wait(18.8 / AVG_SPEED);
        Release(Process9);
    }
};
class Pracovnik10 : public Process { // Customer description
    void Behavior() {
        Seize(Process10, 1);
        Wait(3.4 / AVG_SPEED);
        Release(Process10);
    }
};
class Pracovnik11 : public Process { // Customer description
    void Behavior() {
        Seize(Process11, 1);
        Wait(8.4 / AVG_SPEED);
        Release(Process11);
    }
};
class Pracovnik12 : public Process { // Customer description
    void Behavior() {
        Seize(Process12, 1);
        Wait(2.5 / AVG_SPEED);
        Release(Process12);
    }
};
class Pracovnik14 : public Process { // Customer description
    void Behavior() {
        Seize(Process14, 1);
        Wait(21 / AVG_SPEED);
        Release(Process14);
    }
};
class Pracovnik15 : public Process { // Customer description
    void Behavior() {
        Seize(Process15, 1);
        Wait(9.6 / AVG_SPEED);
        Release(Process15);
    }
};
class Pracovnik19 : public Process { // Customer description
    void Behavior() {
        Seize(Process19, 1);
        Wait(9.2 / AVG_SPEED);
        Release(Process19);
    }
};
class Pracovnik20 : public Process { // Customer description
    void Behavior() {
        Seize(Process20, 1);
        double speed = AVG_SPEED;
        if (BELTS_ON_80PLUS4) {
            speed = BELT_SPEED;
        }
        Wait(43.5 / speed);
        Release(Process20);
    }
};
class Pracovnik21 : public Process { // Customer description
    void Behavior() {
        Seize(Process21, 1);
        Wait(25 / AVG_SPEED);
        Release(Process21);
    }
};
class Pracovnik22 : public Process { // Customer description
    void Behavior() {
        Seize(Process22, 1);
        Wait(3.6 / AVG_SPEED);
        Release(Process22);
    }
};
class Pracovnik25 : public Process { // Customer description
    void Behavior() {
        Seize(Process25, 1);
        Wait(13.6 / AVG_SPEED);
        Release(Process25);
    }
};
class Pracovnik26 : public Process { // Customer description
    void Behavior() {
        Seize(Process26, 1);
        Wait(5 / AVG_SPEED);
        Release(Process26);
    }
};
class Product : public Process { // Customer description
    double ArrivalTime;          // Attribute for each customer
    void Behavior() {            // - Customer behavior description
        ArrivalTime = Time;      // Mark arrival time
        // prvy riadok v grafe
        Seize(Process1);   // Try to enter Box or queue
        Wait(300);         // In service
        Release(Process1); // Leave Box

        Seize(Process2);
        Wait(68.8 / AVG_SPEED);
        Release(Process2);
        (new Pracovnik2)->Activate();

        Seize(Process3);
        Wait(21.4);
        Wait(5 / AVG_SPEED);
        Release(Process3);
        (new Pracovnik3)->Activate();

        // druhy riadok v grafe
        Seize(Process4);
        Wait(15.8);
        Wait(1.5 / AVG_SPEED);
        Release(Process4);
        (new Pracovnik4)->Activate();

        Seize(Process5);
        Wait(11.3);
        Wait(15 / AVG_SPEED);
        Release(Process5);
        (new Pracovnik5)->Activate();

        Seize(Process6);
        Wait(517.1);
        if (!BELTS_ON_80PLUS1) {
            Wait(14 / AVG_SPEED);
        }
        Release(Process6);
        (new Pracovnik6)->Activate();

        // treti riadok v grafe
        Seize(Process7);
        Wait(414.5);
        if (!BELTS_ON_80PLUS2) {
            Wait(6 / AVG_SPEED);
        }
        Release(Process7);
        (new Pracovnik7)->Activate();

        Seize(Process8);
        if (!BELTS_ON_80PLUS3) {
            Wait(24.2 / AVG_SPEED);
        }
        Wait(624.2);
        if (!BELTS_ON_80PLUS3) {
            Wait(2.5 / AVG_SPEED);
        }
        Release(Process8);
        (new Pracovnik8)->Activate();

        Seize(Process9);
        Wait(12 / AVG_SPEED);
        Wait(41.5);
        Wait(6.8 / AVG_SPEED);
        Release(Process9);
        (new Pracovnik9)->Activate();

        // Stvrty riadok v grafe
        Seize(Process10);
        Wait(329.7);
        Wait(3.4 / AVG_SPEED);
        Release(Process10);
        (new Pracovnik10)->Activate();

        Seize(Process11);
        Wait(90.4);
        Wait(8.4 / AVG_SPEED);
        Release(Process11);
        (new Pracovnik11)->Activate();

        Seize(Process12);
        Wait(326);
        Wait(2.5 / AVG_SPEED);
        Release(Process12);
        (new Pracovnik12)->Activate();

        // Piaty riadok v grafe
        Seize(Process13);
        Wait(96.5);
        Release(Process13);

        Seize(Process14);
        Wait(203);
        Wait(21 / AVG_SPEED);
        Release(Process14);
        (new Pracovnik14)->Activate();

        Seize(Process15);
        Wait(9.6 / AVG_SPEED);
        Wait(25.6);
        Release(Process15);
        (new Pracovnik15)->Activate();

        Seize(Process16);
        Wait(29.7);
        Release(Process16);

        Seize(Process17);
        Wait(36);
        Release(Process17);

        // Siesty riadok v grafe
        Seize(Process18);
        Wait(41.4);
        Release(Process18);

        Seize(Process19);
        Wait(66.5);
        Wait(9.2 / AVG_SPEED);
        Release(Process19);
        (new Pracovnik19)->Activate();

        Seize(Process20);
        Wait(625.2);
        if (!BELTS_ON_80PLUS4) {
            Wait(43.5 / AVG_SPEED);
        }
        Release(Process20);
        (new Pracovnik20)->Activate();

        Seize(Process21);
        Wait(315.4);
        Wait(25 / AVG_SPEED);
        Release(Process21);
        (new Pracovnik21)->Activate();

        // Siedmy riadok v grafe
        Seize(Process22);
        Wait(3.6 / AVG_SPEED);
        Release(Process22);
        (new Pracovnik22)->Activate();

        Seize(Process23);
        Wait(50);
        Release(Process23);

        Seize(Process24);
        Wait(24);
        Release(Process24);

        Seize(Process25);
        Wait(68.8);
        Wait(13.6 / AVG_SPEED);
        Release(Process25);
        (new Pracovnik25)->Activate();

        Seize(Process26);
        Wait(5 / AVG_SPEED);
        Release(Process26);
        (new Pracovnik26)->Activate();

        Table(Time - ArrivalTime); // Record time spent in system
    }
};

class Generator : public Event {   // Generator of customers
    void Behavior() {              // - Generator behavior description
        (new Product)->Activate(); // Create new customer, activate at Time
        if (orders > 0) {
            Activate(Time); // Arrival time interval
            orders--;
        }
    }
};

int main() { // Experiment description
    // DebugON();
    SetOutput("main.out"); // Write results to file
    Print(" MODEL \n");
    Init(0, 8 * 60 * 60);        // Init simulator for time 8h->sec
    (new Generator)->Activate(); // Create generator, activate at 0
    Run();                       // - Simulation run
    Process1.Output();           // Print results
    Process2.Output();           // Print results
    Process3.Output();           // Print results
    Process4.Output();           // Print results
    Process5.Output();           // Print results
    Process6.Output();           // Print results
    Process7.Output();           // Print results
    Process8.Output();           // Print results
    Process9.Output();           // Print results
    Process10.Output();          // Print results
    Process11.Output();          // Print results
    Process12.Output();          // Print results
    Process13.Output();          // Print results
    Process14.Output();          // Print results
    Process15.Output();          // Print results
    Process16.Output();          // Print results
    Process17.Output();          // Print results
    Process18.Output();          // Print results
    Process19.Output();          // Print results
    Process20.Output();          // Print results
    Process21.Output();          // Print results
    Process22.Output();          // Print results
    Process23.Output();          // Print results
    Process24.Output();          // Print results
    Process25.Output();          // Print results
    Process26.Output();          // Print results
    Table.Output();
    SIMLIB_statistics.Output(); // Print simulator internal statistics
    return 0;
}
