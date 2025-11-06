## STATIC_CAST - COMPLETE GUIDE WITH DIAGRAMS

### WHAT IS STATIC_CAST?
`static_cast` is a **compile-time** type conversion operator that performs well-defined, safe conversions between related types. It's called "static" because the conversion is resolved at **compile time**, not runtime.

---

## VISUAL COMPARISON: COMPILE-TIME vs RUNTIME

### STATIC_CAST (Compile-time)
```
Source Code:           Compilation:              Runtime:
                      
int a = 42;           ┌─────────────────┐      ┌─────────────┐
double b =            │ Compiler checks │      │             │
static_cast<double>(a)│ if int→double   │ ───→ │ Just execute│
                      │ is valid ✓      │      │ converted   │
                      └─────────────────┘      │ instruction │
                                              └─────────────┘
                      Fast & Safe!             Zero overhead!
```

### DYNAMIC_CAST (Runtime) - For comparison
```
Source Code:          Compilation:              Runtime:
                     
Animal* ptr = ...;    ┌─────────────────┐      ┌─────────────┐
Dog* dog =            │ Compiler adds   │      │ Check vtable│
dynamic_cast<Dog*>    │ runtime check   │ ───→ │ Read RTTI   │
(ptr);                │ instructions    │      │ Verify cast │
                      └─────────────────┘      └─────────────┘
                      Safe but slower!          Runtime cost!
```

---

## MEMORY LAYOUT DIAGRAMS

### 1. NUMERIC CONVERSIONS
```
WIDENING CONVERSION (Safe - no data loss):
int (4 bytes):     [  42  ][    ][    ][    ]
                      │
                      ▼ static_cast<double>
double (8 bytes):  [ 42.0 ][    ][    ][    ][    ][    ][    ][    ]

NARROWING CONVERSION (Potential data loss):
double (8 bytes):  [3.14159][    ][    ][    ][    ][    ][    ][    ]
                      │
                      ▼ static_cast<int>
int (4 bytes):     [  3  ][    ][    ][    ]  ← Fractional part lost!
```

### 2. POINTER CONVERSIONS (Upcasting)
```
INHERITANCE HIERARCHY:
    ┌─────────────┐
    │    Base     │ ← Base class
    └─────────────┘
          △
          │ inherits
    ┌─────────────┐
    │   Derived   │ ← Derived class
    └─────────────┘

MEMORY LAYOUT:
Derived object:
┌─────────────┐ ← Base part
│  base_data  │
├─────────────┤
│derived_data │ ← Derived part
└─────────────┘

UPCASTING (Always safe):
Derived* dPtr ────→ [Derived object]
      │                   │
      ▼ static_cast<Base*> │
Base* bPtr ─────────────────┘ Points to base part
```

### 3. ENUM CONVERSIONS
```
ENUM DEFINITION:
enum Color { RED=1, GREEN=2, BLUE=4 };

MEMORY REPRESENTATION:
Color::RED    → [    1    ] (4 bytes)
                     │
                     ▼ static_cast<int>
int value     → [    1    ] (4 bytes)

REVERSE CONVERSION:
int num = 2   → [    2    ] (4 bytes)
                     │
                     ▼ static_cast<Color>
Color::GREEN  → [    2    ] (4 bytes)
```

---

## COMPLETE CODE EXAMPLE WITH DIAGRAMS

<function_calls>
<invoke name="create_file">
<parameter name="content">#include <iostream>
#include <iomanip>
#include <limits>

// Base class for inheritance examples
class Vehicle {
protected:
    int wheels;
    std::string brand;
    
public:
    Vehicle(int w, const std::string& b) : wheels(w), brand(b) {}
    virtual ~Vehicle() {}  // Make it polymorphic for comparison
    
    virtual void showInfo() const {
        std::cout << "Vehicle: " << brand << " with " << wheels << " wheels" << std::endl;
    }
    
    int getWheels() const { return wheels; }
    std::string getBrand() const { return brand; }
};

class Car : public Vehicle {
private:
    int doors;
    
public:
    Car(const std::string& b, int d) : Vehicle(4, b), doors(d) {}
    
    void showInfo() const override {
        std::cout << "Car: " << brand << " with " << doors << " doors" << std::endl;
    }
    
    void honk() const {
        std::cout << "Beep beep! " << brand << " is honking!" << std::endl;
    }
    
    int getDoors() const { return doors; }
};

class Motorcycle : public Vehicle {
private:
    int engineCC;
    
public:
    Motorcycle(const std::string& b, int cc) : Vehicle(2, b), engineCC(cc) {}
    
    void showInfo() const override {
        std::cout << "Motorcycle: " << brand << " with " << engineCC << "cc engine" << std::endl;
    }
    
    void rev() const {
        std::cout << "Vroom! " << brand << " revving " << engineCC << "cc engine!" << std::endl;
    }
    
