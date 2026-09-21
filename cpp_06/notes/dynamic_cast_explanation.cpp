#include <iostream>
#include <typeinfo>

// ================================
// NON-POLYMORPHIC CLASSES (NO virtual functions)
// ================================

class NonPolymorphicBase {
protected:
    int baseData;
public:
    NonPolymorphicBase(int data) : baseData(data) {}
    
    // NO virtual functions = NOT polymorphic
    void print() const {
        std::cout << "NonPolymorphicBase: " << baseData << std::endl;
    }
};

class NonPolymorphicDerived : public NonPolymorphicBase {
private:
    int derivedData;
public:
    NonPolymorphicDerived(int base, int derived) 
        : NonPolymorphicBase(base), derivedData(derived) {}
    
    void print() const {  // Function hiding, NOT overriding
        std::cout << "NonPolymorphicDerived: " << baseData << ", " << derivedData << std::endl;
    }
    
    void specialFunction() const {
        std::cout << "Special function only in derived!" << std::endl;
    }
};

// ================================
// POLYMORPHIC CLASSES (WITH virtual functions)
// ================================

class PolymorphicBase {
protected:
    int baseData;
public:
    PolymorphicBase(int data) : baseData(data) {}
    
    // Virtual destructor makes this polymorphic
    virtual ~PolymorphicBase() {}
    
    // Virtual function enables runtime type identification
    virtual void print() const {
        std::cout << "PolymorphicBase: " << baseData << std::endl;
    }
    
    virtual std::string getType() const {
        return "PolymorphicBase";
    }
};

class PolymorphicDerived : public PolymorphicBase {
private:
    int derivedData;
public:
    PolymorphicDerived(int base, int derived) 
        : PolymorphicBase(base), derivedData(derived) {}
    
    // Virtual function overriding
    virtual void print() const override {
        std::cout << "PolymorphicDerived: " << baseData << ", " << derivedData << std::endl;
    }
    
    virtual std::string getType() const override {
        return "PolymorphicDerived";
    }
    
    void specialFunction() const {
        std::cout << "Special function only in derived!" << std::endl;
    }
};

class AnotherDerived : public PolymorphicBase {
private:
    double extraData;
public:
    AnotherDerived(int base, double extra) 
        : PolymorphicBase(base), extraData(extra) {}
    
    virtual void print() const override {
        std::cout << "AnotherDerived: " << baseData << ", " << extraData << std::endl;
    }
    
    virtual std::string getType() const override {
        return "AnotherDerived";
    }
    
    void anotherSpecialFunction() const {
        std::cout << "Another special function!" << std::endl;
    }
};

void demonstrateWhyPolymorphismIsNeeded() {
    std::cout << "=== WHY DYNAMIC_CAST NEEDS POLYMORPHIC CLASSES ===" << std::endl;
    
    std::cout << "\n1. WHAT IS POLYMORPHISM?" << std::endl;
    std::cout << "Polymorphism = 'many forms' - same interface, different implementations" << std::endl;
    std::cout << "Achieved through virtual functions in C++" << std::endl;
    
    std::cout << "\n2. THE PROBLEM dynamic_cast SOLVES:" << std::endl;
    std::cout << "When you have a base pointer, how do you know what derived type it really points to?" << std::endl;
    
    // Create different objects but store them as base pointers
    PolymorphicBase* objects[] = {
        new PolymorphicDerived(10, 20),
        new AnotherDerived(30, 3.14),
        new PolymorphicBase(40),
        new PolymorphicDerived(50, 60)
    };
    
    std::cout << "\nWe have base pointers, but what do they really point to?" << std::endl;
    
    for (int i = 0; i < 4; ++i) {
        std::cout << "\nObject " << i + 1 << ":" << std::endl;
        
        // We can call virtual functions (polymorphism works)
        std::cout << "  Type reported: " << objects[i]->getType() << std::endl;
        objects[i]->print();
        
        // Try to downcast to PolymorphicDerived
        PolymorphicDerived* derivedPtr = dynamic_cast<PolymorphicDerived*>(objects[i]);
        if (derivedPtr != nullptr) {
            std::cout << "  ✓ Successfully cast to PolymorphicDerived!" << std::endl;
            derivedPtr->specialFunction();
        } else {
            std::cout << "  ✗ Not a PolymorphicDerived" << std::endl;
        }
        
        // Try to downcast to AnotherDerived
        AnotherDerived* anotherPtr = dynamic_cast<AnotherDerived*>(objects[i]);
        if (anotherPtr != nullptr) {
            std::cout << "  ✓ Successfully cast to AnotherDerived!" << std::endl;
            anotherPtr->anotherSpecialFunction();
        }
    }
    
    // Cleanup
    for (int i = 0; i < 4; ++i) {
        delete objects[i];
    }
}

