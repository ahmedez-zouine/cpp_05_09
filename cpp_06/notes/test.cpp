#include <iostream>
#include <typeinfo>
#include <string>
#include <stdexcept>

// Base class for polymorphism examples
class Animal {
public:
    virtual ~Animal() {}
    virtual void makeSound() const = 0;
    virtual std::string getName() const = 0;
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Woof! Woof!" << std::endl;
    }
    std::string getName() const override {
        return "Dog";
    }
    void fetch() const {
        std::cout << "Dog is fetching the ball!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow! Meow!" << std::endl;
    }
    std::string getName() const override {
        return "Cat";
    }
    void climb() const {
        std::cout << "Cat is climbing the tree!" << std::endl;
    }
};

class Bird : public Animal {
public:
    void makeSound() const override {
        std::cout << "Tweet! Tweet!" << std::endl;
    }
    std::string getName() const override {
        return "Bird";
    }
    void fly() const {
        std::cout << "Bird is flying!" << std::endl;
    }
};

// Data structure for serialization example
struct Data {
    int id;
    double value;
    
    Data(int i = 0, double v = 0.0) : id(i), value(v) {}
    
    void print() const {
        std::cout << "Data{id: " << id << ", value: " << value << "}" << std::endl;
    }
};

void demonstrateStaticCast() {
    std::cout << "\n=== STATIC_CAST Examples ===" << std::endl;
    
    // 1. Numeric conversions
    std::cout << "\n1. Numeric Conversions:" << std::endl;
    int intValue = 65;
    char charValue = static_cast<char>(intValue); // ASCII 'A' 1 Byte = 'A'
    double doubleValue = static_cast<double>(intValue); // Number 8 Bytes = 65.0
    float floatValue = static_cast<float>(doubleValue); // 4 Bytes value Number = 65.0f
    
    std::cout << "int: " << intValue << " -> char: '" << charValue << "' (ASCII)" << std::endl;
    std::cout << "int: " << intValue << " -> double: " << doubleValue << std::endl;
    std::cout << "double: " << doubleValue << " -> float: " << floatValue << std::endl;
    
    // 2. Pointer upcasting (safe)
    std::cout << "\n2. Safe Upcasting (Derived* -> Base*):" << std::endl;
    Dog* myDog = new Dog();
    Cat* myCat = new Cat();

    Animal* animalPtr = static_cast<Animal*>(myCat);  // Safe upcasting
    Animal* animalPtrForDog = static_cast<Animal*>(myDog);  // Safe upcasting
    
    std::cout << "Original dog name: " << myDog->getName() << std::endl;
    std::cout << "As animal: " << animalPtr->getName() << std::endl;
    animalPtr->makeSound();
    
    // 3. Enum to int conversion
    std::cout << "\n3. Enum to Integer:" << std::endl;
    enum Color { RED = 1, GREEN = 2, BLUE = 6 };
    enum Colorr { REDD = 1, GREENN = 2, BLUEE = 4 }; // Fix: redeclaration 
    Color myColor = BLUE;
    int colorValue = static_cast<int>(myColor);
    std::cout << "Color BLUE as int: " << colorValue << std::endl;
    
    // 4. Void pointer conversion
    std::cout << "\n4. Void Pointer Conversion:" << std::endl;
    int number = 42;
    void* voidPtr = static_cast<void*>(&number);
    void* voidPTRM = static_cast<void*>(&number);
    int* backintm = static_cast<int*>(voidPTRM);
    int* backToInt = static_cast<int*>(voidPtr);
    (*backToInt)++;
    std::cout << "Original: " << number << ", Through void*: " << *backToInt << std::endl;
    
    delete myDog;
}

