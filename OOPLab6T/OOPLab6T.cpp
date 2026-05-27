#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <windows.h>
// Завдання 1 – дві ієрархії (без та з virtual)
class A {
protected: int a;
public:
    A() : a(0) { std::cout << "[A] конструктор\n"; }
    A(int x) : a(x) { std::cout << "[A] конструктор(" << x << ")\n"; }
    ~A() { std::cout << "[A] деструктор\n"; }
};
class B : public A {
protected: int b;
public:
    B() : b(0) { std::cout << "[B] конструктор\n"; }
    B(int x, int y) : A(x), b(y) { std::cout << "[B] конструктор\n"; }
    ~B() { std::cout << "[B] деструктор\n"; }
};
class C : public A {
protected: double c;
public:
    C() : c(0) { std::cout << "[C] конструктор\n"; }
    C(int x, double y) : A(x), c(y) { std::cout << "[C] конструктор\n"; }
    ~C() { std::cout << "[C] деструктор\n"; }
};
class D : public B, public C {
protected: double d;
public:
    D() : d(0) { std::cout << "[D] конструктор\n"; }
    D(int ab, int bb, int ac, double cc, double dd)
        : B(ab, bb), C(ac, cc), d(dd) {
        std::cout << "[D] конструктор\n";
    }
    ~D() { std::cout << "[D] деструктор\n"; }
    void show() {
        std::cout << "B::A::a=" << B::a << " C::A::a=" << C::a
            << " b=" << b << " c=" << c << " d=" << d << "\n";
    }
};

class AV {
protected: int a;
public:
    AV() : a(0) { std::cout << "[AV] конструктор\n"; }
    AV(int x) : a(x) { std::cout << "[AV] конструктор(" << x << ")\n"; }
    ~AV() { std::cout << "[AV] деструктор\n"; }
};
class BV : virtual public AV {
protected: int b;
public:
    BV() : b(0) { std::cout << "[BV] конструктор\n"; }
    BV(int x, int y) : AV(x), b(y) { std::cout << "[BV] конструктор\n"; }
    ~BV() { std::cout << "[BV] деструктор\n"; }
};
class CV : virtual public AV {
protected: double c;
public:
    CV() : c(0) { std::cout << "[CV] конструктор\n"; }
    CV(int x, double y) : AV(x), c(y) { std::cout << "[CV] конструктор\n"; }
    ~CV() { std::cout << "[CV] деструктор\n"; }
};
class DV : public BV, public CV {
protected: double d;
public:
    DV() : d(0) { std::cout << "[DV] конструктор\n"; }
    DV(int av, int bv, int acv, double ccv, double dv)
        : AV(av), BV(av, bv), CV(acv, ccv), d(dv) {
        std::cout << "[DV] конструктор\n";
    }
    ~DV() { std::cout << "[DV] деструктор\n"; }
    void show() {
        std::cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    }
};
// Завдання 2 – абстрактний клас Worker та похідні
class Worker {
protected:
    std::string name;
    int hoursWorked;
public:
    Worker() : name("Невідомо"), hoursWorked(0) {}
    Worker(const std::string& n, int h) : name(n), hoursWorked(h) {
        std::cout << "[Worker] конструктор: " << name << "\n";
    }
    Worker(const Worker& w) : name(w.name), hoursWorked(w.hoursWorked) {
        std::cout << "[Worker] конструктор копії\n";
    }
    virtual ~Worker() { std::cout << "[Worker] деструктор: " << name << "\n"; }
    virtual double salary() const = 0;
    virtual void print() const {
        std::cout << "Ім'я: " << name << ", Годин: " << hoursWorked;
    }
};

class HourlyWorker : public Worker {
    double hourlyRate;
public:
    HourlyWorker() : hourlyRate(0) {}
    HourlyWorker(const std::string& n, int h, double r)
        : Worker(n, h), hourlyRate(r) {
        std::cout << "[HourlyWorker] конструктор\n";
    }
    HourlyWorker(const HourlyWorker& o) : Worker(o), hourlyRate(o.hourlyRate) {}
    ~HourlyWorker() { std::cout << "[HourlyWorker] деструктор\n"; }
    double salary() const override { return hoursWorked * hourlyRate; }
    void print() const override {
        Worker::print();
        std::cout << ", Ставка/год: " << hourlyRate << ", Зарплата: " << salary() << "\n";
    }
};

