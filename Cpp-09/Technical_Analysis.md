# C++ Module 09 - Detailed Technical Analysis

## Project Overview

This module demonstrates advanced STL container usage and algorithmic implementations through three distinct exercises:

1. **BitcoinExchange** - File processing with `std::map`
2. **RPN Calculator** - Stack-based expression evaluation  
3. **PmergeMe** - Advanced sorting with performance comparison

---

## Exercise 00: Bitcoin Exchange

### Architecture Overview

```mermaid
graph TD
    A[CSV File<br/>data.csv] --> B[BitcoinExchange::upload_csv_file]
    C[Input File<br/>user.txt] --> D[BitcoinExchange::procces_input]
    B --> E[std::map<string, double><br/>prices]
    D --> F[Date Validation]
    F --> G[Value Validation]
    G --> H[Price Lookup]
    E --> H
    H --> I[Output Result]
```

### Data Flow Diagram

```mermaid
sequenceDiagram
    participant Main
    participant BitcoinExchange
    participant Map as std::map
    participant File as CSV/Input Files
    
    Main->>BitcoinExchange: Create instance
    Main->>BitcoinExchange: upload_csv_file()
    BitcoinExchange->>File: Read data.csv
    File-->>BitcoinExchange: CSV data
    BitcoinExchange->>Map: Store date-price pairs
    
    Main->>BitcoinExchange: procces_input(filename)
    BitcoinExchange->>File: Read input file
    File-->>BitcoinExchange: Query lines
    
    loop For each query
        BitcoinExchange->>BitcoinExchange: validate_year()
        BitcoinExchange->>BitcoinExchange: validate_month() 
        BitcoinExchange->>BitcoinExchange: validate_day()
        BitcoinExchange->>BitcoinExchange: validate_value()
        BitcoinExchange->>Map: get_money() - lower_bound
        Map-->>BitcoinExchange: Price for date
        BitcoinExchange->>Main: Output result
    end
```

### Key Components Breakdown

#### 1. Data Storage Structure
```cpp
class BitcoinExchange {
private:
    std::map<std::string, double> prices;  // Date -> Price mapping
    
    // Date format: "YYYY-MM-DD"
    // Automatically sorted by std::map
    // O(log n) lookup time
};
```

#### 2. CSV Parsing Algorithm
```mermaid
flowchart TD
    A[Open data.csv] --> B{File opened?}
    B -->|No| C[Error: Can't open file]
    B -->|Yes| D[Skip header line]
    D --> E[Read next line]
    E --> F{More lines?}
    F -->|No| G[Parsing complete]
    F -->|Yes| H[Split by comma]
    H --> I[Extract date]
    H --> J[Extract price]
    I --> K[Store in map]
    J --> K
    K --> E
```

#### 3. Date Validation Logic
```mermaid
flowchart TD
    A[Input Date] --> B[Split by '-']
    B --> C[Validate Year<br/>2009-2025]
    B --> D[Validate Month<br/>1-12]
    B --> E[Validate Day]
    
    C --> F{Year valid?}
    D --> G{Month valid?}
    E --> H{Day valid?}
    
    F -->|No| I[Error]
    G -->|No| I
    H -->|No| I
    
    F -->|Yes| J[Check leap year]
    G -->|Yes| J
    H -->|Yes| J
    
    J --> K[Validate day in month]
    K --> L{All valid?}
    L -->|Yes| M[Date OK]
    L -->|No| I
```

#### 4. Price Lookup Algorithm
```cpp
double get_money(std::string date_part) {
    // Use lower_bound for efficient search
    auto it = prices.lower_bound(date_part);
    
    if (it != prices.end() && it->first == date_part)
        return it->second;  // Exact match found
    
    if (it == prices.begin())
        return -1;  // Date too early
    
    --it;  // Get previous date
    return it->second;  // Return closest earlier price
}
```

### Memory Layout

```mermaid
graph LR
    subgraph "std::map Internal Structure"
        A[Root Node] --> B[Left Subtree<br/>Earlier Dates]
        A --> C[Right Subtree<br/>Later Dates]
        B --> D["2009-01-02<br/>$0.001"]
        B --> E["2009-01-03<br/>$0.002"]
        C --> F["2023-12-01<br/>$42000"]
        C --> G["2023-12-02<br/>$43000"]
    end
```

