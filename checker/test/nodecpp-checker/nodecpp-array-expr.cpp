// RUN: nodecpp-checker %s -- -std=c++11 | FileCheck %s -check-prefix=CHECK-MESSAGES -implicit-check-not="{{warning|error}}:"

void f() { 
	int i;

	(&i)[2];
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: (S1)
}