    int getEngineCC() const { return engineCC; }
};

void demonstrateNumericConversions() {
    std::cout << "=== STATIC_CAST: NUMERIC CONVERSIONS ===" << std::endl;
    
    std::cout << "\n1. WIDENING CONVERSIONS (Safe - no data loss):" << std::endl;
    
    // Integer to floating point
    int intValue = 42;
    double doubleValue = static_cast<double>(intValue);
    float floatValue = static_cast<float>(intValue);
    
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Original int:    " << intValue << " (4 bytes)" << std::endl;
    std::cout << "As double:       " << doubleValue << " (8 bytes)" << std::endl;
    std::cout << "As float:        " << floatValue << " (4 bytes)" << std::endl;
    
    // Small integer to larger integer
    char charValue = 65;  // ASCII 'A'
    int intFromChar = static_cast<int>(charValue);
    long longValue = static_cast<long>(intValue);
    
    std::cout << "\nCharacter conversions:" << std::endl;
    std::cout << "char value:      '" << charValue << "' (ASCII " << static_cast<int>(charValue) << ")" << std::endl;
    std::cout << "As int:          " << intFromChar << std::endl;
    std::cout << "int to long:     " << longValue << " (8 bytes)" << std::endl;
    
    std::cout << "\n2. NARROWING CONVERSIONS (Potential data loss):" << std::endl;
    
    // Floating point to integer (loses fractional part)
    double piValue = 3.14159265359;
    int intFromDouble = static_cast<int>(piValue);
    
    std::cout << "Original double: " << std::setprecision(11) << piValue << std::endl;
    std::cout << "As int:          " << intFromDouble << " (fractional part lost)" << std::endl;
    
    // Large integer to smaller integer (potential overflow)
    int largeInt = 300;
    char charFromInt = static_cast<char>(largeInt);
    
    std::cout << "Large int:       " << largeInt << std::endl;
    std::cout << "As char:         " << static_cast<int>(charFromInt) << " (overflow occurred!)" << std::endl;
    
    // Demonstrate the bit-level overflow
    std::cout << "Explanation:     300 in binary exceeds char range (signed: -128 to 127)" << std::endl;
    std::cout << "300 % 256 = " << (300 % 256) << ", then adjusted for signed range" << std::endl;
}

void demonstratePointerConversions() {
    std::cout << "\n=== STATIC_CAST: POINTER CONVERSIONS ===" << std::endl;
    
    std::cout << "\n1. UPCASTING (Derived* → Base*) - Always Safe:" << std::endl;
    
    Car* myCar = new Car("Toyota", 4);
    Motorcycle* myBike = new Motorcycle("Yamaha", 600);
    
    // Safe upcasting - derived to base
    Vehicle* vehicleFromCar = static_cast<Vehicle*>(myCar);
    Vehicle* vehicleFromBike = static_cast<Vehicle*>(myBike);
    
    std::cout << "Original car object:" << std::endl;
    myCar->showInfo();
    myCar->honk();
    
    std::cout << "\nSame object accessed through base pointer:" << std::endl;
    vehicleFromCar->showInfo();  // Still calls Car::showInfo() due to virtual function
    
    std::cout << "\nOriginal motorcycle object:" << std::endl;
    myBike->showInfo();
    myBike->rev();
    
    std::cout << "\nSame object through base pointer:" << std::endl;
    vehicleFromBike->showInfo();  // Still calls Motorcycle::showInfo()
    
    std::cout << "\n2. DOWNCASTING (Base* → Derived*) - DANGEROUS with static_cast:" << std::endl;
    
    Vehicle* vehiclePtr = new Car("Honda", 2);  // Actually points to Car
    
    // This compiles but is dangerous - no runtime checking!
    Car* carPtr = static_cast<Car*>(vehiclePtr);
    std::cout << "Dangerous downcast (happens to work because it's actually a Car):" << std::endl;
    carPtr->showInfo();
    carPtr->honk();
    
    // This is VERY dangerous - vehiclePtr doesn't actually point to Motorcycle!
    Vehicle* anotherVehicle = new Car("Ford", 4);
    Motorcycle* badCast = static_cast<Motorcycle*>(anotherVehicle);
    std::cout << "\nDANGEROUS: Casting Car* to Motorcycle* (UNDEFINED BEHAVIOR!):" << std::endl;
    std::cout << "This might crash or give garbage data..." << std::endl;
    // badCast->rev();  // DON'T DO THIS! Undefined behavior
    
    std::cout << "Address of Car object:        " << anotherVehicle << std::endl;
    std::cout << "Same address as Motorcycle*:  " << badCast << std::endl;
    std::cout << "But the object is NOT a Motorcycle!" << std::endl;
    
    delete myCar;
    delete myBike;
    delete vehiclePtr;
    delete anotherVehicle;
}

