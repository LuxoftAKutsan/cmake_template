#include "ifoo.h"

class Foo : public IFoo {
public:
   virtual bool doStuff() = 0;
};
