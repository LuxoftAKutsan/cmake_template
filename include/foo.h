#include "ifoo.h"

class Foo : public IFoo {
public:
   virtual void doStuff() = 0;
};
