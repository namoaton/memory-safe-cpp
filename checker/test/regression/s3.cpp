// RUN: nodecpp-checker %s | FileCheck %s -implicit-check-not="{{warning|error}}:"


int bad1;
// CHECK: :[[@LINE-1]]:5: warning: (S3)

extern int bad2;
// CHECK: :[[@LINE-1]]:12: warning: (S3)

static int bad3;
// CHECK: :[[@LINE-1]]:12: warning: (S3)

thread_local int bad4;
// CHECK: :[[@LINE-1]]:18: warning: (S3)

void func() {
	static int bad;
// CHECK: :[[@LINE-1]]:13: warning: (S3)
}

class Bad {
	static int bad;
// CHECK: :[[@LINE-1]]:13: warning: (S3)
};

constexpr int good = 5;
const int good2 = 5;

class Good {
	static constexpr int good = 5;
	static const int good2 = 5;
	static void func() {}
};

static
void func2() {
	//this is ok
}