void demonstrateVoidPointerConversions() {
    std::cout << "\n=== STATIC_CAST: VOID POINTER CONVERSIONS ===" << std::endl;
    
    int number = 42;
    double decimal = 3.14159;
    Car car("BMW", 4);
    
    // Convert to void* (type erasure)
    void* voidPtr1 = static_cast<void*>(&number);
    void* voidPtr2 = static_cast<void*>(&decimal);
    void* voidPtr3 = static_cast<void*>(&car);
    
    std::cout << "Original values and their void* addresses:" << std::endl;
    std::cout << "int " << number << " at address: " << voidPtr1 << std::endl;
    std::cout << "double " << decimal << " at address: " << voidPtr2 << std::endl;
    std::cout << "Car object at address: " << voidPtr3 << std::endl;
    
    // Convert back from void* (must know the correct type!)
    int* intPtr = static_cast<int*>(voidPtr1);
    double* doublePtr = static_cast<double*>(voidPtr2);
    Car* carPtr = static_cast<Car*>(voidPtr3);
    
    std::cout << "\nValues retrieved through converted pointers:" << std::endl;
    std::cout << "Retrieved int: " << *intPtr << std::endl;
    std::cout << "Retrieved double: " << *doublePtr << std::endl;
    std::cout << "Retrieved car info: ";
    carPtr->showInfo();
    
    std::cout << "\nDANGER: Wrong type conversion from void*:" << std::endl;
    // This compiles but gives garbage!
    double* wrongPtr = static_cast<double*>(voidPtr1);  // int* cast to double*
    std::cout << "int memory interpreted as double: " << *wrongPtr << " (GARBAGE!)" << std::endl;
}

void demonstrateEnumConversions() {
    std::cout << "\n=== STATIC_CAST: ENUM CONVERSIONS ===" << std::endl;
    
    enum Priority { LOW = 1, MEDIUM = 5, HIGH = 10 };
    enum Status { PENDING = 0, ACTIVE = 1, INACTIVE = 2 };
    
    std::cout << "\n1. Enum to Integer:" << std::endl;
    Priority taskPriority = HIGH;
    Status currentStatus = ACTIVE;
    
    int priorityValue = static_cast<int>(taskPriority);
    int statusValue = static_cast<int>(currentStatus);
    
    std::cout << "Priority::HIGH as int: " << priorityValue << std::endl;
    std::cout << "Status::ACTIVE as int: " << statusValue << std::endl;
    
    std::cout << "\n2. Integer to Enum (be careful!):" << std::endl;
    int userInput = 5;
    Priority convertedPriority = static_cast<Priority>(userInput);
    
    std::cout << "Integer " << userInput << " as Priority enum: " << convertedPriority << std::endl;
    
    // Dangerous: converting invalid integer to enum
    int invalidInput = 99;
    Priority dangerousPriority = static_cast<Priority>(invalidInput);
    std::cout << "Invalid integer " << invalidInput << " as Priority: " << dangerousPriority << std::endl;
    std::cout << "This creates an invalid enum value!" << std::endl;
    
    std::cout << "\n3. Enum to Different Enum (usually not meaningful):" << std::endl;
    Status statusFromPriority = static_cast<Status>(taskPriority);
    std::cout << "Priority::HIGH (" << static_cast<int>(taskPriority) << ") as Status: " 
              << statusFromPriority << std::endl;
    std::cout << "This conversion might not make logical sense!" << std::endl;
}

void demonstrateConstConversions() {
    std::cout << "\n=== STATIC_CAST: CONST AND POINTER CONVERSIONS ===" << std::endl;
    
    std::cout << "\n1. Adding const (always safe):" << std::endl;
    int mutableInt = 100;
    const int* constPtr = static_cast<const int*>(&mutableInt);
    
    std::cout << "Original mutable int: " << mutableInt << std::endl;
    std::cout << "Through const pointer: " << *constPtr << std::endl;
    // *constPtr = 200;  // Won't compile - const protection
    
    std::cout << "\n2. Const with inheritance:" << std::endl;
    Car* mutableCar = new Car("Tesla", 4);
    const Vehicle* constVehicle = static_cast<const Vehicle*>(mutableCar);
    
    constVehicle->showInfo();  // OK - const method
    // constVehicle->honk();   // Won't compile if honk() isn't const
    
    std::cout << "\nNote: static_cast CANNOT remove const!" << std::endl;
    std::cout << "Use const_cast for removing const qualifiers." << std::endl;
    
    delete mutableCar;
}