---

## Exercise 01: RPN Calculator

### Algorithm Flow

```mermaid
flowchart TD
    A[Input: "3 4 + 2 *"] --> B[Split by spaces]
    B --> C[Token Queue: 3, 4, +, 2, *]
    C --> D[Initialize empty stack]
    
    D --> E[Process next token]
    E --> F{Is number?}
    F -->|Yes| G[Push to stack]
    F -->|No| H{Is operator?}
    H -->|Yes| I[Pop 2 operands]
    H -->|No| J[Error: Invalid token]
    
    I --> K[Calculate result]
    K --> L[Push result back]
    
    G --> M{More tokens?}
    L --> M
    M -->|Yes| E
    M -->|No| N{Stack size = 1?}
    N -->|Yes| O[Return result]
    N -->|No| P[Error: Invalid expression]
```

### Stack Operations Visualization

```mermaid
graph TD
    subgraph "Example: 3 4 + 2 *"
        A["Step 1: Push 3<br/>Stack: [3]"]
        B["Step 2: Push 4<br/>Stack: [3,4]"]
        C["Step 3: '+' operator<br/>Pop 4,3 → 3+4=7<br/>Stack: [7]"]
        D["Step 4: Push 2<br/>Stack: [7,2]"]
        E["Step 5: '*' operator<br/>Pop 2,7 → 7*2=14<br/>Stack: [14]"]
        F["Result: 14"]
        
        A --> B --> C --> D --> E --> F
    end
```

### Implementation Details

```cpp
class RPN {
    int calculate(std::string input) {
        std::stack<int> stack;
        std::stringstream ss(input);
        std::string token;
        
        while (getline(ss, token, ' ')) {
            if (isdigit(token[0])) {
                stack.push(token[0] - '0');  // Convert char to int
            } else {
                // Pop two operands (order matters!)
                int b = stack.top(); stack.pop();
                int a = stack.top(); stack.pop();
                
                int result = operate(a, b, token[0]);
                stack.push(result);
            }
        }
        
        return stack.top();
    }
};
```

---

## Exercise 02: Ford-Johnson Algorithm (PmergeMe)

### Algorithm Overview

```mermaid
flowchart TD
    A[Input Array] --> B[Pair Adjacent Elements]
    B --> C[Sort Pairs<br/>larger, smaller]
    C --> D[Collect Larger Elements]
    D --> E[Recursively Sort Larger]
    E --> F[Generate Jacobsthal Sequence]
    F --> G[Insert Smaller Elements<br/>in Jacobsthal Order]
    G --> H[Handle Odd Element]
    H --> I[Sorted Array]
```

### Detailed Algorithm Steps

#### Step 1: Pairing and Comparison
```mermaid
graph LR
    subgraph "Input: [3, 5, 9, 7, 4]"
        A[3, 5] --> B[Compare]
        C[9, 7] --> D[Compare]
        E[4] --> F[Odd element]
    end
    
    subgraph "After Pairing"
        G[Larger: 5, 9]
        H[Smaller: 3, 7]
        I[Odd: 4]
    end
    
    B --> G
    D --> G
    B --> H
    D --> H
    F --> I
```

#### Step 2: Jacobsthal Number Generation
```mermaid
flowchart TD
    A[Jacobsthal Sequence] --> B[J₀ = 0]
    B --> C[J₁ = 1] 
    C --> D[J₂ = 1]
    D --> E[Jₙ = Jₙ₋₁ + 2×Jₙ₋₂]
    
    E --> F[Sequence: 0, 1, 1, 3, 5, 11, 21...]
    
    subgraph "Purpose"
        G[Minimizes binary search<br/>comparisons during insertion]
        H[Optimal insertion order<br/>for worst-case performance]
    end
```