void demonstrateDynamicCast() {
    std::cout << "\n=== DYNAMIC_CAST Examples ===" << std::endl;
    
    std::cout << "\n1. Safe Downcasting with Pointers:" << std::endl;
    
    // Create different animals
    Animal* animals[] = {
        new Dog(),
        new Cat(),
        new Bird(),
        new Dog()
    };
    
    for (int i = 0; i < 4; ++i) {
        std::cout << "\nAnimal " << i+1 << " (" << animals[i]->getName() << "):" << std::endl;
        animals[i]->makeSound();
        
        // Try to downcast to Dog
        Dog* dogPtr = dynamic_cast<Dog*>(animals[i]);
        if (dogPtr != nullptr) {
            std::cout << "|---> Successfully cast to Dog!" << std::endl;
            dogPtr->fetch();
        } else {
            std::cout << "|---> Not a Dog, cannot fetch." << std::endl;
        }
        
        // Try to downcast to Cat
        Cat* catPtr = dynamic_cast<Cat*>(animals[i]);
        if (catPtr != nullptr) {
            std::cout << "  -> Successfully cast to Cat!" << std::endl;
            catPtr->climb();
        }
        
        // Try to downcast to Bird
        Bird* birdPtr = dynamic_cast<Bird*>(animals[i]);
        if (birdPtr != nullptr) {
            std::cout << "  -> Successfully cast to Bird!" << std::endl;
            birdPtr->fly();
        }
    }
    
    std::cout << "\n2. Dynamic Cast with References (Exception Handling):" << std::endl;
    try {
        Animal* animal = new Cat();
        
        // This will succeed
        Cat& catRef = dynamic_cast<Cat&>(*animal);
        std::cout << "Successfully cast to Cat reference!" << std::endl;
        catRef.climb();
        
        // This will throw an exception
        Dog& dogRef = dynamic_cast<Dog&>(*animal);
        dogRef.fetch();  // This line won't execute
        
        delete animal;
    } catch (const std::bad_cast& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "Cannot cast Cat to Dog reference!" << std::endl;
    }
    
    // Cleanup
    for (int i = 0; i < 4; ++i) {
        delete animals[i];
    }
}