void demonstrateNonPolymorphicLimitations() {
    std::cout << "\n=== NON-POLYMORPHIC CLASSES LIMITATIONS ===" << std::endl;
    
    std::cout << "\nWhy dynamic_cast WON'T work with non-polymorphic classes:" << std::endl;
    
    // This will compile but won't work as expected
    NonPolymorphicBase* basePtr = new NonPolymorphicDerived(100, 200);
    
    std::cout << "Created NonPolymorphicDerived, stored as NonPolymorphicBase*" << std::endl;
    
    // This calls base version, not derived (no virtual functions)
    basePtr->print();  // Calls NonPolymorphicBase::print(), not derived version!
    
    std::cout << "\nTrying dynamic_cast (THIS WON'T COMPILE):" << std::endl;
    std::cout << "// NonPolymorphicDerived* derived = dynamic_cast<NonPolymorphicDerived*>(basePtr);" << std::endl;
    std::cout << "// ERROR: 'NonPolymorphicBase' is not polymorphic" << std::endl;
    
    // This is what you'd have to do instead (DANGEROUS!)
    NonPolymorphicDerived* derived = static_cast<NonPolymorphicDerived*>(basePtr);
    std::cout << "\nUsing static_cast (DANGEROUS - no runtime checking):" << std::endl;
    derived->print();  // This works, but what if basePtr wasn't really a NonPolymorphicDerived?
    
    delete basePtr;
}

void explainRTTI() {
    std::cout << "\n=== RTTI (Run-Time Type Information) EXPLANATION ===" << std::endl;
    
    std::cout << "\nRTTI is what makes dynamic_cast possible:" << std::endl;
    std::cout << "1. Compiler adds type information to polymorphic objects" << std::endl;
    std::cout << "2. This information is stored in the vtable (virtual table)" << std::endl;
    std::cout << "3. dynamic_cast uses this information for safe casting" << std::endl;
    
    PolymorphicBase* poly1 = new PolymorphicDerived(1, 2);
    PolymorphicBase* poly2 = new AnotherDerived(3, 4.5);
    PolymorphicBase* poly3 = new PolymorphicBase(6);
    
    std::cout << "\nUsing typeid() to inspect RTTI:" << std::endl;
    std::cout << "poly1 type: " << typeid(*poly1).name() << std::endl;
    std::cout << "poly2 type: " << typeid(*poly2).name() << std::endl;
    std::cout << "poly3 type: " << typeid(*poly3).name() << std::endl;
    
    std::cout << "\nRTTI enables dynamic_cast to:" << std::endl;
    std::cout << "- Check actual object type at runtime" << std::endl;
    std::cout << "- Safely return nullptr if cast is invalid" << std::endl;
    std::cout << "- Throw exception for invalid reference casts" << std::endl;
    
    delete poly1;
    delete poly2;
    delete poly3;
}

void demonstrateVTableConcept() {
    std::cout << "\n=== VTABLE (Virtual Table) CONCEPT ===" << std::endl;
    
    std::cout << "\nWhat happens with virtual functions:" << std::endl;
    std::cout << "1. Each polymorphic class gets a vtable (table of function pointers)" << std::endl;
    std::cout << "2. Each object has a vptr (pointer to its class's vtable)" << std::endl;
    std::cout << "3. RTTI information is stored alongside the vtable" << std::endl;
    std::cout << "4. dynamic_cast uses vptr to access RTTI" << std::endl;
    
    PolymorphicDerived derived(10, 20);
    PolymorphicBase* basePtr = &derived;
    
    std::cout << "\nMemory layout (conceptual):" << std::endl;
    std::cout << "Object in memory:" << std::endl;
    std::cout << "  [vptr] -> vtable -> RTTI info" << std::endl;
    // std::cout << "  [baseData: " << derived.baseData << "]" << std::endl;
    std::cout << "  [derivedData: (private)]" << std::endl;
    
    std::cout << "\nSize comparison:" << std::endl;
    std::cout << "NonPolymorphicBase size: " << sizeof(NonPolymorphicBase) << " bytes" << std::endl;
    std::cout << "PolymorphicBase size: " << sizeof(PolymorphicBase) << " bytes (includes vptr)" << std::endl;
    
    // The virtual function call mechanism
    std::cout << "\nVirtual function call process:" << std::endl;
    std::cout << "basePtr->print() calls:" << std::endl;
    std::cout << "1. Follow vptr to vtable" << std::endl;
    std::cout << "2. Look up print() in vtable" << std::endl;
    std::cout << "3. Call the actual derived implementation" << std::endl;
    
    basePtr->print();  // Calls PolymorphicDerived::print() through vtable
}

