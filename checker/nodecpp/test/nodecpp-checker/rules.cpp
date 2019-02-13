// RUN: nodecpp-checker %s -- -std=c++11 -isystem %S/Inputs | FileCheck %s -check-prefix=CHECK-MESSAGES -implicit-check-not="{{warning|error}}:"

#include <safe_ptr.h>

using namespace nodecpp::safememory;

class X { public: virtual ~X() {} };

class Der :public X {};

void fp(X* p);
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: (S1.3)

void fop(owning_ptr<X> op);

void func() {

    int i = 5;
    X* p = nullptr;
 // CHECK-MESSAGES: :[[@LINE-1]]:8: warning: (S1.3)
    X* p1 = nullptr;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: (S1.3)
    X* p2 = nullptr;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: (S1.3)
    naked_ptr<X> np;
    soft_ptr<X> sp;
    owning_ptr<X> op;

    //[Rule S1]
    //PROHIBIT
//    (int*)p; on rule S1.1

    p^p2;
// CHECK-MESSAGES: :[[@LINE-1]]:6: error: invalid operands to binary expression
    p+i;
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: (S1)
    p[i];
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: (S1)  
    p1=p2=p+i;
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: (S1)

//   *nullptr; on rule S1.2
//    *p; on rule S1.2
    
    //ALLOW
    dynamic_cast<Der*>(p);
    p=p2;
    p=np.get();
    p=sp.get();
    p=op.get();
    fp(p);
    fp(np.get());
    fp(sp.get());
    fp(op.get());
    &i;
    *np;
    *sp;
    *op;

    //[Rule S1.1]
    //PROHIBIT
    (int*)p;
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S1.1)
    static_cast<Der*>(p);
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S1.1)
    reinterpret_cast<int*>(p);
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S1.1)
//    soft_ptr_static_cast<X*>(p);


    //[Rule S1.2]
    //PROHIBIT
    *nullptr;
// CHECK-MESSAGES: :[[@LINE-1]]:5: error: indirection requires pointer operand
    *p;
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S1.2)


    //[Rule S1.3]
    //PROHIBIT
    int* x = nullptr;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: (S1.3)

    //[Rule S1.4]
    //PROHIBIT
    union Prohibit { naked_ptr<X> x; int y; };
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: unsafe type declaration
// CHECK-MESSAGES: :[[@LINE-2]]:35: note: (S1.4)

    //ALLOW
    union Allow { int x; long y; };
}

void rule_S2() {

    const X* cp = nullptr;
// CHECK-MESSAGES: :[[@LINE-1]]:14: warning: (S1.3)

    //[Rule S2.1]
    //PROHIBIT
    const_cast<X*>(cp);
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S2.1)

    //[Rule S2.2]
    //PROHIBIT
    class Prohibit2 { mutable int x = 0; };
// CHECK-MESSAGES: :[[@LINE-1]]:35: warning: (S2.2)
}

//rule S3

int x;
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S3)
thread_local int x2;
// CHECK-MESSAGES: :[[@LINE-1]]:18: warning: (S3)
static int x3;
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: (S3)


class ProhibitS3 {
    public:
    static int x;
// CHECK-MESSAGES: :[[@LINE-1]]:16: warning: (S3)    
};

void rule_S3() {

    static int x;
// CHECK-MESSAGES: :[[@LINE-1]]:16: warning: (S3)
}


void rule_S4() {
    //PROHIBIT: 
    new X();
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S4)
    new int;
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S4)

    make_owning<X>();
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: (S4.1)
    soft_ptr<X> sp = make_owning<X>();
// CHECK-MESSAGES: :[[@LINE-1]]:22: warning: (S4.1)

    //ALLOW
    auto x1 = make_owning<X>();
    owning_ptr<X> x2 = make_owning<X>();
    fop(make_owning<X>());
}



void rule_S6() {
    //PROHIBIT: 
	asm("mov al, 2");
// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: (S6.1)

	__asm("mov al, 2");
// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: (S6.1)
}

void rule_S7() {
    //PROHIBIT: 

    auto fp = &rule_S7;
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: (S1.3)    
}


void rule_S8() {
    //PROHIBIT: 
	
	int i = 0;
	memset(&i,0,sizeof(i));
// CHECK-MESSAGES: :[[@LINE-1]]:2: warning: (S8)

    //ALLOW
    owning_ptr<X> x2 = make_owning<X>();// ok, safe library
	rule_S8(); // ok, defined in safe code
}
