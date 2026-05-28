#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct A { int a; A(int x=0):a(x){} };
struct B : A { int b; B(int x=0,int y=0):A(x),b(y){} };
struct C : A { double c; C(int x=0,double y=0):A(x),c(y){} };
struct D : C { double d; D(int ac=0,double cc=0,double dd=0):C(ac,cc),d(dd){} };
struct E : B { double e; E(int ab=0,int bb=0,double ee=0):B(ab,bb),e(ee){} };
struct F : D, E {
    double f;
    F(int dac,double dc,double dd,int eab,int eb,double ee,double ff)
        :D(dac,dc,dd),E(eab,eb,ee),f(ff){}
    void show(){
        cout << "D::C::A::a=" << D::C::a
             << " E::B::A::a=" << E::B::a
             << " D::d=" << D::d
             << " E::e=" << E::e
             << " f=" << f << "\n";
    }
};

struct AV { int a; AV(int x=0):a(x){} };
struct BV : virtual AV { int b; BV(int x=0,int y=0):AV(x),b(y){} };
struct CV : virtual AV { double c; CV(int x=0,double y=0):AV(x),c(y){} };
struct DV : CV { double d; DV(int ac=0,double cc=0,double dd=0):CV(ac,cc),d(dd){} };
struct EV : BV { double e; EV(int ab=0,int bb=0,double ee=0):BV(ab,bb),e(ee){} };
struct FV : DV, EV {
    double f;
    FV(int av,int dac,double dc,double dd,int eab,int eb,double ee,double ff)
        :AV(av),DV(dac,dc,dd),EV(eab,eb,ee),f(ff){}
    void show(){
        cout << "a=" << a
             << " b=" << b << " c=" << c
             << " DV::d=" << DV::d
             << " EV::e=" << EV::e
             << " f=" << f << "\n";
    }
};

void task1(){
    cout << "\n=== Завдання 1: ієрархія БЕЗ virtual ===\n";
    int dac,eab,eb; double dc,dd,ee,ff;
    cout << "D (a_C c d): "; cin>>dac>>dc>>dd;
    cout << "E (a_B b e): "; cin>>eab>>eb>>ee;
    cout << "f: "; cin>>ff;
    F obj(dac,dc,dd,eab,eb,ee,ff);
    obj.show();
    cout << "sizeof: A="<<sizeof(A)<<" B="<<sizeof(B)<<" C="<<sizeof(C)
         <<" D="<<sizeof(D)<<" E="<<sizeof(E)<<" F="<<sizeof(F)<<"\n";

    cout << "\n=== Завдання 1: ієрархія З virtual ===\n";
    int av,dac2,eab2,eb2; double dc2,dd2,ee2,ff2;
    cout << "a (спільний): "; cin>>av;
    cout << "DV (a_C c d): "; cin>>dac2>>dc2>>dd2;
    cout << "EV (a_B b e): "; cin>>eab2>>eb2>>ee2;
    cout << "f: "; cin>>ff2;
    FV objV(av,dac2,dc2,dd2,eab2,eb2,ee2,ff2);
    objV.show();
    cout << "sizeof: AV="<<sizeof(AV)<<" BV="<<sizeof(BV)<<" CV="<<sizeof(CV)
         <<" DV="<<sizeof(DV)<<" EV="<<sizeof(EV)<<" FV="<<sizeof(FV)<<"\n";
}

struct Worker {
    string name; int h;
    Worker(string n,int h):name(n),h(h){}
    virtual ~Worker(){}
    virtual double salary()=0;
    virtual void print(){ cout<<name<<" ("<<h<<"год): "<<salary()<<" грн\n"; }
};
struct Hourly    : Worker { double r; Hourly(string n,int h,double r):Worker(n,h),r(r){} double salary(){return h*r;} };
struct Salaried  : Worker { double s; Salaried(string n,int h,double s):Worker(n,h),s(s){} double salary(){return s;} };
struct Commission: Worker { double b,r; Commission(string n,int h,double b,double r):Worker(n,h),b(b),r(r){} double salary(){return b*r/100;} };