void showDynamicCastInternals() {
    std::cout << "\n=== HOW DYNAMIC_CAST WORKS INTERNALLY ===" << std::endl;
    
    PolymorphicBase* basePtr = new PolymorphicDerived(42, 99);
    
    std::cout << "\nWhen you call: dynamic_cast<PolymorphicDerived*>(basePtr)" << std::endl;
    std::cout << "The runtime system:" << std::endl;
    std::cout << "1. Follows basePtr's vptr to find the vtable" << std::endl;
    std::cout << "2. Reads RTTI information from the vtable" << std::endl;
    std::cout << "3. Checks if actual type IS-A PolymorphicDerived" << std::endl;
    std::cout << "4. If yes: returns the pointer (possibly with offset adjustment)" << std::endl;
    std::cout << "5. If no: returns nullptr" << std::endl;
    
    // Demonstrate successful cast
    PolymorphicDerived* success = dynamic_cast<PolymorphicDerived*>(basePtr);
    std::cout << "\nSuccessful cast result: " << (success ? "Valid pointer" : "nullptr") << std::endl;
    
    // Demonstrate failed cast
    AnotherDerived* failure = dynamic_cast<AnotherDerived*>(basePtr);
    std::cout << "Failed cast result: " << (failure ? "Valid pointer" : "nullptr") << std::endl;
    
    std::cout << "\nThis is why polymorphism is required:" << std::endl;
    std::cout << "- Non-polymorphic objects don't have vtables" << std::endl;
    std::cout << "- No vtable = no RTTI = no runtime type checking" << std::endl;
    std::cout << "- Without RTTI, dynamic_cast cannot work safely" << std::endl;
    
    delete basePtr;
}

void comparisonWithStaticCast() {
    std::cout << "\n=== DYNAMIC_CAST vs STATIC_CAST COMPARISON ===" << std::endl;
    
    PolymorphicBase* basePtr = new PolymorphicBase(100);  // Just base, not derived!
    
    std::cout << "\nBase pointer pointing to actual Base object (not derived)" << std::endl;
    basePtr->print();
    
    std::cout << "\nTrying static_cast (DANGEROUS):" << std::endl;
    PolymorphicDerived* staticResult = static_cast<PolymorphicDerived*>(basePtr);
    std::cout << "static_cast result: " << (staticResult ? "Non-null pointer" : "nullptr") << std::endl;
    std::cout << "But this is WRONG! basePtr doesn't point to a PolymorphicDerived!" << std::endl;
    // staticResult->specialFunction();  // UNDEFINED BEHAVIOR - don't call this!
    
    std::cout << "\nTrying dynamic_cast (SAFE):" << std::endl;
    PolymorphicDerived* dynamicResult = dynamic_cast<PolymorphicDerived*>(basePtr);
    std::cout << "dynamic_cast result: " << (dynamicResult ? "Non-null pointer" : "nullptr") << std::endl;
    std::cout << "dynamic_cast correctly detected the invalid cast!" << std::endl;
    
    if (dynamicResult) {
        dynamicResult->specialFunction();
    } else {
        std::cout << "Safe: dynamic_cast prevented calling derived function on base object" << std::endl;
    }
    
    delete basePtr;
}

int main() {
    demonstrateWhyPolymorphismIsNeeded();
    demonstrateNonPolymorphicLimitations();
    explainRTTI();
    demonstrateVTableConcept();
    showDynamicCastInternals();
    comparisonWithStaticCast();
    
    std::cout << "\n=== SUMMARY: WHY POLYMORPHISM IS REQUIRED ===" << std::endl;
    std::cout << "\n1. TECHNICAL REASON:" << std::endl;
    std::cout << "   - dynamic_cast needs RTTI (Run-Time Type Information)" << std::endl;
    std::cout << "   - RTTI is only available for polymorphic classes" << std::endl;
    std::cout << "   - Polymorphic = has virtual functions" << std::endl;
    
    std::cout << "\n2. IMPLEMENTATION DETAILS:" << std::endl;
    std::cout << "   - Virtual functions create vtables" << std::endl;
    std::cout << "   - RTTI info is stored with vtables" << std::endl;
    std::cout << "   - dynamic_cast accesses RTTI through vtables" << std::endl;
    
    std::cout << "\n3. SAFETY BENEFITS:" << std::endl;
    std::cout << "   - Runtime type checking prevents crashes" << std::endl;
    std::cout << "   - Returns nullptr for invalid casts" << std::endl;
    std::cout << "   - Throws exception for invalid reference casts" << std::endl;
    
    std::cout << "\n4. DESIGN PRINCIPLE:" << std::endl;
    std::cout << "   - If you need dynamic_cast, you probably need polymorphism anyway" << std::endl;
    std::cout << "   - Polymorphic design = virtual destructor + virtual functions" << std::endl;
    std::cout << "   - Good OOP practice for inheritance hierarchies" << std::endl;
    
    return 0;
}