class SalariedWorker : public Worker {
    double fixedSalary;
public:
    SalariedWorker() : fixedSalary(0) {}
    SalariedWorker(const std::string& n, int h, double s)
        : Worker(n, h), fixedSalary(s) {
        std::cout << "[SalariedWorker] конструктор\n";
    }
    SalariedWorker(const SalariedWorker& o) : Worker(o), fixedSalary(o.fixedSalary) {}
    ~SalariedWorker() { std::cout << "[SalariedWorker] деструктор\n"; }
    double salary() const override { return fixedSalary; }
    void print() const override {
        Worker::print();
        std::cout << ", Оклад: " << fixedSalary << ", Зарплата: " << salary() << "\n";
    }
};

class CommissionWorker : public Worker {
    double baseAmount, commissionRate;
public:
    CommissionWorker() : baseAmount(0), commissionRate(0) {}
    CommissionWorker(const std::string& n, int h, double b, double r)
        : Worker(n, h), baseAmount(b), commissionRate(r) {
        std::cout << "[CommissionWorker] конструктор\n";
    }
    CommissionWorker(const CommissionWorker& o) : Worker(o), baseAmount(o.baseAmount), commissionRate(o.commissionRate) {}
    ~CommissionWorker() { std::cout << "[CommissionWorker] деструктор\n"; }
    double salary() const override { return baseAmount * commissionRate / 100.0; }
    void print() const override {
        Worker::print();
        std::cout << ", База: " << baseAmount << ", Ставка%: " << commissionRate
            << ", Зарплата: " << salary() << "\n";
    }
};
// Завдання 3 – SaltWater -> Sea/Gulf -> Bay (virtual base)

class SaltWater {
protected: double salinity;
public:
    SaltWater() : salinity(3.5) { std::cout << "[SaltWater] конструктор\n"; }
    SaltWater(double s) : salinity(s) { std::cout << "[SaltWater] конструктор\n"; }
    SaltWater(const SaltWater& o) : salinity(o.salinity) { std::cout << "[SaltWater] конструктор копії\n"; }
    virtual ~SaltWater() { std::cout << "[SaltWater] деструктор\n"; }
    virtual void print(std::ostream& out) const { out << "Солоність: " << salinity << "%"; }
    friend std::ostream& operator<<(std::ostream& out, const SaltWater& sw) { sw.print(out); return out; }
    friend std::istream& operator>>(std::istream& in, SaltWater& sw) { in >> sw.salinity; return in; }
};

class Sea : virtual public SaltWater {
protected: std::string name; double areaKm2;
public:
    Sea() : name("Невідоме"), areaKm2(0) { std::cout << "[Sea] конструктор\n"; }
    Sea(const std::string& n, double a, double s) : SaltWater(s), name(n), areaKm2(a) { std::cout << "[Sea] конструктор\n"; }
    Sea(const Sea& s) : SaltWater(s), name(s.name), areaKm2(s.areaKm2) { std::cout << "[Sea] конструктор копії\n"; }
    virtual ~Sea() { std::cout << "[Sea] деструктор\n"; }
    void print(std::ostream& out) const override {
        out << "Море: " << name << ", Площа: " << areaKm2 << " км², "; SaltWater::print(out);
    }
    friend std::ostream& operator<<(std::ostream& out, const Sea& s) { s.print(out); return out; }
    friend std::istream& operator>>(std::istream& in, Sea& s) { in >> s.name >> s.areaKm2 >> s.salinity; return in; }
};