void task2(){
    cout << "\n=== Завдання 2: Працівники ===\n";
    int n; cout<<"Кількість: "; cin>>n;
    vector<Worker*> ws;
    for(int i=0;i<n;i++){
        int t; string name; int h;
        cout<<"["<<i+1<<"] тип(1-погодинний 2-штатний 3-відсотковий) ім'я години: ";
        cin>>t>>name>>h;
        if(t==1){ double r; cout<<"    ставка/год: "; cin>>r; ws.push_back(new Hourly(name,h,r)); }
        else if(t==2){ double s; cout<<"    оклад: "; cin>>s; ws.push_back(new Salaried(name,h,s)); }
        else{ double b,r; cout<<"    база відсоток: "; cin>>b>>r; ws.push_back(new Commission(name,h,b,r)); }
    }
    cout<<"--- Зарплати ---\n";
    for(auto* w:ws){ w->print(); delete w; }
}


struct SaltWater { double sal; SaltWater(double s=3.5):sal(s){}
    virtual void show(){ cout<<"соль="<<sal<<"%"; } };
struct Sea  : virtual SaltWater { string name; double area;
    Sea(string n,double a,double s):SaltWater(s),name(n),area(a){}
    void show(){ cout<<"Море:"<<name<<" площа="<<area<<"км² "; SaltWater::show(); } };
struct Gulf : virtual SaltWater { string name; double depth;
    Gulf(string n,double d,double s):SaltWater(s),name(n),depth(d){}
    void show(){ cout<<"Залив:"<<name<<" глиб="<<depth<<"м "; SaltWater::show(); } };
struct Bay  : Sea, Gulf {
    double len;
    Bay(string sn,double a,string gn,double d,double s,double l)
        :SaltWater(s),Sea(sn,a,s),Gulf(gn,d,s),len(l){}
    void show(){ cout<<"Бухта:"<<Sea::name<<"/"<<Gulf::name
        <<" площа="<<area<<"км² глиб="<<depth<<"м дов="<<len<<"м "; SaltWater::show(); }
};

void task3(){
    cout << "\n=== Завдання 3: Море / Залив / Бухта ===\n";
    string sn; double sa,ss;
    cout<<"Море (назва площа соль): "; cin>>sn>>sa>>ss;
    Sea sea(sn,sa,ss); sea.show(); cout<<"\n";

    string gn; double gd,gs;
    cout<<"Залив (назва глибина соль): "; cin>>gn>>gd>>gs;
    Gulf gulf(gn,gd,gs); gulf.show(); cout<<"\n";

    string bsn,bgn; double ba,bd,bs,bl;
    cout<<"Бухта (назва_моря площа назва_затоки глибина соль довжина): ";
    cin>>bsn>>ba>>bgn>>bd>>bs>>bl;
    Bay bay(bsn,ba,bgn,bd,bs,bl); bay.show(); cout<<"\n";
    Bay copy(bay); cout<<"Копія: "; copy.show(); cout<<"\n";
    cout<<"sizeof: SaltWater="<<sizeof(SaltWater)<<" Sea="<<sizeof(Sea)
        <<" Gulf="<<sizeof(Gulf)<<" Bay="<<sizeof(Bay)<<"\n";
}
int main(){
    int choice=0;
    do {
        cout<<"\n========== МЕНЮ ==========\n"
            <<"1. Завдання 1 – ієрархії (virtual / без virtual)\n"
            <<"2. Завдання 2 – клас Працівник\n"
            <<"3. Завдання 3 – Sea / Gulf / Bay\n"
            <<"0. Вихід\n"
            <<"Ваш вибір: ";
        cin>>choice;
        switch(choice){
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 0: cout<<"До побачення!\n"; break;
            default: cout<<"Невірний вибір.\n";
        }
    } while(choice!=0);
}