void compareWithOtherCasts() {
    std::cout << "\n=== STATIC_CAST vs OTHER CAST TYPES ===" << std::endl;
    
    double value = 3.14159;
    Car car("Audi", 4);
    Vehicle* basePtr = &car;
    
    std::cout << "\nSame conversions with different cast types:" << std::endl;
    
    // Numeric conversion
    std::cout << "1. Numeric conversion (double to int):" << std::endl;
    int staticResult = static_cast<int>(value);
    int cStyleResult = (int)value;  // C-style cast
    
    std::cout << "static_cast result: " << staticResult << std::endl;
    std::cout << "C-style cast result: " << cStyleResult << std::endl;
    std::cout << "Both give same result, but static_cast is explicit and safer" << std::endl;
    
    // Pointer downcasting
    std::cout << "\n2. Pointer downcasting (Base* to Derived*):" << std::endl;
    Car* staticCast = static_cast<Car*>(basePtr);        // No runtime check
    Car* dynamicCast = dynamic_cast<Car*>(basePtr);      // Runtime check
    
    std::cout << "static_cast result: " << (staticCast ? "Valid pointer" : "nullptr") << std::endl;
    std::cout << "dynamic_cast result: " << (dynamicCast ? "Valid pointer" : "nullptr") << std::endl;
    std::cout << "Both work here because basePtr actually points to Car" << std::endl;
    std::cout << "But dynamic_cast would return nullptr for invalid casts" << std::endl;
    
    // Demonstrate the difference with invalid cast
    Vehicle baseObject(4, "Generic");
    Vehicle* baseOnlyPtr = &baseObject;  // Points to base object, not derived
    
    std::cout << "\n3. Invalid downcast example:" << std::endl;
    Car* staticInvalid = static_cast<Car*>(baseOnlyPtr);     // Dangerous!
    Car* dynamicInvalid = dynamic_cast<Car*>(baseOnlyPtr);   // Safe - returns nullptr
    
    std::cout << "static_cast on base object: " << (staticInvalid ? "Non-null (DANGEROUS!)" : "nullptr") << std::endl;
    std::cout << "dynamic_cast on base object: " << (dynamicInvalid ? "Non-null" : "nullptr (SAFE!)") << std::endl;
}

void demonstrateCompileTimeNature() {
    std::cout << "\n=== STATIC_CAST: COMPILE-TIME NATURE ===" << std::endl;
    
    std::cout << "\nstatic_cast is resolved at COMPILE TIME:" << std::endl;
    std::cout << "1. Compiler checks if conversion is allowed" << std::endl;
    std::cout << "2. If valid, generates appropriate conversion code" << std::endl;
    std::cout << "3. No runtime overhead for the cast itself" << std::endl;
    
    int a = 42;
    double b = static_cast<double>(a);
    
    std::cout << "\nExample: int to double conversion" << std::endl;
    std::cout << "Compiler generates: load int, convert to double, store" << std::endl;
    std::cout << "Runtime: just executes the conversion instruction" << std::endl;
    
    std::cout << "\nThis is different from dynamic_cast which:" << std::endl;
    std::cout << "1. Generates runtime type checking code" << std::endl;
    std::cout << "2. Accesses object's vtable at runtime" << std::endl;
    std::cout << "3. Has performance overhead for safety" << std::endl;
}

int main() {
    std::cout << "=== COMPLETE STATIC_CAST GUIDE WITH EXAMPLES ===" << std::endl;
    
    demonstrateNumericConversions();
    demonstratePointerConversions();
    demonstrateVoidPointerConversions();
    demonstrateEnumConversions();
    demonstrateConstConversions();
    compareWithOtherCasts();
    demonstrateCompileTimeNature();
    
    std::cout << "\n=== STATIC_CAST SUMMARY ===" << std::endl;
    std::cout << "\n✅ USE static_cast FOR:" << std::endl;
    std::cout << "   • Numeric conversions (int ↔ float ↔ double)" << std::endl;
    std::cout << "   • Upcasting (Derived* → Base*)" << std::endl;
    std::cout << "   • void* conversions (when you know the type)" << std::endl;
    std::cout << "   • Enum ↔ integer conversions" << std::endl;
    std::cout << "   • Adding const qualifiers" << std::endl;
    
    std::cout << "\n❌ DON'T use static_cast for:" << std::endl;
    std::cout << "   • Downcasting without certainty (use dynamic_cast)" << std::endl;
    std::cout << "   • Removing const (use const_cast)" << std::endl;
    std::cout << "   • Unrelated pointer types (use reinterpret_cast)" << std::endl;
    std::cout << "   • When you need runtime type checking" << std::endl;
    
    std::cout << "\n🎯 KEY CHARACTERISTICS:" << std::endl;
    std::cout << "   • Compile-time checking and resolution" << std::endl;
    std::cout << "   • Zero runtime overhead" << std::endl;
    std::cout << "   • Explicit and readable" << std::endl;
    std::cout << "   • Safer than C-style casts" << std::endl;
    
    return 0;
}