void demonstrateReinterpretCast() {
    std::cout << "\n=== REINTERPRET_CAST Examples ===" << std::endl;
    
    std::cout << "\n1. Pointer to Integer Conversion (Serialization):" << std::endl;
    Data* originalData = new Data(100, 3.14159);
    originalData->print();
    
    // Convert pointer to integer for storage/transmission
    uintptr_t serializedPtr = reinterpret_cast<uintptr_t>(originalData);
    std::cout << "Pointer as integer: 0x" << std::hex << serializedPtr << std::dec << std::endl;
    
    // Convert back to pointer
    Data* deserializedPtr = reinterpret_cast<Data*>(serializedPtr);
    std::cout << "Deserialized data: ";
    deserializedPtr->print();
    
    std::cout << "Pointers match: " << (originalData == deserializedPtr ? "YES" : "NO") << std::endl;
    
    std::cout << "\n2. Integer to Pointer (Memory Address Access):" << std::endl;
    // WARNING: This is dangerous and platform-specific!
    int value = 42;
    uintptr_t address = reinterpret_cast<uintptr_t>(&value);
    std::cout << "Variable address: 0x" << std::hex << address << std::dec << std::endl;
    
    // Convert address back to pointer
    int* ptrFromAddress = reinterpret_cast<int*>(address);
    std::cout << "Value through reconstructed pointer: " << *ptrFromAddress << std::endl;
    
    std::cout << "\n3. Unrelated Pointer Types (DANGEROUS!):" << std::endl;
    int intArray[] = {0x41424344, 0x45464748};  // ASCII values
    char* charPtr = reinterpret_cast<char*>(intArray);
    
    std::cout << "Int array as chars: ";
    for (size_t i = 0; i < sizeof(intArray); ++i) {
        if (charPtr[i] >= 32 && charPtr[i] <= 126) {  // Printable ASCII
            std::cout << charPtr[i];
        } else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
    
    std::cout << "\n4. Function Pointer Conversion:" << std::endl;
    void (*funcPtr)() = demonstrateStaticCast;
    uintptr_t funcAddress = reinterpret_cast<uintptr_t>(funcPtr);
    std::cout << "Function address: 0x" << std::hex << funcAddress << std::dec << std::endl;
    
    delete originalData;
}

void demonstrateConstCast() {
    std::cout << "\n=== CONST_CAST Examples ===" << std::endl;
    
    std::cout << "\n1. Removing const from Non-const Original (SAFE):" << std::endl;
    int normalValue = 100;
    const int& constRef = normalValue;  // const reference to non-const object
    
    std::cout << "Original value: " << normalValue << std::endl;
    std::cout << "Const reference: " << constRef << std::endl;
    
    // Remove const (safe because original wasn't const)
    int* modifiablePtr = const_cast<int*>(&constRef);
    *modifiablePtr = 200;
    
    std::cout << "After modification through const_cast: " << normalValue << std::endl;
    
    std::cout << "\n2. Working with Legacy C APIs:" << std::endl;
    const char* constString = "Hello, World!";
    
    // Some legacy C functions expect char* but don't modify the string
    char* legacyPtr = const_cast<char*>(constString);
    std::cout << "String through legacy pointer: " << legacyPtr << std::endl;
    // NOTE: Actually modifying this would be undefined behavior!
    
    std::cout << "\n3. Mutable Members in Const Objects:" << std::endl;
    class Counter {
    private:
        mutable int count;  // Can be modified even in const objects
        int data;
        
    public:
        Counter(int d) : count(0), data(d) {}
        
        void increment() const {
            count++;  // OK because count is mutable
        }
        
        int getCount() const { return count; }
        int getData() const { return data; }
        
        void setData(int d) {
            data = d;  // Only works on non-const objects
        }
    };
    
    const Counter constCounter(42);
    constCounter.increment();  // OK - count is mutable
    std::cout << "Const counter count: " << constCounter.getCount() << std::endl;
    
    // Remove const to call non-const method
    Counter& nonConstRef = const_cast<Counter&>(constCounter);
    nonConstRef.setData(99);  // Dangerous! May cause undefined behavior
    std::cout << "Modified data: " << constCounter.getData() << std::endl;
    
    std::cout << "\n4. Volatile Qualifier Removal:" << std::endl;
    volatile int volatileVar = 50;
    int* normalPtr = const_cast<int*>(&volatileVar);  // Remove volatile
    std::cout << "Volatile variable through normal pointer: " << *normalPtr << std::endl;
}

void demonstrateCStyleCast() {
    std::cout << "\n=== C-STYLE CAST Examples (NOT RECOMMENDED) ===" << std::endl;
    
    std::cout << "\n1. C-style vs C++ style comparison:" << std::endl;
    
    double pi = 3.14159;
    
    // C-style cast (ambiguous, potentially dangerous)
    int cStyleInt = (int)pi;
    
    // Equivalent C++ cast (explicit, safe)
    int cppStyleInt = static_cast<int>(pi);
    
    std::cout << "Original double: " << pi << std::endl;
    std::cout << "C-style cast: " << cStyleInt << std::endl;
    std::cout << "C++ static_cast: " << cppStyleInt << std::endl;
    
    std::cout << "\n2. Why C-style casts are dangerous:" << std::endl;
    
    const int constValue = 42;
    // C-style cast can remove const (dangerous!)
    int* dangerousPtr = (int*)&constValue;
    std::cout << "Original const value: " << constValue << std::endl;
    
    // This might work but is undefined behavior:
    // *dangerousPtr = 99;  // DON'T DO THIS!
    
    // C++ way forces you to be explicit about removing const
    // int* saferPtr = const_cast<int*>(&constValue);  // Still dangerous but explicit
    
    std::cout << "\n3. C-style cast hides multiple conversions:" << std::endl;
    
    Dog* dog = new Dog();
    // C-style cast (unclear what type of conversion)
    void* cStyleVoid = (void*)dog;
    
    // C++ way (explicit about the conversion type)
    void* cppStyleVoid = static_cast<void*>(dog);
    
    std::cout << "Both create void pointers, but C++ cast is explicit" << std::endl;
    
    delete dog;
}

void demonstrateCastingEdgeCases() {
    std::cout << "\n=== CASTING EDGE CASES AND PITFALLS ===" << std::endl;
    
    std::cout << "\n1. Overflow in Numeric Conversions:" << std::endl;
    int largeInt = 300;
    char smallChar = static_cast<char>(largeInt);  // Overflow!
    
    std::cout << "Large int: " << largeInt << std::endl;
    std::cout << "As char: " << static_cast<int>(smallChar) << " (overflowed!)" << std::endl;
    
    std::cout << "\n2. Precision Loss in Floating Point:" << std::endl;
    double preciseDouble = 3.14159265359;
    float lessprecise = static_cast<float>(preciseDouble);
    
    std::cout << "Double: " << preciseDouble << std::endl;
    std::cout << "Float:  " << lessprecise << std::endl;
    std::cout << "Precision lost: " << (preciseDouble - lessprecise) << std::endl;
    
    std::cout << "\n3. Special Float Values:" << std::endl;
    double infinity = std::numeric_limits<double>::infinity();
    double notANumber = std::numeric_limits<double>::quiet_NaN();
    
    std::cout << "Infinity: " << infinity << std::endl;
    std::cout << "NaN: " << notANumber << std::endl;
    
    // Casting special values to int is undefined behavior
    std::cout << "Casting special values to int is undefined behavior!" << std::endl;
    
    std::cout << "\n4. Null Pointer Checks with dynamic_cast:" << std::endl;
    Animal* nullAnimal = nullptr;
    Dog* dogFromNull = dynamic_cast<Dog*>(nullAnimal);
    
    std::cout << "dynamic_cast from nullptr: " << (dogFromNull == nullptr ? "nullptr" : "valid pointer") << std::endl;
}

int main()
{
    std::cout << "=== COMPREHENSIVE C++ CASTING TUTORIAL ===" << std::endl;
    
    // Fix the original code issues
    std::cout << "\n=== FIXING YOUR ORIGINAL CODE ===" << std::endl;
    int a = 8;
    char b = static_cast<char>(a);
    
    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Value of b: " << b << " (char value:|" << b << "|)" << std::endl;
    std::cout << "Address of a: " << static_cast<void*>(&a) << std::endl;
    std::cout << "Address of b: " << static_cast<void*>(&b) << std::endl;
    
    b++;
    std::cout << "Value of b after increment: " << b << " (char: '" << b << "')" << std::endl;
    
    a++;  // Fixed: was "&a = a++" which is invalid syntax
    std::cout << "Value of a after increment: " << a << std::endl;
    std::cout << "Size of b: " << sizeof(b) << " byte(s)" << std::endl;
    
    // Demonstrate all casting types
    demonstrateStaticCast();
    demonstrateDynamicCast();
    demonstrateReinterpretCast();
    demonstrateConstCast();
    demonstrateCStyleCast();
    demonstrateCastingEdgeCases();
    
    std::cout << "\n=== CASTING SUMMARY ===" << std::endl;
    std::cout << "1. static_cast    - Safe compile-time conversions" << std::endl;
    std::cout << "2. dynamic_cast   - Runtime-checked polymorphic casting" << std::endl;
    std::cout << "3. reinterpret_cast - Low-level bit reinterpretation" << std::endl;
    std::cout << "4. const_cast     - Add/remove const/volatile qualifiers" << std::endl;
    std::cout << "5. C-style cast   - AVOID! Use specific C++ casts instead" << std::endl;
    
    return 0;
}