class Gulf : virtual public SaltWater {
protected: std::string gulfName; double depthM;
public:
    Gulf() : gulfName("Невідомий"), depthM(0) { std::cout << "[Gulf] конструктор\n"; }
    Gulf(const std::string& n, double d, double s) : SaltWater(s), gulfName(n), depthM(d) { std::cout << "[Gulf] конструктор\n"; }
    Gulf(const Gulf& g) : SaltWater(g), gulfName(g.gulfName), depthM(g.depthM) { std::cout << "[Gulf] конструктор копії\n"; }
    virtual ~Gulf() { std::cout << "[Gulf] деструктор\n"; }
    void print(std::ostream& out) const override {
        out << "Залив: " << gulfName << ", Глибина: " << depthM << " м, "; SaltWater::print(out);
    }
    friend std::ostream& operator<<(std::ostream& out, const Gulf& g) { g.print(out); return out; }
    friend std::istream& operator>>(std::istream& in, Gulf& g) { in >> g.gulfName >> g.depthM >> g.salinity; return in; }
};

class Bay : public Sea, public Gulf {
    double lengthM;
public:
    Bay() : lengthM(0) { std::cout << "[Bay] конструктор\n"; }
    Bay(const std::string& sn, double area, const std::string& gn, double depth, double sal, double len)
        : SaltWater(sal), Sea(sn, area, sal), Gulf(gn, depth, sal), lengthM(len) {
        std::cout << "[Bay] конструктор\n";
    }
    Bay(const Bay& b) : SaltWater(b), Sea(b), Gulf(b), lengthM(b.lengthM) { std::cout << "[Bay] конструктор копії\n"; }
    virtual ~Bay() { std::cout << "[Bay] деструктор\n"; }
    void print(std::ostream& out) const override {
        out << "Бухта: " << name << "/" << gulfName
            << ", Площа: " << areaKm2 << " км², Глибина: " << depthM
            << " м, Довжина: " << lengthM << " м, "; SaltWater::print(out);
    }
    friend std::ostream& operator<<(std::ostream& out, const Bay& b) { b.print(out); return out; }
    friend std::istream& operator>>(std::istream& in, Bay& b) {
        in >> b.name >> b.areaKm2 >> b.gulfName >> b.depthM >> b.salinity >> b.lengthM; return in;
    }
};

void task1() {
    std::cout << "\n=== Завдання 1: Ієрархії множинного успадкування ===\n";

    std::cout << "\n--- Без virtual (A->B, A->C, B+C->D) ---\n";
    int ab, bb, ac; double cc, dd;
    std::cout << "Введіть поля для об'єкта D:\n";
    std::cout << "  a для B (int): "; std::cin >> ab;
    std::cout << "  b (int): "; std::cin >> bb;
    std::cout << "  a для C (int): "; std::cin >> ac;
    std::cout << "  c (double): "; std::cin >> cc;
    std::cout << "  d (double): "; std::cin >> dd;
    D obj(ab, bb, ac, cc, dd);
    std::cout << "Дані об'єкта D: "; obj.show();
    std::cout << "sizeof(A)=" << sizeof(A) << " sizeof(B)=" << sizeof(B)
        << " sizeof(C)=" << sizeof(C) << " sizeof(D)=" << sizeof(D) << "\n";

    std::cout << "\n--- З virtual (AV->BV, AV->CV, BV+CV->DV) ---\n";
    int av, bv, acv; double ccv, dv;
    std::cout << "Введіть поля для об'єкта DV:\n";
    std::cout << "  a (int): "; std::cin >> av;
    std::cout << "  b (int): "; std::cin >> bv;
    std::cout << "  a для CV (int): "; std::cin >> acv;
    std::cout << "  c (double): "; std::cin >> ccv;
    std::cout << "  d (double): "; std::cin >> dv;
    DV objV(av, bv, acv, ccv, dv);
    std::cout << "Дані об'єкта DV: "; objV.show();
    std::cout << "sizeof(AV)=" << sizeof(AV) << " sizeof(BV)=" << sizeof(BV)
        << " sizeof(CV)=" << sizeof(CV) << " sizeof(DV)=" << sizeof(DV) << "\n";
}

