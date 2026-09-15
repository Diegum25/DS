#include <stdio.h>
#include <stdlib.h>

typedef struct Base{
    int number;
    void (*function)(struct Base* this); // virtual function override like
}Base;

// base class has to be the first member of struct for downcasting.
typedef struct{
    Base super;
}Child1;

typedef struct{
    Base super;
}Child2;

void function1(Base* this){
    printf("Hi 1\n");
}

void function2(Base* this){
    printf("Hi 2\n");
}

void function3(Base* this){
    printf("Hi 3\n");
}

void printNumber(Base* this){ // regular class method
    printf("My number is %d\n",this->number);
};

void functionCaller(Base* object){
    if (object->function) object->function(object); // virtual function override like
    printNumber(object); // regular class method
}

int main(){
    // cant cast structs but can cast pointers
    Base* class1 = calloc(1, sizeof(Base));
    Child1* class2 = calloc(1, sizeof(Child1));
    Child2* class3 = calloc(1, sizeof(Child2));

    class1->function = &function1; // still has to be assigned
    class1->number = 100;
    class2->super.function = &function2;
    class2->super.number = 200;
    class3->super.function = &function3;
    class3->super.number = 300;


    functionCaller(class1);
    functionCaller((Base*)class2);
    functionCaller((Base*)class3);
    
    free(class1);
    free(class2);
    free(class3);

    return 0;
}