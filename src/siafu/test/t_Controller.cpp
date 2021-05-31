#include <siafu/Controller.h>
#include <assert.h>

void test1(){
    Controller* controller = new Controller("","1");
    Progress* progress = controller->getProgress();
    assert(progress != NULL);
    std::cout << "Test 1 passed\n";
}

int main(){
    test1();
}