void task2() {
    std::cout << "\n=== Завдання 2: Клас «Працівник» та похідні ===\n";
    std::vector<Worker*> workers;
    int n;
    std::cout << "Скільки працівників ввести? "; std::cin >> n;
    clearInput();

    for (int i = 0; i < n; i++) {
        std::cout << "\nПрацівник " << (i + 1) << ". Тип (1-погодинний, 2-штатний, 3-відсотковий): ";
        int type; std::cin >> type; clearInput();
        std::string name;
        std::cout << "  Ім'я (без пробілів): "; std::cin >> name;
        int hours; std::cout << "  Кількість годин: "; std::cin >> hours;

        if (type == 1) {
            double rate; std::cout << "  Ставка за годину: "; std::cin >> rate;
            workers.push_back(new HourlyWorker(name, hours, rate));
        }
        else if (type == 2) {
            double sal; std::cout << "  Фіксований оклад: "; std::cin >> sal;
            workers.push_back(new SalariedWorker(name, hours, sal));
        }
        else {
            double base, rate;
            std::cout << "  Базова сума виробітку: "; std::cin >> base;
            std::cout << "  Відсоток комісії: "; std::cin >> rate;
            workers.push_back(new CommissionWorker(name, hours, base, rate));
        }
    }

    std::cout << "\n--- Нарахування зарплати ---\n";
    for (auto* w : workers) w->print();

    for (auto* w : workers) delete w;
}

void task3() {
    std::cout << "\n=== Завдання 3: Ієрархія «SaltWater – Sea – Gulf – Bay» ===\n";

    std::cout << "\n-- Об'єкт Sea (море) --\n";
    std::string seaName; double seaArea, seaSal;
    std::cout << "  Назва (без пробілів): "; std::cin >> seaName;
    std::cout << "  Площа (км²): "; std::cin >> seaArea;
    std::cout << "  Солоність (%): "; std::cin >> seaSal;
    Sea sea(seaName, seaArea, seaSal);
    std::cout << sea << "\n";

    std::cout << "\n-- Об'єкт Gulf (залив) --\n";
    std::string gulfName; double gulfDepth, gulfSal;
    std::cout << "  Назва (без пробілів): "; std::cin >> gulfName;
    std::cout << "  Глибина (м): "; std::cin >> gulfDepth;
    std::cout << "  Солоність (%): "; std::cin >> gulfSal;
    Gulf gulf(gulfName, gulfDepth, gulfSal);
    std::cout << gulf << "\n";

    std::cout << "\n-- Об'єкт Bay (бухта = море + залив) --\n";
    std::string bSeaName, bGulfName; double bArea, bDepth, bSal, bLen;
    std::cout << "  Назва моря (без пробілів): "; std::cin >> bSeaName;
    std::cout << "  Площа моря (км²): "; std::cin >> bArea;
    std::cout << "  Назва затоки (без пробілів): "; std::cin >> bGulfName;
    std::cout << "  Глибина (м): "; std::cin >> bDepth;
    std::cout << "  Солоність (%): "; std::cin >> bSal;
    std::cout << "  Довжина бухти (м): "; std::cin >> bLen;
    Bay bay(bSeaName, bArea, bGulfName, bDepth, bSal, bLen);
    std::cout << bay << "\n";

    std::cout << "\n-- Копія бухти (конструктор копіювання) --\n";
    Bay bayCopy(bay);
    std::cout << bayCopy << "\n";

    std::cout << "\nsizeof(SaltWater)=" << sizeof(SaltWater)
        << " sizeof(Sea)=" << sizeof(Sea)
        << " sizeof(Gulf)=" << sizeof(Gulf)
        << " sizeof(Bay)=" << sizeof(Bay) << "\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice = 0;
    do {
        std::cout << "\n========== МЕНЮ ==========\n";
        std::cout << "1. Завдання 1 – ієрархії (virtual / без virtual)\n";
        std::cout << "2. Завдання 2 – клас Працівник\n";
        std::cout << "3. Завдання 3 – SaltWater / Sea / Gulf / Bay\n";
        std::cout << "0. Вихід\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice;
        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 0: std::cout << "До побачення!\n"; break;
        default: std::cout << "Невірний вибір.\n";
        }
    } while (choice != 0);
    return 0;
}