#### Step 3: Insertion Process
```mermaid
sequenceDiagram
    participant Sorted as Sorted Array [5, 9]
    participant Smaller as Smaller Elements [3, 7]
    participant Jacob as Jacobsthal Order
    
    Jacob->>Smaller: Get insertion order
    Smaller->>Sorted: Insert 3 using binary search
    Note over Sorted: [3, 5, 9]
    Smaller->>Sorted: Insert 7 using binary search  
    Note over Sorted: [3, 5, 7, 9]
    Note over Sorted: Insert odd element 4
    Note over Sorted: [3, 4, 5, 7, 9]
```

### Container Performance Comparison

```mermaid
graph TD
    subgraph "std::vector"
        A[Contiguous Memory]
        B[Cache Friendly]
        C[O(1) Random Access]
        D[O(n) Insert/Delete]
    end
    
    subgraph "std::deque"
        E[Segmented Memory]
        F[Less Cache Friendly]
        G[O(1) Random Access]
        H[O(1) Front/Back Insert]
        I[O(n) Middle Insert/Delete]
    end
    
    subgraph "Performance Measurement"
        J[clock() timer]
        K[Microseconds precision]
        L[Multiple test runs]
    end
```

### Memory Layout Comparison

```mermaid
graph TD
    subgraph "std::vector Memory"
        A[Element 0]
        B[Element 1] 
        C[Element 2]
        D[Element 3]
        E[...]
        A --- B --- C --- D --- E
    end
    
    subgraph "std::deque Memory"
        F[Chunk 1<br/>Elements 0-N]
        G[Chunk 2<br/>Elements N+1-2N]
        H[Chunk 3<br/>Elements 2N+1-3N]
        I[Control Block<br/>Pointers to chunks]
        I --> F
        I --> G  
        I --> H
    end
```

---

## Performance Analysis

### Time Complexity Summary

| Operation | BitcoinExchange | RPN Calculator | Ford-Johnson |
|-----------|-----------------|----------------|--------------|
| **Best Case** | O(log n) | O(n) | O(n log n) |
| **Average Case** | O(log n) | O(n) | O(n log n) |
| **Worst Case** | O(log n) | O(n) | O(n log n) |
| **Space** | O(n) | O(n) | O(n) |

### Container Operation Costs

```mermaid
graph LR
    subgraph "std::map"
        A[Insert: O(log n)]
        B[Search: O(log n)]
        C[Delete: O(log n)]
    end
    
    subgraph "std::stack"
        D[Push: O(1)]
        E[Pop: O(1)]
        F[Top: O(1)]
    end
    
    subgraph "std::vector"
        G[Access: O(1)]
        H[Insert end: O(1)]
        I[Insert middle: O(n)]
    end
    
    subgraph "std::deque"
        J[Access: O(1)]
        K[Insert front/back: O(1)]
        L[Insert middle: O(n)]
    end
```

---

## Real-World Applications

### BitcoinExchange Use Cases
- **Financial Trading Systems**: Real-time price lookups
- **Time-Series Databases**: Historical data queries
- **Analytics Platforms**: Market trend analysis

### RPN Calculator Use Cases
- **Scientific Calculators**: HP calculator series
- **Programming Languages**: PostScript, Forth
- **Compiler Design**: Expression parsing backends

### Ford-Johnson Sort Use Cases
- **Embedded Systems**: When comparisons are expensive
- **Database Engines**: Optimized sorting algorithms
- **Academic Research**: Algorithm complexity studies

---

## Code Quality Features

### Error Handling Strategy
```mermaid
flowchart TD
    A[Input Validation] --> B{Valid?}
    B -->|No| C[Error Message]
    B -->|Yes| D[Process Data]
    D --> E{Processing OK?}
    E -->|No| F[Cleanup & Error]
    E -->|Yes| G[Success]
    
    C --> H[Return Error Code]
    F --> H
    G --> I[Return Success]
```

### Memory Management
- **RAII**: All containers manage their own memory
- **Exception Safety**: STL containers provide strong guarantees
- **No Raw Pointers**: Using smart containers eliminates memory leaks

### Design Patterns Used
1. **Strategy Pattern**: Different sorting algorithms for different containers
2. **Template Pattern**: Generic sorting interface
3. **Factory Pattern**: Container creation and initialization
4. **RAII Pattern**: Automatic resource management

This comprehensive analysis shows how your C++ Module 09 project demonstrates advanced programming concepts while solving real-world computational problems.